#include "events/user_event.hpp"

#include <gtest/gtest.h>

TEST(UserEvent, Defaults)
{
  const cen::user_event event;
  ASSERT_EQ(0, event.code());
  ASSERT_EQ(0u, event.window_id());
  ASSERT_FALSE(event.data_1());
  ASSERT_FALSE(event.data_2());
}

TEST(UserEvent, SetWindowId)
{
  cen::user_event event;

  const Uint32 id = 123;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(UserEvent, SetCode)
{
  cen::user_event event;

  const auto code = 13;
  event.set_code(code);

  ASSERT_EQ(code, event.code());
}

TEST(UserEvent, SetData1)
{
  cen::user_event event;
  const auto& cevent = event;

  int i = 42;
  event.set_data_1(&i);

  ASSERT_EQ(&i, event.data_1());
  ASSERT_EQ(&i, cevent.data_1());
  ASSERT_FALSE(event.data_2());
}

TEST(UserEvent, SetData2)
{
  cen::user_event event;
  const auto& cevent = event;

  int i = 42;
  event.set_data_2(&i);

  ASSERT_EQ(&i, event.data_2());
  ASSERT_EQ(&i, cevent.data_2());
  ASSERT_FALSE(event.data_1());
}

TEST(UserEvent, AsSDLEvent)
{
  const cen::user_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.user.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.user.timestamp, event.time());
  ASSERT_EQ(sdl.user.code, event.code());
  ASSERT_EQ(sdl.user.windowID, event.window_id());
  ASSERT_EQ(sdl.user.data1, event.data_1());
  ASSERT_EQ(sdl.user.data2, event.data_2());
}
