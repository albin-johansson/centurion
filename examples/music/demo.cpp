#include <centurion.hpp>
#include <optional>  // optional

namespace {

using event_dispatcher = cen::event_dispatcher<cen::quit_event, cen::keyboard_event>;

constexpr cen::iarea window_size = cen::window::default_size();

constexpr auto msg_zero = "\"0\" to play the click one time.";
constexpr auto msg_one = "\"1\" to play the click one time.";
constexpr auto msg_two = "\"2\" to play the click two times.";
constexpr auto msg_nine = "\"9\" to play the click forever.";
constexpr auto msg_fade = "\"F\" to fade in the music over 5 seconds.";
constexpr auto msg_halt = "\"ESC\" to halt the music.";
constexpr auto msg_playing = "Music is playing!";
constexpr auto msg_fading = "Music is fading!";
constexpr auto msg_no_music = "No music is playing";

class music_example final {
 public:
  music_example()
      : mWindow {"Music example",
                 window_size,
                 cen::window::hidden | cen::window::allow_high_dpi}
      , mRenderer {mWindow.make_renderer()}
      , mFont {RESOURCE_DIR "fira_code.ttf", 16}
      , mSong {RESOURCE_DIR "hiddenPond.mp3"}
      , mClick {RESOURCE_DIR "click.wav"}
  {
    mRenderer.set_logical_size(window_size);

    mDispatcher.bind<cen::quit_event>().to<&music_example::on_quit_event>(this);
    mDispatcher.bind<cen::keyboard_event>().to<&music_example::on_keyboard_event>(this);

    load_messages();
  }

  auto run() -> int
  {
    mWindow.show();

    while (m_running) {
      mDispatcher.poll();
      render();
    }

    mWindow.hide();
    return 0;
  }

 private:
  cen::window mWindow;
  cen::renderer mRenderer;
  cen::font mFont;
  event_dispatcher mDispatcher;
  cen::music mSong;
  cen::music mClick;
  bool m_running {true};

  std::vector<cen::texture> mInstructions;
  std::optional<cen::texture> mTexPlayingMusic;
  std::optional<cen::texture> mTexFadingMusic;
  std::optional<cen::texture> mTexNoMusic;

  void load_messages()
  {
    const auto load = [this](const char* msg, cen::color fg = cen::colors::white) {
      return mRenderer.make_texture(mFont.render_blended(msg, fg));
    };

    mInstructions.push_back(load(msg_zero));
    mInstructions.push_back(load(msg_one));
    mInstructions.push_back(load(msg_two));
    mInstructions.push_back(load(msg_nine));
    mInstructions.push_back(load(msg_fade));
    mInstructions.push_back(load(msg_halt));

    mTexPlayingMusic = load(msg_playing, cen::colors::lime_green);
    mTexFadingMusic = load(msg_fading, cen::colors::hot_pink);
    mTexNoMusic = load(msg_no_music, cen::colors::red);
  }

  void on_quit_event(const cen::quit_event&) { m_running = false; }

  void on_keyboard_event(const cen::keyboard_event& event)
  {
    if (event.released()) {
      if (event.is_active(cen::scancodes::zero)) {
        mClick.play(0);
      }
      else if (event.is_active(cen::scancodes::one)) {
        mClick.play(1);
      }
      else if (event.is_active(cen::scancodes::two)) {
        mClick.play(2);
      }
      else if (event.is_active(cen::scancodes::nine)) {
        mClick.play(cen::music::forever);
      }
      else if (event.is_active(cen::scancodes::f)) {
        mSong.fade_in(cen::music::ms_type {5'000});
      }
      else if (event.is_active(cen::scancodes::escape)) {
        cen::music::halt();
      }
    }
  }

  void render()
  {
    auto position_of = [y = 50](const cen::texture& texture) mutable {
      const auto x = (window_size.width - texture.width()) / 2;
      const auto oldY = y;

      y += 25;
      return cen::ipoint {x, oldY};
    };

    mRenderer.clear_with(cen::colors::steel_blue);

    for (const auto& texture : mInstructions) {
      mRenderer.render(texture, position_of(texture));
    }

    constexpr cen::ipoint offset {0, 25};
    if (cen::music::is_playing() && !cen::music::is_fading()) {
      mRenderer.render(*mTexPlayingMusic, position_of(*mTexPlayingMusic) + offset);
    }
    else if (cen::music::is_fading()) {
      mRenderer.render(*mTexFadingMusic, position_of(*mTexFadingMusic) + offset);
    }
    else {
      mRenderer.render(*mTexNoMusic, position_of(*mTexNoMusic) + offset);
    }

    mRenderer.present();
  }
};

}  // namespace

auto main(int, char**) -> int
{
  const cen::sdl sdl;
  const cen::img img;
  const cen::mix mix;
  const cen::ttf ttf;

  music_example example;
  return example.run();
}
