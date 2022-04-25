#include <gtest/gtest.h>

#include <iostream>  // cout

#include "centurion/window.hpp"

TEST(WindowHandle, PointerConstructor)
{
  {  // From null pointer
    cen::window_handle handle{nullptr};
    ASSERT_FALSE(handle);
    ASSERT_FALSE(handle.get());
  }

  {  // From valid pointer
    cen::window window;
    cen::window_handle handle{window.get()};
    ASSERT_TRUE(handle);
    ASSERT_TRUE(handle.get());
  }
}

TEST(WindowHandle, FromWindowRef)
{
  cen::window window;
  cen::window_handle handle{window};
  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST(WindowHandle, StreamOperator)
{
  cen::window window;
  cen::window_handle handle{window};

  std::cout << handle << '\n';
}