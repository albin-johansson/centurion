#include <gtest/gtest.h>

#include <memory>  // unique_ptr

#include "video/renderer.hpp"
#include "video/texture.hpp"
#include "video/window.hpp"

class TextureHandleTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    constexpr auto path = "resources/panda.png";
    m_window = std::make_unique<cen::window>();
    m_renderer = std::make_unique<cen::renderer>(*m_window);
    m_texture = std::make_unique<cen::texture>(*m_renderer, path);
  }

  static void TearDownTestSuite()
  {
    m_texture.reset();
    m_renderer.reset();
    m_window.reset();
  }

  inline static std::unique_ptr<cen::window> m_window;
  inline static std::unique_ptr<cen::renderer> m_renderer;
  inline static std::unique_ptr<cen::texture> m_texture;
};

TEST_F(TextureHandleTest, FromTexture)
{
  cen::texture_handle handle{*m_texture};
  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST_F(TextureHandleTest, FromRawPointer)
{
  cen::texture_handle bad{nullptr};
  ASSERT_FALSE(bad);
  ASSERT_FALSE(bad.get());

  cen::texture_handle good{m_texture->get()};
  ASSERT_TRUE(good);
  ASSERT_TRUE(good.get());
}
