#include <gtest/gtest.h>

#include <memory>  // unique_ptr

#include "render.hpp"
#include "video/window.hpp"

class TextureHandleTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    constexpr auto path = "resources/panda.png";
    window = std::make_unique<cen::Window>();
    renderer = std::make_unique<cen::Renderer>(*window);
    texture = std::make_unique<cen::Texture>(*renderer, path);
  }

  static void TearDownTestSuite()
  {
    texture.reset();
    renderer.reset();
    window.reset();
  }

  inline static std::unique_ptr<cen::Window> window;
  inline static std::unique_ptr<cen::Renderer> renderer;
  inline static std::unique_ptr<cen::Texture> texture;
};

TEST_F(TextureHandleTest, FromTexture)
{
  cen::TextureHandle handle{*texture};
  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST_F(TextureHandleTest, FromRawPointer)
{
  cen::TextureHandle bad{nullptr};
  ASSERT_FALSE(bad);
  ASSERT_FALSE(bad.get());

  cen::TextureHandle good{texture->get()};
  ASSERT_TRUE(good);
  ASSERT_TRUE(good.get());
}
