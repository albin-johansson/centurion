#include <gtest/gtest.h>

#include <iostream>  // clog

#include "core/logging.hpp"
#include "window.hpp"

TEST(WindowHandle, PointerConstructor)
{
  {  // From null pointer
    cen::WindowHandle handle{nullptr};
    ASSERT_FALSE(handle);
    ASSERT_FALSE(handle.get());
  }

  {  // From valid pointer
    cen::Window window;
    cen::WindowHandle handle{window.get()};
    ASSERT_TRUE(handle);
    ASSERT_TRUE(handle.get());
  }
}

TEST(WindowHandle, FromWindowRef)
{
  cen::Window window;
  cen::WindowHandle handle{window};
  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST(WindowHandle, ToString)
{
  cen::Window window;
  cen::WindowHandle handle{window};

  cen::log_info_raw(cen::ToString(handle));
}

TEST(WindowHandle, StreamOperator)
{
  cen::Window window;
  cen::WindowHandle handle{window};

  std::clog << handle << '\n';
}