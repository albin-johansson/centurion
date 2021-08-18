#include "events/display_event_id.hpp"

#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/to_underlying.hpp"

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST(DisplayEventId, Values)
{
  ASSERT_EQ(4, cen::display_event_id_count());

  ASSERT_EQ(cen::to_underlying(cen::display_event_id::none), SDL_DISPLAYEVENT_NONE);
  ASSERT_EQ(cen::to_underlying(cen::display_event_id::orientation),
            SDL_DISPLAYEVENT_ORIENTATION);
  ASSERT_EQ(cen::to_underlying(cen::display_event_id::connected),
            SDL_DISPLAYEVENT_CONNECTED);
  ASSERT_EQ(cen::to_underlying(cen::display_event_id::disconnected),
            SDL_DISPLAYEVENT_DISCONNECTED);
}

TEST(DisplayEventId, ToString)
{
  const auto invalid = static_cast<cen::display_event_id>(cen::display_event_id_count());
  ASSERT_THROW(cen::to_string(invalid), cen::cen_error);

  ASSERT_EQ("none", cen::to_string(cen::display_event_id::none));
  ASSERT_EQ("orientation", cen::to_string(cen::display_event_id::orientation));
  ASSERT_EQ("connected", cen::to_string(cen::display_event_id::connected));
  ASSERT_EQ("disconnected", cen::to_string(cen::display_event_id::disconnected));

  std::clog << "Display event ID example: " << cen::display_event_id::connected << '\n';
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)