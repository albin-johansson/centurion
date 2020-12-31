#include <gtest/gtest.h>

#include "event.hpp"

TEST(QuitEvent, Construction)
{
  EXPECT_NO_THROW(cen::quit_event{});

  SDL_QuitEvent e;
  EXPECT_NO_THROW(cen::quit_event{e});
}
