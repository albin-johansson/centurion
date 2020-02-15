#ifndef CENTURION_RENDERER_SOURCE
#define CENTURION_RENDERER_SOURCE

#include "renderer.h"

#include <SDL.h>

#include <stdexcept>

#include "bool_converter.h"
#include "centurion_utils.h"
#include "colors.h"
#include "font.h"
#include "image.h"
#include "point.h"

namespace centurion {
namespace video {

CENTURION_DEF Renderer::Renderer(gsl::owner<SDL_Renderer*> renderer) {
  if (!renderer) {
    throw std::invalid_argument{
        "Can't create renderer from null SDL_Renderer!"};
  }
  this->renderer = renderer;

  set_color(Colors::black);
  set_logical_integer_scale(false);
}

CENTURION_DEF Renderer::Renderer(gsl::not_null<SDL_Window*> window,
                                 uint32_t flags) {
  renderer = SDL_CreateRenderer(window, -1, flags);

  set_blend_mode(SDL_BLENDMODE_BLEND);
  set_color(Colors::black);
  set_logical_integer_scale(false);
}

CENTURION_DEF Renderer::Renderer(Renderer&& other) noexcept {
  SDL_DestroyRenderer(renderer);

  renderer = other.renderer;
  other.renderer = nullptr;

  translationViewport = other.translationViewport;
}

CENTURION_DEF Renderer::~Renderer() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
}

CENTURION_DEF std::unique_ptr<Renderer> Renderer::unique(
    gsl::owner<SDL_Renderer*> renderer) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Renderer>(renderer);
#else
  return centurion::make_unique<Renderer>(renderer);
#endif
}

CENTURION_DEF std::unique_ptr<Renderer> Renderer::unique(
    gsl::not_null<SDL_Window*> window, uint32_t flags) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Renderer>(window, flags);
#else
  return centurion::make_unique<Renderer>(window, flags);
#endif
}

CENTURION_DEF std::shared_ptr<Renderer> Renderer::shared(
    gsl::owner<SDL_Renderer*> renderer) {
  return std::make_shared<Renderer>(renderer);
}

CENTURION_DEF std::shared_ptr<Renderer> Renderer::shared(
    gsl::not_null<SDL_Window*> window, uint32_t flags) {
  return std::make_shared<Renderer>(window, flags);
}

CENTURION_DEF Renderer& Renderer::operator=(Renderer&& other) noexcept {
  SDL_DestroyRenderer(renderer);

  renderer = other.renderer;
  other.renderer = nullptr;

  translationViewport = other.translationViewport;

  return *this;
}

CENTURION_DEF void Renderer::clear() const noexcept {
  SDL_RenderClear(renderer);
}

CENTURION_DEF void Renderer::present() const noexcept {
  SDL_RenderPresent(renderer);
}

CENTURION_DEF void Renderer::draw_image(const Image& img, int x, int y) const
    noexcept {
  const auto dst = SDL_Rect{x, y, img.get_width(), img.get_height()};
  SDL_RenderCopy(renderer, img, nullptr, &dst);
}

CENTURION_DEF void Renderer::draw_image(const Image& img, float x,
                                        float y) const noexcept {
  const auto dst = SDL_FRect{x, y, static_cast<float>(img.get_width()),
                             static_cast<float>(img.get_height())};
  SDL_RenderCopyF(renderer, img, nullptr, &dst);
}

CENTURION_DEF void Renderer::draw_image(const Image& img, int x, int y,
                                        int width, int height) const noexcept {
  const auto dst = SDL_Rect{x, y, width, height};
  SDL_RenderCopy(renderer, img, nullptr, &dst);
}

CENTURION_DEF void Renderer::draw_image(const Image& img, float x, float y,
                                        float width, float height) const
    noexcept {
  const auto dst = SDL_FRect{x, y, width, height};
  SDL_RenderCopyF(renderer, img, nullptr, &dst);
}

CENTURION_DEF void Renderer::draw_image(const Image& img,
                                        const SDL_Rect& source,
                                        const SDL_FRect& destination) const
    noexcept {
  SDL_RenderCopyF(renderer, img, &source, &destination);
}

CENTURION_DEF void Renderer::draw_image_translated(
    const Image& img, const SDL_Rect& source,
    const SDL_FRect& destination) const noexcept {
  const auto dst = SDL_FRect{destination.x - translationViewport.x,
                             destination.y - translationViewport.y,
                             destination.w, destination.h};
  SDL_RenderCopyF(renderer, img, &source, &dst);
}

CENTURION_DEF void Renderer::draw_image(const Image& image,
                                        const SDL_Rect& source,
                                        const SDL_Rect& destination,
                                        double angle) const noexcept {
  SDL_Point center{source.x + (source.w / 2), source.y + (source.h / 2)};
  SDL_RenderCopyEx(renderer, image, &source, &destination, angle, &center,
                   SDL_FLIP_NONE);
}

CENTURION_DEF void Renderer::draw_image(const Image& image,
                                        const SDL_Rect& source,
                                        const SDL_FRect& destination,
                                        double angle) const noexcept {
  SDL_FPoint center{static_cast<float>(source.x + (source.w / 2.0)),
                    static_cast<float>(source.y + (source.h / 2.0))};
  SDL_RenderCopyExF(renderer, image, &source, &destination, angle, &center,
                    SDL_FLIP_NONE);
}

CENTURION_DEF void Renderer::draw_image(const Image& image,
                                        const SDL_Rect& source,
                                        const SDL_Rect& destination,
                                        const math::IPoint& center,
                                        double angle) const noexcept {
  const auto c = center.to_sdl_point();
  SDL_RenderCopyEx(renderer, image, &source, &destination, angle, &c,
                   SDL_FLIP_NONE);
}

CENTURION_DEF void Renderer::draw_image(const Image& image,
                                        const SDL_Rect& source,
                                        const SDL_FRect& destination,
                                        const math::FPoint& center,
                                        double angle) const noexcept {
  const auto c = center.to_sdl_fpoint();
  SDL_RenderCopyExF(renderer, image, &source, &destination, angle, &c,
                    SDL_FLIP_NONE);
}

CENTURION_DEF void Renderer::draw_image(const Image& image,
                                        const SDL_Rect& source,
                                        const SDL_Rect& destination,
                                        double angle,
                                        SDL_RendererFlip flip) const noexcept {
  SDL_RenderCopyEx(renderer, image, &source, &destination, angle, nullptr,
                   flip);
}

CENTURION_DEF void Renderer::draw_image(const Image& image,
                                        const SDL_Rect& source,
                                        const SDL_FRect& destination,
                                        double angle,
                                        SDL_RendererFlip flip) const noexcept {
  SDL_RenderCopyExF(renderer, image, &source, &destination, angle, nullptr,
                    flip);
}

CENTURION_DEF void Renderer::draw_image(const Image& image,
                                        const SDL_Rect& source,
                                        const SDL_Rect& destination,
                                        double angle,
                                        const math::IPoint& center,
                                        SDL_RendererFlip flip) const noexcept {
  const auto c = center.to_sdl_point();
  SDL_RenderCopyEx(renderer, image, &source, &destination, angle, &c, flip);
}

CENTURION_DEF void Renderer::draw_image(const Image& image,
                                        const SDL_Rect& source,
                                        const SDL_FRect& destination,
                                        double angle,
                                        const math::FPoint& center,
                                        SDL_RendererFlip flip) const noexcept {
  const auto c = center.to_sdl_fpoint();
  SDL_RenderCopyExF(renderer, image, &source, &destination, angle, &c, flip);
}

CENTURION_DEF void Renderer::fill_rect(float x, float y, float width,
                                       float height) const noexcept {
  const auto rect = SDL_FRect{x, y, width, height};
  SDL_RenderFillRectF(renderer, &rect);
}

CENTURION_DEF void Renderer::fill_rect(int x, int y, int width,
                                       int height) const noexcept {
  const auto rect = SDL_Rect{x, y, width, height};
  SDL_RenderFillRect(renderer, &rect);
}

CENTURION_DEF void Renderer::draw_rect(float x, float y, float width,
                                       float height) const noexcept {
  const auto rect = SDL_FRect{x, y, width, height};
  SDL_RenderDrawRectF(renderer, &rect);
}

CENTURION_DEF void Renderer::draw_rect(int x, int y, int width,
                                       int height) const noexcept {
  const auto rect = SDL_Rect{x, y, width, height};
  SDL_RenderDrawRect(renderer, &rect);
}

CENTURION_DEF void Renderer::draw_line(const math::FPoint& start,
                                       const math::FPoint& end) const noexcept {
  SDL_RenderDrawLineF(renderer, start.get_x(), start.get_y(), end.get_x(),
                      end.get_y());
}

CENTURION_DEF void Renderer::draw_line(const math::IPoint& start,
                                       const math::IPoint& end) const noexcept {
  SDL_RenderDrawLine(renderer, start.get_x(), start.get_y(), end.get_x(),
                     end.get_y());
}

CENTURION_DEF void Renderer::draw_lines(
    const std::vector<math::IPoint>& points) const noexcept {
  if (points.empty()) {
    return;
  } else {
    // TODO write own method that achieves the same thing to avoid the
    // reinterpret_cast
    const auto* front = reinterpret_cast<const SDL_Point*>(&points.front());
    SDL_RenderDrawLines(renderer, front, static_cast<int>(points.size()));
  }
}

CENTURION_DEF void Renderer::draw_text(const std::string& text, float x,
                                       float y, const Font& font) const {
  if (!text.empty()) {
    const auto texture = create_image(text, font);

    if (!texture) {
      return;
    }

    draw_image(*texture, x, y);
  }
}

CENTURION_DEF void Renderer::set_color(uint8_t red, uint8_t green, uint8_t blue,
                                       uint8_t alpha) const noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

CENTURION_DEF void Renderer::set_color(const Color& color) const noexcept {
  SDL_SetRenderDrawColor(renderer, color.get_red(), color.get_green(),
                         color.get_blue(), color.get_alpha());
}

#ifdef CENTURION_HAS_OPTIONAL

CENTURION_DEF void Renderer::set_clip(std::optional<SDL_Rect> area) noexcept {
  if (area) {
    SDL_RenderSetClipRect(renderer, &*area);
  } else {
    SDL_RenderSetClipRect(renderer, nullptr);
  }
}

#endif

CENTURION_DEF void Renderer::set_viewport(const SDL_Rect& viewport) noexcept {
  SDL_RenderSetViewport(renderer, &viewport);
}

CENTURION_DEF void Renderer::set_translation_viewport(
    const SDL_FRect& viewport) noexcept {
  translationViewport = viewport;
}

CENTURION_DEF void Renderer::set_blend_mode(
    const SDL_BlendMode& blendMode) noexcept {
  SDL_SetRenderDrawBlendMode(renderer, blendMode);
}

CENTURION_DEF void Renderer::set_target(const Image* texture) noexcept {
  if (texture && texture->is_target()) {
    SDL_SetRenderTarget(renderer, *texture);
  } else {
    SDL_SetRenderTarget(renderer, nullptr);
  }
}

CENTURION_DEF void Renderer::set_scale(float xScale, float yScale) noexcept {
  if (xScale > 0 && yScale > 0) {
    SDL_RenderSetScale(renderer, xScale, yScale);
  }
}

CENTURION_DEF void Renderer::set_logical_size(int width, int height) noexcept {
  if (width > 0 && height > 0) {
    SDL_RenderSetLogicalSize(renderer, width, height);
  }
}

CENTURION_DEF void Renderer::set_logical_integer_scale(
    bool useLogicalIntegerScale) noexcept {
  SDL_RenderSetIntegerScale(renderer,
                            BoolConverter::convert(useLogicalIntegerScale));
}

CENTURION_DEF Color Renderer::get_color() const noexcept {
  uint8_t r = 0, g = 0, b = 0, a = 0;
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  return {r, g, b, a};
}

CENTURION_DEF int Renderer::get_logical_width() const noexcept {
  int w = 0;
  SDL_RenderGetLogicalSize(renderer, &w, nullptr);
  return w;
}

CENTURION_DEF int Renderer::get_logical_height() const noexcept {
  int h = 0;
  SDL_RenderGetLogicalSize(renderer, nullptr, &h);
  return h;
}

CENTURION_DEF bool Renderer::is_clipping_enabled() const noexcept {
  return SDL_RenderIsClipEnabled(renderer);
}

#ifdef CENTURION_HAS_OPTIONAL

CENTURION_DEF std::optional<SDL_Rect> Renderer::get_clip() const noexcept {
  SDL_Rect rect{0, 0, 0, 0};
  SDL_RenderGetClipRect(renderer, &rect);
  if (SDL_RectEmpty(&rect)) {
    return std::nullopt;
  } else {
    return rect;
  }
}

#endif

CENTURION_DEF SDL_RendererInfo Renderer::get_info() const noexcept {
  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  return info;
}

CENTURION_DEF int Renderer::get_output_width() const noexcept {
  int width = 0;
  SDL_GetRendererOutputSize(renderer, &width, nullptr);
  return width;
}

CENTURION_DEF int Renderer::get_output_height() const noexcept {
  int height = 0;
  SDL_GetRendererOutputSize(renderer, nullptr, &height);
  return height;
}

CENTURION_DEF std::pair<int, int> Renderer::get_output_size() const noexcept {
  int width = 0;
  int height = 0;
  SDL_GetRendererOutputSize(renderer, &width, &height);
  return {width, height};
}

CENTURION_DEF float Renderer::get_x_scale() const noexcept {
  float xScale = 0;
  SDL_RenderGetScale(renderer, &xScale, nullptr);
  return xScale;
}

CENTURION_DEF float Renderer::get_y_scale() const noexcept {
  float yScale = 0;
  SDL_RenderGetScale(renderer, nullptr, &yScale);
  return yScale;
}

CENTURION_DEF SDL_Rect Renderer::get_viewport() const noexcept {
  SDL_Rect viewport{0, 0, 0, 0};
  SDL_RenderGetViewport(renderer, &viewport);
  return viewport;
}

CENTURION_DEF const SDL_FRect& Renderer::get_translation_viewport() const
    noexcept {
  return translationViewport;
}

CENTURION_DEF uint32_t Renderer::get_flags() const noexcept {
  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  return info.flags;
}

CENTURION_DEF bool Renderer::is_vsync_enabled() const noexcept {
  return get_flags() & SDL_RENDERER_PRESENTVSYNC;
}

CENTURION_DEF bool Renderer::is_accelerated() const noexcept {
  return get_flags() & SDL_RENDERER_ACCELERATED;
}

CENTURION_DEF bool Renderer::is_software_based() const noexcept {
  return get_flags() & SDL_RENDERER_SOFTWARE;
}

CENTURION_DEF bool Renderer::is_supporting_target_textures() const noexcept {
  return get_flags() & SDL_RENDERER_TARGETTEXTURE;
}

CENTURION_DEF bool Renderer::is_using_integer_logical_scaling() const noexcept {
  return SDL_RenderGetIntegerScale(renderer);
}

CENTURION_DEF std::unique_ptr<Image> Renderer::create_image(
    const std::string& s, const Font& font) const {
  if (s.empty()) {
    return nullptr;
  }

  SDL_Surface* surface = TTF_RenderText_Blended(font, s.c_str(), get_color());

  if (!surface) {
    return nullptr;
  }

  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return std::make_unique<Image>(texture);
}

CENTURION_DEF std::string Renderer::to_string() const {
  const auto address = impl::address_of(this);
  const auto owidth = std::to_string(get_output_width());
  const auto oheight = std::to_string(get_output_height());
  return "[Renderer@" + address + " | Output width: " + owidth +
         ", Output height: " + oheight + "]";
}

CENTURION_DEF Renderer::operator SDL_Renderer*() const noexcept {
  return renderer;
}

}  // namespace video
}  // namespace centurion

#endif  // CENTURION_RENDERER_SOURCE