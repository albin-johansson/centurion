#include "events/event.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

using ID = cen::DisplayEventID;

TEST(DisplayEventID, Values)
{
  ASSERT_EQ(SDL_DISPLAYEVENT_NONE, ToUnderlying(ID::None));
  ASSERT_EQ(SDL_DISPLAYEVENT_ORIENTATION, ToUnderlying(ID::Orientation));
  ASSERT_EQ(SDL_DISPLAYEVENT_CONNECTED, ToUnderlying(ID::Connected));
  ASSERT_EQ(SDL_DISPLAYEVENT_DISCONNECTED, ToUnderlying(ID::Disconnected));
}

TEST(DisplayEventID, ToString)
{
  ASSERT_THROW(to_string(static_cast<ID>(4)), cen::Error);

  ASSERT_EQ("None", to_string(ID::None));
  ASSERT_EQ("Orientation", to_string(ID::Orientation));
  ASSERT_EQ("Connected", to_string(ID::Connected));
  ASSERT_EQ("Disconnected", to_string(ID::Disconnected));

  std::clog << "Display event ID example: " << ID::Connected << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)