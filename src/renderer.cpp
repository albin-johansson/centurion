#ifndef CENTURION_RENDERER_SOURCE
#define CENTURION_RENDERER_SOURCE

#include "renderer.h"

#include <SDL.h>

#include "centurion_exception.h"
#include "centurion_utils.h"
#include "colors.h"
#include "font.h"
#include "point.h"
#include "texture.h"
#include "window.h"

namespace centurion {
namespace video {

CENTURION_DEF
Renderer::Renderer(gsl::owner<SDL_Renderer*> renderer)
{
  if (!renderer) {
    throw CenturionException{"Can't create renderer from null SDL_Renderer!"};
  }
  this->m_renderer = renderer;

  set_color(black);
  set_logical_integer_scale(false);
}

CENTURION_DEF
Renderer::Renderer(const Window& window, SDL_RendererFlags flags)
{
  m_renderer = SDL_CreateRenderer(window.get_internal(), -1, flags);

  set_blend_mode(BlendMode::Blend);
  set_color(black);
  set_logical_integer_scale(false);
}

CENTURION_DEF
Renderer::Renderer(Renderer&& other) noexcept
{
  if (this != &other) {
    destroy();

    m_renderer = other.m_renderer;
    other.m_renderer = nullptr;

    m_translationViewport = other.m_translationViewport;
  }
}

CENTURION_DEF
Renderer::~Renderer()
{
  destroy();
}

CENTURION_DEF
void Renderer::destroy() noexcept
{
  if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
  }
}

CENTURION_DEF
std::unique_ptr<Renderer> Renderer::unique(gsl::owner<SDL_Renderer*> renderer)
{
  return centurion::make_unique<Renderer>(renderer);
}

CENTURION_DEF
std::unique_ptr<Renderer> Renderer::unique(const Window& window,
                                           SDL_RendererFlags flags)
{
  return centurion::make_unique<Renderer>(window, flags);
}

CENTURION_DEF
std::shared_ptr<Renderer> Renderer::shared(gsl::owner<SDL_Renderer*> renderer)
{
  return std::make_shared<Renderer>(renderer);
}

CENTURION_DEF
std::shared_ptr<Renderer> Renderer::shared(const Window& window,
                                           SDL_RendererFlags flags)
{
  return std::make_shared<Renderer>(window, flags);
}

CENTURION_DEF
Renderer& Renderer::operator=(Renderer&& other) noexcept
{
  if (this != &other) {
    destroy();

    m_renderer = other.m_renderer;
    other.m_renderer = nullptr;

    m_translationViewport = other.m_translationViewport;
  }
  return *this;
}

CENTURION_DEF
void Renderer::clear() noexcept
{
  SDL_RenderClear(m_renderer);
}

CENTURION_DEF
void Renderer::present() noexcept
{
  SDL_RenderPresent(m_renderer);
}

CENTURION_DEF
void Renderer::draw_rect(const math::IRect& rect) noexcept
{
  SDL_RenderDrawRect(m_renderer, static_cast<const SDL_Rect*>(rect));
}

CENTURION_DEF
void Renderer::fill_rect(const math::IRect& rect) noexcept
{
  SDL_RenderFillRect(m_renderer, static_cast<const SDL_Rect*>(rect));
}

CENTURION_DEF
void Renderer::draw_rect_f(const math::FRect& rect) noexcept
{
  SDL_RenderDrawRectF(m_renderer, static_cast<const SDL_FRect*>(rect));
}

CENTURION_DEF
void Renderer::fill_rect_f(const math::FRect& rect) noexcept
{
  SDL_RenderFillRectF(m_renderer, static_cast<const SDL_FRect*>(rect));
}

CENTURION_DEF
void Renderer::draw_line(const math::IPoint& start,
                         const math::IPoint& end) noexcept
{
  SDL_RenderDrawLine(m_renderer, start.x(), start.y(), end.x(), end.y());
}

CENTURION_DEF
void Renderer::draw_lines(const std::vector<math::IPoint>& points) noexcept
{
  if (!points.empty()) {
    const auto* firstPoint = static_cast<const SDL_Point*>(points.front());
    SDL_RenderDrawLines(
        m_renderer, firstPoint, static_cast<int>(points.size()));
  }
}

CENTURION_DEF
void Renderer::draw_line_f(const math::FPoint& start,
                           const math::FPoint& end) noexcept
{
  SDL_RenderDrawLineF(m_renderer, start.x(), start.y(), end.x(), end.y());
}

CENTURION_DEF
void Renderer::render(const Texture& texture, math::IPoint position) noexcept
{
  const SDL_Rect dst{position.x(), position.y(),
                     texture.get_width(),
                     texture.get_height()};
  SDL_RenderCopy(m_renderer, texture, nullptr, &dst);
}

CENTURION_DEF
void Renderer::render(const Texture& texture, const math::IRect& rect) noexcept
{
  const auto* dst = static_cast<const SDL_Rect*>(rect);
  SDL_RenderCopy(m_renderer, texture, nullptr, dst);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const math::IRect& src,
                      const math::IRect& dst) noexcept
{
  SDL_RenderCopy(m_renderer,
                 texture,
                 static_cast<const SDL_Rect*>(src),
                 static_cast<const SDL_Rect*>(dst));
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const math::IRect& src,
                      const math::IRect& dst,
                      double angle) noexcept
{
  SDL_RenderCopyEx(m_renderer,
                   texture,
                   static_cast<const SDL_Rect*>(src),
                   static_cast<const SDL_Rect*>(dst),
                   angle,
                   nullptr,
                   SDL_FLIP_NONE);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const math::IRect& src,
                      const math::IRect& dst,
                      double angle,
                      math::IPoint center) noexcept
{
  SDL_RenderCopyEx(m_renderer,
                   texture,
                   static_cast<const SDL_Rect*>(src),
                   static_cast<const SDL_Rect*>(dst),
                   angle,
                   static_cast<const SDL_Point*>(center),
                   SDL_FLIP_NONE);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const math::IRect& src,
                      const math::IRect& dst,
                      SDL_RendererFlip flip) noexcept
{
  SDL_RenderCopyEx(m_renderer,
                   texture,
                   static_cast<const SDL_Rect*>(src),
                   static_cast<const SDL_Rect*>(dst),
                   0,
                   nullptr,
                   flip);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const math::IRect& src,
                      const math::IRect& dst,
                      double angle,
                      math::IPoint center,
                      SDL_RendererFlip flip) noexcept
{
  SDL_RenderCopyEx(m_renderer,
                   texture,
                   static_cast<const SDL_Rect*>(src),
                   static_cast<const SDL_Rect*>(dst),
                   angle,
                   static_cast<const SDL_Point*>(center),
                   flip);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture, math::FPoint position) noexcept
{
  const auto dst = SDL_FRect{position.x(),
                             position.y(),
                             static_cast<float>(texture.get_width()),
                             static_cast<float>(texture.get_height())};
  SDL_RenderCopyF(m_renderer, texture, nullptr, &dst);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const math::FRect& rect) noexcept
{
  const auto* dst = static_cast<const SDL_FRect*>(rect);
  SDL_RenderCopyF(m_renderer, texture, nullptr, dst);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const math::IRect& src,
                        const math::FRect& dst) noexcept
{
  SDL_RenderCopyF(m_renderer,
                  texture,
                  static_cast<const SDL_Rect*>(src),
                  static_cast<const SDL_FRect*>(dst));
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const math::IRect& src,
                        const math::FRect& dst,
                        double angle) noexcept
{
  SDL_RenderCopyExF(m_renderer,
                    texture,
                    static_cast<const SDL_Rect*>(src),
                    static_cast<const SDL_FRect*>(dst),
                    angle,
                    nullptr,
                    SDL_FLIP_NONE);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const math::IRect& src,
                        const math::FRect& dst,
                        double angle,
                        math::FPoint center) noexcept
{
  SDL_RenderCopyExF(m_renderer,
                    texture,
                    static_cast<const SDL_Rect*>(src),
                    static_cast<const SDL_FRect*>(dst),
                    angle,
                    static_cast<const SDL_FPoint*>(center),
                    SDL_FLIP_NONE);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const math::IRect& src,
                        const math::FRect& dst,
                        SDL_RendererFlip flip) noexcept
{
  SDL_RenderCopyExF(m_renderer,
                    texture,
                    static_cast<const SDL_Rect*>(src),
                    static_cast<const SDL_FRect*>(dst),
                    0,
                    nullptr,
                    flip);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const math::IRect& src,
                        const math::FRect& dst,
                        double angle,
                        math::FPoint center,
                        SDL_RendererFlip flip) noexcept
{
  SDL_RenderCopyExF(m_renderer,
                    texture,
                    static_cast<const SDL_Rect*>(src),
                    static_cast<const SDL_FRect*>(dst),
                    angle,
                    static_cast<const SDL_FPoint*>(center),
                    flip);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture, math::IPoint position) noexcept
{
  const auto tx = position.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = position.y() - static_cast<int>(m_translationViewport.y());
  render(texture, {tx, ty});
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& rect) noexcept
{
  const auto tx = rect.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = rect.y() - static_cast<int>(m_translationViewport.y());
  render(texture, {tx, ty, rect.width(), rect.height()});
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(texture, src, {tx, ty, dst.width(), dst.height()});
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst,
                        double angle) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(texture, src, {tx, ty, dst.width(), dst.height()}, angle);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst,
                        double angle,
                        math::IPoint center) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(
      texture, src, {tx, ty, dst.width(), dst.height()}, angle, center);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst,
                        SDL_RendererFlip flip) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(texture, src, {tx, ty, dst.width(), dst.height()}, flip);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst,
                        double angle,
                        math::IPoint center,
                        SDL_RendererFlip flip) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(texture,
         src,
         {tx, ty, dst.width(), dst.height()},
         angle,
         center,
         flip);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture, math::FPoint position) noexcept
{
  const auto tx = position.x() - m_translationViewport.x();
  const auto ty = position.y() - m_translationViewport.y();
  render_f(texture, {tx, ty});
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::FRect& rect) noexcept
{
  const auto tx = rect.x() - m_translationViewport.x();
  const auto ty = rect.y() - m_translationViewport.y();
  render_f(texture, {tx, ty, rect.width(), rect.height()});
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(texture, src, {tx, ty, dst.width(), dst.height()});
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst,
                         double angle) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(texture, src, {tx, ty, dst.width(), dst.height()}, angle);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst,
                         double angle,
                         math::FPoint center) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(
      texture, src, {tx, ty, dst.width(), dst.height()}, angle, center);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst,
                         SDL_RendererFlip flip) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(texture, src, {tx, ty, dst.width(), dst.height()}, flip);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst,
                         double angle,
                         math::FPoint center,
                         SDL_RendererFlip flip) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(texture,
           src,
           {tx, ty, dst.width(), dst.height()},
           angle,
           center,
           flip);
}

CENTURION_DEF
void Renderer::render_text(const char* text, math::IRect pos, const Font& font)
{
  if (text) {
    const auto texture = create_image(text, font);
    if (texture) {
      render(*texture, pos);
    }
  }
}

CENTURION_DEF
void Renderer::render_text_f(const char* text,
                             math::FRect pos,
                             const Font& font)
{
  if (text) {
    const auto texture = create_image(text, font);
    if (texture) {
      render_f(*texture, pos);
    }
  }
}

CENTURION_DEF
void Renderer::set_color(const Color& color) noexcept
{
  SDL_SetRenderDrawColor(
      m_renderer, color.red(), color.green(), color.blue(), color.alpha());
}

CENTURION_DEF
void Renderer::set_clip(Optional<math::IRect> area) noexcept
{
  if (area) {
    SDL_RenderSetClipRect(m_renderer, static_cast<const SDL_Rect*>(*area));
  } else {
    SDL_RenderSetClipRect(m_renderer, nullptr);
  }
}

CENTURION_DEF
void Renderer::set_viewport(const math::IRect& viewport) noexcept
{
  SDL_RenderSetViewport(m_renderer, static_cast<const SDL_Rect*>(viewport));
}

CENTURION_DEF
void Renderer::set_translation_viewport(const math::FRect& viewport) noexcept
{
  m_translationViewport = viewport;
}

CENTURION_DEF
void Renderer::set_blend_mode(BlendMode mode) noexcept
{
  SDL_SetRenderDrawBlendMode(m_renderer, static_cast<SDL_BlendMode>(mode));
}

CENTURION_DEF
void Renderer::set_target(const Texture* texture) noexcept
{
  if (texture && texture->is_target()) {
    SDL_SetRenderTarget(m_renderer, *texture);
  } else {
    SDL_SetRenderTarget(m_renderer, nullptr);
  }
}

CENTURION_DEF
void Renderer::set_scale(float xScale, float yScale) noexcept
{
  if (xScale > 0 && yScale > 0) {
    SDL_RenderSetScale(m_renderer, xScale, yScale);
  }
}

CENTURION_DEF
void Renderer::set_logical_size(int width, int height) noexcept
{
  if (width > 0 && height > 0) {
    SDL_RenderSetLogicalSize(m_renderer, width, height);
  }
}

CENTURION_DEF
void Renderer::set_logical_integer_scale(bool useLogicalIntegerScale) noexcept
{
  SDL_RenderSetIntegerScale(m_renderer, convert_bool(useLogicalIntegerScale));
}

CENTURION_DEF
Color Renderer::color() const noexcept
{
  Uint8 r = 0, g = 0, b = 0, a = 0;
  SDL_GetRenderDrawColor(m_renderer, &r, &g, &b, &a);
  return {r, g, b, a};
}

CENTURION_DEF
int Renderer::logical_width() const noexcept
{
  int w = 0;
  SDL_RenderGetLogicalSize(m_renderer, &w, nullptr);
  return w;
}

CENTURION_DEF
int Renderer::logical_height() const noexcept
{
  int h = 0;
  SDL_RenderGetLogicalSize(m_renderer, nullptr, &h);
  return h;
}

CENTURION_DEF
bool Renderer::clipping_enabled() const noexcept
{
  return SDL_RenderIsClipEnabled(m_renderer);
}

CENTURION_DEF
Optional<math::IRect> Renderer::clip() const noexcept
{
  SDL_Rect rect{0, 0, 0, 0};
  SDL_RenderGetClipRect(m_renderer, &rect);
  if (SDL_RectEmpty(&rect)) {
    return tl::nullopt;
  } else {
    return math::IRect{rect.x, rect.y, rect.w, rect.h};
  }
}

CENTURION_DEF
SDL_RendererInfo Renderer::info() const noexcept
{
  SDL_RendererInfo info;
  SDL_GetRendererInfo(m_renderer, &info);
  return info;
}

CENTURION_DEF
int Renderer::output_width() const noexcept
{
  int width = 0;
  SDL_GetRendererOutputSize(m_renderer, &width, nullptr);
  return width;
}

CENTURION_DEF
int Renderer::output_height() const noexcept
{
  int height = 0;
  SDL_GetRendererOutputSize(m_renderer, nullptr, &height);
  return height;
}

CENTURION_DEF
std::pair<int, int> Renderer::output_size() const noexcept
{
  int width = 0;
  int height = 0;
  SDL_GetRendererOutputSize(m_renderer, &width, &height);
  return {width, height};
}

CENTURION_DEF
BlendMode Renderer::blend_mode() const noexcept
{
  SDL_BlendMode mode;
  SDL_GetRenderDrawBlendMode(m_renderer, &mode);
  return static_cast<BlendMode>(mode);
}

CENTURION_DEF
float Renderer::x_scale() const noexcept
{
  float xScale = 0;
  SDL_RenderGetScale(m_renderer, &xScale, nullptr);
  return xScale;
}

CENTURION_DEF
float Renderer::y_scale() const noexcept
{
  float yScale = 0;
  SDL_RenderGetScale(m_renderer, nullptr, &yScale);
  return yScale;
}

CENTURION_DEF
math::IRect Renderer::viewport() const noexcept
{
  SDL_Rect viewport{0, 0, 0, 0};
  SDL_RenderGetViewport(m_renderer, &viewport);
  return {viewport.x, viewport.y, viewport.w, viewport.h};
}

CENTURION_DEF
const math::FRect& Renderer::translation_viewport() const noexcept
{
  return m_translationViewport;
}

CENTURION_DEF
Uint32 Renderer::flags() const noexcept
{
  SDL_RendererInfo info;
  SDL_GetRendererInfo(m_renderer, &info);
  return info.flags;
}

CENTURION_DEF
bool Renderer::vsync_enabled() const noexcept
{
  return flags() & SDL_RENDERER_PRESENTVSYNC;
}

CENTURION_DEF
bool Renderer::accelerated() const noexcept
{
  return flags() & SDL_RENDERER_ACCELERATED;
}

CENTURION_DEF
bool Renderer::software_based() const noexcept
{
  return flags() & SDL_RENDERER_SOFTWARE;
}

CENTURION_DEF
bool Renderer::supports_target_textures() const noexcept
{
  return flags() & SDL_RENDERER_TARGETTEXTURE;
}

CENTURION_DEF
bool Renderer::using_integer_logical_scaling() const noexcept
{
  return SDL_RenderGetIntegerScale(m_renderer);
}

CENTURION_DEF
std::unique_ptr<Texture> Renderer::create_image(const std::string& s,
                                                const Font& font) const
{
  if (s.empty()) {
    return nullptr;
  }

  SDL_Surface* surface = TTF_RenderText_Blended(font, s.c_str(), color());

  if (!surface) {
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
  SDL_FreeSurface(surface);

  return centurion::make_unique<Texture>(texture);
}

CENTURION_DEF
std::string Renderer::to_string() const
{
  const auto address = address_of(this);
  const auto owidth = std::to_string(output_width());
  const auto oheight = std::to_string(output_height());
  return "[Renderer@" + address + " | Output width: " + owidth +
         ", Output height: " + oheight + "]";
}

CENTURION_DEF
SDL_Renderer* Renderer::get_internal() const noexcept
{
  return m_renderer;
}

CENTURION_DEF
Renderer::operator SDL_Renderer*() const noexcept
{
  return m_renderer;
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_RENDERER_SOURCE