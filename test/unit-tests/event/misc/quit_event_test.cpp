#include <gtest/gtest.h>

#include "misc_events.hpp"

TEST(QuitEvent, Defaults)
{
  const cen::quit_event event;
  ASSERT_EQ(cen::event_type::quit, event.type());
}

TEST(QuitEvent, AsSDLEvent)
{
  const cen::quit_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.quit.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.quit.timestamp, event.timestamp().count());
}
