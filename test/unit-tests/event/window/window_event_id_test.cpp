#include <gtest/gtest.h>

#include <iostream>  // clog

#include "events/event.hpp"

using ID = cen::WindowEventID;

TEST(WindowEventID, Values)
{
  ASSERT_EQ(SDL_WINDOWEVENT_NONE, ToUnderlying(ID::None));
  ASSERT_EQ(SDL_WINDOWEVENT_SHOWN, ToUnderlying(ID::Shown));
  ASSERT_EQ(SDL_WINDOWEVENT_HIDDEN, ToUnderlying(ID::Hidden));
  ASSERT_EQ(SDL_WINDOWEVENT_EXPOSED, ToUnderlying(ID::Exposed));
  ASSERT_EQ(SDL_WINDOWEVENT_MOVED, ToUnderlying(ID::Moved));
  ASSERT_EQ(SDL_WINDOWEVENT_RESIZED, ToUnderlying(ID::Resized));
  ASSERT_EQ(SDL_WINDOWEVENT_SIZE_CHANGED, ToUnderlying(ID::SizeChanged));
  ASSERT_EQ(SDL_WINDOWEVENT_MINIMIZED, ToUnderlying(ID::Minimized));
  ASSERT_EQ(SDL_WINDOWEVENT_MAXIMIZED, ToUnderlying(ID::Maximized));
  ASSERT_EQ(SDL_WINDOWEVENT_RESTORED, ToUnderlying(ID::Restored));
  ASSERT_EQ(SDL_WINDOWEVENT_ENTER, ToUnderlying(ID::Enter));
  ASSERT_EQ(SDL_WINDOWEVENT_LEAVE, ToUnderlying(ID::Leave));
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_GAINED, ToUnderlying(ID::FocusGained));
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_LOST, ToUnderlying(ID::FocusLost));
  ASSERT_EQ(SDL_WINDOWEVENT_CLOSE, ToUnderlying(ID::Close));
  ASSERT_EQ(SDL_WINDOWEVENT_TAKE_FOCUS, ToUnderlying(ID::TakeFocus));
  ASSERT_EQ(SDL_WINDOWEVENT_HIT_TEST, ToUnderlying(ID::HitTest));
}

TEST(WindowEventID, ToString)
{
  ASSERT_THROW(to_string(static_cast<ID>(18)), cen::Error);

  ASSERT_EQ("None", to_string(ID::None));
  ASSERT_EQ("Shown", to_string(ID::Shown));
  ASSERT_EQ("Hidden", to_string(ID::Hidden));
  ASSERT_EQ("Exposed", to_string(ID::Exposed));
  ASSERT_EQ("Moved", to_string(ID::Moved));
  ASSERT_EQ("Resized", to_string(ID::Resized));
  ASSERT_EQ("SizeChanged", to_string(ID::SizeChanged));
  ASSERT_EQ("Minimized", to_string(ID::Minimized));
  ASSERT_EQ("Maximized", to_string(ID::Maximized));
  ASSERT_EQ("Restored", to_string(ID::Restored));
  ASSERT_EQ("Enter", to_string(ID::Enter));
  ASSERT_EQ("Leave", to_string(ID::Leave));
  ASSERT_EQ("FocusGained", to_string(ID::FocusGained));
  ASSERT_EQ("FocusLost", to_string(ID::FocusLost));
  ASSERT_EQ("Close", to_string(ID::Close));
  ASSERT_EQ("TakeFocus", to_string(ID::TakeFocus));
  ASSERT_EQ("HitTest", to_string(ID::HitTest));

  std::clog << "Window event ID example: " << ID::Resized << '\n';
}
