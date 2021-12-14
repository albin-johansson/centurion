#ifndef CENTURION_PIXELS_HPP_
#define CENTURION_PIXELS_HPP_

#include <SDL.h>

#include <cassert>      // assert
#include <memory>       // unique_ptr
#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "core/common.hpp"
#include "core/exception.hpp"
#include "core/features.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "video/color.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class pixel_format : Uint32 {
  unknown = SDL_PIXELFORMAT_UNKNOWN,

  index1lsb = SDL_PIXELFORMAT_INDEX1LSB,
  index1msb = SDL_PIXELFORMAT_INDEX1MSB,
  index4lsb = SDL_PIXELFORMAT_INDEX4LSB,
  index4msb = SDL_PIXELFORMAT_INDEX4MSB,
  index8 = SDL_PIXELFORMAT_INDEX8,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  xrgb4444 = SDL_PIXELFORMAT_XRGB4444,
  xbgr4444 = SDL_PIXELFORMAT_XBGR4444,

  xrgb1555 = SDL_PIXELFORMAT_XRGB1555,
  xbgr1555 = SDL_PIXELFORMAT_XBGR1555,

  xrgb8888 = SDL_PIXELFORMAT_XRGB8888,
  xbgr8888 = SDL_PIXELFORMAT_XBGR8888,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  rgb332 = SDL_PIXELFORMAT_RGB332,
  rgb444 = SDL_PIXELFORMAT_RGB444,

#if SDL_VERSION_ATLEAST(2, 0, 12)
  bgr444 = SDL_PIXELFORMAT_BGR444,
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  rgb555 = SDL_PIXELFORMAT_RGB555,
  bgr555 = SDL_PIXELFORMAT_BGR555,

  argb4444 = SDL_PIXELFORMAT_ARGB4444,
  rgba4444 = SDL_PIXELFORMAT_RGBA4444,
  abgr4444 = SDL_PIXELFORMAT_ABGR4444,
  bgra4444 = SDL_PIXELFORMAT_BGRA4444,

  argb1555 = SDL_PIXELFORMAT_ARGB1555,
  rgba5551 = SDL_PIXELFORMAT_RGBA5551,
  abgr1555 = SDL_PIXELFORMAT_ABGR1555,
  bgra5551 = SDL_PIXELFORMAT_BGRA5551,

  rgb565 = SDL_PIXELFORMAT_RGB565,
  bgr565 = SDL_PIXELFORMAT_BGR565,

  rgb24 = SDL_PIXELFORMAT_RGB24,
  bgr24 = SDL_PIXELFORMAT_BGR24,

  rgb888 = SDL_PIXELFORMAT_RGB888,
  rgbx8888 = SDL_PIXELFORMAT_RGBX8888,
  bgr888 = SDL_PIXELFORMAT_BGR888,
  bgrx8888 = SDL_PIXELFORMAT_BGRX8888,

  argb8888 = SDL_PIXELFORMAT_ARGB8888,
  rgba8888 = SDL_PIXELFORMAT_RGBA8888,
  abgr8888 = SDL_PIXELFORMAT_ABGR8888,
  bgra8888 = SDL_PIXELFORMAT_BGRA8888,

  argb2101010 = SDL_PIXELFORMAT_ARGB2101010,

#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rgba32 = SDL_PIXELFORMAT_RGBA8888,
  argb32 = SDL_PIXELFORMAT_ARGB8888,
  bgra32 = SDL_PIXELFORMAT_BGRA8888,
  abgr32 = SDL_PIXELFORMAT_ABGR8888,
#else
  rgba32 = SDL_PIXELFORMAT_ABGR8888,
  argb32 = SDL_PIXELFORMAT_BGRA8888,
  bgra32 = SDL_PIXELFORMAT_ARGB8888,
  abgr32 = SDL_PIXELFORMAT_RGBA8888,
#endif

  yv12 = SDL_PIXELFORMAT_YV12,
  iyuv = SDL_PIXELFORMAT_IYUV,
  yuy2 = SDL_PIXELFORMAT_YUY2,
  uyvy = SDL_PIXELFORMAT_UYVY,
  yvyu = SDL_PIXELFORMAT_YVYU,
  nv12 = SDL_PIXELFORMAT_NV12,
  nv21 = SDL_PIXELFORMAT_NV21,
  external_oes = SDL_PIXELFORMAT_EXTERNAL_OES
};

class palette final {
 public:
  using iterator = SDL_Color*;
  using const_iterator = const SDL_Color*;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a palette with the specified amount of colors.
   *
   * \param nColors the number of colors in the palette.
   *
   * \throws sdl_error if the palette couldn't be created.
   *
   * \since 6.0.0
   */
  explicit palette(const int nColors) : m_palette{SDL_AllocPalette(nColors)}
  {
    if (!m_palette) {
      throw SDLError{};
    }
  }

  /// \} End of construction

  /**
   * \brief Sets a color in the palette.
   *
   * \pre `index` must not be negative.
   * \pre `index` must be less than the size of the palette.
   *
   * \param index the index of the color slot that will be changed.
   * \param color the new color that will be used.
   *
   * \since 6.0.0
   */
  auto set_color(const int index, const Color& color) noexcept -> Result
  {
    assert(index >= 0);
    assert(index < size());
    return SDL_SetPaletteColors(m_palette.get(), color.data(), index, 1) == 0;
  }

  /**
   * \brief Returns the color in the palette at the specified index.
   *
   * \note This function returns a copy of the color, not a reference!
   *
   * \param index the index of color in the palette.
   *
   * \throws cen_error if the supplied index is out of bounds.
   *
   * \return a copy of the color at the specified index in the palette.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto at(const int index) const -> Color
  {
    if (index >= 0 && index < size()) {
      return Color{m_palette->colors[index]};
    }
    else {
      throw Error{"Palette index out of bounds!"};
    }
  }

  /**
   * \brief Returns the color in the palette at the specified index.
   *
   * \warning This function performs no bounds checking, see `at()` for a bounds checked
   * version of this function.
   *
   * \pre `index` must not be negative.
   * \pre `index` must be less than the size of the palette.
   *
   * \note This function returns a copy of the color, not a reference!
   *
   * \param index the index of color in the palette.
   *
   * \return a copy of the color at the specified index in the palette.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto operator[](const int index) const noexcept -> Color
  {
    assert(index >= 0);
    assert(index < size());
    return Color{m_palette->colors[index]};
  }

  /**
   * \brief Returns the amount of colors in the palette.
   *
   * \return the amount of colors in the palette.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto size() const noexcept -> int { return m_palette->ncolors; }

  /**
   * \brief Returns the version of the palette.
   *
   * \note This value can be incremented by `SetColor()`.
   *
   * \return the current version of the palette.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto version() const noexcept -> Uint32 { return m_palette->version; }

  /**
   * \brief Returns a pointer to the associated SDL palette.
   *
   * \warning Do not claim ownership of the returned pointer!
   *
   * \return a pointer to the associated SDL palette
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Palette* { return m_palette.get(); }

  /// \name Iteration
  /// \{

  [[nodiscard]] auto begin() noexcept -> iterator { return m_palette->colors; }

  [[nodiscard]] auto begin() const noexcept -> const_iterator { return m_palette->colors; }

  [[nodiscard]] auto end() noexcept -> iterator { return m_palette->colors + size(); }

  [[nodiscard]] auto end() const noexcept -> const_iterator
  {
    return m_palette->colors + size();
  }

  /// \} End of iteration

 private:
  struct deleter final {
    void operator()(SDL_Palette* palette) noexcept { SDL_FreePalette(palette); }
  };

  std::unique_ptr<SDL_Palette, deleter> m_palette;
};

template <typename B>
class basic_pixel_format_info;

using pixel_format_info = basic_pixel_format_info<detail::OwnerTag>;
using pixel_format_info_handle = basic_pixel_format_info<detail::HandleTag>;

template <typename B>
class basic_pixel_format_info final {
 public:
  // clang-format off

  explicit basic_pixel_format_info(MaybeOwner<SDL_PixelFormat*> format) noexcept(detail::is_handle<B>)
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
  explicit basic_pixel_format_info(const pixel_format format)
      : mFormat{SDL_AllocFormat(ToUnderlying(format))}
  {
    if (!mFormat) {
      throw SDLError{};
    }
  }

  template <typename BB = B, detail::EnableHandle<BB> = 0>
  explicit basic_pixel_format_info(const pixel_format_info& info) noexcept
      : mFormat{info.get()}
  {}

  [[nodiscard]] auto pixel_to_rgb(const Uint32 pixel) const noexcept -> Color
  {
    Uint8 red{};
    Uint8 green{};
    Uint8 blue{};
    SDL_GetRGB(pixel, mFormat, &red, &green, &blue);
    return Color{red, green, blue};
  }

  [[nodiscard]] auto pixel_to_rgba(const Uint32 pixel) const noexcept -> Color
  {
    Uint8 red{};
    Uint8 green{};
    Uint8 blue{};
    Uint8 alpha{};
    SDL_GetRGBA(pixel, mFormat, &red, &green, &blue, &alpha);
    return Color{red, green, blue, alpha};
  }

  [[nodiscard]] auto rgb_to_pixel(const Color& color) const noexcept -> Uint32
  {
    return SDL_MapRGB(mFormat, color.GetRed(), color.GetGreen(), color.GetBlue());
  }

  [[nodiscard]] auto rgba_to_pixel(const Color& color) const noexcept -> Uint32
  {
    return SDL_MapRGBA(mFormat,
                       color.GetRed(),
                       color.GetGreen(),
                       color.GetBlue(),
                       color.GetAlpha());
  }

  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(mFormat->format);
  }

  [[nodiscard]] auto name() const noexcept -> const char*
  {
    return SDL_GetPixelFormatName(mFormat->format);
  }

  [[nodiscard]] auto get() const noexcept -> SDL_PixelFormat* { return mFormat.get(); }

  template <typename BB = B, detail::EnableHandle<BB> = 0>
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return mFormat;
  }

 private:
  detail::Pointer<B, SDL_PixelFormat> mFormat;
};

[[nodiscard]] constexpr auto to_string(const pixel_format format) -> std::string_view
{
  switch (format) {
    case pixel_format::unknown:
      return "unknown";

    case pixel_format::index1lsb:
      return "index1lsb";

    case pixel_format::index1msb:
      return "index1msb";

    case pixel_format::index4lsb:
      return "index4lsb";

    case pixel_format::index4msb:
      return "index4msb";

    case pixel_format::index8:
      return "index8";

    case pixel_format::rgb332:
      return "rgb332";

    case pixel_format::argb4444:
      return "argb4444";

    case pixel_format::rgba4444:
      return "rgba4444";

    case pixel_format::abgr4444:
      return "abgr4444";

    case pixel_format::bgra4444:
      return "bgra4444";

    case pixel_format::argb1555:
      return "argb1555";

    case pixel_format::rgba5551:
      return "rgba5551";

    case pixel_format::abgr1555:
      return "abgr1555";

    case pixel_format::bgra5551:
      return "bgra5551";

    case pixel_format::rgb565:
      return "rgb565";

    case pixel_format::bgr565:
      return "bgr565";

    case pixel_format::rgb24:
      return "rgb24";

    case pixel_format::bgr24:
      return "bgr24";

    case pixel_format::rgbx8888:
      return "rgbx8888";

    case pixel_format::bgrx8888:
      return "bgrx8888";

    case pixel_format::argb8888:
      return "argb8888";

    case pixel_format::rgba8888:
      return "rgba8888";

    case pixel_format::abgr8888:
      return "abgr8888";

    case pixel_format::bgra8888:
      return "bgra8888";

    case pixel_format::argb2101010:
      return "argb2101010";

    case pixel_format::yv12:
      return "yv12";

    case pixel_format::iyuv:
      return "iyuv";

    case pixel_format::yuy2:
      return "yuy2";

    case pixel_format::uyvy:
      return "uyvy";

    case pixel_format::yvyu:
      return "yvyu";

    case pixel_format::nv12:
      return "nv12";

    case pixel_format::nv21:
      return "nv21";

    case pixel_format::external_oes:
      return "external_oes";

#if SDL_VERSION_ATLEAST(2, 0, 14)

    case pixel_format::xrgb4444:
      return "xrgb4444";

    case pixel_format::xbgr4444:
      return "xbgr4444";

    case pixel_format::xrgb1555:
      return "xrgb1555";

    case pixel_format::xbgr1555:
      return "xbgr1555";

    case pixel_format::xrgb8888:
      return "xrgb8888";

    case pixel_format::xbgr8888:
      return "xbgr8888";

#elif SDL_VERSION_ATLEAST(2, 0, 12)

    case pixel_format::bgr444:  // Equal to xbgr4444
      return "bgr444";

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    default:
      throw Error{"Did not recognize pixel format mode!"};
  }
}

[[nodiscard]] inline auto to_string(const palette& palette) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("palette{{data: {}, size: {}}}",
                     detail::address_of(palette.get()),
                     palette.size());
#else
  return "palette{data: " + detail::address_of(palette.get()) +
         ", size: " + std::to_string(palette.size()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
[[nodiscard]] auto to_string(const basic_pixel_format_info<T>& info) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("pixel_format_info{{data: {}, name: {}}}",
                     detail::address_of(info.get()),
                     info.name());
#else
  return "pixel_format_info{data: " + detail::address_of(info.get()) +
         ", name: " + info.name() + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const pixel_format format) -> std::ostream&
{
  return stream << to_string(format);
}

inline auto operator<<(std::ostream& stream, const palette& palette) -> std::ostream&
{
  return stream << to_string(palette);
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_pixel_format_info<T>& info) -> std::ostream&
{
  return stream << to_string(info);
}

}  // namespace cen

#endif  // CENTURION_PIXELS_HPP_
