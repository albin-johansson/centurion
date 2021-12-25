#ifndef CENTURION_SURFACE_HPP_
#define CENTURION_SURFACE_HPP_

#include <SDL.h>

#include "color.hpp"
#include "common.hpp"
#include "features.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "math.hpp"
#include "pixels.hpp"
#include "video.hpp"

#ifndef CENTURION_NO_SDL_IMAGE
#include <SDL_image.h>
#endif  // CENTURION_NO_SDL_IMAGE

#include <cassert>   // assert
#include <optional>  // optional, nullopt
#include <ostream>   // ostream
#include <string>    // string, to_string

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup video
/// \{

template <typename T>
class BasicSurface;

using Surface = BasicSurface<detail::OwnerTag>;
using SurfaceHandle = BasicSurface<detail::HandleTag>;

template <typename T>
class BasicSurface final {
 public:
  /* Creates a surface based on existing surface, ownership is claimed by owning surfaces */
  explicit BasicSurface(MaybeOwner<SDL_Surface*> surface) noexcept(detail::is_handle<T>)
      : mSurface{surface}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mSurface) {
        throw Error{"Cannot create owning surface from null pointer!"};
      }
    }
  }

#ifndef CENTURION_NO_SDL_IMAGE

  /* Creates a surface based on the image at the specified file path */
  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicSurface(const char* file) : mSurface{IMG_Load(file)}
  {
    if (!mSurface) {
      throw IMGError{};
    }
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicSurface(const std::string& file) : BasicSurface{file.c_str()}
  {}

#endif  // CENTURION_NO_SDL_IMAGE

  /* Creates a blank surface with the specified size and format */
  template <typename TT = T, detail::EnableOwner<TT> = 0>
  BasicSurface(const Area& size, const PixelFormat format)
      : mSurface{SDL_CreateRGBSurfaceWithFormat(0,
                                                size.width,
                                                size.height,
                                                0,
                                                ToUnderlying(format))}
  {
    if (!mSurface) {
      throw SDLError{};
    }
  }

  BasicSurface(const BasicSurface& other) noexcept(detail::is_handle<T>)
  {
    if constexpr (detail::is_owner<T>) {
      Copy(other);
    }
    else {
      mSurface = other.get();
    }
  }

  BasicSurface(BasicSurface&& other) noexcept = default;

  auto operator=(const BasicSurface& other) noexcept(detail::is_handle<T>) -> BasicSurface&
  {
    if (this != &other) {
      if constexpr (detail::is_owner<T>) {
        Copy(other);
      }
      else {
        mSurface = other.get();
      }
    }

    return *this;
  }

  auto operator=(BasicSurface&& other) noexcept -> BasicSurface& = default;

  /* Creates a blank surface with the specified blend mode and pixel format */
  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto WithFormat(const char* file,
                                       const BlendMode mode,
                                       const PixelFormat format) -> BasicSurface
  {
    assert(file);

    BasicSurface source{file};
    source.SetBlendMode(mode);

    return source.ConvertTo(format);
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto WithFormat(const std::string& file,
                                       const BlendMode mode,
                                       const PixelFormat format) -> BasicSurface
  {
    return WithFormat(file.c_str(), mode, format);
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto FromBMP(const char* file) -> BasicSurface
  {
    assert(file);
    return BasicSurface{SDL_LoadBMP(file)};
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] static auto FromBMP(const std::string& file) -> BasicSurface
  {
    return FromBMP(file.c_str());
  }

  auto SaveAsBMP(const char* file) const noexcept -> Result
  {
    assert(file);
    return SDL_SaveBMP(get(), file) != -1;
  }

  auto SaveAsBMP(const std::string& file) const noexcept -> Result  // NOLINT
  {
    return SaveAsBMP(file.c_str());
  }

#ifndef CENTURION_NO_SDL_IMAGE

  auto SaveAsPNG(const char* file) const noexcept -> Result
  {
    assert(file);
    return IMG_SavePNG(get(), file) != -1;
  }

  auto SaveAsPNG(const std::string& file) const noexcept -> Result
  {
    return SaveAsPNG(file.c_str());
  }

  /* Save as JPG image, the quality parameter is passed on to libjpeg by SDL */
  auto SaveAsJPG(const char* file, const int quality) const noexcept -> Result
  {
    assert(file);
    return IMG_SaveJPG(get(), file, quality) != -1;
  }

  auto SaveAsJPG(const std::string& file, const int quality) const noexcept -> Result
  {
    return SaveAsJPG(file.c_str(), quality);
  }

#endif  // CENTURION_NO_SDL_IMAGE

  /* Attempts to lock the access to the surface pixel data */
  auto Lock() noexcept -> Result
  {
    if (MustLock()) {
      return SDL_LockSurface(mSurface) == 0;
    }
    else {
      return true;
    }
  }

  void Unlock() noexcept
  {
    if (MustLock()) {
      SDL_UnlockSurface(mSurface);
    }
  }

  void SetAlphaMod(const Uint8 alpha) noexcept { SDL_SetSurfaceAlphaMod(mSurface, alpha); }

  void SetColorMod(const Color& color) noexcept
  {
    SDL_SetSurfaceColorMod(mSurface, color.GetRed(), color.GetGreen(), color.GetBlue());
  }

  void SetBlendMode(const BlendMode mode) noexcept
  {
    SDL_SetSurfaceBlendMode(mSurface, static_cast<SDL_BlendMode>(mode));
  }

  /* Configure RLE acceleration hint. */
  auto SetRLE(const bool enabled) noexcept -> Result
  {
    return SDL_SetSurfaceRLE(mSurface, enabled ? 1 : 0) == 0;
  }

  /* Creates a copy of the surface using another pixel format */
  [[nodiscard]] auto ConvertTo(const PixelFormat format) const -> BasicSurface
  {
    if (auto* converted = SDL_ConvertSurfaceFormat(mSurface, ToUnderlying(format), 0)) {
      BasicSurface result{converted};
      result.SetBlendMode(GetBlendMode());
      return result;
    }
    else {
      throw SDLError{};
    }
  }

  /* Does the surface need to be locked before modifying the pixel data? */
  [[nodiscard]] auto MustLock() const noexcept -> bool { return SDL_MUSTLOCK(mSurface); }

  [[nodiscard]] auto GetAlpha() const noexcept -> Uint8
  {
    Uint8 alpha{0xFF};
    SDL_GetSurfaceAlphaMod(mSurface, &alpha);
    return alpha;
  }

  [[nodiscard]] auto GetColorMod() const noexcept -> Color
  {
    Uint8 red{};
    Uint8 green{};
    Uint8 blue{};
    if (SDL_GetSurfaceColorMod(mSurface, &red, &green, &blue) == 0) {
      return Color{red, green, blue};
    }
    else {
      return colors::white;
    }
  }

  [[nodiscard]] auto GetBlendMode() const noexcept -> BlendMode
  {
    SDL_BlendMode mode{};
    SDL_GetSurfaceBlendMode(mSurface, &mode);
    return static_cast<BlendMode>(mode);
  }

  [[nodiscard]] auto GetWidth() const noexcept -> int { return mSurface->w; }

  [[nodiscard]] auto GetHeight() const noexcept -> int { return mSurface->h; }

  [[nodiscard]] auto GetSize() const noexcept -> Area { return Area{GetWidth(), GetHeight()}; }

  /* Returns the pitch, i.e. the length of a row of pixels in bytes */
  [[nodiscard]] auto GetPitch() const noexcept -> int { return mSurface->pitch; }

  [[nodiscard]] auto GetPixelData() noexcept -> void* { return mSurface->pixels; }

  [[nodiscard]] auto GetPixelData() const noexcept -> const void* { return mSurface->pixels; }

  [[nodiscard]] auto GetFormatInfo() const noexcept -> PixelFormatInfoHandle
  {
    return PixelFormatInfoHandle{mSurface->format};
  }

  [[nodiscard]] auto GetClip() const noexcept -> Rect { return Rect{mSurface->clip_rect}; }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto HasRLE() const noexcept -> bool
  {
    return SDL_HasSurfaceRLE(mSurface) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mSurface != nullptr;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Surface* { return mSurface.get(); }

 private:
  detail::Pointer<T, SDL_Surface> mSurface;

  void Copy(const BasicSurface& other) { mSurface.reset(other.DuplicateSurface()); }

  [[nodiscard]] auto DuplicateSurface() const -> Owner<SDL_Surface*>
  {
    if (auto* copy = SDL_DuplicateSurface(mSurface)) {
      return copy;
    }
    else {
      throw SDLError{};
    }
  }

  [[nodiscard]] auto InBounds(const Point point) const noexcept -> bool
  {
    const Rect bounds{0, 0, GetWidth(), GetHeight()};
    return bounds.Contains(point);
  }

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  BasicSurface() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// \name String conversions
/// \{

template <typename T>
[[nodiscard]] auto to_string(const BasicSurface<T>& surface) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Surface{{data: {}, width: {}, height: {}}}",
                     detail::address_of(surface.get()),
                     surface.width(),
                     surface.height());
#else
  return "Surface{data: " + detail::address_of(surface.get()) +
         ", width: " + std::to_string(surface.GetWidth()) +
         ", height: " + std::to_string(surface.GetHeight()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

template <typename T>
auto operator<<(std::ostream& stream, const BasicSurface<T>& surface) -> std::ostream&
{
  return stream << to_string(surface);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_SURFACE_HPP_
