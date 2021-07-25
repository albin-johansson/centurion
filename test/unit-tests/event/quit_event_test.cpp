#include <gtest/gtest.h>

#include "events/event.hpp"

TEST(QuitEvent, Defaults)
{
  cen::quit_event event;
  ASSERT_GT(event.time(), 0u);
  ASSERT_EQ(cen::event_type::quit, event.type());
}

TEST(QuitEvent, Construction)
{
  ASSERT_NO_THROW(cen::quit_event{});

  SDL_QuitEvent e;
  ASSERT_NO_THROW(cen::quit_event{e});
}

TEST(QuitEvent, AsSDLEvent)
{
  const cen::quit_event event;
  const auto sdl = cen::as_sdl_event(event);

  ASSERT_EQ(sdl.quit.type, cen::to_underlying(event.type()));
  ASSERT_EQ(sdl.quit.timestamp, event.time());
}
