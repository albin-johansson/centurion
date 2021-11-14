#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/logging.hpp"
#include "video/window.hpp"

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

TEST(WindowHandle, ToString)
{
  cen::window window;
  cen::window_handle handle{window};

  cen::log_info_raw(cen::to_string(handle));
}

TEST(WindowHandle, StreamOperator)
{
  cen::window window;
  cen::window_handle handle{window};

  std::clog << handle << '\n';
}