#include <gtest/gtest.h>

#include <iostream>  // cout
#include <memory>    // unique_ptr

#include "core/log.hpp"
#include "video/renderer.hpp"
#include "video/window.hpp"

class RendererHandleTest : public testing::Test
{
 protected:
  [[maybe_unused]] static void SetUpTestSuite()
  {
    m_window = std::make_unique<cen::window>();
    m_renderer = std::make_unique<cen::renderer>(*m_window);
  }

  [[maybe_unused]] static void TearDownTestSuite()
  {
    m_renderer.reset();
    m_window.reset();
  }

  inline static std::unique_ptr<cen::window> m_window;
  inline static std::unique_ptr<cen::renderer> m_renderer;
};

TEST_F(RendererHandleTest, RawPointerConstructor)
{
  {  // Null pointer
    cen::renderer_handle handle{nullptr};
    ASSERT_FALSE(handle);
    ASSERT_FALSE(handle.get());
  }

  {  // Valid pointer
    const cen::renderer_handle handle{m_renderer->get()};

    ASSERT_TRUE(handle);
    ASSERT_TRUE(handle.get());
  }
}

TEST_F(RendererHandleTest, FromOwningRenderer)
{
  const cen::renderer_handle handle{*m_renderer};

  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST_F(RendererHandleTest, ToStringAndStreamOperator)
{
  const cen::renderer_handle handle{*m_renderer};

  std::cout << "COUT: " << handle << '\n';
  cen::log::put(cen::to_string(handle));
}
