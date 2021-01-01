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
FAKE_VALUE_FUNC(int, SDL_RenderFillRect, SDL_Renderer*, const SDL_Rect*)
FAKE_VALUE_FUNC(int, SDL_RenderFillRectF, SDL_Renderer*, const SDL_FRect*)
FAKE_VALUE_FUNC(int, SDL_GetRendererOutputSize, SDL_Renderer*, int*, int*)
FAKE_VALUE_FUNC(int, SDL_RenderDrawLine, SDL_Renderer*, int, int, int, int)
FAKE_VALUE_FUNC(int, SDL_RenderDrawLineF, SDL_Renderer*, float, float, float, float)
FAKE_VALUE_FUNC(int, SDL_RenderDrawLines, SDL_Renderer*, const SDL_Point*, int)
FAKE_VALUE_FUNC(int, SDL_RenderDrawLinesF, SDL_Renderer*, const SDL_FPoint*, int)
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
    RESET_FAKE(SDL_RenderFillRect);
    RESET_FAKE(SDL_RenderFillRectF);
    RESET_FAKE(SDL_GetRendererOutputSize);
    RESET_FAKE(SDL_RenderDrawLine);
    RESET_FAKE(SDL_RenderDrawLineF);
    RESET_FAKE(SDL_RenderDrawLines);
    RESET_FAKE(SDL_RenderDrawLinesF);
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

TEST_F(RendererTest, FillRect)
{
  constexpr cen::irect irect;
  m_renderer.fill_rect(irect);
  EXPECT_EQ(1, SDL_RenderFillRect_fake.call_count);
  EXPECT_EQ(0, SDL_RenderFillRectF_fake.call_count);

  constexpr cen::frect frect;
  m_renderer.fill_rect(frect);
  EXPECT_EQ(1, SDL_RenderFillRect_fake.call_count);
  EXPECT_EQ(1, SDL_RenderFillRectF_fake.call_count);
}

TEST_F(RendererTest, Fill)
{
  m_renderer.fill();
  EXPECT_EQ(1, SDL_GetRendererOutputSize_fake.call_count);
  EXPECT_EQ(1, SDL_RenderFillRect_fake.call_count);
}

TEST_F(RendererTest, FillWith)
{
  m_renderer.fill_with(cen::color{0xAA, 0xBB, 0xCC, 0xDD});
  EXPECT_EQ(1, SDL_GetRenderDrawColor_fake.call_count);
  EXPECT_EQ(2, SDL_SetRenderDrawColor_fake.call_count);
  EXPECT_EQ(1, SDL_GetRendererOutputSize_fake.call_count);
  EXPECT_EQ(1, SDL_RenderFillRect_fake.call_count);

  EXPECT_EQ(0xAA, SDL_SetRenderDrawColor_fake.arg1_history[0]);
  EXPECT_EQ(0xBB, SDL_SetRenderDrawColor_fake.arg2_history[0]);
  EXPECT_EQ(0xCC, SDL_SetRenderDrawColor_fake.arg3_history[0]);
  EXPECT_EQ(0xDD, SDL_SetRenderDrawColor_fake.arg4_history[0]);
}

TEST_F(RendererTest, DrawLine)
{
  {
    const cen::ipoint start{12, 34};
    const cen::ipoint end{56, 78};
    m_renderer.draw_line(start, end);
    EXPECT_EQ(1, SDL_RenderDrawLine_fake.call_count);
    EXPECT_EQ(0, SDL_RenderDrawLineF_fake.call_count);

    EXPECT_EQ(start.x(), SDL_RenderDrawLine_fake.arg1_val);
    EXPECT_EQ(start.y(), SDL_RenderDrawLine_fake.arg2_val);
    EXPECT_EQ(end.x(), SDL_RenderDrawLine_fake.arg3_val);
    EXPECT_EQ(end.y(), SDL_RenderDrawLine_fake.arg4_val);
  }

  {
    const cen::fpoint start{12, 34};
    const cen::fpoint end{56, 78};
    m_renderer.draw_line(start, end);
    EXPECT_EQ(1, SDL_RenderDrawLine_fake.call_count);
    EXPECT_EQ(1, SDL_RenderDrawLineF_fake.call_count);

    EXPECT_EQ(start.x(), SDL_RenderDrawLineF_fake.arg1_val);
    EXPECT_EQ(start.y(), SDL_RenderDrawLineF_fake.arg2_val);
    EXPECT_EQ(end.x(), SDL_RenderDrawLineF_fake.arg3_val);
    EXPECT_EQ(end.y(), SDL_RenderDrawLineF_fake.arg4_val);
  }
}

TEST_F(RendererTest, DrawLines)
{
  {
    std::array<cen::ipoint, 3> points{{{11, 22}, {33, 44}, {55, 66}}};
    m_renderer.draw_lines(points);
    EXPECT_EQ(1, SDL_RenderDrawLines_fake.call_count);
    EXPECT_EQ(0, SDL_RenderDrawLinesF_fake.call_count);

    for (auto i = 0; i < points.size(); ++i) {
      EXPECT_EQ(points.at(i).x(), SDL_RenderDrawLines_fake.arg1_val[i].x);
      EXPECT_EQ(points.at(i).y(), SDL_RenderDrawLines_fake.arg1_val[i].y);
    }
  }

  {
    std::array<cen::fpoint, 3> points{{{11, 22}, {33, 44}, {55, 66}}};
    m_renderer.draw_lines(points);
    EXPECT_EQ(1, SDL_RenderDrawLines_fake.call_count);
    EXPECT_EQ(1, SDL_RenderDrawLinesF_fake.call_count);

    for (auto i = 0; i < points.size(); ++i) {
      EXPECT_EQ(points.at(i).x(), SDL_RenderDrawLinesF_fake.arg1_val[i].x);
      EXPECT_EQ(points.at(i).y(), SDL_RenderDrawLinesF_fake.arg1_val[i].y);
    }
  }
}