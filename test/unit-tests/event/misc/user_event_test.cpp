#include <gtest/gtest.h>

#include "misc_events.hpp"

TEST(UserEvent, Defaults)
{
  const cen::user_event event;

  ASSERT_EQ(0, event.code());
  ASSERT_EQ(0u, event.window_id());

  ASSERT_EQ(nullptr, event.data1());
  ASSERT_EQ(nullptr, event.data2());
}

TEST(UserEvent, SetWindowID)
{
  cen::user_event event;

  const cen::uint32 id = 123;
  event.set_window_id(id);

  ASSERT_EQ(id, event.window_id());
}

TEST(UserEvent, SetCode)
{
  cen::user_event event;

  const cen::int32 code = 13;
  event.set_code(code);

  ASSERT_EQ(code, event.code());
}

TEST(UserEvent, SetData1)
{
  cen::user_event event;
  const auto& ref = event;

  int i = 42;
  event.set_data1(&i);

  ASSERT_EQ(&i, event.data1());
  ASSERT_EQ(&i, ref.data1());
  ASSERT_EQ(nullptr, event.data2());
}

TEST(UserEvent, SetData2)
{
  cen::user_event event;
  const auto& ref = event;

  int i = 42;
  event.set_data2(&i);

  ASSERT_EQ(&i, event.data2());
  ASSERT_EQ(&i, ref.data2());
  ASSERT_EQ(nullptr, event.data1());
}

TEST(UserEvent, AsSDLEvent)
{
  const cen::user_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.user.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.user.timestamp, event.timestamp().count());
  ASSERT_EQ(underlying.user.code, event.code());
  ASSERT_EQ(underlying.user.windowID, event.window_id());
  ASSERT_EQ(underlying.user.data1, event.data1());
  ASSERT_EQ(underlying.user.data2, event.data2());
}
