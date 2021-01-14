#include "centurion.hpp"
#include "event.hpp"
#include "font_cache.hpp"
#include "renderer.hpp"
#include "window.hpp"

namespace {

class interactive_font_cache final
{
 public:
  interactive_font_cache()
      : m_window{}
      , m_renderer{m_window}
      , m_cache{"resources/daniel.ttf", 24}
  {
    m_renderer.set_color(cen::colors::white);
    m_cache.add_latin1(m_renderer);

    init();
  }

  void run()
  {
    m_window.show();

    bool running = true;
    while (running) {
      running = handle_input();
      render();
    }

    m_window.hide();
  }

 private:
  inline static constexpr auto m_fst = 72;
  inline static constexpr auto m_snd = 23;

  cen::window m_window;
  cen::renderer m_renderer;
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

  void init()
  {
    m_renderer.set_color(cen::colors::magenta);
    m_cache.store_blended_latin1(m_fst, "cool string! <|>", m_renderer);

    const cen::unicode_string cool = {0x2192, 0x2665, 0x2190, 0x263A};
    m_cache.store_blended_unicode(m_snd, cool, m_renderer);
  }

  [[nodiscard]] auto handle_input() -> bool
  {
    cen::event event;

    while (event.poll()) {
      if (event.is<cen::quit_event>()) {
        return false;
      }

      if (const auto* key = event.try_get<cen::keyboard_event>()) {
        if (key->released() && key->is_active(SDL_SCANCODE_ESCAPE)) {
          return false;
        } else {
          if (key->is_active(cen::scancodes::backspace)) {
            if (!m_text.empty()) {
              m_text.pop_back();
            }
          }
        }

      } else if (const auto* text = event.try_get<cen::text_input_event>()) {
        m_text += text->text_utf8();
      }
    }

    return true;
  }

  void render()
  {
    m_renderer.clear_with(cen::colors::black);

    using namespace std::string_view_literals;

    m_renderer.render_text(m_cache, "abcdefghijklmnopqrstuvwxyz"sv, {50, 10});
    m_renderer.render_text(m_cache, m_text, {50, 150});
    m_renderer.render_text(m_cache, m_unicodeString, {50, 100});

    m_renderer.render(m_cache.get_stored(m_fst), cen::ipoint{50, 200});
    m_renderer.render(m_cache.get_stored(m_snd), cen::ipoint{300, 400});

    m_renderer.present();
  }
};

}  // namespace

int main(int, char**)
{
  const cen::library library;

  interactive_font_cache ifc;
  ifc.run();

  return 0;
}
