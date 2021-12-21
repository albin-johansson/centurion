#include <gtest/gtest.h>

#include "event.hpp"

TEST(DropEvent, Defaults)
{
  const cen::DropEvent event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::DropFile, event.GetType());

  ASSERT_EQ(nullptr, event.GetFile());
  ASSERT_EQ(0u, event.GetWindowID());
  ASSERT_FALSE(event.WillFreeFile());
}

TEST(DropEvent, SetWillFreeFile)
{
  cen::DropEvent event;

  event.SetWillFreeFile(true);
  ASSERT_TRUE(event.WillFreeFile());

  event.SetWillFreeFile(false);
  ASSERT_FALSE(event.WillFreeFile());
}

TEST(DropEvent, SetFile)
{
  cen::DropEvent event;
  ASSERT_NO_THROW(event.SetFile(nullptr));

  event.SetWillFreeFile(true);
  ASSERT_TRUE(event.WillFreeFile());

  /* This is the only time in the tests that a drop event should free the file,
     check the code coverage reports in order to see if it's freed. */
  event.SetFile(static_cast<char*>(SDL_malloc(sizeof(char))));
}

TEST(DropEvent, SetWindowID)
{
  cen::DropEvent event;

  event.SetWindowID(84);
  ASSERT_EQ(84, event.GetWindowID());
}

TEST(DropEvent, AsSDLEvent)
{
  const cen::DropEvent event;
  const auto underlying = cen::AsSDLEvent(event);

  ASSERT_EQ(underlying.drop.type, cen::ToUnderlying(event.GetType()));
  ASSERT_EQ(underlying.drop.timestamp, event.GetTimestamp());
}
