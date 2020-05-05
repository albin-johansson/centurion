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
  this->renderer = renderer;

  set_color(black);
  set_logical_integer_scale(false);
}

CENTURION_DEF
Renderer::Renderer(const Window& window, SDL_RendererFlags flags)
{
  renderer = SDL_CreateRenderer(window.get_internal(), -1, flags);

  set_blend_mode(BlendMode::Blend);
  set_color(black);
  set_logical_integer_scale(false);
}

CENTURION_DEF
Renderer::Renderer(Renderer&& other) noexcept
{
  if (this != &other) {
    destroy();

    renderer = other.renderer;
    other.renderer = nullptr;

    translationViewport = other.translationViewport;
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
  if (renderer) {
    SDL_DestroyRenderer(renderer);
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

    renderer = other.renderer;
    other.renderer = nullptr;

    translationViewport = other.translationViewport;
  }
  return *this;
}

CENTURION_DEF
void Renderer::clear() const noexcept
{
  SDL_RenderClear(renderer);
}

CENTURION_DEF
void Renderer::present() const noexcept
{
  SDL_RenderPresent(renderer);
}

CENTURION_DEF
void Renderer::draw_rect(const math::IRect& rect) const noexcept
{
  SDL_RenderDrawRect(renderer, static_cast<const SDL_Rect*>(rect));
}

CENTURION_DEF
void Renderer::fill_rect(const math::IRect& rect) const noexcept
{
  SDL_RenderFillRect(renderer, static_cast<const SDL_Rect*>(rect));
}

CENTURION_DEF
void Renderer::draw_rect_f(const math::FRect& rect) const noexcept
{
  SDL_RenderDrawRectF(renderer, static_cast<const SDL_FRect*>(rect));
}

CENTURION_DEF
void Renderer::fill_rect_f(const math::FRect& rect) const noexcept
{
  SDL_RenderFillRectF(renderer, static_cast<const SDL_FRect*>(rect));
}

CENTURION_DEF
void Renderer::draw_line(const math::IPoint& start,
                         const math::IPoint& end) const noexcept
{
  SDL_RenderDrawLine(
      renderer, start.get_x(), start.get_y(), end.get_x(), end.get_y());
}

CENTURION_DEF
void Renderer::draw_lines(
    const std::vector<math::IPoint>& points) const noexcept
{
  if (!points.empty()) {
    const auto* firstPoint = static_cast<const SDL_Point*>(points.front());
    SDL_RenderDrawLines(renderer, firstPoint, static_cast<int>(points.size()));
  }
}

CENTURION_DEF
void Renderer::draw_line_f(const math::FPoint& start,
                           const math::FPoint& end) const noexcept
{
  SDL_RenderDrawLineF(
      renderer, start.get_x(), start.get_y(), end.get_x(), end.get_y());
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      math::IPoint position) const noexcept
{
  const SDL_Rect dst{position.get_x(),
                     position.get_y(),
                     texture.get_width(),
                     texture.get_height()};
  SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const math::IRect& rect) const noexcept
{
  const auto* dst = static_cast<const SDL_Rect*>(rect);
  SDL_RenderCopy(renderer, texture, nullptr, dst);
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const math::IRect& src,
                      const math::IRect& dst) const noexcept
{
  SDL_RenderCopy(renderer,
                 texture,
                 static_cast<const SDL_Rect*>(src),
                 static_cast<const SDL_Rect*>(dst));
}

CENTURION_DEF
void Renderer::render(const Texture& texture,
                      const math::IRect& src,
                      const math::IRect& dst,
                      double angle) const noexcept
{
  SDL_RenderCopyEx(renderer,
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
                      math::IPoint center) const noexcept
{
  SDL_RenderCopyEx(renderer,
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
                      SDL_RendererFlip flip) const noexcept
{
  SDL_RenderCopyEx(renderer,
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
                      SDL_RendererFlip flip) const noexcept
{
  SDL_RenderCopyEx(renderer,
                   texture,
                   static_cast<const SDL_Rect*>(src),
                   static_cast<const SDL_Rect*>(dst),
                   angle,
                   static_cast<const SDL_Point*>(center),
                   flip);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        math::FPoint position) const noexcept
{
  const auto dst = SDL_FRect{position.get_x(),
                             position.get_y(),
                             static_cast<float>(texture.get_width()),
                             static_cast<float>(texture.get_height())};
  SDL_RenderCopyF(renderer, texture, nullptr, &dst);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const math::FRect& rect) const noexcept
{
  const auto* dst = static_cast<const SDL_FRect*>(rect);
  SDL_RenderCopyF(renderer, texture, nullptr, dst);
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const math::IRect& src,
                        const math::FRect& dst) const noexcept
{
  SDL_RenderCopyF(renderer,
                  texture,
                  static_cast<const SDL_Rect*>(src),
                  static_cast<const SDL_FRect*>(dst));
}

CENTURION_DEF
void Renderer::render_f(const Texture& texture,
                        const math::IRect& src,
                        const math::FRect& dst,
                        double angle) const noexcept
{
  SDL_RenderCopyExF(renderer,
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
                        math::FPoint center) const noexcept
{
  SDL_RenderCopyExF(renderer,
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
                        SDL_RendererFlip flip) const noexcept
{
  SDL_RenderCopyExF(renderer,
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
                        SDL_RendererFlip flip) const noexcept
{
  SDL_RenderCopyExF(renderer,
                    texture,
                    static_cast<const SDL_Rect*>(src),
                    static_cast<const SDL_FRect*>(dst),
                    angle,
                    static_cast<const SDL_FPoint*>(center),
                    flip);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        math::IPoint position) const noexcept
{
  const auto tx =
      position.get_x() - static_cast<int>(translationViewport.get_x());
  const auto ty =
      position.get_y() - static_cast<int>(translationViewport.get_y());
  render(texture, {tx, ty});
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& rect) const noexcept
{
  const auto tx = rect.get_x() - static_cast<int>(translationViewport.get_x());
  const auto ty = rect.get_y() - static_cast<int>(translationViewport.get_y());
  render(texture, {tx, ty, rect.get_width(), rect.get_height()});
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst) const noexcept
{
  const auto tx = dst.get_x() - static_cast<int>(translationViewport.get_x());
  const auto ty = dst.get_y() - static_cast<int>(translationViewport.get_y());
  render(texture, src, {tx, ty, dst.get_width(), dst.get_height()});
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst,
                        double angle) const noexcept
{
  const auto tx = dst.get_x() - static_cast<int>(translationViewport.get_x());
  const auto ty = dst.get_y() - static_cast<int>(translationViewport.get_y());
  render(texture, src, {tx, ty, dst.get_width(), dst.get_height()}, angle);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst,
                        double angle,
                        math::IPoint center) const noexcept
{
  const auto tx = dst.get_x() - static_cast<int>(translationViewport.get_x());
  const auto ty = dst.get_y() - static_cast<int>(translationViewport.get_y());
  render(
      texture, src, {tx, ty, dst.get_width(), dst.get_height()}, angle, center);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst,
                        SDL_RendererFlip flip) const noexcept
{
  const auto tx = dst.get_x() - static_cast<int>(translationViewport.get_x());
  const auto ty = dst.get_y() - static_cast<int>(translationViewport.get_y());
  render(texture, src, {tx, ty, dst.get_width(), dst.get_height()}, flip);
}

CENTURION_DEF
void Renderer::render_t(const Texture& texture,
                        const math::IRect& src,
                        const math::IRect& dst,
                        double angle,
                        math::IPoint center,
                        SDL_RendererFlip flip) const noexcept
{
  const auto tx = dst.get_x() - static_cast<int>(translationViewport.get_x());
  const auto ty = dst.get_y() - static_cast<int>(translationViewport.get_y());
  render(texture,
         src,
         {tx, ty, dst.get_width(), dst.get_height()},
         angle,
         center,
         flip);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         math::FPoint position) const noexcept
{
  const auto tx = position.get_x() - translationViewport.get_x();
  const auto ty = position.get_y() - translationViewport.get_y();
  render_f(texture, {tx, ty});
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::FRect& rect) const noexcept
{
  const auto tx = rect.get_x() - translationViewport.get_x();
  const auto ty = rect.get_y() - translationViewport.get_y();
  render_f(texture, {tx, ty, rect.get_width(), rect.get_height()});
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst) const noexcept
{
  const auto tx = dst.get_x() - translationViewport.get_x();
  const auto ty = dst.get_y() - translationViewport.get_y();
  render_f(texture, src, {tx, ty, dst.get_width(), dst.get_height()});
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst,
                         double angle) const noexcept
{
  const auto tx = dst.get_x() - translationViewport.get_x();
  const auto ty = dst.get_y() - translationViewport.get_y();
  render_f(texture, src, {tx, ty, dst.get_width(), dst.get_height()}, angle);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst,
                         double angle,
                         math::FPoint center) const noexcept
{
  const auto tx = dst.get_x() - translationViewport.get_x();
  const auto ty = dst.get_y() - translationViewport.get_y();
  render_f(
      texture, src, {tx, ty, dst.get_width(), dst.get_height()}, angle, center);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst,
                         SDL_RendererFlip flip) const noexcept
{
  const auto tx = dst.get_x() - translationViewport.get_x();
  const auto ty = dst.get_y() - translationViewport.get_y();
  render_f(texture, src, {tx, ty, dst.get_width(), dst.get_height()}, flip);
}

CENTURION_DEF
void Renderer::render_tf(const Texture& texture,
                         const math::IRect& src,
                         const math::FRect& dst,
                         double angle,
                         math::FPoint center,
                         SDL_RendererFlip flip) const noexcept
{
  const auto tx = dst.get_x() - translationViewport.get_x();
  const auto ty = dst.get_y() - translationViewport.get_y();
  render_f(texture,
           src,
           {tx, ty, dst.get_width(), dst.get_height()},
           angle,
           center,
           flip);
}

CENTURION_DEF
void Renderer::render_text(const char* text,
                           math::IRect pos,
                           const Font& font) const
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
                             const Font& font) const
{
  if (text) {
    const auto texture = create_image(text, font);
    if (texture) {
      render_f(*texture, pos);
    }
  }
}

CENTURION_DEF
void Renderer::set_color(const Color& color) const noexcept
{
  SDL_SetRenderDrawColor(
      renderer, color.red(), color.green(), color.blue(), color.alpha());
}

CENTURION_DEF
void Renderer::set_clip(Optional<math::IRect> area) noexcept
{
  if (area) {
    SDL_RenderSetClipRect(renderer, static_cast<const SDL_Rect*>(*area));
  } else {
    SDL_RenderSetClipRect(renderer, nullptr);
  }
}

CENTURION_DEF
void Renderer::set_viewport(const math::IRect& viewport) noexcept
{
  SDL_RenderSetViewport(renderer, static_cast<const SDL_Rect*>(viewport));
}

CENTURION_DEF
void Renderer::set_translation_viewport(const math::FRect& viewport) noexcept
{
  translationViewport = viewport;
}

CENTURION_DEF
void Renderer::set_blend_mode(BlendMode mode) noexcept
{
  SDL_SetRenderDrawBlendMode(renderer, static_cast<SDL_BlendMode>(mode));
}

CENTURION_DEF
void Renderer::set_target(const Texture* texture) noexcept
{
  if (texture && texture->is_target()) {
    SDL_SetRenderTarget(renderer, *texture);
  } else {
    SDL_SetRenderTarget(renderer, nullptr);
  }
}

CENTURION_DEF
void Renderer::set_scale(float xScale, float yScale) noexcept
{
  if (xScale > 0 && yScale > 0) {
    SDL_RenderSetScale(renderer, xScale, yScale);
  }
}

CENTURION_DEF
void Renderer::set_logical_size(int width, int height) noexcept
{
  if (width > 0 && height > 0) {
    SDL_RenderSetLogicalSize(renderer, width, height);
  }
}

CENTURION_DEF
void Renderer::set_logical_integer_scale(bool useLogicalIntegerScale) noexcept
{
  SDL_RenderSetIntegerScale(renderer, convert_bool(useLogicalIntegerScale));
}

CENTURION_DEF
Color Renderer::get_color() const noexcept
{
  uint8_t r = 0, g = 0, b = 0, a = 0;
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  return {r, g, b, a};
}

CENTURION_DEF
int Renderer::get_logical_width() const noexcept
{
  int w = 0;
  SDL_RenderGetLogicalSize(renderer, &w, nullptr);
  return w;
}

CENTURION_DEF
int Renderer::get_logical_height() const noexcept
{
  int h = 0;
  SDL_RenderGetLogicalSize(renderer, nullptr, &h);
  return h;
}

CENTURION_DEF
bool Renderer::is_clipping_enabled() const noexcept
{
  return SDL_RenderIsClipEnabled(renderer);
}

CENTURION_DEF
Optional<math::IRect> Renderer::get_clip() const noexcept
{
  SDL_Rect rect{0, 0, 0, 0};
  SDL_RenderGetClipRect(renderer, &rect);
  if (SDL_RectEmpty(&rect)) {
    return tl::nullopt;
  } else {
    return math::IRect{rect.x, rect.y, rect.w, rect.h};
  }
}

CENTURION_DEF
SDL_RendererInfo Renderer::get_info() const noexcept
{
  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  return info;
}

CENTURION_DEF
int Renderer::get_output_width() const noexcept
{
  int width = 0;
  SDL_GetRendererOutputSize(renderer, &width, nullptr);
  return width;
}

CENTURION_DEF
int Renderer::get_output_height() const noexcept
{
  int height = 0;
  SDL_GetRendererOutputSize(renderer, nullptr, &height);
  return height;
}

CENTURION_DEF
std::pair<int, int> Renderer::get_output_size() const noexcept
{
  int width = 0;
  int height = 0;
  SDL_GetRendererOutputSize(renderer, &width, &height);
  return {width, height};
}

CENTURION_DEF
BlendMode Renderer::get_blend_mode() const noexcept
{
  SDL_BlendMode mode;
  SDL_GetRenderDrawBlendMode(renderer, &mode);
  return static_cast<BlendMode>(mode);
}

CENTURION_DEF
float Renderer::get_x_scale() const noexcept
{
  float xScale = 0;
  SDL_RenderGetScale(renderer, &xScale, nullptr);
  return xScale;
}

CENTURION_DEF
float Renderer::get_y_scale() const noexcept
{
  float yScale = 0;
  SDL_RenderGetScale(renderer, nullptr, &yScale);
  return yScale;
}

CENTURION_DEF
math::IRect Renderer::get_viewport() const noexcept
{
  SDL_Rect viewport{0, 0, 0, 0};
  SDL_RenderGetViewport(renderer, &viewport);
  return {viewport.x, viewport.y, viewport.w, viewport.h};
}

CENTURION_DEF
const math::FRect& Renderer::get_translation_viewport() const noexcept
{
  return translationViewport;
}

CENTURION_DEF
uint32_t Renderer::get_flags() const noexcept
{
  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  return info.flags;
}

CENTURION_DEF
bool Renderer::is_vsync_enabled() const noexcept
{
  return get_flags() & SDL_RENDERER_PRESENTVSYNC;
}

CENTURION_DEF
bool Renderer::is_accelerated() const noexcept
{
  return get_flags() & SDL_RENDERER_ACCELERATED;
}

CENTURION_DEF
bool Renderer::is_software_based() const noexcept
{
  return get_flags() & SDL_RENDERER_SOFTWARE;
}

CENTURION_DEF
bool Renderer::is_supporting_target_textures() const noexcept
{
  return get_flags() & SDL_RENDERER_TARGETTEXTURE;
}

CENTURION_DEF
bool Renderer::is_using_integer_logical_scaling() const noexcept
{
  return SDL_RenderGetIntegerScale(renderer);
}

CENTURION_DEF
std::unique_ptr<Texture> Renderer::create_image(const std::string& s,
                                                const Font& font) const
{
  if (s.empty()) {
    return nullptr;
  }

  SDL_Surface* surface = TTF_RenderText_Blended(font, s.c_str(), get_color());

  if (!surface) {
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return centurion::make_unique<Texture>(texture);
}

CENTURION_DEF
std::string Renderer::to_string() const
{
  const auto address = address_of(this);
  const auto owidth = std::to_string(get_output_width());
  const auto oheight = std::to_string(get_output_height());
  return "[Renderer@" + address + " | Output width: " + owidth +
         ", Output height: " + oheight + "]";
}

CENTURION_DEF
SDL_Renderer* Renderer::get_internal() const noexcept
{
  return renderer;
}

CENTURION_DEF
Renderer::operator SDL_Renderer*() const noexcept
{
  return renderer;
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_RENDERER_SOURCE