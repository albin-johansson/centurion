#include <gtest/gtest.h>

#include <iostream>  // cout

#include "window_events.hpp"

using id = cen::window_event_id;

TEST(WindowEventID, Values)
{
  ASSERT_EQ(SDL_WINDOWEVENT_NONE, to_underlying(id::none));
  ASSERT_EQ(SDL_WINDOWEVENT_SHOWN, to_underlying(id::shown));
  ASSERT_EQ(SDL_WINDOWEVENT_HIDDEN, to_underlying(id::hidden));
  ASSERT_EQ(SDL_WINDOWEVENT_EXPOSED, to_underlying(id::exposed));
  ASSERT_EQ(SDL_WINDOWEVENT_MOVED, to_underlying(id::moved));
  ASSERT_EQ(SDL_WINDOWEVENT_RESIZED, to_underlying(id::resized));
  ASSERT_EQ(SDL_WINDOWEVENT_SIZE_CHANGED, to_underlying(id::size_changed));
  ASSERT_EQ(SDL_WINDOWEVENT_MINIMIZED, to_underlying(id::minimized));
  ASSERT_EQ(SDL_WINDOWEVENT_MAXIMIZED, to_underlying(id::maximized));
  ASSERT_EQ(SDL_WINDOWEVENT_RESTORED, to_underlying(id::restored));
  ASSERT_EQ(SDL_WINDOWEVENT_ENTER, to_underlying(id::enter));
  ASSERT_EQ(SDL_WINDOWEVENT_LEAVE, to_underlying(id::leave));
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_GAINED, to_underlying(id::focus_gained));
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_LOST, to_underlying(id::focus_lost));
  ASSERT_EQ(SDL_WINDOWEVENT_CLOSE, to_underlying(id::close));
  ASSERT_EQ(SDL_WINDOWEVENT_TAKE_FOCUS, to_underlying(id::take_focus));
  ASSERT_EQ(SDL_WINDOWEVENT_HIT_TEST, to_underlying(id::hit_test));
}

TEST(WindowEventID, ToString)
{
  ASSERT_THROW(to_string(static_cast<id>(100)), cen::exception);

  ASSERT_EQ("none", to_string(id::none));
  ASSERT_EQ("shown", to_string(id::shown));
  ASSERT_EQ("hidden", to_string(id::hidden));
  ASSERT_EQ("exposed", to_string(id::exposed));
  ASSERT_EQ("moved", to_string(id::moved));
  ASSERT_EQ("resized", to_string(id::resized));
  ASSERT_EQ("size_changed", to_string(id::size_changed));
  ASSERT_EQ("minimized", to_string(id::minimized));
  ASSERT_EQ("maximized", to_string(id::maximized));
  ASSERT_EQ("restored", to_string(id::restored));
  ASSERT_EQ("enter", to_string(id::enter));
  ASSERT_EQ("leave", to_string(id::leave));
  ASSERT_EQ("focus_gained", to_string(id::focus_gained));
  ASSERT_EQ("focus_lost", to_string(id::focus_lost));
  ASSERT_EQ("close", to_string(id::close));
  ASSERT_EQ("take_focus", to_string(id::take_focus));
  ASSERT_EQ("hit_test", to_string(id::hit_test));

  std::cout << "window_event_id::resized == " << id::resized << '\n';
}
