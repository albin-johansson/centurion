#include "game_loop.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "event.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("Variable timestep", "[.game_loop]")
{
  ctn::window window;
  ctn::renderer renderer{window};

  ctn::experimental::variable_timestep_loop loop;

  const auto speed = 100.0f;
  auto x = 10.0f;

  auto input = [] {
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
  };

  auto logic = [&](ctn::milliseconds<float> delta) {
    const auto secs = std::chrono::duration_cast<ctn::seconds<float>>(delta);
    x += (speed * secs.count());
  };

  auto render = [&]() {
    renderer.clear_with(ctn::colors::pink);

    renderer.fill_rect(ctn::rect_f{{x, 50.0f}, {100.0f, 150.0f}});

    renderer.present();
  };

  window.show();
  loop.run(input, logic, render);
  window.hide();
}