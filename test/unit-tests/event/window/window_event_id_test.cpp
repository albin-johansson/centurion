#include <gtest/gtest.h>

#include <iostream>  // clog

#include "event.hpp"

using ID = cen::WindowEventID;

TEST(WindowEventID, Values)
{
  ASSERT_EQ(SDL_WINDOWEVENT_NONE, to_underlying(ID::None));
  ASSERT_EQ(SDL_WINDOWEVENT_SHOWN, to_underlying(ID::Shown));
  ASSERT_EQ(SDL_WINDOWEVENT_HIDDEN, to_underlying(ID::Hidden));
  ASSERT_EQ(SDL_WINDOWEVENT_EXPOSED, to_underlying(ID::Exposed));
  ASSERT_EQ(SDL_WINDOWEVENT_MOVED, to_underlying(ID::Moved));
  ASSERT_EQ(SDL_WINDOWEVENT_RESIZED, to_underlying(ID::Resized));
  ASSERT_EQ(SDL_WINDOWEVENT_SIZE_CHANGED, to_underlying(ID::SizeChanged));
  ASSERT_EQ(SDL_WINDOWEVENT_MINIMIZED, to_underlying(ID::Minimized));
  ASSERT_EQ(SDL_WINDOWEVENT_MAXIMIZED, to_underlying(ID::Maximized));
  ASSERT_EQ(SDL_WINDOWEVENT_RESTORED, to_underlying(ID::Restored));
  ASSERT_EQ(SDL_WINDOWEVENT_ENTER, to_underlying(ID::Enter));
  ASSERT_EQ(SDL_WINDOWEVENT_LEAVE, to_underlying(ID::Leave));
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_GAINED, to_underlying(ID::FocusGained));
  ASSERT_EQ(SDL_WINDOWEVENT_FOCUS_LOST, to_underlying(ID::FocusLost));
  ASSERT_EQ(SDL_WINDOWEVENT_CLOSE, to_underlying(ID::Close));
  ASSERT_EQ(SDL_WINDOWEVENT_TAKE_FOCUS, to_underlying(ID::TakeFocus));
  ASSERT_EQ(SDL_WINDOWEVENT_HIT_TEST, to_underlying(ID::HitTest));
}

TEST(WindowEventID, ToString)
{
  ASSERT_THROW(ToString(static_cast<ID>(18)), cen::exception);

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
