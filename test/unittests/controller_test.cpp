#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "controller.hpp"

TEST_CASE("load_game_controller_mappings", "[game_controller]")
{
  const auto nAdded =
      ctn::controller::load_mappings("resources/gamecontrollerdb.txt");
  CHECK(nAdded > 0);
}

#include <array>

#include "event.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("Interactive game controller test", "[.game_controller]")
{
  ctn::window window{"Game controller demo"};
  ctn::renderer renderer{window};
  ctn::event event;

  ctn::controller::load_mappings("resources/gamecontrollerdb.txt");

  ctn::controller controller{0};

  ctn::frect rect{{0, 0}, {100, 100}};

  float dx{};
  float dy{};

  constexpr auto deadZone = 8000;

  constexpr std::array<ctn::color, 3> colors{
      ctn::colors::pink, ctn::colors::steel_blue, ctn::colors::red};
  int colorIndex{};
  ctn::color color = colors.at(colorIndex);

  bool running = true;
  window.show();
  while (running) {
    while (event.poll()) {
      if (event.is<ctn::quit_event>()) {
        running = false;
        break;
      } else if (const auto* cbe =
                     event.try_get<ctn::controller_button_event>()) {
        if (cbe->state() == ctn::button_state::released) {
          ++colorIndex;
          color = colors.at(colorIndex % int{colors.size()});
        }
      } else if (const auto* cae =
                     event.try_get<ctn::controller_axis_event>()) {
        const auto axis = cae->axis();
        const auto value = cae->value();  // -32768 to 32767)
        const auto fvalue = static_cast<float>(value);

        const auto step = 0.0005f;

        if (axis == ctn::controller_axis::left_x) {
          if ((value < -deadZone) || (value > deadZone)) {
            dx = fvalue * step;
          } else {
            dx = 0;
          }
        } else if (axis == ctn::controller_axis::left_y) {
          if ((value < -deadZone) || (value > deadZone)) {
            dy = fvalue * step;
          } else {
            dy = 0;
          }
        }
      }
    }

    rect.set_x(rect.x() + dx);
    rect.set_y(rect.y() + dy);

    renderer.clear_with(color);

    renderer.set_color(ctn::colors::dark_red);
    renderer.fill_rect(rect);

    renderer.present();
  }
  window.hide();
}