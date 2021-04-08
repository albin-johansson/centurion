#include <cstddef>  // size_t
#include <utility>  // move

#include "centurion.hpp"

namespace {

inline constexpr std::size_t font_id = 7;
inline constexpr cen::iarea window_size = cen::window::default_size();

inline constexpr auto msg_zero = "\"0\" to play the click one time.";
inline constexpr auto msg_one = "\"1\" to play the click one time.";
inline constexpr auto msg_two = "\"2\" to play the click two times.";
inline constexpr auto msg_nine = "\"9\" to play the click forever.";
inline constexpr auto msg_f = "\"F\" to fade in the music over 5 seconds.";
inline constexpr auto msg_escape = "\"ESC\" to halt the music.";

inline constexpr auto msg_playing_music = "Music is playing!";
inline constexpr auto msg_fading_music = "Music is fading!";
inline constexpr auto msg_no_music = "No music is playing";

struct messages final
{
  cen::texture infoZero;
  cen::texture infoOne;
  cen::texture infoTwo;
  cen::texture infoNine;
  cen::texture infoFadeIn;
  cen::texture infoEsc;
  cen::texture playingMusic;
  cen::texture fadingMusic;
  cen::texture noMusic;

  [[nodiscard]] static auto make(cen::renderer& renderer) -> messages
  {
    auto& font = renderer.get_font(font_id);

    renderer.set_color(cen::colors::green);
    auto playing = renderer.render_blended_latin1(msg_playing_music, font);

    renderer.set_color(cen::colors::magenta);
    auto fading = renderer.render_blended_latin1(msg_fading_music, font);

    renderer.set_color(cen::colors::red);
    auto paused = renderer.render_blended_latin1(msg_no_music, font);

    renderer.set_color(cen::colors::white);
    return messages{renderer.render_blended_latin1(msg_zero, font),
                    renderer.render_blended_latin1(msg_one, font),
                    renderer.render_blended_latin1(msg_two, font),
                    renderer.render_blended_latin1(msg_nine, font),
                    renderer.render_blended_latin1(msg_f, font),
                    renderer.render_blended_latin1(msg_escape, font),
                    std::move(playing),
                    std::move(fading),
                    std::move(paused)};
  }
};

using event_dispatcher =
    cen::event_dispatcher<cen::quit_event, cen::keyboard_event>;

class interactive_music final
{
 public:
  interactive_music()
      : m_window{}
      , m_renderer{m_window}
      , m_song{"resources/hiddenPond.mp3"}
      , m_click{"resources/click.wav"}
  {
    m_renderer.emplace_font(font_id, "resources/fira_code.ttf", 14);

    m_window.set_title("Interactive music test");
    m_window.set_size(window_size);

    // clang-format off
    m_dispatcher.bind<cen::quit_event>().to<&interactive_music::on_quit_event>(this);
    m_dispatcher.bind<cen::keyboard_event>().to<&interactive_music::on_keyboard_event>(this);
    // clang-format on
  }

  auto run() -> int
  {
    const auto messages = messages::make(m_renderer);
    m_window.show();

    while (m_running)
    {
      m_dispatcher.poll();
      render(messages);
    }

    m_window.hide();
    return 0;
  }

 private:
  cen::window m_window;
  cen::renderer m_renderer;
  event_dispatcher m_dispatcher;
  cen::music m_song;
  cen::music m_click;
  bool m_running{true};

  void on_quit_event(const cen::quit_event&)
  {
    m_running = false;
  }

  void on_keyboard_event(const cen::keyboard_event& event)
  {
    if (event.released())
    {
      if (event.is_active(cen::scancodes::zero))
      {
        m_click.play(0);
      }
      else if (event.is_active(cen::scancodes::one))
      {
        m_click.play(1);
      }
      else if (event.is_active(cen::scancodes::two))
      {
        m_click.play(2);
      }
      else if (event.is_active(cen::scancodes::nine))
      {
        m_click.play(cen::music::forever);
      }
      else if (event.is_active(cen::scancodes::f))
      {
        m_song.fade_in(cen::seconds<int>{5});
      }
      else if (event.is_active(cen::scancodes::escape))
      {
        cen::music::halt();
      }
    }
  }

  void render(const messages& msgs)
  {
    auto nextPos = [y = 50](const cen::texture& texture) mutable {
      const auto x = (window_size.width - texture.width()) / 2;

      const auto tmpY = y;
      y += 25;

      return cen::ipoint{x, tmpY};
    };

    m_renderer.clear_with(cen::colors::black);

    m_renderer.render(msgs.infoZero, nextPos(msgs.infoZero));
    m_renderer.render(msgs.infoOne, nextPos(msgs.infoOne));
    m_renderer.render(msgs.infoTwo, nextPos(msgs.infoTwo));
    m_renderer.render(msgs.infoNine, nextPos(msgs.infoNine));
    m_renderer.render(msgs.infoFadeIn, nextPos(msgs.infoFadeIn));
    m_renderer.render(msgs.infoEsc, nextPos(msgs.infoEsc));

    constexpr cen::ipoint offset{0, 25};
    if (cen::music::is_playing() && !cen::music::is_fading())
    {
      m_renderer.render(msgs.playingMusic, nextPos(msgs.playingMusic) + offset);
    }
    else if (cen::music::is_fading())
    {
      m_renderer.render(msgs.fadingMusic, nextPos(msgs.fadingMusic) + offset);
    }
    else
    {
      m_renderer.render(msgs.noMusic, nextPos(msgs.noMusic) + offset);
    }

    m_renderer.present();
  }
};

}  // namespace

auto main(int, char**) -> int
{
  const cen::library centurion;
  interactive_music demo;
  return demo.run();
}