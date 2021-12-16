#include <gtest/gtest.h>

#include <iostream>  // clog
#include <memory>    // unique_ptr

#include "core/logging.hpp"
#include "render.hpp"
#include "video/window.hpp"

class RendererHandleTest : public testing::Test {
 protected:
  [[maybe_unused]] static void SetUpTestSuite()
  {
    window = std::make_unique<cen::Window>();
    renderer = std::make_unique<cen::Renderer>(*window);
  }

  [[maybe_unused]] static void TearDownTestSuite()
  {
    renderer.reset();
    window.reset();
  }

  inline static std::unique_ptr<cen::Window> window;
  inline static std::unique_ptr<cen::Renderer> renderer;
};

TEST_F(RendererHandleTest, RawPointerConstructor)
{
  {  // Null pointer
    cen::RendererHandle handle{nullptr};
    ASSERT_FALSE(handle);
    ASSERT_FALSE(handle.get());
  }

  {  // Valid pointer
    const cen::RendererHandle handle{renderer->get()};

    ASSERT_TRUE(handle);
    ASSERT_TRUE(handle.get());
  }
}

TEST_F(RendererHandleTest, FromOwningRenderer)
{
  const cen::RendererHandle handle{*renderer};

  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST_F(RendererHandleTest, ToStringAndStreamOperator)
{
  const cen::RendererHandle handle{*renderer};

  std::clog << handle << '\n';
  cen::log_info_raw(cen::to_string(handle));
}
