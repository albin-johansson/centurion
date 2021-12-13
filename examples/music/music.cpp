#include <centurion.hpp>
#include <optional>  // optional

namespace {

using event_dispatcher = cen::event_dispatcher<cen::quit_event, cen::keyboard_event>;

constexpr cen::usize font_id = 7;
constexpr cen::Area window_size = cen::window::default_size();

constexpr auto msg_zero = "\"0\" to play the click one time.";
constexpr auto msg_one = "\"1\" to play the click one time.";
constexpr auto msg_two = "\"2\" to play the click two times.";
constexpr auto msg_nine = "\"9\" to play the click forever.";
constexpr auto msg_fade = "\"F\" to fade in the music over 5 seconds.";
constexpr auto msg_halt = "\"ESC\" to halt the music.";
constexpr auto msg_playing = "Music is playing!";
constexpr auto msg_fading = "Music is fading!";
constexpr auto msg_no_music = "No music is playing";

class music_example final
{
 public:
  music_example()
      : m_window{}
      , m_renderer{m_window}
      , m_song{RESOURCE_DIR "hiddenPond.mp3"}
      , m_click{RESOURCE_DIR "click.wav"}
  {
    m_renderer.emplace_font(font_id, RESOURCE_DIR "fira_code.ttf", 16);

    m_window.set_title("Music example");
    m_window.set_size(window_size);

    m_dispatcher.bind<cen::quit_event>().to<&music_example::on_quit_event>(this);
    m_dispatcher.bind<cen::keyboard_event>().to<&music_example::on_keyboard_event>(this);

    load_messages();
  }

  auto run() -> int
  {
    m_window.show();

    while (m_running) {
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
  cen::Music m_song;
  cen::Music m_click;
  bool m_running{true};

  std::vector<cen::texture> m_instructions;
  std::optional<cen::texture> m_tex_playing_music;
  std::optional<cen::texture> m_tex_fading_music;
  std::optional<cen::texture> m_tex_no_music;

  void load_messages()
  {
    auto& font = m_renderer.get_font(font_id);

    m_renderer.set_color(cen::colors::white);
    m_instructions.push_back(m_renderer.render_blended_latin1(msg_zero, font));
    m_instructions.push_back(m_renderer.render_blended_latin1(msg_one, font));
    m_instructions.push_back(m_renderer.render_blended_latin1(msg_two, font));
    m_instructions.push_back(m_renderer.render_blended_latin1(msg_nine, font));
    m_instructions.push_back(m_renderer.render_blended_latin1(msg_fade, font));
    m_instructions.push_back(m_renderer.render_blended_latin1(msg_halt, font));

    m_renderer.set_color(cen::colors::lime_green);
    m_tex_playing_music = m_renderer.render_blended_latin1(msg_playing, font);

    m_renderer.set_color(cen::colors::hot_pink);
    m_tex_fading_music = m_renderer.render_blended_latin1(msg_fading, font);

    m_renderer.set_color(cen::colors::red);
    m_tex_no_music = m_renderer.render_blended_latin1(msg_no_music, font);
  }

  void on_quit_event(const cen::quit_event&)
  {
    m_running = false;
  }

  void on_keyboard_event(const cen::keyboard_event& event)
  {
    if (event.released()) {
      if (event.is_active(cen::scancodes::zero)) {
        m_click.Play(0);
      }
      else if (event.is_active(cen::scancodes::one)) {
        m_click.Play(1);
      }
      else if (event.is_active(cen::scancodes::two)) {
        m_click.Play(2);
      }
      else if (event.is_active(cen::scancodes::nine)) {
        m_click.Play(cen::Music::forever);
      }
      else if (event.is_active(cen::scancodes::f)) {
        m_song.FadeIn(cen::seconds<int>{5});
      }
      else if (event.is_active(cen::scancodes::escape)) {
        cen::Music::Halt();
      }
    }
  }

  void render()
  {
    auto position_of = [y = 50](const cen::texture& texture) mutable {
      const auto x = (window_size.width - texture.width()) / 2;
      const auto oldY = y;

      y += 25;
      return cen::Point{x, oldY};
    };

    m_renderer.clear_with(cen::colors::steel_blue);

    for (const auto& texture : m_instructions) {
      m_renderer.render(texture, position_of(texture));
    }

    constexpr cen::Point offset{0, 25};
    if (cen::Music::IsPlaying() && !cen::Music::IsFading()) {
      m_renderer.render(*m_tex_playing_music, position_of(*m_tex_playing_music) + offset);
    }
    else if (cen::Music::IsFading()) {
      m_renderer.render(*m_tex_fading_music, position_of(*m_tex_fading_music) + offset);
    }
    else {
      m_renderer.render(*m_tex_no_music, position_of(*m_tex_no_music) + offset);
    }

    m_renderer.present();
  }
};

}  // namespace

auto main(int, char**) -> int
{
  const cen::SDLLibrary sdl;
  const cen::IMGLibrary img;
  const cen::MixLibrary mix;
  const cen::TTFLibrary ttf;

  music_example example;
  return example.run();
}
