#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "event.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

using ID = cen::DisplayEventID;

TEST(DisplayEventID, Values)
{
  ASSERT_EQ(SDL_DISPLAYEVENT_NONE, to_underlying(ID::None));
  ASSERT_EQ(SDL_DISPLAYEVENT_ORIENTATION, to_underlying(ID::Orientation));
  ASSERT_EQ(SDL_DISPLAYEVENT_CONNECTED, to_underlying(ID::Connected));
  ASSERT_EQ(SDL_DISPLAYEVENT_DISCONNECTED, to_underlying(ID::Disconnected));
}

TEST(DisplayEventID, ToString)
{
  ASSERT_THROW(ToString(static_cast<ID>(4)), cen::exception);

  ASSERT_EQ("None", ToString(ID::None));
  ASSERT_EQ("Orientation", ToString(ID::Orientation));
  ASSERT_EQ("Connected", ToString(ID::Connected));
  ASSERT_EQ("Disconnected", ToString(ID::Disconnected));

  std::clog << "Display event ID example: " << ID::Connected << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)