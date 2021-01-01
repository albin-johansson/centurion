#include "renderer.hpp"

#include <fff.h>
#include <gtest/gtest.h>

#include <array>        // array
#include <tuple>        // tuple, make_tuple
#include <type_traits>  // is_same_v

// clang-format off
extern "C" {
FAKE_VOID_FUNC(SDL_RenderPresent, SDL_Renderer*)
FAKE_VALUE_FUNC(int, SDL_RenderClear, SDL_Renderer*)
FAKE_VALUE_FUNC(int, SDL_SetRenderDrawColor, SDL_Renderer*, Uint8, Uint8, Uint8, Uint8)
FAKE_VALUE_FUNC(int, SDL_GetRenderDrawColor, SDL_Renderer*, Uint8*, Uint8*, Uint8*, Uint8*)
FAKE_VALUE_FUNC(int, SDL_RenderDrawRect, SDL_Renderer*, const SDL_Rect*)
FAKE_VALUE_FUNC(int, SDL_RenderDrawRectF, SDL_Renderer*, const SDL_FRect*)
FAKE_VALUE_FUNC(int, SDL_RenderFillRect, SDL_Renderer*, const SDL_Rect*)
FAKE_VALUE_FUNC(int, SDL_RenderFillRectF, SDL_Renderer*, const SDL_FRect*)
FAKE_VALUE_FUNC(int, SDL_GetRendererOutputSize, SDL_Renderer*, int*, int*)
FAKE_VALUE_FUNC(int, SDL_RenderDrawLine, SDL_Renderer*, int, int, int, int)
FAKE_VALUE_FUNC(int, SDL_RenderDrawLineF, SDL_Renderer*, float, float, float, float)
FAKE_VALUE_FUNC(int, SDL_RenderDrawLines, SDL_Renderer*, const SDL_Point*, int)
FAKE_VALUE_FUNC(int, SDL_RenderDrawLinesF, SDL_Renderer*, const SDL_FPoint*, int)
FAKE_VALUE_FUNC(int, SDL_RenderCopy, SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_Rect*)
FAKE_VALUE_FUNC(int, SDL_RenderCopyF, SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_FRect*)
FAKE_VALUE_FUNC(int, SDL_RenderCopyEx, SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_Rect*, double, const SDL_Point*, SDL_RendererFlip)
FAKE_VALUE_FUNC(int, SDL_RenderCopyExF, SDL_Renderer*, SDL_Texture*, const SDL_Rect*, const SDL_FRect*, double, const SDL_FPoint*, SDL_RendererFlip)
FAKE_VALUE_FUNC(int, SDL_QueryTexture, SDL_Texture*, Uint32*, int*, int*, int*)
FAKE_VALUE_FUNC(int, SDL_RenderSetClipRect, SDL_Renderer*, const SDL_Rect*)
}
// clang-format on

class RendererTest : public testing::Test
{
 protected:
  void SetUp() override
  {
    RESET_FAKE(SDL_RenderPresent);
    RESET_FAKE(SDL_RenderClear);
    RESET_FAKE(SDL_SetRenderDrawColor);
    RESET_FAKE(SDL_GetRenderDrawColor);
    RESET_FAKE(SDL_RenderDrawRect);
    RESET_FAKE(SDL_RenderDrawRectF);
    RESET_FAKE(SDL_RenderFillRect);
    RESET_FAKE(SDL_RenderFillRectF);
    RESET_FAKE(SDL_GetRendererOutputSize);
    RESET_FAKE(SDL_RenderDrawLine);
    RESET_FAKE(SDL_RenderDrawLineF);
    RESET_FAKE(SDL_RenderDrawLines);
    RESET_FAKE(SDL_RenderDrawLinesF);
    RESET_FAKE(SDL_RenderCopy);
    RESET_FAKE(SDL_RenderCopyF);
    RESET_FAKE(SDL_RenderCopyEx);
    RESET_FAKE(SDL_RenderCopyExF);
    RESET_FAKE(SDL_QueryTexture);
    RESET_FAKE(SDL_RenderSetClipRect);
  }

  cen::renderer_handle m_renderer{nullptr};
  cen::texture_handle m_texture{nullptr};
};

template <typename Fake, typename... Args>
void validate_render_function(const Fake& fake, Args&&... args)
{
  static_assert(sizeof...(Args) >= 2,
                "Must at least provide source and destination rectangles!");

  const auto tuple = std::make_tuple(args...);

  const auto& src = std::get<0>(tuple);
  static_assert(std::is_same_v<const cen::irect&, decltype(src)>);

  EXPECT_EQ(src.x(), fake.arg2_val->x);
  EXPECT_EQ(src.y(), fake.arg2_val->y);
  EXPECT_EQ(src.width(), fake.arg2_val->w);
  EXPECT_EQ(src.height(), fake.arg2_val->h);

  const auto& dst = std::get<1>(tuple);
  static_assert(std::is_same_v<const cen::irect&, decltype(src)> ||
                std::is_same_v<const cen::frect&, decltype(src)>);

  EXPECT_EQ(dst.x(), fake.arg3_val->x);
  EXPECT_EQ(dst.y(), fake.arg3_val->y);
  EXPECT_EQ(dst.width(), fake.arg3_val->w);
  EXPECT_EQ(dst.height(), fake.arg3_val->h);

  if constexpr (sizeof...(Args) >= 3) {
    const auto angle = std::get<2>(tuple);
    static_assert(std::is_same_v<const double, decltype(angle)>);

    EXPECT_EQ(angle, fake.arg4_val);
  }

  if constexpr (sizeof...(Args) >= 4) {
    const auto& center = std::get<3>(tuple);
    static_assert(std::is_same_v<const cen::ipoint&, decltype(center)> ||
                  std::is_same_v<const cen::fpoint&, decltype(center)>);

    EXPECT_EQ(center.x(), fake.arg5_val->x);
    EXPECT_EQ(center.y(), fake.arg5_val->y);
  }

  if constexpr (sizeof...(Args) >= 5) {
    const auto flip = std::get<4>(tuple);
    static_assert(std::is_same_v<const SDL_RendererFlip, decltype(flip)>);

    EXPECT_EQ(flip, fake.arg6_val);
  }
}

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
  {
    constexpr cen::irect rect;
    m_renderer.draw_rect(rect);
  }

  {
    constexpr cen::frect rect;
    m_renderer.draw_rect(rect);
  }

  EXPECT_EQ(1, SDL_RenderDrawRect_fake.call_count);
  EXPECT_EQ(1, SDL_RenderDrawRectF_fake.call_count);
}

TEST_F(RendererTest, FillRect)
{
  {
    constexpr cen::irect rect;
    m_renderer.fill_rect(rect);
    EXPECT_EQ(1, SDL_RenderFillRect_fake.call_count);
    EXPECT_EQ(0, SDL_RenderFillRectF_fake.call_count);
  }

  {
    constexpr cen::frect rect;
    m_renderer.fill_rect(rect);
    EXPECT_EQ(1, SDL_RenderFillRect_fake.call_count);
    EXPECT_EQ(1, SDL_RenderFillRectF_fake.call_count);
  }
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

    EXPECT_EQ(start.x(), SDL_RenderDrawLine_fake.arg1_val);
    EXPECT_EQ(start.y(), SDL_RenderDrawLine_fake.arg2_val);
    EXPECT_EQ(end.x(), SDL_RenderDrawLine_fake.arg3_val);
    EXPECT_EQ(end.y(), SDL_RenderDrawLine_fake.arg4_val);
  }

  {
    const cen::fpoint start{12, 34};
    const cen::fpoint end{56, 78};
    m_renderer.draw_line(start, end);

    EXPECT_EQ(start.x(), SDL_RenderDrawLineF_fake.arg1_val);
    EXPECT_EQ(start.y(), SDL_RenderDrawLineF_fake.arg2_val);
    EXPECT_EQ(end.x(), SDL_RenderDrawLineF_fake.arg3_val);
    EXPECT_EQ(end.y(), SDL_RenderDrawLineF_fake.arg4_val);
  }

  EXPECT_EQ(1, SDL_RenderDrawLine_fake.call_count);
  EXPECT_EQ(1, SDL_RenderDrawLineF_fake.call_count);
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

TEST_F(RendererTest, RenderWithPoint)
{
  {
    const cen::ipoint pos{12, 34};
    m_renderer.render(m_texture, pos);
  }

  {
    const cen::fpoint pos{56, 78};
    m_renderer.render(m_texture, pos);
  }

  EXPECT_EQ(1, SDL_RenderCopy_fake.call_count);
  EXPECT_EQ(1, SDL_RenderCopyF_fake.call_count);
}

TEST_F(RendererTest, RenderWithRectangle)
{
  {
    const cen::irect rect{{12, 34}, {56, 78}};
    m_renderer.render(m_texture, rect);
  }

  {
    const cen::frect rect{{21, 43}, {65, 87}};
    m_renderer.render(m_texture, rect);
  }

  EXPECT_EQ(1, SDL_RenderCopy_fake.call_count);
  EXPECT_EQ(1, SDL_RenderCopyF_fake.call_count);
}

TEST_F(RendererTest, RenderWithSourceDestination)
{
  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::irect dst{{21, 43}, {65, 87}};

    m_renderer.render(m_texture, src, dst);
    validate_render_function(SDL_RenderCopy_fake, src, dst);
  }

  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::frect dst{{21, 43}, {65, 87}};

    m_renderer.render(m_texture, src, dst);
    validate_render_function(SDL_RenderCopyF_fake, src, dst);
  }

  EXPECT_EQ(1, SDL_RenderCopy_fake.call_count);
  EXPECT_EQ(1, SDL_RenderCopyF_fake.call_count);
}

TEST_F(RendererTest, RenderWithSourceDestinationAngle)
{
  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::irect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;

    m_renderer.render(m_texture, src, dst, angle);
    validate_render_function(SDL_RenderCopyEx_fake, src, dst, angle);
  }

  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::frect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;

    m_renderer.render(m_texture, src, dst, angle);
    validate_render_function(SDL_RenderCopyExF_fake, src, dst, angle);
  }

  EXPECT_EQ(1, SDL_RenderCopyEx_fake.call_count);
  EXPECT_EQ(1, SDL_RenderCopyExF_fake.call_count);
}

TEST_F(RendererTest, RenderWithSourceDestinationAngleCenter)
{
  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::irect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;
    const cen::ipoint center{15, 12};

    m_renderer.render(m_texture, src, dst, angle, center);
    validate_render_function(SDL_RenderCopyEx_fake, src, dst, angle, center);
  }

  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::frect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;
    const cen::fpoint center{15, 12};

    m_renderer.render(m_texture, src, dst, angle, center);
    validate_render_function(SDL_RenderCopyExF_fake, src, dst, angle, center);
  }

  EXPECT_EQ(1, SDL_RenderCopyEx_fake.call_count);
  EXPECT_EQ(1, SDL_RenderCopyExF_fake.call_count);
}

TEST_F(RendererTest, RenderWithSourceDestinationAngleCenterFlip)
{
  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::irect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;
    const cen::ipoint center{15, 12};
    const auto flip = SDL_FLIP_HORIZONTAL;

    m_renderer.render(m_texture, src, dst, angle, center, flip);
    validate_render_function(SDL_RenderCopyEx_fake,
                             src,
                             dst,
                             angle,
                             center,
                             flip);
  }

  {
    const cen::irect src{{12, 34}, {56, 78}};
    const cen::frect dst{{21, 43}, {65, 87}};
    const auto angle = 12.3;
    const cen::fpoint center{15, 12};
    const auto flip = SDL_FLIP_VERTICAL;

    m_renderer.render(m_texture, src, dst, angle, center, flip);
    validate_render_function(SDL_RenderCopyExF_fake,
                             src,
                             dst,
                             angle,
                             center,
                             flip);
  }

  EXPECT_EQ(1, SDL_RenderCopyEx_fake.call_count);
  EXPECT_EQ(1, SDL_RenderCopyExF_fake.call_count);
}

TEST_F(RendererTest, SetColor)
{
  constexpr auto color = cen::colors::magenta;
  m_renderer.set_color(color);

  EXPECT_EQ(1, SDL_SetRenderDrawColor_fake.call_count);
  EXPECT_EQ(color.red(), SDL_SetRenderDrawColor_fake.arg1_val);
  EXPECT_EQ(color.green(), SDL_SetRenderDrawColor_fake.arg2_val);
  EXPECT_EQ(color.blue(), SDL_SetRenderDrawColor_fake.arg3_val);
  EXPECT_EQ(color.alpha(), SDL_SetRenderDrawColor_fake.arg4_val);
}

TEST_F(RendererTest, SetClip)
{
  constexpr cen::irect clip{{12, 34}, {56, 78}};
  m_renderer.set_clip(clip);

  EXPECT_EQ(1, SDL_RenderSetClipRect_fake.call_count);
  EXPECT_NE(nullptr, SDL_RenderSetClipRect_fake.arg1_val);

  m_renderer.set_clip(std::nullopt);
  EXPECT_EQ(2, SDL_RenderSetClipRect_fake.call_count);
  EXPECT_EQ(nullptr, SDL_RenderSetClipRect_fake.arg1_val);
}
