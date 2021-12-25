#ifndef CENTURION_PIXELS_HPP_
#define CENTURION_PIXELS_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "color.hpp"
#include "common.hpp"
#include "features.hpp"
#include "memory.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class PixelFormat : Uint32 {
  Unknown = SDL_PIXELFORMAT_UNKNOWN,

  Index1LSB = SDL_PIXELFORMAT_INDEX1LSB,
  Index1MSB = SDL_PIXELFORMAT_INDEX1MSB,
  Index4LSB = SDL_PIXELFORMAT_INDEX4LSB,
  Index4MSB = SDL_PIXELFORMAT_INDEX4MSB,
  Index8 = SDL_PIXELFORMAT_INDEX8,

  RGBA32 = SDL_PIXELFORMAT_RGBA32,
  ARGB32 = SDL_PIXELFORMAT_ARGB32,
  BGRA32 = SDL_PIXELFORMAT_BGRA32,
  ABGR32 = SDL_PIXELFORMAT_ABGR32,

  RGB332 = SDL_PIXELFORMAT_RGB332,
  RGB444 = SDL_PIXELFORMAT_RGB444,

#if SDL_VERSION_ATLEAST(2, 0, 12)
  BGR444 = SDL_PIXELFORMAT_BGR444,
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  RGB555 = SDL_PIXELFORMAT_RGB555,
  BGR555 = SDL_PIXELFORMAT_BGR555,

  ARGB4444 = SDL_PIXELFORMAT_ARGB4444,
  RGBA4444 = SDL_PIXELFORMAT_RGBA4444,
  ABGR4444 = SDL_PIXELFORMAT_ABGR4444,
  BGRA4444 = SDL_PIXELFORMAT_BGRA4444,

  ARGB1555 = SDL_PIXELFORMAT_ARGB1555,
  RGBA5551 = SDL_PIXELFORMAT_RGBA5551,
  ABGR1555 = SDL_PIXELFORMAT_ABGR1555,
  BGRA5551 = SDL_PIXELFORMAT_BGRA5551,

  RGB565 = SDL_PIXELFORMAT_RGB565,
  BGR565 = SDL_PIXELFORMAT_BGR565,

  RGB24 = SDL_PIXELFORMAT_RGB24,
  BGR24 = SDL_PIXELFORMAT_BGR24,

  RGB888 = SDL_PIXELFORMAT_RGB888,
  BGR888 = SDL_PIXELFORMAT_BGR888,

  RGBX8888 = SDL_PIXELFORMAT_RGBX8888,
  BGRX8888 = SDL_PIXELFORMAT_BGRX8888,

  ARGB8888 = SDL_PIXELFORMAT_ARGB8888,
  RGBA8888 = SDL_PIXELFORMAT_RGBA8888,
  ABGR8888 = SDL_PIXELFORMAT_ABGR8888,
  BGRA8888 = SDL_PIXELFORMAT_BGRA8888,

  ARGB2101010 = SDL_PIXELFORMAT_ARGB2101010,

  YV12 = SDL_PIXELFORMAT_YV12,
  IYUV = SDL_PIXELFORMAT_IYUV,
  YUY2 = SDL_PIXELFORMAT_YUY2,
  UYVY = SDL_PIXELFORMAT_UYVY,
  YVYU = SDL_PIXELFORMAT_YVYU,
  NV12 = SDL_PIXELFORMAT_NV12,
  NV21 = SDL_PIXELFORMAT_NV21,
  ExternalOES = SDL_PIXELFORMAT_EXTERNAL_OES,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  XRGB4444 = SDL_PIXELFORMAT_XRGB4444,
  XBGR4444 = SDL_PIXELFORMAT_XBGR4444,

  XRGB1555 = SDL_PIXELFORMAT_XRGB1555,
  XBGR1555 = SDL_PIXELFORMAT_XBGR1555,

  XRGB8888 = SDL_PIXELFORMAT_XRGB8888,
  XBGR8888 = SDL_PIXELFORMAT_XBGR8888
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
};

class Palette final {
 public:
  using iterator = SDL_Color*;
  using const_iterator = const SDL_Color*;

  explicit Palette(const int nColors) : mPalette{SDL_AllocPalette(nColors)}
  {
    if (!mPalette) {
      throw SDLError{};
    }
  }

  auto SetColor(const int index, const Color& color) noexcept -> Result
  {
    assert(index >= 0);
    assert(index < GetSize());
    return SDL_SetPaletteColors(mPalette.get(), color.data(), index, 1) == 0;
  }

  [[nodiscard]] auto GetColor(const int index) const -> Color
  {
    if (index >= 0 && index < GetSize()) {
      return Color{mPalette->colors[index]};
    }
    else {
      throw Error{"Palette index out of bounds!"};
    }
  }

  [[nodiscard]] auto GetSize() const noexcept -> int { return mPalette->ncolors; }

  [[nodiscard]] auto GetVersion() const noexcept -> Uint32 { return mPalette->version; }

  [[nodiscard]] auto data() const noexcept -> SDL_Palette* { return mPalette.get(); }

  [[nodiscard]] auto get() const noexcept -> SDL_Palette* { return mPalette.get(); }

  [[nodiscard]] auto begin() noexcept -> iterator { return mPalette->colors; }

  [[nodiscard]] auto begin() const noexcept -> const_iterator { return mPalette->colors; }

  [[nodiscard]] auto end() noexcept -> iterator { return mPalette->colors + GetSize(); }

  [[nodiscard]] auto end() const noexcept -> const_iterator
  {
    return mPalette->colors + GetSize();
  }

 private:
  Managed<SDL_Palette> mPalette;
};

template <typename B>
class BasicPixelFormatInfo;

using PixelFormatInfo = BasicPixelFormatInfo<detail::OwnerTag>;
using PixelFormatInfoHandle = BasicPixelFormatInfo<detail::HandleTag>;

template <typename B>
class BasicPixelFormatInfo final {
 public:
  // clang-format off

  explicit BasicPixelFormatInfo(MaybeOwner<SDL_PixelFormat*> format) noexcept(detail::is_handle<B>)
      : mFormat{format}
  {
    if constexpr (detail::is_owner<B>) {
      if (!mFormat) {
        throw Error{"Null pixel format!"};
      }
    }
  }

  // clang-format on

  template <typename BB = B, detail::EnableOwner<BB> = 0>
  explicit BasicPixelFormatInfo(const PixelFormat format)
      : mFormat{SDL_AllocFormat(ToUnderlying(format))}
  {
    if (!mFormat) {
      throw SDLError{};
    }
  }

  template <typename BB = B, detail::EnableHandle<BB> = 0>
  explicit BasicPixelFormatInfo(const PixelFormatInfo& info) noexcept : mFormat{info.get()}
  {}

  [[nodiscard]] auto PixelToRGB(const Uint32 pixel) const noexcept -> Color
  {
    Uint8 red{};
    Uint8 green{};
    Uint8 blue{};
    SDL_GetRGB(pixel, mFormat, &red, &green, &blue);
    return Color{red, green, blue};
  }

  [[nodiscard]] auto PixelToRGBA(const Uint32 pixel) const noexcept -> Color
  {
    Uint8 red{};
    Uint8 green{};
    Uint8 blue{};
    Uint8 alpha{};
    SDL_GetRGBA(pixel, mFormat, &red, &green, &blue, &alpha);
    return Color{red, green, blue, alpha};
  }

  [[nodiscard]] auto RGBToPixel(const Color& color) const noexcept -> Uint32
  {
    return SDL_MapRGB(mFormat, color.GetRed(), color.GetGreen(), color.GetBlue());
  }

  [[nodiscard]] auto RGBAToPixel(const Color& color) const noexcept -> Uint32
  {
    return SDL_MapRGBA(mFormat,
                       color.GetRed(),
                       color.GetGreen(),
                       color.GetBlue(),
                       color.GetAlpha());
  }

  [[nodiscard]] auto GetFormat() const noexcept -> PixelFormat
  {
    return static_cast<PixelFormat>(mFormat->format);
  }

  [[nodiscard]] auto GetName() const noexcept -> const char*
  {
    return SDL_GetPixelFormatName(mFormat->format);
  }

  [[nodiscard]] auto data() const noexcept -> SDL_PixelFormat* { return mFormat.get(); }

  [[nodiscard]] auto get() const noexcept -> SDL_PixelFormat* { return mFormat.get(); }

  template <typename BB = B, detail::EnableHandle<BB> = 0>
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return mFormat;
  }

 private:
  detail::Pointer<B, SDL_PixelFormat> mFormat;
};

[[nodiscard]] constexpr auto to_string(const PixelFormat format) -> std::string_view
{
  switch (format) {
    case PixelFormat::Unknown:
      return "Unknown";

    case PixelFormat::Index1LSB:
      return "Index1LSB";

    case PixelFormat::Index1MSB:
      return "Index1MSB";

    case PixelFormat::Index4LSB:
      return "Index4LSB";

    case PixelFormat::Index4MSB:
      return "Index4MSB";

    case PixelFormat::Index8:
      return "Index8";

    case PixelFormat::RGB332:
      return "RGB332";

    case PixelFormat::ARGB4444:
      return "ARGB4444";

    case PixelFormat::RGBA4444:
      return "RGBA4444";

    case PixelFormat::ABGR4444:
      return "ABGR4444";

    case PixelFormat::BGRA4444:
      return "BGRA4444";

    case PixelFormat::ARGB1555:
      return "ARGB1555";

    case PixelFormat::RGBA5551:
      return "RGBA5551";

    case PixelFormat::ABGR1555:
      return "ABGR1555";

    case PixelFormat::BGRA5551:
      return "BGRA5551";

    case PixelFormat::RGB565:
      return "RGB565";

    case PixelFormat::BGR565:
      return "BGR565";

    case PixelFormat::RGB24:
      return "RGB24";

    case PixelFormat::BGR24:
      return "BGR24";

    case PixelFormat::RGBX8888:
      return "RGBX8888";

    case PixelFormat::BGRX8888:
      return "BGRX8888";

    case PixelFormat::ARGB8888:
      return "ARGB8888";

    case PixelFormat::RGBA8888:
      return "RGBA8888";

    case PixelFormat::ABGR8888:
      return "ABGR8888";

    case PixelFormat::BGRA8888:
      return "BGRA8888";

    case PixelFormat::ARGB2101010:
      return "ARGB2101010";

    case PixelFormat::YV12:
      return "YV12";

    case PixelFormat::IYUV:
      return "IYUV";

    case PixelFormat::YUY2:
      return "YUY2";

    case PixelFormat::UYVY:
      return "UYVY";

    case PixelFormat::YVYU:
      return "YVYU";

    case PixelFormat::NV12:
      return "NV12";

    case PixelFormat::NV21:
      return "NV21";

    case PixelFormat::ExternalOES:
      return "ExternalOES";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case PixelFormat::XRGB4444:
      return "XRGB4444";

    case PixelFormat::XBGR4444:
      return "XBGR4444";

    case PixelFormat::XRGB1555:
      return "XRGB1555";

    case PixelFormat::XBGR1555:
      return "XBGR1555";

    case PixelFormat::XRGB8888:
      return "XRGB8888";

    case PixelFormat::XBGR8888:
      return "XBGR8888";

#elif SDL_VERSION_ATLEAST(2, 0, 12)

    case PixelFormat::BGR444:
      return "BGR444";

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    default:
      throw Error{"Did not recognize pixel format!"};
  }
}

inline auto operator<<(std::ostream& stream, const PixelFormat format) -> std::ostream&
{
  return stream << to_string(format);
}

[[nodiscard]] inline auto to_string(const Palette& palette) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Palette(data: {}, size: {})",
                     detail::address_of(palette.get()),
                     palette.GetSize());
#else
  return "Palette(data: " + detail::address_of(palette.get()) +
         ", size: " + std::to_string(palette.GetSize()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const Palette& palette) -> std::ostream&
{
  return stream << to_string(palette);
}

template <typename T>
[[nodiscard]] auto to_string(const BasicPixelFormatInfo<T>& info) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("PixelFormatInfo(data: {}, name: {})",
                     detail::address_of(info.get()),
                     info.GetName());
#else
  return "PixelFormatInfo(data: " + detail::address_of(info.get()) +
         ", name: " + info.GetName() + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicPixelFormatInfo<T>& info) -> std::ostream&
{
  return stream << to_string(info);
}

}  // namespace cen

#endif  // CENTURION_PIXELS_HPP_
