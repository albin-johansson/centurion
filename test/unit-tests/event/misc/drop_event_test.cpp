#include <gtest/gtest.h>

#include "centurion/misc_events.hpp"

TEST(DropEvent, Defaults)
{
  const cen::drop_event event;
  ASSERT_EQ(cen::event_type::drop_file, event.type());

  ASSERT_EQ(nullptr, event.file());
  ASSERT_EQ(0u, event.window_id());
  ASSERT_FALSE(event.will_free_file());
}

TEST(DropEvent, SetWillFreeFile)
{
  cen::drop_event event;

  event.set_will_free_file(true);
  ASSERT_TRUE(event.will_free_file());

  event.set_will_free_file(false);
  ASSERT_FALSE(event.will_free_file());
}

TEST(DropEvent, SetFile)
{
  cen::drop_event event;
  ASSERT_NO_THROW(event.set_file(nullptr));

  event.set_will_free_file(true);
  ASSERT_TRUE(event.will_free_file());

  /* This is the only time in the tests that a drop event should free the file,
     check the code coverage reports in order to see if it's freed. */
  event.set_file(static_cast<char*>(SDL_malloc(sizeof(char))));
}

TEST(DropEvent, SetWindowID)
{
  cen::drop_event event;

  event.set_window_id(84);
  ASSERT_EQ(84u, event.window_id());
}

TEST(DropEvent, AsSDLEvent)
{
  const cen::drop_event event;
  const auto underlying = cen::as_sdl_event(event);

  ASSERT_EQ(underlying.drop.type, cen::to_underlying(event.type()));
  ASSERT_EQ(underlying.drop.timestamp, event.timestamp().count());
}
