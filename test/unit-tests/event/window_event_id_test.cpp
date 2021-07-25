#include <gtest/gtest.h>

#include <iostream>  // cout

#include "events/event.hpp"

using id = cen::window_event_id;

TEST(WindowEventID, EqualityOperator)
{
  ASSERT_EQ(id::none, SDL_WINDOWEVENT_NONE);
  ASSERT_EQ(id::shown, SDL_WINDOWEVENT_SHOWN);
  ASSERT_EQ(id::hidden, SDL_WINDOWEVENT_HIDDEN);
  ASSERT_EQ(id::exposed, SDL_WINDOWEVENT_EXPOSED);
  ASSERT_EQ(id::moved, SDL_WINDOWEVENT_MOVED);
  ASSERT_EQ(id::resized, SDL_WINDOWEVENT_RESIZED);
  ASSERT_EQ(id::size_changed, SDL_WINDOWEVENT_SIZE_CHANGED);
  ASSERT_EQ(id::minimized, SDL_WINDOWEVENT_MINIMIZED);
  ASSERT_EQ(id::maximized, SDL_WINDOWEVENT_MAXIMIZED);
  ASSERT_EQ(id::restored, SDL_WINDOWEVENT_RESTORED);
  ASSERT_EQ(id::enter, SDL_WINDOWEVENT_ENTER);
  ASSERT_EQ(id::leave, SDL_WINDOWEVENT_LEAVE);
  ASSERT_EQ(id::focus_gained, SDL_WINDOWEVENT_FOCUS_GAINED);
  ASSERT_EQ(id::focus_lost, SDL_WINDOWEVENT_FOCUS_LOST);
  ASSERT_EQ(id::close, SDL_WINDOWEVENT_CLOSE);
  ASSERT_EQ(id::take_focus, SDL_WINDOWEVENT_TAKE_FOCUS);
  ASSERT_EQ(id::hit_test, SDL_WINDOWEVENT_HIT_TEST);

  ASSERT_EQ(SDL_WINDOWEVENT_NONE, id::none);
  ASSERT_EQ(SDL_WINDOWEVENT_SHOWN, id::shown);
  ASSERT_EQ(SDL_WINDOWEVENT_HIDDEN, id::hidden);
  ASSERT_EQ(SDL_WINDOWEVENT_EXPOSED, id::exposed);
  ASSERT_EQ(SDL_WINDOWEVENT_MOVED, id::moved);
  ASSERT_EQ(SDL_WINDOWEVENT_RESIZED, id::resized);
  ASSERT_EQ(SDL_WINDOWEVENT_SIZE_CHANGED, id::size_changed);
  ASSERT_EQ(SDL_WINDOWEVENT_MINIMIZED, id::minimized);
  ASSERT_EQ(SDL_WINDOWEVENT_MAXIMIZED, id::maximized);
  ASSERT_EQ(SDL_WINDOWEVENT_RESTORED, id::restored);
  ASSERT_EQ(SDL_WINDOWEVENT_ENTER, id::enter);
  ASSERT_EQ(SDL_WINDOWEVENT_LEAVE, id::leave);
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_GAINED, id::focus_gained);
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_LOST, id::focus_lost);
  ASSERT_EQ(SDL_WINDOWEVENT_CLOSE, id::close);
  ASSERT_EQ(SDL_WINDOWEVENT_TAKE_FOCUS, id::take_focus);
  ASSERT_EQ(SDL_WINDOWEVENT_HIT_TEST, id::hit_test);
}

TEST(WindowEventID, InequalityOperator)
{
  ASSERT_NE(id::resized, SDL_WINDOWEVENT_FOCUS_GAINED);
  ASSERT_FALSE(id::leave != SDL_WINDOWEVENT_LEAVE);

  ASSERT_NE(SDL_WINDOWEVENT_MINIMIZED, id::moved);
  ASSERT_FALSE(SDL_WINDOWEVENT_RESTORED != id::restored);
}

TEST(WindowEventID, ToString)
{
  ASSERT_THROW(cen::to_string(static_cast<cen::window_event_id>(18)), cen::cen_error);

  ASSERT_EQ("none", cen::to_string(id::none));
  ASSERT_EQ("shown", cen::to_string(id::shown));
  ASSERT_EQ("hidden", cen::to_string(id::hidden));
  ASSERT_EQ("exposed", cen::to_string(id::exposed));
  ASSERT_EQ("moved", cen::to_string(id::moved));
  ASSERT_EQ("resized", cen::to_string(id::resized));
  ASSERT_EQ("size_changed", cen::to_string(id::size_changed));
  ASSERT_EQ("minimized", cen::to_string(id::minimized));
  ASSERT_EQ("maximized", cen::to_string(id::maximized));
  ASSERT_EQ("restored", cen::to_string(id::restored));
  ASSERT_EQ("enter", cen::to_string(id::enter));
  ASSERT_EQ("leave", cen::to_string(id::leave));
  ASSERT_EQ("focus_gained", cen::to_string(id::focus_gained));
  ASSERT_EQ("focus_lost", cen::to_string(id::focus_lost));
  ASSERT_EQ("close", cen::to_string(id::close));
  ASSERT_EQ("take_focus", cen::to_string(id::take_focus));
  ASSERT_EQ("hit_test", cen::to_string(id::hit_test));

  std::cout << "Window event ID example: " << id::resized << '\n';
}
