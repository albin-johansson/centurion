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
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "memory.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/**
 * \ingroup video
 * \defgroup pixels Pixels
 *
 * \brief Contains utilities related to pixel formats and colors.
 *
 * \see `palette`
 * \see `pixel_format`
 * \see `pixel_format_info`
 */

/// \addtogroup pixels
/// \{

/**
 * \brief Represents different pixel formats.
 */
enum class pixel_format : uint32 {
  unknown = SDL_PIXELFORMAT_UNKNOWN,

  index1_lsb = SDL_PIXELFORMAT_INDEX1LSB,
  index1_msb = SDL_PIXELFORMAT_INDEX1MSB,
  index4_lsb = SDL_PIXELFORMAT_INDEX4LSB,
  index4_msb = SDL_PIXELFORMAT_INDEX4MSB,
  index8 = SDL_PIXELFORMAT_INDEX8,

  rgba32 = SDL_PIXELFORMAT_RGBA32,
  argb32 = SDL_PIXELFORMAT_ARGB32,
  bgra32 = SDL_PIXELFORMAT_BGRA32,
  abgr32 = SDL_PIXELFORMAT_ABGR32,

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
  bgr888 = SDL_PIXELFORMAT_BGR888,

  rgbx8888 = SDL_PIXELFORMAT_RGBX8888,
  bgrx8888 = SDL_PIXELFORMAT_BGRX8888,

  argb8888 = SDL_PIXELFORMAT_ARGB8888,
  rgba8888 = SDL_PIXELFORMAT_RGBA8888,
  abgr8888 = SDL_PIXELFORMAT_ABGR8888,
  bgra8888 = SDL_PIXELFORMAT_BGRA8888,

  argb2101010 = SDL_PIXELFORMAT_ARGB2101010,

  yv12 = SDL_PIXELFORMAT_YV12,
  iyuv = SDL_PIXELFORMAT_IYUV,
  yuy2 = SDL_PIXELFORMAT_YUY2,
  uyvy = SDL_PIXELFORMAT_UYVY,
  yvyu = SDL_PIXELFORMAT_YVYU,
  nv12 = SDL_PIXELFORMAT_NV12,
  nv21 = SDL_PIXELFORMAT_NV21,
  external_oes = SDL_PIXELFORMAT_EXTERNAL_OES,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  xrgb4444 = SDL_PIXELFORMAT_XRGB4444,
  xbgr4444 = SDL_PIXELFORMAT_XBGR4444,

  xrgb1555 = SDL_PIXELFORMAT_XRGB1555,
  xbgr1555 = SDL_PIXELFORMAT_XBGR1555,

  xrgb8888 = SDL_PIXELFORMAT_XRGB8888,
  xbgr8888 = SDL_PIXELFORMAT_XBGR8888
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
};

/// \name Pixel format functions
/// \{

[[nodiscard]] constexpr auto to_string(const pixel_format format) -> std::string_view
{
  switch (format) {
    case pixel_format::unknown:
      return "unknown";

    case pixel_format::index1_lsb:
      return "index1_lsb";

    case pixel_format::index1_msb:
      return "index1_msb";

    case pixel_format::index4_lsb:
      return "index4_lsb";

    case pixel_format::index4_msb:
      return "index4_msb";

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

    case pixel_format::bgr444:
      return "bgr444";

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

    default:
      throw exception{"Did not recognize pixel format!"};
  }
}

inline auto operator<<(std::ostream& stream, const pixel_format format) -> std::ostream&
{
  return stream << to_string(format);
}

/// \} End of pixel format functions

/**
 * \brief Represents a palette of colors.
 *
 * \details This class features an interface similar to a general container type, with support
 * for the subscript operator and element iteration.
 */
class palette final {
 public:
  using iterator = SDL_Color*;
  using const_iterator = const SDL_Color*;

  /// \name Construction
  /// \{

  /**
   * \brief Creates a palette.
   *
   * \param count the number of colors in the palette.
   *
   * \throws sdl_error if the palette cannot be created.
   */
  explicit palette(const int count) : mPalette{SDL_AllocPalette(count)}
  {
    if (!mPalette) {
      throw sdl_error{};
    }
  }

  /// \} End of construction

  /// \name Setters
  /// \{

  /**
   * \brief Sets a color in the palette.
   *
   * \pre `index` must not be negative.
   * \pre `index` must be less than the size of the palette.
   *
   * \param index the index of the color slot that will be changed.
   * \param color the new color that will be used.
   */
  auto set_color(const int index, const color& color) noexcept -> result
  {
    assert(index >= 0);
    assert(index < size());
    return SDL_SetPaletteColors(mPalette.get(), color.data(), index, 1) == 0;
  }

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the color in the palette at the specified index.
   *
   * \param index the index of color in the palette.
   *
   * \throws cen_error if the index is invalid.
   *
   * \return the found color.
   */
  [[nodiscard]] auto at(const int index) const -> color
  {
    if (index >= 0 && index < size()) {
      return color{mPalette->colors[index]};
    }
    else {
      throw exception{"Palette index out of bounds!"};
    }
  }

  /// \copydoc at()
  [[nodiscard]] auto operator[](const int index) const -> color { return at(index); }

  /**
   * \brief Returns the amount of colors in the palette.
   *
   * \return the amount of colors.
   */
  [[nodiscard]] auto size() const noexcept -> int { return mPalette->ncolors; }

  /**
   * \brief Returns the version of the palette.
   *
   * \note This value can be incremented by `set_color()`.
   *
   * \return the palette version.
   */
  [[nodiscard]] auto version() const noexcept -> uint32 { return mPalette->version; }

  /// \} End of getters

  /// \name Misc functions
  /// \{

  [[nodiscard]] auto get() const noexcept -> SDL_Palette* { return mPalette.get(); }

  [[nodiscard]] auto begin() noexcept -> iterator { return mPalette->colors; }

  [[nodiscard]] auto begin() const noexcept -> const_iterator { return mPalette->colors; }

  [[nodiscard]] auto end() noexcept -> iterator { return mPalette->colors + size(); }

  [[nodiscard]] auto end() const noexcept -> const_iterator
  {
    return mPalette->colors + size();
  }

  /// \} End of misc functions

 private:
  managed_ptr<SDL_Palette> mPalette;
};

/// \name Palette functions
/// \{

[[nodiscard]] inline auto to_string(const palette& palette) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("palette(data: {}, size: {})",
                     detail::address_of(palette.get()),
                     palette.size());
#else
  return "palette(data: " + detail::address_of(palette.get()) +
         ", size: " + std::to_string(palette.size()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const palette& palette) -> std::ostream&
{
  return stream << to_string(palette);
}

/// \} End of palette functions

template <typename B>
class basic_pixel_format_info;

using pixel_format_info = basic_pixel_format_info<detail::owner_tag>;
using pixel_format_info_handle = basic_pixel_format_info<detail::handle_tag>;

/**
 * \brief Provides information about a pixel format.
 *
 * \ownerhandle `pixel_format_info`/`pixel_format_info_handle`
 *
 * \see `pixel_format`
 * \see `pixel_format_info`
 * \see `pixel_format_info_handle`
 */
template <typename T>
class basic_pixel_format_info final {
 public:
  /// \name Construction
  /// \{

  // clang-format off

  /**
   * \brief Creates a pixel format info instance.
   *
   * \details Ownership of the supplied pointer is claimed if the instance has owning semantics.
   *
   * \param format the associated pixel format.
   *
   * \throws exception if the pointer is null and the class has owning semantics.
   */
  explicit basic_pixel_format_info(maybe_owner<SDL_PixelFormat*> format) noexcept(detail::is_handle<T>)
      : mFormat{format}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mFormat) {
        throw exception{"Null pixel format!"};
      }
    }
  }

  // clang-format on

  /**
   * \brief Creates a pixel format info instance.
   *
   * \param format the pixel format to query.
   *
   * \throws sdl_error if the pixel format information cannot be obtained.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_pixel_format_info(const pixel_format format)
      : mFormat{SDL_AllocFormat(to_underlying(format))}
  {
    if (!mFormat) {
      throw sdl_error{};
    }
  }

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_pixel_format_info(const pixel_format_info& owner) noexcept
      : mFormat{owner.get()}
  {}

  /// \} End of construction

  /// \name Pixel/RGB/RGBA conversions
  /// \{

  /**
   * \brief Returns an RGB color that corresponds to a masked pixel value.
   *
   * \details The returned color is always fully opaque.
   *
   * \param pixel the pixel value.
   *
   * \return a color that corresponds to a pixel value, according to the format.
   */
  [[nodiscard]] auto pixel_to_rgb(const uint32 pixel) const noexcept -> color
  {
    uint8 red{};
    uint8 green{};
    uint8 blue{};
    SDL_GetRGB(pixel, mFormat, &red, &green, &blue);
    return {red, green, blue};
  }

  /**
   * \brief Returns an RGBA color that corresponds to a masked pixel value.
   *
   * \param pixel the pixel value.
   *
   * \return a color that corresponds to a pixel value, according to the format.
   */
  [[nodiscard]] auto pixel_to_rgba(const uint32 pixel) const noexcept -> color
  {
    uint8 red{};
    uint8 green{};
    uint8 blue{};
    uint8 alpha{};
    SDL_GetRGBA(pixel, mFormat, &red, &green, &blue, &alpha);
    return {red, green, blue, alpha};
  }

  /**
   * \brief Returns a pixel color value based on the RGB values of a color.
   *
   * \details The pixel is assumed to be fully opaque.
   *
   * \param color the color that will be converted.
   *
   * \return a masked pixel color value, based on the format.
   */
  [[nodiscard]] auto rgb_to_pixel(const color& color) const noexcept -> uint32
  {
    return SDL_MapRGB(mFormat, color.red(), color.green(), color.blue());
  }

  /**
   * \brief Returns a pixel color value based on the RGBA values of a color.
   *
   * \param color the color that will be converted.
   *
   * \return a masked pixel color value, based on the format.
   */
  [[nodiscard]] auto rgba_to_pixel(const color& color) const noexcept -> uint32
  {
    return SDL_MapRGBA(mFormat, color.red(), color.green(), color.blue(), color.alpha());
  }

  /// \} End of pixel/RGB/RGBA conversions

  /// \name Getters
  /// \{

  /**
   * \brief Returns the associated pixel format.
   *
   * \return the associated pixel format.
   */
  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(mFormat->format);
  }

  /**
   * \brief Returns a human-readable name associated with the format.
   *
   * \details This function returns `"SDL_PIXELFORMAT_UNKNOWN"` if the format is ill-formed.
   *
   * \return a non-null human-readable name associated with the format.
   */
  [[nodiscard]] auto name() const noexcept -> const char*
  {
    return SDL_GetPixelFormatName(mFormat->format);
  }

  /// \} End of getters

  /// \name Misc functions
  /// \{

  [[nodiscard]] auto get() const noexcept -> SDL_PixelFormat* { return mFormat.get(); }

  /**
   * \brief Indicates whether a handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return mFormat;
  }

  /// \} End of misc functions

 private:
  detail::pointer<T, SDL_PixelFormat> mFormat;
};

/// \name Pixel format info functions
/// \{

template <typename T>
[[nodiscard]] auto to_string(const basic_pixel_format_info<T>& info) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("pixel_format_info(data: {}, name: '{}')",
                     detail::address_of(info.get()),
                     info.name());
#else
  return "pixel_format_info(data: " + detail::address_of(info.get()) + ", name: '" +
         info.name() + "')";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_pixel_format_info<T>& info) -> std::ostream&
{
  return stream << to_string(info);
}

/// \} End of pixel format info functions

/// \} End of group pixels

}  // namespace cen

#endif  // CENTURION_PIXELS_HPP_
