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

CENTURION_DEF
Renderer::Renderer(Owner<SDL_Renderer*> renderer)
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
  m_renderer = SDL_CreateRenderer(window.get(), -1, flags);

  set_blend_mode(BlendMode::Blend);
  set_color(black);
  set_logical_integer_scale(false);
}

CENTURION_DEF
Renderer::Renderer(Renderer&& other) noexcept
{
  move(std::forward<Renderer>(other));
}

CENTURION_DEF
Renderer::~Renderer()
{
  destroy();
}

CENTURION_DEF
Renderer& Renderer::operator=(Renderer&& other) noexcept
{
  if (this != &other) {
    move(std::forward<Renderer>(other));
  }
  return *this;
}

CENTURION_DEF
void Renderer::destroy() noexcept
{
  if (m_renderer) {
    SDL_DestroyRenderer(m_renderer);
  }
}

CENTURION_DEF
void Renderer::move(Renderer&& other) noexcept
{
  destroy();

  m_renderer = other.m_renderer;
  m_translationViewport = other.m_translationViewport;

  other.m_renderer = nullptr;
}

CENTURION_DEF
UniquePtr<Renderer> Renderer::unique(Owner<SDL_Renderer*> renderer)
{
  return centurion::detail::make_unique<Renderer>(renderer);
}

CENTURION_DEF
UniquePtr<Renderer> Renderer::unique(const Window& window,
                                     SDL_RendererFlags flags)
{
  return centurion::detail::make_unique<Renderer>(window, flags);
}

CENTURION_DEF
SharedPtr<Renderer> Renderer::shared(Owner<SDL_Renderer*> renderer)
{
  return std::make_shared<Renderer>(renderer);
}

CENTURION_DEF
SharedPtr<Renderer> Renderer::shared(const Window& window,
                                     SDL_RendererFlags flags)
{
  return std::make_shared<Renderer>(window, flags);
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
void Renderer::draw_rect(const IRect& rect) noexcept
{
  SDL_RenderDrawRect(m_renderer, static_cast<const SDL_Rect*>(rect));
}

CENTURION_DEF
void Renderer::fill_rect(const IRect& rect) noexcept
{
  SDL_RenderFillRect(m_renderer, static_cast<const SDL_Rect*>(rect));
}

CENTURION_DEF
void Renderer::draw_rect_f(const FRect& rect) noexcept
{
  SDL_RenderDrawRectF(m_renderer, static_cast<const SDL_FRect*>(rect));
}

CENTURION_DEF
void Renderer::fill_rect_f(const FRect& rect) noexcept
{
  SDL_RenderFillRectF(m_renderer, static_cast<const SDL_FRect*>(rect));
}

CENTURION_DEF
void Renderer::draw_line(const IPoint& start, const IPoint& end) noexcept
{
  SDL_RenderDrawLine(m_renderer, start.x(), start.y(), end.x(), end.y());
}

CENTURION_DEF
void Renderer::draw_lines(const std::vector<IPoint>& points) noexcept
{
  if (!points.empty()) {
    const auto* firstPoint = static_cast<const SDL_Point*>(points.front());
    SDL_RenderDrawLines(
        m_renderer, firstPoint, static_cast<int>(points.size()));
  }
}

CENTURION_DEF
void Renderer::draw_line_f(const FPoint& start, const FPoint& end) noexcept
{
  SDL_RenderDrawLineF(m_renderer, start.x(), start.y(), end.x(), end.y());
}

CENTURION_DEF
void Renderer::render(const Texture& texture, IPoint position) noexcept
{
  const SDL_Rect dst{
      position.x(), position.y(), texture.width(), texture.height()};
  SDL_RenderCopy(m_renderer, texture.get(), nullptr, &dst);
}

CENTURION_DEF
void Renderer::render(const Texture& texture, const IRect& rect) noexcept
{
  const auto* dst = static_cast<const SDL_Rect*>(rect);
  SDL_RenderCopy(m_renderer, texture.get(), nullptr, dst);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const IRect& src,
                      const IRect& dst) noexcept
{
  SDL_RenderCopy(m_renderer,
                 texture.get(),
                 static_cast<const SDL_Rect*>(src),
                 static_cast<const SDL_Rect*>(dst));
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const IRect& src,
                      const IRect& dst,
                      double angle) noexcept
{
  SDL_RenderCopyEx(m_renderer,
                   texture.get(),
                   static_cast<const SDL_Rect*>(src),
                   static_cast<const SDL_Rect*>(dst),
                   angle,
                   nullptr,
                   SDL_FLIP_NONE);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const IRect& src,
                      const IRect& dst,
                      double angle,
                      IPoint center) noexcept
{
  SDL_RenderCopyEx(m_renderer,
                   texture.get(),
                   static_cast<const SDL_Rect*>(src),
                   static_cast<const SDL_Rect*>(dst),
                   angle,
                   static_cast<const SDL_Point*>(center),
                   SDL_FLIP_NONE);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const IRect& src,
                      const IRect& dst,
                      SDL_RendererFlip flip) noexcept
{
  SDL_RenderCopyEx(m_renderer,
                   texture.get(),
                   static_cast<const SDL_Rect*>(src),
                   static_cast<const SDL_Rect*>(dst),
                   0,
                   nullptr,
                   flip);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const IRect& src,
                      const IRect& dst,
                      double angle,
                      IPoint center,
                      SDL_RendererFlip flip) noexcept
{
  SDL_RenderCopyEx(m_renderer,
                   texture.get(),
                   static_cast<const SDL_Rect*>(src),
                   static_cast<const SDL_Rect*>(dst),
                   angle,
                   static_cast<const SDL_Point*>(center),
                   flip);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture, FPoint position) noexcept
{
  const auto dst = SDL_FRect{position.x(),
                             position.y(),
                             static_cast<float>(texture.width()),
                             static_cast<float>(texture.height())};
  SDL_RenderCopyF(m_renderer, texture.get(), nullptr, &dst);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture, const FRect& rect) noexcept
{
  const auto* dst = static_cast<const SDL_FRect*>(rect);
  SDL_RenderCopyF(m_renderer, texture.get(), nullptr, dst);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const IRect& src,
                        const FRect& dst) noexcept
{
  SDL_RenderCopyF(m_renderer,
                  texture.get(),
                  static_cast<const SDL_Rect*>(src),
                  static_cast<const SDL_FRect*>(dst));
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const IRect& src,
                        const FRect& dst,
                        double angle) noexcept
{
  SDL_RenderCopyExF(m_renderer,
                    texture.get(),
                    static_cast<const SDL_Rect*>(src),
                    static_cast<const SDL_FRect*>(dst),
                    angle,
                    nullptr,
                    SDL_FLIP_NONE);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const IRect& src,
                        const FRect& dst,
                        double angle,
                        FPoint center) noexcept
{
  SDL_RenderCopyExF(m_renderer,
                    texture.get(),
                    static_cast<const SDL_Rect*>(src),
                    static_cast<const SDL_FRect*>(dst),
                    angle,
                    static_cast<const SDL_FPoint*>(center),
                    SDL_FLIP_NONE);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const IRect& src,
                        const FRect& dst,
                        SDL_RendererFlip flip) noexcept
{
  SDL_RenderCopyExF(m_renderer,
                    texture.get(),
                    static_cast<const SDL_Rect*>(src),
                    static_cast<const SDL_FRect*>(dst),
                    0,
                    nullptr,
                    flip);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const IRect& src,
                        const FRect& dst,
                        double angle,
                        FPoint center,
                        SDL_RendererFlip flip) noexcept
{
  SDL_RenderCopyExF(m_renderer,
                    texture.get(),
                    static_cast<const SDL_Rect*>(src),
                    static_cast<const SDL_FRect*>(dst),
                    angle,
                    static_cast<const SDL_FPoint*>(center),
                    flip);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture, IPoint position) noexcept
{
  const auto tx = position.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = position.y() - static_cast<int>(m_translationViewport.y());
  render(texture, {tx, ty});
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture, const IRect& rect) noexcept
{
  const auto tx = rect.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = rect.y() - static_cast<int>(m_translationViewport.y());
  render(texture, {tx, ty, rect.width(), rect.height()});
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const IRect& src,
                        const IRect& dst) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(texture, src, {tx, ty, dst.width(), dst.height()});
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const IRect& src,
                        const IRect& dst,
                        double angle) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(texture, src, {tx, ty, dst.width(), dst.height()}, angle);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const IRect& src,
                        const IRect& dst,
                        double angle,
                        IPoint center) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(texture, src, {tx, ty, dst.width(), dst.height()}, angle, center);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const IRect& src,
                        const IRect& dst,
                        SDL_RendererFlip flip) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(texture, src, {tx, ty, dst.width(), dst.height()}, flip);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const IRect& src,
                        const IRect& dst,
                        double angle,
                        IPoint center,
                        SDL_RendererFlip flip) noexcept
{
  const auto tx = dst.x() - static_cast<int>(m_translationViewport.x());
  const auto ty = dst.y() - static_cast<int>(m_translationViewport.y());
  render(
      texture, src, {tx, ty, dst.width(), dst.height()}, angle, center, flip);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture, FPoint position) noexcept
{
  const auto tx = position.x() - m_translationViewport.x();
  const auto ty = position.y() - m_translationViewport.y();
  render_f(texture, {tx, ty});
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture, const FRect& rect) noexcept
{
  const auto tx = rect.x() - m_translationViewport.x();
  const auto ty = rect.y() - m_translationViewport.y();
  render_f(texture, {tx, ty, rect.width(), rect.height()});
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const IRect& src,
                         const FRect& dst) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(texture, src, {tx, ty, dst.width(), dst.height()});
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const IRect& src,
                         const FRect& dst,
                         double angle) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(texture, src, {tx, ty, dst.width(), dst.height()}, angle);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const IRect& src,
                         const FRect& dst,
                         double angle,
                         FPoint center) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(texture, src, {tx, ty, dst.width(), dst.height()}, angle, center);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const IRect& src,
                         const FRect& dst,
                         SDL_RendererFlip flip) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(texture, src, {tx, ty, dst.width(), dst.height()}, flip);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const IRect& src,
                         const FRect& dst,
                         double angle,
                         FPoint center,
                         SDL_RendererFlip flip) noexcept
{
  const auto tx = dst.x() - m_translationViewport.x();
  const auto ty = dst.y() - m_translationViewport.y();
  render_f(
      texture, src, {tx, ty, dst.width(), dst.height()}, angle, center, flip);
}

CENTURION_DEF
void Renderer::set_color(const Color& color) noexcept
{
  SDL_SetRenderDrawColor(
      m_renderer, color.red(), color.green(), color.blue(), color.alpha());
}

CENTURION_DEF
void Renderer::set_clip(Optional<IRect> area) noexcept
{
  if (area) {
    SDL_RenderSetClipRect(m_renderer, static_cast<const SDL_Rect*>(*area));
  } else {
    SDL_RenderSetClipRect(m_renderer, nullptr);
  }
}

CENTURION_DEF
void Renderer::set_viewport(const IRect& viewport) noexcept
{
  SDL_RenderSetViewport(m_renderer, static_cast<const SDL_Rect*>(viewport));
}

CENTURION_DEF
void Renderer::set_translation_viewport(const FRect& viewport) noexcept
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
    SDL_SetRenderTarget(m_renderer, texture->get());
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
void Renderer::set_logical_size(Area size) noexcept
{
  if (size.width > 0 && size.height > 0) {
    SDL_RenderSetLogicalSize(m_renderer, size.width, size.height);
  }
}

CENTURION_DEF
void Renderer::set_logical_integer_scale(bool useLogicalIntegerScale) noexcept
{
  SDL_RenderSetIntegerScale(m_renderer,
                            detail::convert_bool(useLogicalIntegerScale));
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
Optional<IRect> Renderer::clip() const noexcept
{
  SDL_Rect rect{0, 0, 0, 0};
  SDL_RenderGetClipRect(m_renderer, &rect);
  if (SDL_RectEmpty(&rect)) {
    return nothing;
  } else {
    return IRect{rect.x, rect.y, rect.w, rect.h};
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
Area Renderer::output_size() const noexcept
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
IRect Renderer::viewport() const noexcept
{
  SDL_Rect viewport{0, 0, 0, 0};
  SDL_RenderGetViewport(m_renderer, &viewport);
  return {viewport.x, viewport.y, viewport.w, viewport.h};
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
UniquePtr<Texture> Renderer::text_blended(const std::string& text,
                                          const Font& font) const noexcept
{
  return render_text(text, [this, &font](const char* text) noexcept {
    return TTF_RenderText_Blended(font.get(), text, color());
  });
}

CENTURION_DEF
UniquePtr<Texture> Renderer::text_blended_wrapped(
    const std::string& text,
    Uint32 wrap,
    const Font& font) const noexcept
{
  return render_text(text, [this, &font, wrap](const char* text) noexcept {
    return TTF_RenderText_Blended_Wrapped(font.get(), text, color(), wrap);
  });
}

CENTURION_DEF
UniquePtr<Texture> Renderer::text_shaded(const std::string& text,
                                         const Color& bg,
                                         const Font& font) const noexcept
{
  return render_text(text, [this, &font, &bg](const char* text) noexcept {
    return TTF_RenderText_Shaded(font.get(), text, color(), bg);
  });
}

CENTURION_DEF
UniquePtr<Texture> Renderer::text_solid(const std::string& text,
                                        const Font& font) const noexcept
{
  return render_text(text, [this, &font](const char* text) noexcept {
    return TTF_RenderText_Solid(font.get(), text, color());
  });
}

CENTURION_DEF
std::string Renderer::to_string() const
{
  const auto address = detail::address_of(this);
  const auto owidth = std::to_string(output_width());
  const auto oheight = std::to_string(output_height());
  return "[Renderer@" + address + " | Output width: " + owidth +
         ", Output height: " + oheight + "]";
}

}  // namespace centurion

#endif  // CENTURION_RENDERER_SOURCE