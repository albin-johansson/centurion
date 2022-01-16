#include <centurion.hpp>
#include <optional>  // optional

namespace {

using event_dispatcher = cen::event_dispatcher<cen::quit_event, cen::KeyboardEvent>;

constexpr cen::iarea window_size = cen::Window::GetDefaultSize();

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
      : mWindow{"Music example", window_size, cen::Window::Hidden | cen::Window::AllowHighDPI}
      , mRenderer{mWindow}
      , mFont{RESOURCE_DIR "fira_code.ttf", 16}
      , mSong{RESOURCE_DIR "hiddenPond.mp3"}
      , mClick{RESOURCE_DIR "click.wav"}
  {
    mDispatcher.bind<cen::quit_event>().to<&music_example::on_quit_event>(this);
    mDispatcher.bind<cen::KeyboardEvent>().to<&music_example::on_keyboard_event>(this);

    load_messages();
  }

  auto run() -> int
  {
    mWindow.Show();

    while (m_running) {
      mDispatcher.poll();
      render();
    }

    mWindow.Hide();
    return 0;
  }

 private:
  cen::Window mWindow;
  cen::Renderer mRenderer;
  cen::font mFont;
  event_dispatcher mDispatcher;
  cen::music mSong;
  cen::music mClick;
  bool m_running{true};

  std::vector<cen::texture> mInstructions;
  std::optional<cen::texture> mTexPlayingMusic;
  std::optional<cen::texture> mTexFadingMusic;
  std::optional<cen::texture> mTexNoMusic;

  void load_messages()
  {
    const auto color = cen::colors::white;
    mInstructions.emplace_back(mRenderer, mFont.render_blended_latin1(msg_zero, color));
    mInstructions.emplace_back(mRenderer, mFont.render_blended_latin1(msg_one, color));
    mInstructions.emplace_back(mRenderer, mFont.render_blended_latin1(msg_two, color));
    mInstructions.emplace_back(mRenderer, mFont.render_blended_latin1(msg_nine, color));
    mInstructions.emplace_back(mRenderer, mFont.render_blended_latin1(msg_fade, color));
    mInstructions.emplace_back(mRenderer, mFont.render_blended_latin1(msg_halt, color));

    mTexPlayingMusic =
        mRenderer.ToTexture(mFont.render_blended_latin1(msg_playing, cen::colors::lime_green));
    mTexFadingMusic =
        mRenderer.ToTexture(mFont.render_blended_latin1(msg_fading, cen::colors::hot_pink));
    mTexNoMusic =
        mRenderer.ToTexture(mFont.render_blended_latin1(msg_no_music, cen::colors::red));
  }

  void on_quit_event(const cen::quit_event&) { m_running = false; }

  void on_keyboard_event(const cen::KeyboardEvent& event)
  {
    if (event.IsReleased()) {
      if (event.IsActive(cen::scancodes::zero)) {
        mClick.play(0);
      }
      else if (event.IsActive(cen::scancodes::one)) {
        mClick.play(1);
      }
      else if (event.IsActive(cen::scancodes::two)) {
        mClick.play(2);
      }
      else if (event.IsActive(cen::scancodes::nine)) {
        mClick.play(cen::music::forever);
      }
      else if (event.IsActive(cen::scancodes::f)) {
        mSong.fade_in(cen::music::ms_type{5'000});
      }
      else if (event.IsActive(cen::scancodes::escape)) {
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
      return cen::ipoint{x, oldY};
    };

    mRenderer.ClearWith(cen::colors::steel_blue);

    for (const auto& texture : mInstructions) {
      mRenderer.Render(texture, position_of(texture));
    }

    constexpr cen::ipoint offset{0, 25};
    if (cen::music::is_playing() && !cen::music::is_fading()) {
      mRenderer.Render(*mTexPlayingMusic, position_of(*mTexPlayingMusic) + offset);
    }
    else if (cen::music::is_fading()) {
      mRenderer.Render(*mTexFadingMusic, position_of(*mTexFadingMusic) + offset);
    }
    else {
      mRenderer.Render(*mTexNoMusic, position_of(*mTexNoMusic) + offset);
    }

    mRenderer.Present();
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
