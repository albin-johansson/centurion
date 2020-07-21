#include "game_loop.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"
#include "renderer.hpp"
#include "window.hpp"

// variable timestep loop game
class vtl_game {
 public:
  vtl_game() : m_window{}, m_renderer{m_window} {}

  auto input() -> bool
  {
    ctn::event event;
    while (event.poll()) {
      if (event.is<ctn::quit_event>()) {
        return false;
      } else if (const auto* key = event.try_get<ctn::keyboard_event>(); key) {
        if (key->released() && key->is_active(ctn::keycodes::escape)) {
          return false;
        }
      }
    }
    return true;
  }

  void logic(ctn::milliseconds<float> delta)
  {
    const auto secs = std::chrono::duration_cast<ctn::seconds<float>>(delta);
    x += (speed * secs.count());
  }

  void render()
  {
    m_renderer.clear_with(ctn::colors::pink);

    m_renderer.fill_rect(ctn::rect_f{{x, 50.0f}, {100.0f, 150.0f}});

    m_renderer.present();
  }

  [[nodiscard]] auto get_window() -> ctn::window& { return m_window; }

  [[nodiscard]] auto get_window() const -> const ctn::window&
  {
    return m_window;
  }

  [[nodiscard]] auto get_renderer() -> ctn::renderer& { return m_renderer; }

  [[nodiscard]] auto get_renderer() const -> const ctn::renderer&
  {
    return m_renderer;
  }

 private:
  ctn::window m_window;
  ctn::renderer m_renderer;
  float x{10.0f};
  const float speed{100.0f};
};

TEST_CASE("Variable timestep", "[.game_loop]")
{
  using ctn::experimental::variable_timestep_loop;
  vtl_game game;

  variable_timestep_loop loop;

  loop.connect_input<&vtl_game::input>(game);
  loop.connect_logic<&vtl_game::logic>(game);
  loop.connect_render<&vtl_game::render>(game);

  game.get_window().show();
  loop.run();
  game.get_window().hide();
}