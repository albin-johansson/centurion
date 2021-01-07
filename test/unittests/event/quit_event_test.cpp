#include <gtest/gtest.h>

#include "event.hpp"

TEST(QuitEvent, Defaults)
{
  cen::quit_event event;
  EXPECT_GT(event.time(), 0u);
  EXPECT_EQ(cen::event_type::quit, event.type());
}

TEST(QuitEvent, Construction)
{
  EXPECT_NO_THROW(cen::quit_event{});

  SDL_QuitEvent e;
  EXPECT_NO_THROW(cen::quit_event{e});
}

TEST(QuitEvent, AsSDLEvent)
{
  const cen::quit_event event;
  const auto sdl = cen::as_sdl_event(event);

  EXPECT_EQ(sdl.quit.type, static_cast<cen::u32>(event.type()));
  EXPECT_EQ(sdl.quit.timestamp, event.time());
}
