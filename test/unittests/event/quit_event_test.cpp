#include <gtest/gtest.h>

#include "event.hpp"

TEST(QuitEvent, Defaults)
{
  cen::quit_event event;
  EXPECT_GT(event.time(), 0);
  EXPECT_EQ(cen::event_type::quit, event.type());
}

TEST(QuitEvent, Construction)
{
  EXPECT_NO_THROW(cen::quit_event{});

  SDL_QuitEvent e;
  EXPECT_NO_THROW(cen::quit_event{e});
}
