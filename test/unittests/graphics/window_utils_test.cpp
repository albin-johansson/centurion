#include "window_utils.hpp"

#include <gtest/gtest.h>

#include <memory>  // unique_ptr

class WindowUtilsTest : public testing::Test
{
 protected:
  static void SetUpTestSuite()
  {
    m_window = std::make_unique<cen::window>();
  }

  static void TearDownTestSuite()
  {
    m_window.reset();
  }

  inline static std::unique_ptr<cen::window> m_window;
};

TEST_F(WindowUtilsTest, GetWindowFromId)
{
  EXPECT_FALSE(cen::get_window_from_id(0));
  EXPECT_EQ(m_window->get(), cen::get_window_from_id(m_window->id()).get());
}

TEST_F(WindowUtilsTest, MouseFocusWindow)
{

}