#include <gtest/gtest.h>

#include <iostream>  // clog

#include "event.hpp"

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
  ASSERT_THROW(ToString(static_cast<ID>(18)), cen::Error);

  ASSERT_EQ("None", ToString(ID::None));
  ASSERT_EQ("Shown", ToString(ID::Shown));
  ASSERT_EQ("Hidden", ToString(ID::Hidden));
  ASSERT_EQ("Exposed", ToString(ID::Exposed));
  ASSERT_EQ("Moved", ToString(ID::Moved));
  ASSERT_EQ("Resized", ToString(ID::Resized));
  ASSERT_EQ("SizeChanged", ToString(ID::SizeChanged));
  ASSERT_EQ("Minimized", ToString(ID::Minimized));
  ASSERT_EQ("Maximized", ToString(ID::Maximized));
  ASSERT_EQ("Restored", ToString(ID::Restored));
  ASSERT_EQ("Enter", ToString(ID::Enter));
  ASSERT_EQ("Leave", ToString(ID::Leave));
  ASSERT_EQ("FocusGained", ToString(ID::FocusGained));
  ASSERT_EQ("FocusLost", ToString(ID::FocusLost));
  ASSERT_EQ("Close", ToString(ID::Close));
  ASSERT_EQ("TakeFocus", ToString(ID::TakeFocus));
  ASSERT_EQ("HitTest", ToString(ID::HitTest));

  std::clog << "Window event ID example: " << ID::Resized << '\n';
}
