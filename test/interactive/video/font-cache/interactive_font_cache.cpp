#include <centurion.hpp>
#include <string>       // string
#include <string_view>  // sv

using namespace std::string_view_literals;

namespace {

inline constexpr auto first_id = 72;
inline constexpr auto second_id = 23;
inline constexpr auto alphabet = "abcdefghijklmnopqrstuvwxyzåäö"sv;

using event_dispatcher =
    cen::event_dispatcher<cen::quit_event, cen::keyboard_event, cen::text_input_event>;

class interactive_font_cache final
{
 public:
  interactive_font_cache()
      : m_window{}
      , m_renderer{m_window}
      , m_cache{"resources/fira_code.ttf", 24}
  {
    m_renderer.set_color(cen::colors::white);
    m_cache.add_latin1(m_renderer);

    m_renderer.set_color(cen::colors::magenta);
    m_cache.store_blended_latin1(first_id, "cool string! <|>", m_renderer);

    const cen::unicode_string cool = {0x2192, 0x2665, 0x2190, 0x263A};
    m_cache.store_blended_unicode(second_id, cool, m_renderer);

    m_dispatcher.bind<cen::quit_event>().to<&interactive_font_cache::on_quit_event>(this);

    m_dispatcher.bind<cen::keyboard_event>()
        .to<&interactive_font_cache::on_keyboard_event>(this);

    m_dispatcher.bind<cen::text_input_event>()
        .to<&interactive_font_cache::on_text_input_event>(this);

    m_text.reserve(100u);
  }

  auto run() -> int
  {
    m_window.show();

    while (m_running)
    {
      m_dispatcher.poll();
      render();
    }

    m_window.hide();

    return 0;
  }

 private:
  cen::window m_window;
  cen::renderer m_renderer;
  event_dispatcher m_dispatcher;
  cen::font_cache m_cache;
  std::string m_text;
  cen::unicode_string m_unicodeString{'c',
                                      'o',
                                      'o',
                                      'l',
                                      ' ',
                                      's',
                                      't',
                                      'r',
                                      'i',
                                      'n',
                                      'g',
                                      '!',
                                      ' ',
                                      '<',
                                      '|',
                                      '>'};
  bool m_running{true};

  void on_quit_event(const cen::quit_event&)
  {
    m_running = false;
  }

  void on_keyboard_event(const cen::keyboard_event& event)
  {
    if (event.released() && event.is_active(cen::scancodes::escape))
    {
      m_running = false;
    }
    else if (event.pressed() && event.is_active(cen::scancodes::backspace))
    {
      if (!m_text.empty())
      {
        m_text.pop_back();
      }
    }
  }

  void on_text_input_event(const cen::text_input_event& event)
  {
    const std::string str{event.text_utf8()};
    for (const auto ch : str)
    {
      if (m_cache.has(ch))
      {
        m_text += ch;
      }
    }
  }

  void render()
  {
    m_renderer.clear_with(cen::colors::black);

    m_renderer.render_text(m_cache, alphabet, {50, 10});
    m_renderer.render_text(m_cache, m_text, {50, 150});
    m_renderer.render_text(m_cache, m_unicodeString, {50, 100});

    m_renderer.render(m_cache.get_stored(first_id), cen::point(50, 200));
    m_renderer.render(m_cache.get_stored(second_id), cen::point(300, 400));

    m_renderer.present();
  }
};

}  // namespace

auto main(int, char**) -> int
{
  const cen::library centurion;
  interactive_font_cache demo;
  return demo.run();
}
