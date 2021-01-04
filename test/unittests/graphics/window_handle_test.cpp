#include <gtest/gtest.h>

#include <iostream>  // cout

#include "log.hpp"
#include "window.hpp"

TEST(WindowHandle, PointerConstructor)
{
  {  // From null pointer
    cen::window_handle handle{nullptr};
    EXPECT_FALSE(handle);
    EXPECT_FALSE(handle.get());
  }

  {  // From valid pointer
    cen::window window;
    cen::window_handle handle{window.get()};
    EXPECT_TRUE(handle);
    EXPECT_TRUE(handle.get());
  }
}

TEST(WindowHandle, FromWindowRef)
{
  cen::window window;
  cen::window_handle handle{window};
  EXPECT_TRUE(handle);
  EXPECT_TRUE(handle.get());
}

TEST(WindowHandle, ToString)
{
  cen::window window;
  cen::window_handle handle{window};

  cen::log::put(cen::to_string(handle));
}

TEST(WindowHandle, StreamOperator)
{
  cen::window window;
  cen::window_handle handle{window};

  std::cout << "COUT: " << handle << '\n';
}