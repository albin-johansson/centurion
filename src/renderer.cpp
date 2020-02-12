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

Renderer::Renderer(gsl::owner<SDL_Renderer*> renderer) {
  if (!renderer) {
    throw std::invalid_argument{
        "Can't create renderer from null SDL_Renderer!"};
  }
  this->renderer = renderer;

  set_color(Colors::black);
  set_logical_integer_scale(false);
}

Renderer::Renderer(gsl::not_null<SDL_Window*> window, uint32_t flags) {
  renderer = SDL_CreateRenderer(window, -1, flags);

  set_blend_mode(SDL_BLENDMODE_BLEND);
  set_color(Colors::black);
  set_logical_integer_scale(false);
}

Renderer::Renderer(Renderer&& other) noexcept {
  SDL_DestroyRenderer(renderer);

  renderer = other.renderer;
  other.renderer = nullptr;

  translationViewport = other.translationViewport;
}

Renderer::~Renderer() {
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
}

std::unique_ptr<Renderer> Renderer::unique(gsl::owner<SDL_Renderer*> renderer) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Renderer>(renderer);
#else
  return centurion::make_unique<Renderer>(renderer);
#endif
}

std::unique_ptr<Renderer> Renderer::unique(gsl::not_null<SDL_Window*> window,
                                           uint32_t flags) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Renderer>(window, flags);
#else
  return centurion::make_unique<Renderer>(window, flags);
#endif
}

std::shared_ptr<Renderer> Renderer::shared(gsl::owner<SDL_Renderer*> renderer) {
  return std::make_shared<Renderer>(renderer);
}

std::shared_ptr<Renderer> Renderer::shared(gsl::not_null<SDL_Window*> window,
                                           uint32_t flags) {
  return std::make_shared<Renderer>(window, flags);
}

Renderer& Renderer::operator=(Renderer&& other) noexcept {
  SDL_DestroyRenderer(renderer);

  renderer = other.renderer;
  other.renderer = nullptr;

  translationViewport = other.translationViewport;

  return *this;
}

void Renderer::clear() const noexcept { SDL_RenderClear(renderer); }

void Renderer::present() const noexcept { SDL_RenderPresent(renderer); }

void Renderer::draw_image(const Image& img, int x, int y) const noexcept {
  const auto dst = SDL_Rect{x, y, img.get_width(), img.get_height()};
  SDL_RenderCopy(renderer, img, nullptr, &dst);
}

void Renderer::draw_image(const Image& img, float x, float y) const noexcept {
  const auto dst = SDL_FRect{x, y, static_cast<float>(img.get_width()),
                             static_cast<float>(img.get_height())};
  SDL_RenderCopyF(renderer, img, nullptr, &dst);
}

void Renderer::draw_image(const Image& img, int x, int y, int width,
                          int height) const noexcept {
  const auto dst = SDL_Rect{x, y, width, height};
  SDL_RenderCopy(renderer, img, nullptr, &dst);
}

void Renderer::draw_image(const Image& img, float x, float y, float width,
                          float height) const noexcept {
  const auto dst = SDL_FRect{x, y, width, height};
  SDL_RenderCopyF(renderer, img, nullptr, &dst);
}

void Renderer::draw_image(const Image& img, const SDL_Rect& source,
                          const SDL_FRect& destination) const noexcept {
  SDL_RenderCopyF(renderer, img, &source, &destination);
}

void Renderer::draw_image_translated(const Image& img, const SDL_Rect& source,
                                     const SDL_FRect& destination) const
    noexcept {
  const auto dst = SDL_FRect{destination.x - translationViewport.x,
                             destination.y - translationViewport.y,
                             destination.w, destination.h};
  SDL_RenderCopyF(renderer, img, &source, &dst);
}

void Renderer::draw_image(const Image& image, const SDL_Rect& source,
                          const SDL_Rect& destination, double angle) const
    noexcept {
  SDL_Point center{source.x + (source.w / 2), source.y + (source.h / 2)};
  SDL_RenderCopyEx(renderer, image, &source, &destination, angle, &center,
                   SDL_FLIP_NONE);
}

void Renderer::draw_image(const Image& image, const SDL_Rect& source,
                          const SDL_FRect& destination, double angle) const
    noexcept {
  SDL_FPoint center{static_cast<float>(source.x + (source.w / 2.0)),
                    static_cast<float>(source.y + (source.h / 2.0))};
  SDL_RenderCopyExF(renderer, image, &source, &destination, angle, &center,
                    SDL_FLIP_NONE);
}

void Renderer::draw_image(const Image& image, const SDL_Rect& source,
                          const SDL_Rect& destination, const Point& center,
                          double angle) const noexcept {
  const SDL_Point c = center;
  SDL_RenderCopyEx(renderer, image, &source, &destination, angle, &c,
                   SDL_FLIP_NONE);
}

void Renderer::draw_image(const Image& image, const SDL_Rect& source,
                          const SDL_FRect& destination, const FPoint& center,
                          double angle) const noexcept {
  const SDL_FPoint c = center;
  SDL_RenderCopyExF(renderer, image, &source, &destination, angle, &c,
                    SDL_FLIP_NONE);
}

void Renderer::draw_image(const Image& image, const SDL_Rect& source,
                          const SDL_Rect& destination, double angle,
                          SDL_RendererFlip flip) const noexcept {
  SDL_RenderCopyEx(renderer, image, &source, &destination, angle, nullptr,
                   flip);
}

void Renderer::draw_image(const Image& image, const SDL_Rect& source,
                          const SDL_FRect& destination, double angle,
                          SDL_RendererFlip flip) const noexcept {
  SDL_RenderCopyExF(renderer, image, &source, &destination, angle, nullptr,
                    flip);
}

void Renderer::draw_image(const Image& image, const SDL_Rect& source,
                          const SDL_Rect& destination, double angle,
                          const Point& center, SDL_RendererFlip flip) const
    noexcept {
  const SDL_Point c = center;
  SDL_RenderCopyEx(renderer, image, &source, &destination, angle, &c, flip);
}

void Renderer::draw_image(const Image& image, const SDL_Rect& source,
                          const SDL_FRect& destination, double angle,
                          const FPoint& center, SDL_RendererFlip flip) const
    noexcept {
  const SDL_FPoint c = center;
  SDL_RenderCopyExF(renderer, image, &source, &destination, angle, &c, flip);
}

void Renderer::fill_rect(float x, float y, float width, float height) const
    noexcept {
  const auto rect = SDL_FRect{x, y, width, height};
  SDL_RenderFillRectF(renderer, &rect);
}

void Renderer::fill_rect(int x, int y, int width, int height) const noexcept {
  const auto rect = SDL_Rect{x, y, width, height};
  SDL_RenderFillRect(renderer, &rect);
}

void Renderer::draw_rect(float x, float y, float width, float height) const
    noexcept {
  const auto rect = SDL_FRect{x, y, width, height};
  SDL_RenderDrawRectF(renderer, &rect);
}

void Renderer::draw_rect(int x, int y, int width, int height) const noexcept {
  const auto rect = SDL_Rect{x, y, width, height};
  SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::draw_line(const FPoint& start, const FPoint& end) const
    noexcept {
  SDL_RenderDrawLineF(renderer, start.get_x(), start.get_y(), end.get_x(),
                      end.get_y());
}

void Renderer::draw_line(const Point& start, const Point& end) const noexcept {
  SDL_RenderDrawLine(renderer, start.get_x(), start.get_y(), end.get_x(),
                     end.get_y());
}

void Renderer::draw_lines(const std::vector<Point>& points) const noexcept {
  if (points.empty()) {
    return;
  } else {
    // TODO write own method that achieves the same thing to avoid the
    // reinterpret_cast
    const auto* front = reinterpret_cast<const SDL_Point*>(&points.front());
    SDL_RenderDrawLines(renderer, front, static_cast<int>(points.size()));
  }
}

void Renderer::draw_text(const std::string& text, float x, float y,
                         const Font& font) const {
  if (!text.empty()) {
    const auto texture = create_image(text, font);

    if (!texture) {
      return;
    }

    draw_image(*texture, x, y);
  }
}

void Renderer::set_color(uint8_t red, uint8_t green, uint8_t blue,
                         uint8_t alpha) const noexcept {
  SDL_SetRenderDrawColor(renderer, red, green, blue, alpha);
}

void Renderer::set_color(const Color& color) const noexcept {
  SDL_SetRenderDrawColor(renderer, color.get_red(), color.get_green(),
                         color.get_blue(), color.get_alpha());
}

#ifdef CENTURION_HAS_OPTIONAL

void Renderer::set_clip(std::optional<SDL_Rect> area) noexcept {
  if (area) {
    SDL_RenderSetClipRect(renderer, &*area);
  } else {
    SDL_RenderSetClipRect(renderer, nullptr);
  }
}

#endif

void Renderer::set_viewport(const SDL_Rect& viewport) noexcept {
  SDL_RenderSetViewport(renderer, &viewport);
}

void Renderer::set_translation_viewport(const SDL_FRect& viewport) noexcept {
  translationViewport = viewport;
}

void Renderer::set_blend_mode(const SDL_BlendMode& blendMode) noexcept {
  SDL_SetRenderDrawBlendMode(renderer, blendMode);
}

void Renderer::set_target(const Image* texture) noexcept {
  if (texture && texture->is_target()) {
    SDL_SetRenderTarget(renderer, *texture);
  } else {
    SDL_SetRenderTarget(renderer, nullptr);
  }
}

void Renderer::set_scale(float xScale, float yScale) noexcept {
  if (xScale > 0 && yScale > 0) {
    SDL_RenderSetScale(renderer, xScale, yScale);
  }
}

void Renderer::set_logical_size(int width, int height) noexcept {
  if (width > 0 && height > 0) {
    SDL_RenderSetLogicalSize(renderer, width, height);
  }
}

void Renderer::set_logical_integer_scale(bool useLogicalIntegerScale) noexcept {
  SDL_RenderSetIntegerScale(renderer,
                            BoolConverter::convert(useLogicalIntegerScale));
}

Color Renderer::get_color() const noexcept {
  uint8_t r = 0, g = 0, b = 0, a = 0;
  SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
  return {r, g, b, a};
}

int Renderer::get_logical_width() const noexcept {
  int w = 0;
  SDL_RenderGetLogicalSize(renderer, &w, nullptr);
  return w;
}

int Renderer::get_logical_height() const noexcept {
  int h = 0;
  SDL_RenderGetLogicalSize(renderer, nullptr, &h);
  return h;
}

bool Renderer::is_clipping_enabled() const noexcept {
  return SDL_RenderIsClipEnabled(renderer);
}

#ifdef CENTURION_HAS_OPTIONAL

std::optional<SDL_Rect> Renderer::get_clip() const noexcept {
  SDL_Rect rect{0, 0, 0, 0};
  SDL_RenderGetClipRect(renderer, &rect);
  if (SDL_RectEmpty(&rect)) {
    return std::nullopt;
  } else {
    return rect;
  }
}

#endif

SDL_RendererInfo Renderer::get_info() const noexcept {
  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  return info;
}

int Renderer::get_output_width() const noexcept {
  int width = 0;
  SDL_GetRendererOutputSize(renderer, &width, nullptr);
  return width;
}

int Renderer::get_output_height() const noexcept {
  int height = 0;
  SDL_GetRendererOutputSize(renderer, nullptr, &height);
  return height;
}

std::pair<int, int> Renderer::get_output_size() const noexcept {
  int width = 0;
  int height = 0;
  SDL_GetRendererOutputSize(renderer, &width, &height);
  return {width, height};
}

float Renderer::get_x_scale() const noexcept {
  float xScale = 0;
  SDL_RenderGetScale(renderer, &xScale, nullptr);
  return xScale;
}

float Renderer::get_y_scale() const noexcept {
  float yScale = 0;
  SDL_RenderGetScale(renderer, nullptr, &yScale);
  return yScale;
}

SDL_Rect Renderer::get_viewport() const noexcept {
  SDL_Rect viewport{0, 0, 0, 0};
  SDL_RenderGetViewport(renderer, &viewport);
  return viewport;
}

const SDL_FRect& Renderer::get_translation_viewport() const noexcept {
  return translationViewport;
}

uint32_t Renderer::get_flags() const noexcept {
  SDL_RendererInfo info;
  SDL_GetRendererInfo(renderer, &info);
  return info.flags;
}

bool Renderer::is_vsync_enabled() const noexcept {
  return get_flags() & SDL_RENDERER_PRESENTVSYNC;
}

bool Renderer::is_accelerated() const noexcept {
  return get_flags() & SDL_RENDERER_ACCELERATED;
}

bool Renderer::is_software_based() const noexcept {
  return get_flags() & SDL_RENDERER_SOFTWARE;
}

bool Renderer::is_supporting_target_textures() const noexcept {
  return get_flags() & SDL_RENDERER_TARGETTEXTURE;
}

bool Renderer::is_using_integer_logical_scaling() const noexcept {
  return SDL_RenderGetIntegerScale(renderer);
}

std::unique_ptr<Image> Renderer::create_image(const std::string& s,
                                              const Font& font) const {
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

std::string Renderer::to_string() const {
  const auto address = CenturionUtils::address(this);
  const auto owidth = std::to_string(get_output_width());
  const auto oheight = std::to_string(get_output_height());
  return "[Renderer@" + address + " | Output width: " + owidth +
         ", Output height: " + oheight + "]";
}

Renderer::operator SDL_Renderer*() const noexcept { return renderer; }

}  // namespace centurion