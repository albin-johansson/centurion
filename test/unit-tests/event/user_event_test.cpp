#include <gtest/gtest.h>

#include "event.hpp"

TEST(UserEvent, Defaults)
{
  const cen::UserEvent event;

  ASSERT_EQ(0, event.GetCode());
  ASSERT_EQ(0u, event.GetWindowID());

  ASSERT_EQ(nullptr, event.GetData1());
  ASSERT_EQ(nullptr, event.GetData2());
}

TEST(UserEvent, SetWindowId)
{
  cen::UserEvent event;

  const Uint32 id = 123;
  event.SetWindowID(id);

  ASSERT_EQ(id, event.GetWindowID());
}

TEST(UserEvent, SetCode)
{
  cen::UserEvent event;

  const auto code = 13;
  event.SetCode(code);

  ASSERT_EQ(code, event.GetCode());
}

TEST(UserEvent, SetData1)
{
  cen::UserEvent event;
  const auto& ref = event;

  int i = 42;
  event.SetData1(&i);

  ASSERT_EQ(&i, event.GetData1());
  ASSERT_EQ(&i, ref.GetData1());
  ASSERT_EQ(nullptr, event.GetData2());
}

TEST(UserEvent, SetData2)
{
  cen::UserEvent event;
  const auto& ref = event;

  int i = 42;
  event.SetData2(&i);

  ASSERT_EQ(&i, event.GetData2());
  ASSERT_EQ(&i, ref.GetData2());
  ASSERT_EQ(nullptr, event.GetData1());
}

TEST(UserEvent, AsSDLEvent)
{
  const cen::UserEvent event;
  const auto underlying = cen::AsSDLEvent(event);

  ASSERT_EQ(underlying.user.type, cen::to_underlying(event.GetType()));
  ASSERT_EQ(underlying.user.timestamp, event.GetTimestamp());
  ASSERT_EQ(underlying.user.code, event.GetCode());
  ASSERT_EQ(underlying.user.windowID, event.GetWindowID());
  ASSERT_EQ(underlying.user.data1, event.GetData1());
  ASSERT_EQ(underlying.user.data2, event.GetData2());
}
