#include <gtest/gtest.h>

#include "event.hpp"

TEST(QuitEvent, Defaults)
{
  cen::quit_event event;
  ASSERT_GT(event.GetTimestamp(), 0u);
  ASSERT_EQ(cen::EventType::Quit, event.GetType());
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
  const auto sdl = cen::AsSDLEvent(event);

  ASSERT_EQ(sdl.quit.type, cen::to_underlying(event.GetType()));
  ASSERT_EQ(sdl.quit.timestamp, event.GetTimestamp());
}
