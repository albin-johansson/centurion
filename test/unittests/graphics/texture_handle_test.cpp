#include <gtest/gtest.h>

#include <memory>  // unique_ptr

#include "renderer.hpp"
#include "texture.hpp"
#include "window.hpp"

class TextureHandleTest : public testing::Test
{
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
  EXPECT_TRUE(handle);
  EXPECT_TRUE(handle.get());
}

TEST_F(TextureHandleTest, FromRawPointer)
{
  cen::texture_handle bad{nullptr};
  EXPECT_FALSE(bad);
  EXPECT_FALSE(bad.get());

  cen::texture_handle good{m_texture->get()};
  EXPECT_TRUE(good);
  EXPECT_TRUE(good.get());
}
