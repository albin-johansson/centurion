#include "renderer_base.hpp"

namespace centurion {

renderer_base::renderer_base(SDL_Renderer* renderer) noexcept
    : m_renderer{renderer}
{}

void renderer_base::set_color(const color& color) noexcept
{
  SDL_SetRenderDrawColor(
      m_renderer, color.red(), color.green(), color.blue(), color.alpha());
}

void renderer_base::set_clip(std::optional<rect_i> area) noexcept
{
  if (area) {
    SDL_RenderSetClipRect(m_renderer, static_cast<const SDL_Rect*>(*area));
  } else {
    SDL_RenderSetClipRect(m_renderer, nullptr);
  }
}

void renderer_base::set_viewport(const rect_i& viewport) noexcept
{
  SDL_RenderSetViewport(m_renderer, static_cast<const SDL_Rect*>(viewport));
}

void renderer_base::set_blend_mode(enum blend_mode mode) noexcept
{
  SDL_SetRenderDrawBlendMode(m_renderer, static_cast<SDL_BlendMode>(mode));
}

void renderer_base::set_target(const texture* target) noexcept
{
  if (target && target->is_target()) {
    SDL_SetRenderTarget(m_renderer, target->get());
  } else {
    SDL_SetRenderTarget(m_renderer, nullptr);
  }
}

void renderer_base::set_scale(float xScale, float yScale) noexcept
{
  if ((xScale > 0) && (yScale > 0)) {
    SDL_RenderSetScale(m_renderer, xScale, yScale);
  }
}

void renderer_base::set_logical_size(const area_i& size) noexcept
{
  if ((size.width > 0) && (size.height > 0)) {
    SDL_RenderSetLogicalSize(m_renderer, size.width, size.height);
  }
}

void renderer_base::set_logical_integer_scale(
    bool useLogicalIntegerScale) noexcept
{
  SDL_RenderSetIntegerScale(m_renderer,
                            detail::convert_bool(useLogicalIntegerScale));
}

auto renderer_base::clip() const noexcept -> std::optional<rect_i>
{
  rect_i rect{};
  SDL_RenderGetClipRect(m_renderer, static_cast<SDL_Rect*>(rect));
  if (!rect.has_area()) {
    return nothing;
  } else {
    return rect;
  }
}

auto renderer_base::info() const noexcept -> std::optional<SDL_RendererInfo>
{
  SDL_RendererInfo info{};
  const auto result = SDL_GetRendererInfo(m_renderer, &info);
  if (result == 0) {
    return info;
  } else {
    return nothing;
  }
}

auto renderer_base::logical_width() const noexcept -> int
{
  int width{};
  SDL_RenderGetLogicalSize(m_renderer, &width, nullptr);
  return width;
}

auto renderer_base::logical_height() const noexcept -> int
{
  int height{};
  SDL_RenderGetLogicalSize(m_renderer, nullptr, &height);
  return height;
}

auto renderer_base::logical_size() const noexcept -> area_i
{
  int width{};
  int height{};
  SDL_RenderGetLogicalSize(m_renderer, &width, &height);
  return {width, height};
}

auto renderer_base::x_scale() const noexcept -> float
{
  float xScale{};
  SDL_RenderGetScale(m_renderer, &xScale, nullptr);
  return xScale;
}

auto renderer_base::y_scale() const noexcept -> float
{
  float yScale{};
  SDL_RenderGetScale(m_renderer, nullptr, &yScale);
  return yScale;
}

auto renderer_base::scale() const noexcept -> std::pair<float, float>
{
  float xScale{};
  float yScale{};
  SDL_RenderGetScale(m_renderer, &xScale, &yScale);
  return {xScale, yScale};
}

auto renderer_base::output_width() const noexcept -> int
{
  int width{};
  SDL_GetRendererOutputSize(m_renderer, &width, nullptr);
  return width;
}

auto renderer_base::output_height() const noexcept -> int
{
  int height{};
  SDL_GetRendererOutputSize(m_renderer, nullptr, &height);
  return height;
}

auto renderer_base::output_size() const noexcept -> area_i
{
  int width{};
  int height{};
  SDL_GetRendererOutputSize(m_renderer, &width, &height);
  return {width, height};
}

auto renderer_base::blend_mode() const noexcept -> enum blend_mode  //
{                                                                   //
  SDL_BlendMode mode{};                                             //
  SDL_GetRenderDrawBlendMode(m_renderer, &mode);
  return static_cast<enum blend_mode>(mode);
}

auto renderer_base::flags() const noexcept -> u32
{
  SDL_RendererInfo info{};
  SDL_GetRendererInfo(m_renderer, &info);
  return info.flags;
}

auto renderer_base::vsync_enabled() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_PRESENTVSYNC);
}

auto renderer_base::accelerated() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_ACCELERATED);
}

auto renderer_base::software_based() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_SOFTWARE);
}

auto renderer_base::supports_target_textures() const noexcept -> bool
{
  return static_cast<bool>(flags() & SDL_RENDERER_TARGETTEXTURE);
}

auto renderer_base::using_integer_logical_scaling() const noexcept -> bool
{
  return SDL_RenderGetIntegerScale(m_renderer);
}

auto renderer_base::clipping_enabled() const noexcept -> bool
{
  return SDL_RenderIsClipEnabled(m_renderer);
}

auto renderer_base::get_color() const noexcept -> color
{
  u8 red{};
  u8 green{};
  u8 blue{};
  u8 alpha{};
  SDL_GetRenderDrawColor(m_renderer, &red, &green, &blue, &alpha);
  return {red, green, blue, alpha};
}

auto renderer_base::viewport() const noexcept -> rect_i
{
  rect_i viewport{};
  SDL_RenderGetViewport(m_renderer, static_cast<SDL_Rect*>(viewport));
  return viewport;
}

auto renderer_base::to_string() const -> std::string
{
  const auto address = detail::address_of(this);
  const auto owidth = std::to_string(output_width());
  const auto oheight = std::to_string(output_height());
  return "[Renderer@" + address + " | Output width: " + owidth +
         ", Output height: " + oheight + "]";
}

auto get_render_driver_info(int index) noexcept
    -> std::optional<SDL_RendererInfo>
{
  SDL_RendererInfo info{};
  const auto result = SDL_GetRenderDriverInfo(index, &info);
  if (result == 0) {
    return info;
  } else {
    return nothing;
  }
}

}  // namespace centurion
