#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/misc_events.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

using id = cen::display_event_id;

TEST(DisplayEventID, Values)
{
  ASSERT_EQ(SDL_DISPLAYEVENT_NONE, to_underlying(id::none));
  ASSERT_EQ(SDL_DISPLAYEVENT_ORIENTATION, to_underlying(id::orientation));
  ASSERT_EQ(SDL_DISPLAYEVENT_CONNECTED, to_underlying(id::connected));
  ASSERT_EQ(SDL_DISPLAYEVENT_DISCONNECTED, to_underlying(id::disconnected));
}

TEST(DisplayEventID, ToString)
{
  ASSERT_THROW(to_string(static_cast<id>(4)), cen::exception);

  ASSERT_EQ("none", to_string(id::none));
  ASSERT_EQ("orientation", to_string(id::orientation));
  ASSERT_EQ("connected", to_string(id::connected));
  ASSERT_EQ("disconnected", to_string(id::disconnected));

  std::cout << "display_event_id::connected == " << id::connected << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)