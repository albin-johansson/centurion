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
#include "features.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
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

using Renderer = BasicRenderer<detail::OwnerTag>;
using RendererHandle = BasicRenderer<detail::HandleTag>;

template <typename T>
class BasicRenderer final {
 public:
  enum RendererFlags : Uint32 {
    Software = SDL_RENDERER_SOFTWARE,             ///< Software renderer
    Accelerated = SDL_RENDERER_ACCELERATED,       ///< Hardware-accelerated
    TargetTextures = SDL_RENDERER_TARGETTEXTURE,  ///< Supports target textures
    VSync = SDL_RENDERER_PRESENTVSYNC             ///< Renderer Uses VSync
  };

  explicit BasicRenderer(MaybeOwner<SDL_Renderer*> renderer) noexcept(detail::is_handle<T>)
      : mRenderer{renderer}
  {
    if constexpr (detail::is_owner<T>) {
      if (!get()) {
        throw Error{"Cannot create renderer from null pointer!"};
      }
    }
  }

  template <typename Window, typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicRenderer(const Window& window, const Uint32 flags = GetDefaultFlags())
      : mRenderer{SDL_CreateRenderer(window.get(), -1, flags)}
  {
    if (!get()) {
      throw SDLError{};
    }
  }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit BasicRenderer(const Renderer& owner) noexcept : mRenderer{owner.get()}
  {}

  /* Clears the rendering target with the currently active color. */
  auto Clear() noexcept -> Result { return SDL_RenderClear(get()) == 0; }

  /* Clears the rendering target with the specified color, active color is unchanged. */
  void ClearWith(const Color& color) noexcept
  {
    const auto previous = GetColor();
    SetColor(color);
    Clear();
    SetColor(previous);
  }

  /* Applies the previous rendering calls to the rendering target. */
  void Present() noexcept { SDL_RenderPresent(get()); }

  void Fill() noexcept { FillRect<int>({{}, GetOutputSize()}); }

  void FillWith(const Color& color) noexcept
  {
    const auto previous = GetColor();

    SetColor(color);
    Fill();

    SetColor(previous);
  }

  template <typename U>
  auto DrawRect(const BasicRect<U>& rect) noexcept -> Result
  {
    if constexpr (BasicRect<U>::integral) {
      return SDL_RenderDrawRect(get(), rect.data()) == 0;
    }
    else {
      return SDL_RenderDrawRectF(get(), rect.data()) == 0;
    }
  }

  template <typename U>
  auto FillRect(const BasicRect<U>& rect) noexcept -> Result
  {
    if constexpr (BasicRect<U>::integral) {
      return SDL_RenderFillRect(get(), rect.data()) == 0;
    }
    else {
      return SDL_RenderFillRectF(get(), rect.data()) == 0;
    }
  }

  template <typename U>
  auto DrawLine(const BasicPoint<U>& start, const BasicPoint<U>& end) noexcept -> Result
  {
    if constexpr (BasicPoint<U>::integral) {
      return SDL_RenderDrawLine(get(), start.GetX(), start.GetY(), end.GetX(), end.GetY()) ==
             0;
    }
    else {
      return SDL_RenderDrawLineF(get(), start.GetX(), start.GetY(), end.GetX(), end.GetY()) ==
             0;
    }
  }

  template <typename Container>
  auto DrawLines(const Container& container) noexcept -> Result
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
  auto DrawPoint(const BasicPoint<U>& point) noexcept -> Result
  {
    if constexpr (BasicPoint<U>::integral) {
      return SDL_RenderDrawPoint(get(), point.GetX(), point.GetY()) == 0;
    }
    else {
      return SDL_RenderDrawPointF(get(), point.GetX(), point.GetY()) == 0;
    }
  }

  template <typename U>
  void DrawCircle(const BasicPoint<U>& position, const float radius) noexcept
  {
    using value_t = typename BasicPoint<U>::value_type;

    auto error = -radius;
    auto x = radius - 0.5f;
    auto y = 0.5f;

    const auto cx = static_cast<float>(position.GetX()) - 0.5f;
    const auto cy = static_cast<float>(position.GetY()) - 0.5f;

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

  void FillCircle(const FPoint center, const float radius)
  {
    const auto cx = center.GetX();
    const auto cy = center.GetY();

    for (auto dy = 1.0f; dy <= radius; dy += 1.0f) {
      const auto dx = std::floor(std::sqrt((2.0f * radius * dy) - (dy * dy)));
      DrawLine<float>({cx - dx, cy + dy - radius}, {cx + dx, cy + dy - radius});
      DrawLine<float>({cx - dx, cy - dy + radius}, {cx + dx, cy - dy + radius});
    }
  }

  template <typename P, typename U>
  auto Render(const BasicTexture<U>& texture, const BasicPoint<P>& position) noexcept -> Result
  {
    if constexpr (BasicPoint<P>::floating) {
      const auto size = cast<FArea>(texture.GetSize());
      const SDL_FRect dst{position.GetX(), position.GetY(), size.width, size.height};
      return SDL_RenderCopyF(get(), texture.get(), nullptr, &dst) == 0;
    }
    else {
      const SDL_Rect dst{position.GetX(),
                         position.GetY(),
                         texture.GetWidth(),
                         texture.GetHeight()};
      return SDL_RenderCopy(get(), texture.get(), nullptr, &dst) == 0;
    }
  }

  template <typename P, typename U>
  auto Render(const BasicTexture<U>& texture, const BasicRect<P>& destination) noexcept
      -> Result
  {
    if constexpr (BasicRect<P>::floating) {
      return SDL_RenderCopyF(get(), texture.get(), nullptr, destination.data()) == 0;
    }
    else {
      return SDL_RenderCopy(get(), texture.get(), nullptr, destination.data()) == 0;
    }
  }

  template <typename P, typename U>
  auto Render(const BasicTexture<U>& texture,
              const Rect& source,
              const BasicRect<P>& destination) noexcept -> Result
  {
    if constexpr (BasicRect<P>::floating) {
      return SDL_RenderCopyF(get(), texture.get(), source.data(), destination.data()) == 0;
    }
    else {
      return SDL_RenderCopy(get(), texture.get(), source.data(), destination.data()) == 0;
    }
  }

  template <typename P, typename U>
  auto Render(const BasicTexture<U>& texture,
              const Rect& source,
              const BasicRect<P>& destination,
              const double angle) noexcept -> Result
  {
    if constexpr (BasicRect<P>::floating) {
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
              const Rect& source,
              const BasicRect<R>& destination,
              const double angle,
              const BasicPoint<P>& center) noexcept -> Result
  {
    static_assert(
        std::is_same_v<typename BasicRect<R>::value_type, typename BasicPoint<P>::value_type>,
        "Destination rectangle and center point must have the same "
        "value types (int or float)!");

    if constexpr (BasicRect<R>::floating) {
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
              const Rect& source,
              const BasicRect<R>& destination,
              const double angle,
              const BasicPoint<P>& center,
              const SDL_RendererFlip flip) noexcept -> Result
  {
    static_assert(
        std::is_same_v<typename BasicRect<R>::value_type, typename BasicPoint<P>::value_type>,
        "Destination rectangle and center point must have the same "
        "value types (int or float)!");

    if constexpr (BasicRect<R>::floating) {
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
      throw SDLError{};
    }

    if (const auto res =
            SDL_RenderReadPixels(get(), nullptr, 0, image.GetPixelData(), image.GetPitch());
        res == -1) {
      throw SDLError{};
    }

    image.Unlock();
    return image;
  }

  template <typename U>
  [[nodiscard]] auto ToTexture(const BasicSurface<U>& surface) const -> Texture
  {
    return Texture{*this, surface};
  }

  auto SetColor(const Color& color) noexcept -> Result
  {
    return SDL_SetRenderDrawColor(get(),
                                  color.GetRed(),
                                  color.GetGreen(),
                                  color.GetBlue(),
                                  color.GetAlpha()) == 0;
  }

  auto SetClip(const std::optional<Rect>& area) noexcept -> Result
  {
    return SDL_RenderSetClipRect(get(), area ? area->data() : nullptr) == 0;
  }

  auto SetViewport(const Rect& viewport) noexcept -> Result
  {
    return SDL_RenderSetViewport(get(), viewport.data()) == 0;
  }

  auto SetBlendMode(const BlendMode mode) noexcept -> Result
  {
    return SDL_SetRenderDrawBlendMode(get(), static_cast<SDL_BlendMode>(mode)) == 0;
  }

  template <typename U>
  auto SetTarget(BasicTexture<U>& target) noexcept -> Result
  {
    assert(target.IsTarget());
    return SDL_SetRenderTarget(get(), target.get()) == 0;
  }

  auto ResetTarget() noexcept -> Result { return SDL_SetRenderTarget(get(), nullptr) == 0; }

  auto SetScale(const float xScale, const float yScale) noexcept -> Result
  {
    assert(xScale > 0);
    assert(yScale > 0);
    return SDL_RenderSetScale(get(), xScale, yScale) == 0;
  }

  auto SetLogicalSize(const Area size) noexcept -> Result
  {
    assert(size.width >= 0);
    assert(size.height >= 0);
    return SDL_RenderSetLogicalSize(get(), size.width, size.height) == 0;
  }

  auto SetLogicalIntegerScaling(const bool enabled) noexcept -> Result
  {
    return SDL_RenderSetIntegerScale(get(), enabled ? SDL_TRUE : SDL_FALSE) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  auto SetVSync(const bool enabled) noexcept -> Result
  {
    return SDL_RenderSetVSync(get(), enabled ? 1 : 0) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

  [[nodiscard]] auto GetRenderTarget() noexcept -> TextureHandle
  {
    return TextureHandle{SDL_GetRenderTarget(get())};
  }

  [[nodiscard]] auto GetLogicalSize() const noexcept -> Area
  {
    Area size{};
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

  [[nodiscard]] auto GetClip() const noexcept -> std::optional<Rect>
  {
    Rect rect{};
    SDL_RenderGetClipRect(get(), rect.data());
    if (!rect.HasArea()) {
      return std::nullopt;
    }
    else {
      return rect;
    }
  }

  [[nodiscard]] auto GetOutputSize() const noexcept -> Area
  {
    Area size{};
    SDL_GetRendererOutputSize(get(), &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto GetBlendMode() const noexcept -> BlendMode
  {
    SDL_BlendMode mode{};
    SDL_GetRenderDrawBlendMode(get(), &mode);
    return static_cast<BlendMode>(mode);
  }

  [[nodiscard]] auto GetColor() const noexcept -> Color
  {
    Uint8 red{};
    Uint8 green{};
    Uint8 blue{};
    Uint8 alpha{};
    SDL_GetRenderDrawColor(get(), &red, &green, &blue, &alpha);
    return {red, green, blue, alpha};
  }

  [[nodiscard]] auto GetViewport() const noexcept -> Rect
  {
    Rect viewport{};
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

  [[nodiscard]] constexpr static auto GetDefaultFlags() noexcept -> Uint32
  {
    return Accelerated | VSync;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Renderer* { return mRenderer.get(); }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mRenderer != nullptr;
  }

 private:
  detail::Pointer<T, SDL_Renderer> mRenderer;
};

class RendererInfo final {
  template <typename T>
  friend auto GetInfo(const BasicRenderer<T>& renderer) noexcept
      -> std::optional<RendererInfo>;

 public:
  [[nodiscard]] auto GetSupportedFlags() const noexcept -> Uint32 { return mInfo.flags; }

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

  [[nodiscard]] auto GetPixelFormats() const noexcept -> Uint32
  {
    return mInfo.num_texture_formats;
  }

  [[nodiscard]] auto GetFormat(const std::size_t index) const noexcept -> PixelFormat
  {
    assert(index < GetPixelFormats());
    return static_cast<PixelFormat>(mInfo.texture_formats[index]);
  }

  [[nodiscard]] auto GetMaxTextureSize() const noexcept -> Area
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
[[nodiscard]] auto to_string(const BasicRenderer<T>& renderer) -> std::string
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
  return stream << to_string(renderer);
}

[[nodiscard]] inline auto to_string(const RendererInfo& info) -> std::string
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
  return stream << to_string(info);
}

}  // namespace cen

#endif  // CENTURION_RENDER_HPP_
