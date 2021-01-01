#include "renderer.hpp"

#include <fff.h>
#include <gtest/gtest.h>

// clang-format off
extern "C" {
FAKE_VALUE_FUNC(int, SDL_RenderClear, SDL_Renderer*)
FAKE_VOID_FUNC(SDL_RenderPresent, SDL_Renderer*)
}
// clang-format on

class RendererTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(SDL_RenderClear);
    RESET_FAKE(SDL_RenderPresent);
  }

  cen::renderer_handle m_renderer{nullptr};
};

TEST_F(RendererTest, Clear)
{
  m_renderer.clear();
  EXPECT_EQ(1, SDL_RenderClear_fake.call_count);
}

TEST_F(RendererTest, Present)
{
  m_renderer.present();
  EXPECT_EQ(1, SDL_RenderPresent_fake.call_count);
}