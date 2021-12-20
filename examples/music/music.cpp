#include <centurion.hpp>
#include <optional>  // optional

namespace {

using event_dispatcher = cen::EventDispatcher<cen::quit_event, cen::keyboard_event>;

constexpr cen::Area window_size = cen::Window::GetDefaultSize();

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
    mDispatcher.Bind<cen::quit_event>().To<&music_example::on_quit_event>(this);
    mDispatcher.Bind<cen::keyboard_event>().To<&music_example::on_keyboard_event>(this);

    load_messages();
  }

  auto run() -> int
  {
    mWindow.Show();

    while (m_running) {
      mDispatcher.Poll();
      render();
    }

    mWindow.Hide();
    return 0;
  }

 private:
  cen::Window mWindow;
  cen::Renderer mRenderer;
  cen::Font mFont;
  event_dispatcher mDispatcher;
  cen::Music mSong;
  cen::Music mClick;
  bool m_running{true};

  std::vector<cen::Texture> mInstructions;
  std::optional<cen::Texture> mTexPlayingMusic;
  std::optional<cen::Texture> mTexFadingMusic;
  std::optional<cen::Texture> mTexNoMusic;

  void load_messages()
  {
    const auto color = cen::colors::white;
    mInstructions.emplace_back(mRenderer, mFont.RenderBlendedLatin1(msg_zero, color));
    mInstructions.emplace_back(mRenderer, mFont.RenderBlendedLatin1(msg_one, color));
    mInstructions.emplace_back(mRenderer, mFont.RenderBlendedLatin1(msg_two, color));
    mInstructions.emplace_back(mRenderer, mFont.RenderBlendedLatin1(msg_nine, color));
    mInstructions.emplace_back(mRenderer, mFont.RenderBlendedLatin1(msg_fade, color));
    mInstructions.emplace_back(mRenderer, mFont.RenderBlendedLatin1(msg_halt, color));

    mTexPlayingMusic =
        mRenderer.ToTexture(mFont.RenderBlendedLatin1(msg_playing, cen::colors::lime_green));
    mTexFadingMusic =
        mRenderer.ToTexture(mFont.RenderBlendedLatin1(msg_fading, cen::colors::hot_pink));
    mTexNoMusic =
        mRenderer.ToTexture(mFont.RenderBlendedLatin1(msg_no_music, cen::colors::red));
  }

  void on_quit_event(const cen::quit_event&) { m_running = false; }

  void on_keyboard_event(const cen::keyboard_event& event)
  {
    if (event.released()) {
      if (event.is_active(cen::scancodes::zero)) {
        mClick.Play(0);
      }
      else if (event.is_active(cen::scancodes::one)) {
        mClick.Play(1);
      }
      else if (event.is_active(cen::scancodes::two)) {
        mClick.Play(2);
      }
      else if (event.is_active(cen::scancodes::nine)) {
        mClick.Play(cen::Music::forever);
      }
      else if (event.is_active(cen::scancodes::f)) {
        mSong.FadeIn(cen::Seconds<int>{5});
      }
      else if (event.is_active(cen::scancodes::escape)) {
        cen::Music::Halt();
      }
    }
  }

  void render()
  {
    auto position_of = [y = 50](const cen::Texture& texture) mutable {
      const auto x = (window_size.width - texture.GetWidth()) / 2;
      const auto oldY = y;

      y += 25;
      return cen::Point{x, oldY};
    };

    mRenderer.ClearWith(cen::colors::steel_blue);

    for (const auto& texture : mInstructions) {
      mRenderer.Render(texture, position_of(texture));
    }

    constexpr cen::Point offset{0, 25};
    if (cen::Music::IsPlaying() && !cen::Music::IsFading()) {
      mRenderer.Render(*mTexPlayingMusic, position_of(*mTexPlayingMusic) + offset);
    }
    else if (cen::Music::IsFading()) {
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
  const cen::SDL sdl;
  const cen::IMG img;
  const cen::Mix mix;
  const cen::TTF ttf;

  music_example example;
  return example.run();
}
