#include <gtest/gtest.h>

#include <memory>  // unique_ptr

#include "centurion/render.hpp"
#include "centurion/window.hpp"

class TextureHandleTest : public testing::Test {
 protected:
  static void SetUpTestSuite()
  {
    constexpr auto path = "resources/panda.png";
    window = std::make_unique<cen::window>();
    renderer = std::make_unique<cen::renderer>(window->create_renderer());
    texture = std::make_unique<cen::texture>(renderer->make_texture(path));
  }

  static void TearDownTestSuite()
  {
    texture.reset();
    renderer.reset();
    window.reset();
  }

  inline static std::unique_ptr<cen::window> window;
  inline static std::unique_ptr<cen::renderer> renderer;
  inline static std::unique_ptr<cen::texture> texture;
};

TEST_F(TextureHandleTest, FromTexture)
{
  cen::texture_handle handle{*texture};
  ASSERT_TRUE(handle);
  ASSERT_TRUE(handle.get());
}

TEST_F(TextureHandleTest, FromRawPointer)
{
  cen::texture_handle bad{nullptr};
  ASSERT_FALSE(bad);
  ASSERT_FALSE(bad.get());

  cen::texture_handle good{texture->get()};
  ASSERT_TRUE(good);
  ASSERT_TRUE(good.get());
}
