#include <utility>  // move

#include "audio/music.hpp"
#include "events/event.hpp"
#include "library.hpp"
#include "video/renderer.hpp"
#include "video/texture.hpp"
#include "video/window.hpp"

namespace {

inline constexpr cen::iarea windowSize{800, 600};

inline constexpr auto msgZero = "\"0\" to play the click one time.";
inline constexpr auto msgOne = "\"1\" to play the click one time.";
inline constexpr auto msgTwo = "\"2\" to play the click two times.";
inline constexpr auto msgNine = "\"9\" to play the click forever.";
inline constexpr auto msgFadeIn = "\"F\" to fade in the music over 5 seconds.";
inline constexpr auto msgEsc = "\"ESC\" to halt the music.";

inline constexpr auto msgPlayingMusic = "Music is playing!";
inline constexpr auto msgFadingMusic = "Music is fading!";
inline constexpr auto msgNoMusic = "No music is playing";

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

  [[nodiscard]] static auto make(cen::renderer& renderer, cen::font& font)
      -> messages
  {
    renderer.set_color(cen::colors::white);

    renderer.set_color(cen::colors::green);
    auto playing = renderer.render_blended_latin1(msgPlayingMusic, font);

    renderer.set_color(cen::colors::magenta);
    auto fading = renderer.render_blended_latin1(msgFadingMusic, font);

    renderer.set_color(cen::colors::red);
    auto paused = renderer.render_blended_latin1(msgNoMusic, font);

    return messages{renderer.render_blended_latin1(msgZero, font),
                    renderer.render_blended_latin1(msgOne, font),
                    renderer.render_blended_latin1(msgTwo, font),
                    renderer.render_blended_latin1(msgNine, font),
                    renderer.render_blended_latin1(msgFadeIn, font),
                    renderer.render_blended_latin1(msgEsc, font),
                    std::move(playing),
                    std::move(fading),
                    std::move(paused)};
  }
};

class interactive_music final
{
 public:
  interactive_music()
      : m_window{}
      , m_renderer{m_window}
      , m_song{"resources/hiddenPond.mp3"}
      , m_click{"resources/click.wav"}
      , m_font{"resources/fira_code.ttf", 14}
  {
    m_window.set_size(windowSize);
    m_window.set_title("Interactive music test");
  }

  void run()
  {
    const auto msgs = messages::make(m_renderer, m_font);
    m_window.show();

    bool running = true;
    while (running)
    {
      running = handle_input();
      render(msgs);
    }

    m_window.hide();
  }

 private:
  cen::window m_window;
  cen::renderer m_renderer;
  cen::music m_song;
  cen::music m_click;
  cen::font m_font;

  [[nodiscard]] auto handle_input() -> bool
  {
    cen::event event;
    while (event.poll())
    {
      if (event.is<cen::quit_event>())
      {
        return false;
      }

      if (const auto* key = event.try_get<cen::keyboard_event>();
          key && key->released())
      {
        if (key->is_active(cen::scancodes::zero))
        {
          m_click.play(0);
        }
        else if (key->is_active(cen::scancodes::one))
        {
          m_click.play(1);
        }
        else if (key->is_active(cen::scancodes::two))
        {
          m_click.play(2);
        }
        else if (key->is_active(cen::scancodes::nine))
        {
          m_click.play(cen::music::forever);
        }
        else if (key->is_active(cen::scancodes::f))
        {
          m_song.fade_in(cen::seconds<int>{5});
        }
        else if (key->is_active(cen::scancodes::escape))
        {
          cen::music::halt();
        }
      }
    }

    return true;
  }

  void render(const messages& msgs)
  {
    auto nextPos = [y = 50](const cen::texture& texture) mutable {
      const auto x = (windowSize.width - texture.width()) / 2;
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

int main(int, char**)
{
  const cen::library lib;

  interactive_music im;
  im.run();

  return 0;
}