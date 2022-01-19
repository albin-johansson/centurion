#include <gtest/gtest.h>

#include "mouse_events.hpp"

TEST(MouseButtonEvent, Defaults)
{
  const cen::mouse_button_event event;
  ASSERT_EQ(cen::event_type::mouse_button_down, event.type());
}

TEST(MouseButtonEvent, SetWindowID)
{
  cen::mouse_button_event event;

  const cen::uint32 id = 64;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(MouseButtonEvent, SetWhich)
{
  cen::mouse_button_event event;

  const cen::uint32 which = 17;
  event.set_which(which);

  ASSERT_EQ(which, event.which());
}

TEST(MouseButtonEvent, SetButton)
{
  cen::mouse_button_event event;

  event.set_button(cen::MouseButton::Right);
  ASSERT_EQ(cen::MouseButton::Right, event.button());
}

TEST(MouseButtonEvent, SetState)
{
  cen::mouse_button_event event;

  event.set_state(cen::ButtonState::Pressed);

  ASSERT_EQ(cen::ButtonState::Pressed, event.state());
  ASSERT_TRUE(event.pressed());
  ASSERT_FALSE(event.released());

  event.set_state(cen::ButtonState::Released);

  ASSERT_EQ(cen::ButtonState::Released, event.state());
  ASSERT_TRUE(event.released());
  ASSERT_FALSE(event.pressed());
}

TEST(MouseButtonEvent, SetClicks)
{
  cen::mouse_button_event event;

  const cen::uint8 clicks = 2;
  event.set_clicks(clicks);

  ASSERT_EQ(clicks, event.clicks());
}

TEST(MouseButtonEvent, SetX)
{
  cen::mouse_button_event event;

  const cen::int32 x = 645;
  event.set_x(x);

  ASSERT_EQ(x, event.x());
}

TEST(MouseButtonEvent, SetY)
{
  cen::mouse_button_event event;

  const cen::int32 y = 177;
  event.set_y(y);

  ASSERT_EQ(y, event.y());
}

TEST(MouseButtonEvent, AsSDLEvent)
{
  const cen::mouse_button_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.button.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.button.timestamp, event.timestamp().count());
}
