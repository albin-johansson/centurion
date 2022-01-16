#ifndef CENTURION_RENDER_HPP_
#define CENTURION_RENDER_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <cmath>        // floor, sqrt
#include <cstddef>      // size_t
#include <optional>     // optional
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string>       // string, string_literals
#include <string_view>  // string_view
#include <utility>      // pair

#include "color.hpp"
#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "math.hpp"
#include "surface.hpp"
#include "texture.hpp"
#include "unicode.hpp"
#include "video.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

template <typename T>
class BasicRenderer;

using Renderer = BasicRenderer<detail::owner_tag>;
using RendererHandle = BasicRenderer<detail::handle_tag>;

template <typename T>
class BasicRenderer final {
 public:
  enum RendererFlags : uint32 {
    Software = SDL_RENDERER_SOFTWARE,             ///< Software renderer
    Accelerated = SDL_RENDERER_ACCELERATED,       ///< Hardware-accelerated
    TargetTextures = SDL_RENDERER_TARGETTEXTURE,  ///< Supports target textures
    VSync = SDL_RENDERER_PRESENTVSYNC             ///< Renderer Uses VSync
  };

  explicit BasicRenderer(maybe_owner<SDL_Renderer*> renderer) noexcept(detail::is_handle<T>)
      : mRenderer{renderer}
  {
    if constexpr (detail::is_owner<T>) {
      if (!get()) {
        throw exception{"Cannot create renderer from null pointer!"};
      }
    }
  }

  template <typename Window, typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit BasicRenderer(const Window& window, const uint32 flags = GetDefaultFlags())
      : mRenderer{SDL_CreateRenderer(window.get(), -1, flags)}
  {
    if (!get()) {
      throw sdl_error{};
    }
  }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit BasicRenderer(const Renderer& owner) noexcept : mRenderer{owner.get()}
  {}

  /* Clears the rendering target with the currently active color. */
  auto Clear() noexcept -> result { return SDL_RenderClear(get()) == 0; }

  /* Clears the rendering target with the specified color, active color is unchanged. */
  void ClearWith(const color& color) noexcept
  {
    const auto previous = GetColor();
    SetColor(color);
    Clear();
    SetColor(previous);
  }

  /* Applies the previous rendering calls to the rendering target. */
  void Present() noexcept { SDL_RenderPresent(get()); }

  void Fill() noexcept { FillRect<int>({{}, GetOutputSize()}); }

  void FillWith(const color& color) noexcept
  {
    const auto previous = GetColor();

    SetColor(color);
    Fill();

    SetColor(previous);
  }

  template <typename U>
  auto DrawRect(const basic_rect<U>& rect) noexcept -> result
  {
    if constexpr (basic_rect<U>::integral) {
      return SDL_RenderDrawRect(get(), rect.data()) == 0;
    }
    else {
      return SDL_RenderDrawRectF(get(), rect.data()) == 0;
    }
  }

  template <typename U>
  auto FillRect(const basic_rect<U>& rect) noexcept -> result
  {
    if constexpr (basic_rect<U>::integral) {
      return SDL_RenderFillRect(get(), rect.data()) == 0;
    }
    else {
      return SDL_RenderFillRectF(get(), rect.data()) == 0;
    }
  }

  template <typename U>
  auto DrawLine(const basic_point<U>& start, const basic_point<U>& end) noexcept -> result
  {
    if constexpr (basic_point<U>::integral) {
      return SDL_RenderDrawLine(get(), start.x(), start.y(), end.x(), end.y()) == 0;
    }
    else {
      return SDL_RenderDrawLineF(get(), start.x(), start.y(), end.x(), end.y()) == 0;
    }
  }

  template <typename Container>
  auto DrawLines(const Container& container) noexcept -> result
  {
    using point_t = typename Container::value_type;  // a point of int or float
    using value_t = typename point_t::value_type;    // either int or float

    if (!container.empty()) {
      const auto& front = container.front();
      const auto* first = front.data();

      if constexpr (std::is_same_v<value_t, int>) {
        return SDL_RenderDrawLines(get(), first, isize(container)) == 0;
      }
      else {
        return SDL_RenderDrawLinesF(get(), first, isize(container)) == 0;
      }
    }
    else {
      return failure;
    }
  }

  template <typename U>
  auto DrawPoint(const basic_point<U>& point) noexcept -> result
  {
    if constexpr (basic_point<U>::integral) {
      return SDL_RenderDrawPoint(get(), point.x(), point.y()) == 0;
    }
    else {
      return SDL_RenderDrawPointF(get(), point.x(), point.y()) == 0;
    }
  }

  template <typename U>
  void DrawCircle(const basic_point<U>& position, const float radius) noexcept
  {
    using value_t = typename basic_point<U>::value_type;

    auto error = -radius;
    auto x = radius - 0.5f;
    auto y = 0.5f;

    const auto cx = static_cast<float>(position.x()) - 0.5f;
    const auto cy = static_cast<float>(position.y()) - 0.5f;

    while (x >= y) {
      DrawPoint<value_t>({static_cast<value_t>(cx + x), static_cast<value_t>(cy + y)});
      DrawPoint<value_t>({static_cast<value_t>(cx + y), static_cast<value_t>(cy + x)});

      if (x != 0) {
        DrawPoint<value_t>({static_cast<value_t>(cx - x), static_cast<value_t>(cy + y)});
        DrawPoint<value_t>({static_cast<value_t>(cx + y), static_cast<value_t>(cy - x)});
      }

      if (y != 0) {
        DrawPoint<value_t>({static_cast<value_t>(cx + x), static_cast<value_t>(cy - y)});
        DrawPoint<value_t>({static_cast<value_t>(cx - y), static_cast<value_t>(cy + x)});
      }

      if (x != 0 && y != 0) {
        DrawPoint<value_t>({static_cast<value_t>(cx - x), static_cast<value_t>(cy - y)});
        DrawPoint<value_t>({static_cast<value_t>(cx - y), static_cast<value_t>(cy - x)});
      }

      error += y;
      ++y;
      error += y;

      if (error >= 0) {
        --x;
        error -= x;
        error -= x;
      }
    }
  }

  void FillCircle(const fpoint center, const float radius)
  {
    const auto cx = center.x();
    const auto cy = center.y();

    for (auto dy = 1.0f; dy <= radius; dy += 1.0f) {
      const auto dx = std::floor(std::sqrt((2.0f * radius * dy) - (dy * dy)));
      DrawLine<float>({cx - dx, cy + dy - radius}, {cx + dx, cy + dy - radius});
      DrawLine<float>({cx - dx, cy - dy + radius}, {cx + dx, cy - dy + radius});
    }
  }

  template <typename P, typename U>
  auto Render(const BasicTexture<U>& texture, const basic_point<P>& position) noexcept
      -> result
  {
    if constexpr (basic_point<P>::floating) {
      const auto size = cast<farea>(texture.GetSize());
      const SDL_FRect dst{position.x(), position.y(), size.width, size.height};
      return SDL_RenderCopyF(get(), texture.get(), nullptr, &dst) == 0;
    }
    else {
      const SDL_Rect dst{position.x(), position.y(), texture.width(), texture.height()};
      return SDL_RenderCopy(get(), texture.get(), nullptr, &dst) == 0;
    }
  }

  template <typename P, typename U>
  auto Render(const BasicTexture<U>& texture, const basic_rect<P>& destination) noexcept
      -> result
  {
    if constexpr (basic_rect<P>::floating) {
      return SDL_RenderCopyF(get(), texture.get(), nullptr, destination.data()) == 0;
    }
    else {
      return SDL_RenderCopy(get(), texture.get(), nullptr, destination.data()) == 0;
    }
  }

  template <typename P, typename U>
  auto Render(const BasicTexture<U>& texture,
              const irect& source,
              const basic_rect<P>& destination) noexcept -> result
  {
    if constexpr (basic_rect<P>::floating) {
      return SDL_RenderCopyF(get(), texture.get(), source.data(), destination.data()) == 0;
    }
    else {
      return SDL_RenderCopy(get(), texture.get(), source.data(), destination.data()) == 0;
    }
  }

  template <typename P, typename U>
  auto Render(const BasicTexture<U>& texture,
              const irect& source,
              const basic_rect<P>& destination,
              const double angle) noexcept -> result
  {
    if constexpr (basic_rect<P>::floating) {
      return SDL_RenderCopyExF(get(),
                               texture.get(),
                               source.data(),
                               destination.data(),
                               angle,
                               nullptr,
                               SDL_FLIP_NONE) == 0;
    }
    else {
      return SDL_RenderCopyEx(get(),
                              texture.get(),
                              source.data(),
                              destination.data(),
                              angle,
                              nullptr,
                              SDL_FLIP_NONE) == 0;
    }
  }

  template <typename R, typename P, typename U>
  auto Render(const BasicTexture<U>& texture,
              const irect& source,
              const basic_rect<R>& destination,
              const double angle,
              const basic_point<P>& center) noexcept -> result
  {
    static_assert(std::is_same_v<typename basic_rect<R>::value_type,
                                 typename basic_point<P>::value_type>,
                  "Destination rectangle and center point must have the same "
                  "value types (int or float)!");

    if constexpr (basic_rect<R>::floating) {
      return SDL_RenderCopyExF(get(),
                               texture.get(),
                               source.data(),
                               destination.data(),
                               angle,
                               center.data(),
                               SDL_FLIP_NONE) == 0;
    }
    else {
      return SDL_RenderCopyEx(get(),
                              texture.get(),
                              source.data(),
                              destination.data(),
                              angle,
                              center.data(),
                              SDL_FLIP_NONE) == 0;
    }
  }

  template <typename R, typename P, typename U>
  auto Render(const BasicTexture<U>& texture,
              const irect& source,
              const basic_rect<R>& destination,
              const double angle,
              const basic_point<P>& center,
              const SDL_RendererFlip flip) noexcept -> result
  {
    static_assert(std::is_same_v<typename basic_rect<R>::value_type,
                                 typename basic_point<P>::value_type>,
                  "Destination rectangle and center point must have the same "
                  "value types (int or float)!");

    if constexpr (basic_rect<R>::floating) {
      return SDL_RenderCopyExF(get(),
                               texture.get(),
                               source.data(),
                               destination.data(),
                               angle,
                               center.data(),
                               flip) == 0;
    }
    else {
      return SDL_RenderCopyEx(get(),
                              texture.get(),
                              source.data(),
                              destination.data(),
                              angle,
                              center.data(),
                              flip) == 0;
    }
  }

  /* Captures a snapshot of the current rendering target as a surface. */
  [[nodiscard]] auto Capture(const PixelFormat format) const -> Surface
  {
    Surface image{GetOutputSize(), format};

    if (!image.Lock()) {
      throw sdl_error{};
    }

    if (const auto res =
            SDL_RenderReadPixels(get(), nullptr, 0, image.GetPixelData(), image.GetPitch());
        res == -1) {
      throw sdl_error{};
    }

    image.Unlock();
    return image;
  }

  template <typename U>
  [[nodiscard]] auto ToTexture(const BasicSurface<U>& surface) const -> Texture
  {
    return Texture{*this, surface};
  }

  auto SetColor(const color& color) noexcept -> result
  {
    return SDL_SetRenderDrawColor(get(),
                                  color.red(),
                                  color.green(),
                                  color.blue(),
                                  color.alpha()) == 0;
  }

  auto SetClip(const std::optional<irect>& area) noexcept -> result
  {
    return SDL_RenderSetClipRect(get(), area ? area->data() : nullptr) == 0;
  }

  auto SetViewport(const irect& viewport) noexcept -> result
  {
    return SDL_RenderSetViewport(get(), viewport.data()) == 0;
  }

  auto SetBlendMode(const BlendMode mode) noexcept -> result
  {
    return SDL_SetRenderDrawBlendMode(get(), static_cast<SDL_BlendMode>(mode)) == 0;
  }

  template <typename U>
  auto SetTarget(BasicTexture<U>& target) noexcept -> result
  {
    assert(target.IsTarget());
    return SDL_SetRenderTarget(get(), target.get()) == 0;
  }

  auto ResetTarget() noexcept -> result { return SDL_SetRenderTarget(get(), nullptr) == 0; }

  auto SetScale(const float xScale, const float yScale) noexcept -> result
  {
    assert(xScale > 0);
    assert(yScale > 0);
    return SDL_RenderSetScale(get(), xScale, yScale) == 0;
  }

  auto SetLogicalSize(const iarea size) noexcept -> result
  {
    assert(size.width >= 0);
    assert(size.height >= 0);
    return SDL_RenderSetLogicalSize(get(), size.width, size.height) == 0;
  }

  auto SetLogicalIntegerScaling(const bool enabled) noexcept -> result
  {
    return SDL_RenderSetIntegerScale(get(), enabled ? SDL_TRUE : SDL_FALSE) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  auto SetVSync(const bool enabled) noexcept -> result
  {
    return SDL_RenderSetVSync(get(), enabled ? 1 : 0) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto GetRenderTarget() noexcept -> TextureHandle
  {
    return TextureHandle{SDL_GetRenderTarget(get())};
  }

  [[nodiscard]] auto GetLogicalSize() const noexcept -> iarea
  {
    iarea size{};
    SDL_RenderGetLogicalSize(get(), &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto GetScale() const noexcept -> std::pair<float, float>
  {
    float xScale{};
    float yScale{};
    SDL_RenderGetScale(get(), &xScale, &yScale);
    return {xScale, yScale};
  }

  [[nodiscard]] auto GetClip() const noexcept -> std::optional<irect>
  {
    irect rect{};
    SDL_RenderGetClipRect(get(), rect.data());
    if (!rect.has_area()) {
      return std::nullopt;
    }
    else {
      return rect;
    }
  }

  [[nodiscard]] auto GetOutputSize() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetRendererOutputSize(get(), &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto GetBlendMode() const noexcept -> BlendMode
  {
    SDL_BlendMode mode{};
    SDL_GetRenderDrawBlendMode(get(), &mode);
    return static_cast<BlendMode>(mode);
  }

  [[nodiscard]] auto GetColor() const noexcept -> color
  {
    uint8 red{};
    uint8 green{};
    uint8 blue{};
    uint8 alpha{};
    SDL_GetRenderDrawColor(get(), &red, &green, &blue, &alpha);
    return {red, green, blue, alpha};
  }

  [[nodiscard]] auto GetViewport() const noexcept -> irect
  {
    irect viewport{};
    SDL_RenderGetViewport(get(), viewport.data());
    return viewport;
  }

  /* Indicates whether the renderer uses integer scaling for logical viewports. */
  [[nodiscard]] auto IsUsingIntegerLogicalScaling() const noexcept -> bool
  {
    return SDL_RenderGetIntegerScale(get());
  }

  [[nodiscard]] auto IsClippingEnabled() const noexcept -> bool
  {
    return SDL_RenderIsClipEnabled(get());
  }

  [[nodiscard]] constexpr static auto GetDefaultFlags() noexcept -> uint32
  {
    return Accelerated | VSync;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Renderer* { return mRenderer.get(); }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mRenderer != nullptr;
  }

 private:
  detail::pointer<T, SDL_Renderer> mRenderer;
};

class RendererInfo final {
  template <typename T>
  friend auto GetInfo(const BasicRenderer<T>& renderer) noexcept
      -> std::optional<RendererInfo>;

 public:
  [[nodiscard]] auto GetSupportedFlags() const noexcept -> uint32 { return mInfo.flags; }

  [[nodiscard]] auto HasVSync() const noexcept -> bool
  {
    return GetSupportedFlags() & SDL_RENDERER_PRESENTVSYNC;
  }

  [[nodiscard]] auto HasTargetTextures() const noexcept -> bool
  {
    return GetSupportedFlags() & SDL_RENDERER_TARGETTEXTURE;
  }

  [[nodiscard]] auto HasHardwareAcceleration() const noexcept -> bool
  {
    return GetSupportedFlags() & SDL_RENDERER_ACCELERATED;
  }

  [[nodiscard]] auto HasSoftwareRenderer() const noexcept -> bool
  {
    return GetSupportedFlags() & SDL_RENDERER_SOFTWARE;
  }

  [[nodiscard]] auto GetPixelFormats() const noexcept -> uint32
  {
    return mInfo.num_texture_formats;
  }

  [[nodiscard]] auto GetFormat(const std::size_t index) const noexcept -> PixelFormat
  {
    assert(index < GetPixelFormats());
    return static_cast<PixelFormat>(mInfo.texture_formats[index]);
  }

  [[nodiscard]] auto GetMaxTextureSize() const noexcept -> iarea
  {
    return {mInfo.max_texture_width, mInfo.max_texture_height};
  }

  [[nodiscard]] auto GetMaxTextureWidth() const noexcept -> int
  {
    return mInfo.max_texture_width;
  }

  [[nodiscard]] auto GetMaxTextureHeight() const noexcept -> int
  {
    return mInfo.max_texture_height;
  }

  [[nodiscard]] auto GetName() const noexcept -> const char* { return mInfo.name; }

 private:
  SDL_RendererInfo mInfo;

  explicit RendererInfo(const SDL_RendererInfo info) noexcept : mInfo{info} {}
};

template <typename T>
[[nodiscard]] auto GetInfo(const BasicRenderer<T>& renderer) noexcept
    -> std::optional<RendererInfo>
{
  SDL_RendererInfo info;
  if (SDL_GetRendererInfo(renderer.get(), &info) == 0) {
    return RendererInfo{info};
  }
  else {
    return std::nullopt;
  }
}

[[nodiscard]] inline auto GetRenderDrivers() noexcept -> int
{
  return SDL_GetNumRenderDrivers();
}

[[nodiscard]] inline auto GetVideoDrivers() noexcept -> int
{
  return SDL_GetNumVideoDrivers();
}

[[nodiscard]] inline auto GetRenderDriverInfo(const int index) noexcept
    -> std::optional<SDL_RendererInfo>
{
  SDL_RendererInfo info{};
  if (SDL_GetRenderDriverInfo(index, &info) == 0) {
    return info;
  }
  else {
    return std::nullopt;
  }
}

template <typename T>
[[nodiscard]] auto ToString(const BasicRenderer<T>& renderer) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Renderer(data: {})", detail::address_of(renderer.get()));
#else
  return "Renderer(data: " + detail::address_of(renderer.get()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicRenderer<T>& renderer) -> std::ostream&
{
  return stream << ToString(renderer);
}

[[nodiscard]] inline auto ToString(const RendererInfo& info) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("RendererInfo(name: {})", str_or_na(info.GetName()));
#else
  using namespace std::string_literals;
  return "RendererInfo(name: "s + str_or_na(info.GetName()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const RendererInfo& info) -> std::ostream&
{
  return stream << ToString(info);
}

}  // namespace cen

#endif  // CENTURION_RENDER_HPP_
