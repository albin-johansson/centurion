#include "renderer.hpp"

#include <fff.h>
#include <gtest/gtest.h>

// clang-format off
extern "C" {
FAKE_VALUE_FUNC(int, SDL_RenderClear, SDL_Renderer*)
FAKE_VALUE_FUNC(int, SDL_SetRenderDrawColor, SDL_Renderer*, Uint8, Uint8, Uint8, Uint8)
FAKE_VALUE_FUNC(int, SDL_GetRenderDrawColor, SDL_Renderer*, Uint8*, Uint8*, Uint8*, Uint8*)
FAKE_VOID_FUNC(SDL_RenderPresent, SDL_Renderer*)
FAKE_VALUE_FUNC(int, SDL_RenderDrawRect, SDL_Renderer*, const SDL_Rect*)
FAKE_VALUE_FUNC(int, SDL_RenderDrawRectF, SDL_Renderer*, const SDL_FRect*)
}
// clang-format on

class RendererTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(SDL_RenderClear);
    RESET_FAKE(SDL_SetRenderDrawColor);
    RESET_FAKE(SDL_GetRenderDrawColor);
    RESET_FAKE(SDL_RenderPresent);
    RESET_FAKE(SDL_RenderDrawRect);
    RESET_FAKE(SDL_RenderDrawRectF);
  }

  cen::renderer_handle m_renderer{nullptr};
};

TEST_F(RendererTest, Clear)
{
  m_renderer.clear();
  EXPECT_EQ(1, SDL_RenderClear_fake.call_count);
}

TEST_F(RendererTest, ClearWith)
{
  m_renderer.clear_with(cen::color{0xAA, 0xBB, 0xCC, 0xDD});

  EXPECT_EQ(1, SDL_GetRenderDrawColor_fake.call_count);
  EXPECT_EQ(2, SDL_SetRenderDrawColor_fake.call_count);
  EXPECT_EQ(1, SDL_RenderClear_fake.call_count);

  EXPECT_EQ(0xAA, SDL_SetRenderDrawColor_fake.arg1_history[0]);
  EXPECT_EQ(0xBB, SDL_SetRenderDrawColor_fake.arg2_history[0]);
  EXPECT_EQ(0xCC, SDL_SetRenderDrawColor_fake.arg3_history[0]);
  EXPECT_EQ(0xDD, SDL_SetRenderDrawColor_fake.arg4_history[0]);
}

TEST_F(RendererTest, Present)
{
  m_renderer.present();
  EXPECT_EQ(1, SDL_RenderPresent_fake.call_count);
}

TEST_F(RendererTest, DrawRect)
{
  constexpr cen::irect irect;
  m_renderer.draw_rect(irect);
  EXPECT_EQ(1, SDL_RenderDrawRect_fake.call_count);
  EXPECT_EQ(0, SDL_RenderDrawRectF_fake.call_count);

  constexpr cen::frect frect;
  m_renderer.draw_rect(frect);
  EXPECT_EQ(1, SDL_RenderDrawRect_fake.call_count);
  EXPECT_EQ(1, SDL_RenderDrawRectF_fake.call_count);
}