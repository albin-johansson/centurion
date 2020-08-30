#include "controller.hpp"

#include <catch.hpp>
#include <utility>
#include <vector>

#include "centurion_as_ctn.hpp"
#include "event.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("controller_type enum values", "[controller]")
{
  SECTION("operator==")
  {
    CHECK(ctn::controller_type::unknown == SDL_CONTROLLER_TYPE_UNKNOWN);
    CHECK(ctn::controller_type::xbox_360 == SDL_CONTROLLER_TYPE_XBOX360);
    CHECK(ctn::controller_type::xbox_one == SDL_CONTROLLER_TYPE_XBOXONE);
    CHECK(ctn::controller_type::ps3 == SDL_CONTROLLER_TYPE_PS3);
    CHECK(ctn::controller_type::ps4 == SDL_CONTROLLER_TYPE_PS4);
    CHECK(ctn::controller_type::nintendo_switch_pro ==
          SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);

    CHECK(SDL_CONTROLLER_TYPE_UNKNOWN == ctn::controller_type::unknown);
    CHECK(SDL_CONTROLLER_TYPE_XBOX360 == ctn::controller_type::xbox_360);
    CHECK(SDL_CONTROLLER_TYPE_XBOXONE == ctn::controller_type::xbox_one);
    CHECK(SDL_CONTROLLER_TYPE_PS3 == ctn::controller_type::ps3);
    CHECK(SDL_CONTROLLER_TYPE_PS4 == ctn::controller_type::ps4);
    CHECK(SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO ==
          ctn::controller_type::nintendo_switch_pro);
  }

  SECTION("operator!=")
  {
    CHECK(ctn::controller_type::ps4 != SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);
    CHECK(SDL_CONTROLLER_TYPE_XBOX360 != ctn::controller_type::unknown);
  }
}

TEST_CASE("controller_axis enum values", "[controller]")
{
  SECTION("operator==")
  {
    CHECK(ctn::controller_axis::invalid == SDL_CONTROLLER_AXIS_INVALID);
    CHECK(ctn::controller_axis::left_x == SDL_CONTROLLER_AXIS_LEFTX);
    CHECK(ctn::controller_axis::left_y == SDL_CONTROLLER_AXIS_LEFTY);
    CHECK(ctn::controller_axis::right_x == SDL_CONTROLLER_AXIS_RIGHTX);
    CHECK(ctn::controller_axis::right_y == SDL_CONTROLLER_AXIS_RIGHTY);
    CHECK(ctn::controller_axis::trigger_left ==
          SDL_CONTROLLER_AXIS_TRIGGERLEFT);
    CHECK(ctn::controller_axis::trigger_right ==
          SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
    CHECK(ctn::controller_axis::max == SDL_CONTROLLER_AXIS_MAX);

    CHECK(SDL_CONTROLLER_AXIS_INVALID == ctn::controller_axis::invalid);
    CHECK(SDL_CONTROLLER_AXIS_LEFTX == ctn::controller_axis::left_x);
    CHECK(SDL_CONTROLLER_AXIS_LEFTY == ctn::controller_axis::left_y);
    CHECK(SDL_CONTROLLER_AXIS_RIGHTX == ctn::controller_axis::right_x);
    CHECK(SDL_CONTROLLER_AXIS_RIGHTY == ctn::controller_axis::right_y);
    CHECK(SDL_CONTROLLER_AXIS_TRIGGERLEFT ==
          ctn::controller_axis::trigger_left);
    CHECK(SDL_CONTROLLER_AXIS_TRIGGERRIGHT ==
          ctn::controller_axis::trigger_right);
    CHECK(SDL_CONTROLLER_AXIS_MAX == ctn::controller_axis::max);
  }

  SECTION("operator!=")
  {
    CHECK(ctn::controller_axis::left_x != SDL_CONTROLLER_AXIS_MAX);
    CHECK(SDL_CONTROLLER_AXIS_TRIGGERLEFT != ctn::controller_axis::right_x);
  }
}

TEST_CASE("controller_button enum values", "[controller]")
{
  SECTION("operator==")
  {
    CHECK(ctn::controller_button::invalid == SDL_CONTROLLER_BUTTON_INVALID);
    CHECK(ctn::controller_button::a == SDL_CONTROLLER_BUTTON_A);
    CHECK(ctn::controller_button::b == SDL_CONTROLLER_BUTTON_B);
    CHECK(ctn::controller_button::x == SDL_CONTROLLER_BUTTON_X);
    CHECK(ctn::controller_button::y == SDL_CONTROLLER_BUTTON_Y);
    CHECK(ctn::controller_button::back == SDL_CONTROLLER_BUTTON_BACK);
    CHECK(ctn::controller_button::guide == SDL_CONTROLLER_BUTTON_GUIDE);
    CHECK(ctn::controller_button::start == SDL_CONTROLLER_BUTTON_START);
    CHECK(ctn::controller_button::left_stick ==
          SDL_CONTROLLER_BUTTON_LEFTSTICK);
    CHECK(ctn::controller_button::right_stick ==
          SDL_CONTROLLER_BUTTON_RIGHTSTICK);
    CHECK(ctn::controller_button::left_shoulder ==
          SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
    CHECK(ctn::controller_button::right_shoulder ==
          SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
    CHECK(ctn::controller_button::dpad_up == SDL_CONTROLLER_BUTTON_DPAD_UP);
    CHECK(ctn::controller_button::dpad_down == SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    CHECK(ctn::controller_button::dpad_right ==
          SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    CHECK(ctn::controller_button::dpad_left == SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    CHECK(ctn::controller_button::max == SDL_CONTROLLER_BUTTON_MAX);
  }

  SECTION("operator!=")
  {
    CHECK(ctn::controller_button::right_stick != SDL_CONTROLLER_BUTTON_DPAD_UP);
    CHECK(SDL_CONTROLLER_BUTTON_B != ctn::controller_button::guide);
  }
}

TEST_CASE("controller_bind_type enum values", "[controller]")
{
  SECTION("operator==")
  {
    CHECK(ctn::controller_bind_type::axis == SDL_CONTROLLER_BINDTYPE_AXIS);
    CHECK(ctn::controller_bind_type::button == SDL_CONTROLLER_BINDTYPE_BUTTON);
    CHECK(ctn::controller_bind_type::none == SDL_CONTROLLER_BINDTYPE_NONE);
    CHECK(ctn::controller_bind_type::hat == SDL_CONTROLLER_BINDTYPE_HAT);

    CHECK(SDL_CONTROLLER_BINDTYPE_AXIS == ctn::controller_bind_type::axis);
    CHECK(SDL_CONTROLLER_BINDTYPE_BUTTON == ctn::controller_bind_type::button);
    CHECK(SDL_CONTROLLER_BINDTYPE_NONE == ctn::controller_bind_type::none);
    CHECK(SDL_CONTROLLER_BINDTYPE_HAT == ctn::controller_bind_type::hat);
  }

  SECTION("operator!=")
  {
    CHECK(ctn::controller_bind_type::axis != SDL_CONTROLLER_BINDTYPE_HAT);
    CHECK(SDL_CONTROLLER_BINDTYPE_BUTTON != ctn::controller_bind_type::none);
  }
}

TEST_CASE("controller load_mappings", "[controller]")
{
  CHECK(ctn::controller::load_mappings("resources/gamecontrollerdb.txt") > 0);
}

namespace centurion {

class controller_handler  // TODO worth adding?
{
 public:
  void add_all()
  {
    const auto amount = ctn::joystick::amount().value_or(0);
    for (int i = 0; i < amount; ++i) {
      if (ctn::controller::is_supported(i)) {
        emplace(i);
      }
    }
  }

  template <typename... Args>
  void emplace(Args&&... args)
  {
    m_controllers.emplace_back(std::forward<Args>(args)...);
  }

  void remove(int index)
  {
    auto erase = [](auto& container, auto&& predicate) {
      container.erase(
          std::remove_if(begin(container), end(container), predicate),
          end(container));
    };

    erase(m_controllers, [=](const ctn::controller& c) {
      const auto i = c.index();
      return i && index == *i;
    });
  }

  auto at(int index) -> controller&
  {
    const auto it = find(index);
    if (it != end(m_controllers)) {
      return *it;
    } else {
      throw centurion_exception{"Failed to find controller!"};
    }
  }

 private:
  std::vector<controller> m_controllers;

  [[nodiscard]] auto find(int index) -> std::vector<controller>::iterator
  {
    const auto it = std::find_if(begin(m_controllers),
                                 end(m_controllers),
                                 [=](const ctn::controller& c) noexcept {
                                   const auto i = c.index();
                                   return i && index == *i;
                                 });
    return it;
  }
};

}  // namespace centurion

// TODO game controller visualization program

TEST_CASE("interactive controller", "[.controller]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  ctn::event event;
  ctn::controller_handler controllers;
  controllers.add_all();

  //  bool running{true};
  //
  //  int colorIndex{};
  //  constexpr std::array<ctn::color, 5> colors{ctn::colors::red,
  //                                             ctn::colors::salmon,
  //                                             ctn::colors::cyan,
  //                                             ctn::colors::dark_sea_green,
  //                                             ctn::colors::orchid};
  //
  //  auto handleDeviceEvent = [&](const ctn::controller_device_event& event) {
  //    if (event.type() == ctn::event_type::controller_device_removed) {
  //      const auto id = event.which();
  //      controllers.remove(id);
  //    } else if (event.type() == ctn::event_type::controller_device_added) {
  //      controllers.emplace(event.which());
  //    }
  //  };
  //
  //  auto handleButtonEvent = [&](const ctn::controller_button_event& event) {
  //    if (event.state() == ctn::button_state::released) {
  //      ++colorIndex;
  //    }
  //  };
  //
  //  window.show();
  //  while (running) {
  //    while (event.poll()) {
  //      if (event.is<ctn::quit_event>()) {
  //        running = false;
  //        break;
  //      } else if (auto* de = event.try_get<ctn::controller_device_event>()) {
  //        handleDeviceEvent(*de);
  //      } else if (auto* be = event.try_get<ctn::controller_button_event>()) {
  //        handleButtonEvent(*be);
  //      }
  //    }
  //
  //    renderer.clear_with(colors.at(colorIndex % colors.size()));
  //
  //    renderer.set_color(ctn::colors::wheat);
  //    renderer.fill_rect<int>({{10, 10}, {100, 100}});
  //
  //    renderer.present();
  //  }
  //  window.hide();
}

// TEST_CASE("load_game_controller_mappings", "[controller]")
//{
//  const auto nAdded =
//      ctn::controller::load_mappings("resources/gamecontrollerdb.txt");
//  CHECK(nAdded > 0);
//}
//
//#include <array>
//

//
// TEST_CASE("Interactive game controller test", "[..controller]")
//{
//  ctn::window window{"Game controller demo"};
//  ctn::renderer renderer{window};
//  ctn::event event;
//
//  ctn::controller::load_mappings("resources/gamecontrollerdb.txt");
//
//  ctn::controller controller{0};
//
//  ctn::frect rect{{0, 0}, {100, 100}};
//
//  float dx{};
//  float dy{};
//
//  constexpr auto deadZone = 8000;
//
//  constexpr std::array<ctn::color, 3> colors{
//      ctn::colors::pink, ctn::colors::steel_blue, ctn::colors::red};
//  int colorIndex{};
//  ctn::color color = colors.at(colorIndex);
//
//  bool running = true;
//  window.show();
//  while (running) {
//    while (event.poll()) {
//      if (event.is<ctn::quit_event>()) {
//        running = false;
//        break;
//      } else if (const auto* cbe =
//                     event.try_get<ctn::controller_button_event>()) {
//        if (cbe->state() == ctn::button_state::released) {
//          ++colorIndex;
//          color = colors.at(colorIndex % int{colors.size()});
//        }
//      } else if (const auto* cae =
//                     event.try_get<ctn::controller_axis_event>()) {
//        const auto axis = cae->axis();
//        const auto value = cae->value();  // -32768 to 32767)
//        const auto fvalue = static_cast<float>(value);
//
//        const auto step = 0.0005f;
//
//        if (axis == ctn::controller_axis::left_x) {
//          if ((value < -deadZone) || (value > deadZone)) {
//            dx = fvalue * step;
//          } else {
//            dx = 0;
//          }
//        } else if (axis == ctn::controller_axis::left_y) {
//          if ((value < -deadZone) || (value > deadZone)) {
//            dy = fvalue * step;
//          } else {
//            dy = 0;
//          }
//        }
//      }
//    }
//
//    rect.set_x(rect.x() + dx);
//    rect.set_y(rect.y() + dy);
//
//    renderer.clear_with(color);
//
//    renderer.set_color(ctn::colors::dark_red);
//    renderer.fill_rect(rect);
//
//    renderer.present();
//  }
//  window.hide();
//}