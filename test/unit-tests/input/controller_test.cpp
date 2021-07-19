#include "input/controller.hpp"

#include <gtest/gtest.h>

#include <array>
#include <utility>
#include <vector>

#include "events/event.hpp"
#include "video/renderer.hpp"
#include "video/window.hpp"

TEST(Controller, PointerConstructor)
{
  ASSERT_THROW(cen::controller{nullptr}, cen::cen_error);
}

TEST(Controller, IndexConstructor)
{
  ASSERT_THROW(cen::controller{}, cen::sdl_error);
}

TEST(Controller, FromJoystick)
{
  ASSERT_THROW(cen::controller::from_joystick(0), cen::sdl_error);
}

TEST(Controller, LoadMappings)
{
  const auto path = "resources/controllers.txt";
  ASSERT_GT(cen::controller::load_mappings(path), 0);
  ASSERT_FALSE(cen::controller::load_mappings("foobar").has_value());
}

TEST(Controller, MappingCount)
{
  ASSERT_EQ(SDL_GameControllerNumMappings(), cen::controller::mapping_count());
}

TEST(Controller, Count)
{
  auto nControllers = 0;
  for (auto i = 0, count = cen::joystick::count().value(); i < count; ++i)
  {
    if (SDL_IsGameController(i))
    {
      ++nControllers;
    }
  }

  ASSERT_EQ(nControllers, cen::controller::count());
}

TEST(Controller, ControllerButtonEnum)
{
  using button = cen::controller_button;

  ASSERT_EQ(button::invalid, SDL_CONTROLLER_BUTTON_INVALID);
  ASSERT_EQ(button::a, SDL_CONTROLLER_BUTTON_A);
  ASSERT_EQ(button::b, SDL_CONTROLLER_BUTTON_B);
  ASSERT_EQ(button::x, SDL_CONTROLLER_BUTTON_X);
  ASSERT_EQ(button::y, SDL_CONTROLLER_BUTTON_Y);
  ASSERT_EQ(button::back, SDL_CONTROLLER_BUTTON_BACK);
  ASSERT_EQ(button::guide, SDL_CONTROLLER_BUTTON_GUIDE);
  ASSERT_EQ(button::start, SDL_CONTROLLER_BUTTON_START);
  ASSERT_EQ(button::left_stick, SDL_CONTROLLER_BUTTON_LEFTSTICK);
  ASSERT_EQ(button::right_stick, SDL_CONTROLLER_BUTTON_RIGHTSTICK);
  ASSERT_EQ(button::left_shoulder, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);
  ASSERT_EQ(button::right_shoulder, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
  ASSERT_EQ(button::dpad_up, SDL_CONTROLLER_BUTTON_DPAD_UP);
  ASSERT_EQ(button::dpad_down, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
  ASSERT_EQ(button::dpad_right, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
  ASSERT_EQ(button::dpad_left, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
  ASSERT_EQ(button::max, SDL_CONTROLLER_BUTTON_MAX);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(button::misc1, SDL_CONTROLLER_BUTTON_MISC1);
  ASSERT_EQ(button::paddle1, SDL_CONTROLLER_BUTTON_PADDLE1);
  ASSERT_EQ(button::paddle2, SDL_CONTROLLER_BUTTON_PADDLE2);
  ASSERT_EQ(button::paddle3, SDL_CONTROLLER_BUTTON_PADDLE3);
  ASSERT_EQ(button::paddle4, SDL_CONTROLLER_BUTTON_PADDLE4);
  ASSERT_EQ(button::touchpad, SDL_CONTROLLER_BUTTON_TOUCHPAD);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  ASSERT_NE(button::right_stick, SDL_CONTROLLER_BUTTON_DPAD_UP);
  ASSERT_NE(SDL_CONTROLLER_BUTTON_B, button::guide);
}

TEST(Controller, ControllerBindTypeEnum)
{
  using bind_type = cen::controller_bind_type;

  ASSERT_EQ(bind_type::axis, SDL_CONTROLLER_BINDTYPE_AXIS);
  ASSERT_EQ(bind_type::button, SDL_CONTROLLER_BINDTYPE_BUTTON);
  ASSERT_EQ(bind_type::none, SDL_CONTROLLER_BINDTYPE_NONE);
  ASSERT_EQ(bind_type::hat, SDL_CONTROLLER_BINDTYPE_HAT);

  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_AXIS, bind_type::axis);
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_BUTTON, bind_type::button);
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_NONE, bind_type::none);
  ASSERT_EQ(SDL_CONTROLLER_BINDTYPE_HAT, bind_type::hat);

  ASSERT_NE(bind_type::axis, SDL_CONTROLLER_BINDTYPE_HAT);
  ASSERT_NE(SDL_CONTROLLER_BINDTYPE_BUTTON, bind_type::none);
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST(Controller, FromIndex)
{
  ASSERT_THROW(cen::controller::from_index(0), cen::sdl_error);
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

namespace cen {

class controller_handler  // TODO worth adding?
{
 public:
  void add_all()
  {
    const auto amount = cen::joystick::count().value_or(0);
    for (int i = 0; i < amount; ++i)
    {
      if (cen::controller::is_supported(i))
      {
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
      container.erase(std::remove_if(begin(container), end(container), predicate),
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
    if (it != end(m_controllers))
    {
      return *it;
    }
    else
    {
      throw cen_error{"Failed to find controller!"};
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
