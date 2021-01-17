#include "controller.hpp"

#include <gtest/gtest.h>

#include <array>
#include <utility>
#include <vector>

#include "event.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST(Controller, PointerConstructor)
{
  EXPECT_THROW(cen::controller{nullptr}, cen::exception);
}

TEST(Controller, IndexConstructor)
{
  EXPECT_THROW(cen::controller{}, cen::sdl_error);
}

TEST(Controller, FromJoystick)
{
  EXPECT_THROW(cen::controller::from_joystick(0), cen::sdl_error);
}

TEST(Controller, FromIndex)
{
  EXPECT_THROW(cen::controller::from_index(0), cen::sdl_error);
}

TEST(Controller, LoadMappings)
{
  const auto path = "resources/controllers.txt";
  EXPECT_GT(cen::controller::load_mappings(path), 0);
  EXPECT_FALSE(cen::controller::load_mappings("foobar").has_value());
}

TEST(Controller, NumMappings)
{
  EXPECT_EQ(SDL_GameControllerNumMappings(), cen::controller::num_mappings());
}

TEST(Controller, ControllerTypeEnum)
{
  using type = cen::controller_type;

  EXPECT_EQ(type::unknown, SDL_CONTROLLER_TYPE_UNKNOWN);
  EXPECT_EQ(type::xbox_360, SDL_CONTROLLER_TYPE_XBOX360);
  EXPECT_EQ(type::xbox_one, SDL_CONTROLLER_TYPE_XBOXONE);
  EXPECT_EQ(type::ps3, SDL_CONTROLLER_TYPE_PS3);
  EXPECT_EQ(type::ps4, SDL_CONTROLLER_TYPE_PS4);
  EXPECT_EQ(type::nintendo_switch_pro, SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);

  EXPECT_EQ(SDL_CONTROLLER_TYPE_UNKNOWN, type::unknown);
  EXPECT_EQ(SDL_CONTROLLER_TYPE_XBOX360, type::xbox_360);
  EXPECT_EQ(SDL_CONTROLLER_TYPE_XBOXONE, type::xbox_one);
  EXPECT_EQ(SDL_CONTROLLER_TYPE_PS3, type::ps3);
  EXPECT_EQ(SDL_CONTROLLER_TYPE_PS4, type::ps4);
  EXPECT_EQ(SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO, type::nintendo_switch_pro);

  EXPECT_NE(type::ps4, SDL_CONTROLLER_TYPE_NINTENDO_SWITCH_PRO);
  EXPECT_NE(SDL_CONTROLLER_TYPE_XBOX360, type::unknown);
}

TEST(Controller, ControllerAxisEnum)
{
  using axis = cen::controller_axis;

  EXPECT_EQ(axis::invalid, SDL_CONTROLLER_AXIS_INVALID);
  EXPECT_EQ(axis::left_x, SDL_CONTROLLER_AXIS_LEFTX);
  EXPECT_EQ(axis::left_y, SDL_CONTROLLER_AXIS_LEFTY);
  EXPECT_EQ(axis::right_x, SDL_CONTROLLER_AXIS_RIGHTX);
  EXPECT_EQ(axis::right_y, SDL_CONTROLLER_AXIS_RIGHTY);
  EXPECT_EQ(axis::trigger_left, SDL_CONTROLLER_AXIS_TRIGGERLEFT);
  EXPECT_EQ(axis::trigger_right, SDL_CONTROLLER_AXIS_TRIGGERRIGHT);
  EXPECT_EQ(axis::max, SDL_CONTROLLER_AXIS_MAX);

  EXPECT_EQ(SDL_CONTROLLER_AXIS_INVALID, axis::invalid);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_LEFTX, axis::left_x);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_LEFTY, axis::left_y);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_RIGHTX, axis::right_x);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_RIGHTY, axis::right_y);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_TRIGGERLEFT, axis::trigger_left);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_TRIGGERRIGHT, axis::trigger_right);
  EXPECT_EQ(SDL_CONTROLLER_AXIS_MAX, axis::max);

  EXPECT_NE(axis::left_x, SDL_CONTROLLER_AXIS_MAX);
  EXPECT_NE(SDL_CONTROLLER_AXIS_TRIGGERLEFT, axis::right_x);
}

TEST(Controller, ControllerButtonEnum)
{
  using button = cen::controller_button;

  EXPECT_EQ(button::invalid, SDL_CONTROLLER_BUTTON_INVALID);
  EXPECT_EQ(button::a, SDL_CONTROLLER_BUTTON_A);
  EXPECT_EQ(button::b, SDL_CONTROLLER_BUTTON_B);
  EXPECT_EQ(button::x, SDL_CONTROLLER_BUTTON_X);
  EXPECT_EQ(button::y, SDL_CONTROLLER_BUTTON_Y);
  EXPECT_EQ(button::back, SDL_CONTROLLER_BUTTON_BACK);
  EXPECT_EQ(button::guide, SDL_CONTROLLER_BUTTON_GUIDE);
  EXPECT_EQ(button::start, SDL_CONTROLLER_BUTTON_START);
  EXPECT_EQ(button::left_stick, SDL_CONTROLLER_BUTTON_LEFTSTICK);
  EXPECT_EQ(button::right_stick, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
  EXPECT_EQ(button::left_shoulder, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
  EXPECT_EQ(button::right_shoulder, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
  EXPECT_EQ(button::dpad_up, SDL_CONTROLLER_BUTTON_DPAD_UP);
  EXPECT_EQ(button::dpad_down, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
  EXPECT_EQ(button::dpad_right, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
  EXPECT_EQ(button::dpad_left, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
  EXPECT_EQ(button::max, SDL_CONTROLLER_BUTTON_MAX);

  EXPECT_NE(button::right_stick, SDL_CONTROLLER_BUTTON_DPAD_UP);
  EXPECT_NE(SDL_CONTROLLER_BUTTON_B, button::guide);
}

TEST(Controller, ControllerBindTypeEnum)
{
  using bind_type = cen::controller_bind_type;

  EXPECT_EQ(bind_type::axis, SDL_CONTROLLER_BINDTYPE_AXIS);
  EXPECT_EQ(bind_type::button, SDL_CONTROLLER_BINDTYPE_BUTTON);
  EXPECT_EQ(bind_type::none, SDL_CONTROLLER_BINDTYPE_NONE);
  EXPECT_EQ(bind_type::hat, SDL_CONTROLLER_BINDTYPE_HAT);

  EXPECT_EQ(SDL_CONTROLLER_BINDTYPE_AXIS, bind_type::axis);
  EXPECT_EQ(SDL_CONTROLLER_BINDTYPE_BUTTON, bind_type::button);
  EXPECT_EQ(SDL_CONTROLLER_BINDTYPE_NONE, bind_type::none);
  EXPECT_EQ(SDL_CONTROLLER_BINDTYPE_HAT, bind_type::hat);

  EXPECT_NE(bind_type::axis, SDL_CONTROLLER_BINDTYPE_HAT);
  EXPECT_NE(SDL_CONTROLLER_BINDTYPE_BUTTON, bind_type::none);
}

namespace cen {

class controller_handler  // TODO worth adding?
{
 public:
  void add_all()
  {
    const auto amount = cen::joystick::count().value_or(0);
    for (int i = 0; i < amount; ++i) {
      if (cen::controller::is_supported(i)) {
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

    erase(m_controllers, [=](const cen::controller& c) {
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
      throw exception{"Failed to find controller!"};
    }
  }

 private:
  std::vector<controller> m_controllers;

  [[nodiscard]] auto find(int index) -> std::vector<controller>::iterator
  {
    return std::find_if(begin(m_controllers),
                        end(m_controllers),
                        [=](const cen::controller& c) noexcept {
                          const auto i = c.index();
                          return i && index == *i;
                        });
  }
};

}  // namespace cen
