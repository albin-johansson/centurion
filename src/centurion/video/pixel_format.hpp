#ifndef CENTURION_PIXEL_FORMAT_HEADER
#define CENTURION_PIXEL_FORMAT_HEADER

// clang-format off
#include "../compiler/features.hpp"
// clang-format on

#include <SDL.h>

#include <ostream>  // ostream
#include <string>   // string, to_string

#ifdef CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/czstring.hpp"
#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/not_null.hpp"
#include "../core/owner.hpp"
#include "../core/to_underlying.hpp"
#include "../detail/address_of.hpp"
#include "../detail/owner_handle_api.hpp"
#include "color.hpp"

namespace cen {

/// \addtogroup video
/// \{

/**
 * \enum pixel_format
 *
 * \brief Represents different pixel formats.
 *
 * \see `SDL_PixelFormatEnum`
 *
 * \since 3.1.0
 */
enum class pixel_format : u32
{
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

template <typename B>
class basic_pixel_format_info;

/**
 * \typedef pixel_format_info
 *
 * \brief Represents an owning pixel format info instance.
 *
 * \since 5.2.0
 */
using pixel_format_info = basic_pixel_format_info<detail::owning_type>;

/**
 * \typedef pixel_format_info_handle
 *
 * \brief Represents a non-owning pixel format info instance.
 *
 * \since 5.2.0
 */
using pixel_format_info_handle = basic_pixel_format_info<detail::handle_type>;

/**
 * \class basic_pixel_format_info
 *
 * \brief Provides information about a pixel format.
 *
 * \details See `pixel_format_info` and `pixel_format_info_handle` for owning and
 * non-owning versions of this class.
 *
 * \note This class is part of the centurion owner/handle framework.
 *
 * \see pixel_format
 * \see pixel_format_info
 * \see pixel_format_info_handle
 * \see SDL_PixelFormat
 * \see SDL_PixelFormatEnum
 *
 * \since 5.2.0
 */
template <typename B>
class basic_pixel_format_info final
{
 public:
  /// \name Construction
  /// \{

  // clang-format off

  /**
   * \brief Creates a pixel format info instance based on an existing pointer.
   *
   * \note Ownership of the supplied pointer might be claimed, depending on the
   * ownership semantics of the class.
   *
   * \param format a pointer to the associated pixel format.
   *
   * \throws cen_error if the supplied pointer is null *and* the class has owning semantics.
   *
   * \since 5.2.0
   */
  explicit basic_pixel_format_info(maybe_owner<SDL_PixelFormat*> format) noexcept(!detail::is_owning<B>())
      : m_format{format}
  {
    if constexpr (detail::is_owning<B>())
    {
      if (!m_format)
      {
        throw cen_error{"Null pixel format!"};
      }
    }
  }

  // clang-format on

  /**
   * \brief Creates an owning instance based on a pixel format.
   *
   * \tparam BB dummy template parameter for SFINAE.
   *
   * \param format the associated pixel format.
   *
   * \throws sdl_error if the pixel format info could not be obtained.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_owner<BB> = 0>
  explicit basic_pixel_format_info(const pixel_format format)
      : m_format{SDL_AllocFormat(to_underlying(format))}
  {
    if (!m_format)
    {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a handle based on an owning pixel format info instance.
   *
   * \param info the associated pixel format info instance.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_handle<BB> = 0>
  explicit basic_pixel_format_info(const pixel_format_info& info) noexcept
      : m_format{info.get()}
  {}

  /// \} End of construction

  /// \name Pixel/RGB/RGBA conversions
  /// \{

  /**
   * \brief Returns a color that corresponds to a masked pixel value.
   *
   * \param pixel the masked pixel value.
   *
   * \return a color that corresponds to a pixel value, according to the format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto pixel_to_rgb(const u32 pixel) const noexcept -> color
  {
    u8 red{};
    u8 green{};
    u8 blue{};
    SDL_GetRGB(pixel, m_format, &red, &green, &blue);
    return color{red, green, blue};
  }

  /**
   * \brief Returns a color that corresponds to a masked pixel value.
   *
   * \param pixel the masked pixel value.
   *
   * \return a color that corresponds to a pixel value, according to the format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto pixel_to_rgba(const u32 pixel) const noexcept -> color
  {
    u8 red{};
    u8 green{};
    u8 blue{};
    u8 alpha{};
    SDL_GetRGBA(pixel, m_format, &red, &green, &blue, &alpha);
    return color{red, green, blue, alpha};
  }

  /**
   * \brief Returns a pixel color value based on the RGB values of a color.
   *
   * \note The alpha component is assumed to be `0xFF`, i.e. fully opaque.
   *
   * \param color the color that will be converted.
   *
   * \return a masked pixel color value, based on the pixel format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto rgb_to_pixel(const color& color) const noexcept -> u32
  {
    return SDL_MapRGB(m_format, color.red(), color.green(), color.blue());
  }

  /**
   * \brief Returns a pixel color value based on the RGBA values of a color.
   *
   * \param color the color that will be converted.
   *
   * \return a masked pixel color value, based on the pixel format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto rgba_to_pixel(const color& color) const noexcept -> u32
  {
    return SDL_MapRGBA(m_format, color.red(), color.green(), color.blue(), color.alpha());
  }

  /// \} End of pixel/RGB/RGBA conversions

  /// \name Queries
  /// \{

  /**
   * \brief Returns the associated pixel format.
   *
   * \return the associated pixel format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(m_format->format);
  }

  /**
   * \brief Returns a human-readable name associated with the format.
   *
   * \details This function never returns a null-pointer, instead it returns
   * "SDL_PIXELFORMAT_UNKNOWN" if the format is ill-formed.
   *
   * \return a human-readable name associated with the format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto name() const noexcept -> not_null<czstring>
  {
    return SDL_GetPixelFormatName(m_format->format);
  }

  /**
   * \brief Returns a pointer to the associated pixel format instance.
   *
   * \warning Do not claim ownership of the returned pointer.
   *
   * \return a pointer to the internal pixel format.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_PixelFormat*
  {
    return m_format.get();
  }

  /// \} End of queries

  /// \name Conversions
  /// \{

  /**
   * \brief Indicates whether or not a handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.2.0
   */
  template <typename BB = B, detail::is_handle<BB> = 0>
  [[nodiscard]] explicit operator bool() const noexcept
  {
    return m_format;
  }

  /// \} End of conversions

 private:
  struct deleter final
  {
    void operator()(SDL_PixelFormat* format) noexcept
    {
      SDL_FreeFormat(format);
    }
  };
  detail::pointer_manager<B, SDL_PixelFormat, deleter> m_format;
};

/**
 * \brief Returns a textual representation of a pixel format info instance.
 *
 * \tparam T the ownership semantics tag.
 *
 * \param info the pixel format info instance that will be converted.
 *
 * \return a string that represents the pixel format info.
 *
 * \since 6.2.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_pixel_format_info<T>& info) -> std::string
{
#ifdef CENTURION_HAS_FEATURE_FORMAT
  return std::format("pixel_format_info{{data: {}, name: {}}}",
                     detail::address_of(info.get()),
                     info.name());
#else
  return "pixel_format_info{data: " + detail::address_of(info.get()) +
         ", name: " + info.name() + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/**
 * \brief Prints a textual representation of a pixel format info instance.
 *
 * \tparam T the ownership semantics tag.
 *
 * \param stream the output stream that will be used.
 * \param info the pixel format info that will be printed.
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_pixel_format_info<T>& info)
    -> std::ostream&
{
  return stream << to_string(info);
}

/// \name Pixel format comparison operators
/// \{

/**
 * \brief Indicates whether or not the two pixel format values are the same.
 *
 * \param lhs the left-hand side pixel format value.
 * \param rhs the right-hand side pixel format value.
 *
 * \return `true` if the pixel format values are the same; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto operator==(const pixel_format lhs,
                                        const SDL_PixelFormatEnum rhs) noexcept -> bool
{
  return static_cast<SDL_PixelFormatEnum>(lhs) == rhs;
}

/// \copydoc operator==(pixel_format, SDL_PixelFormatEnum)
[[nodiscard]] constexpr auto operator==(const SDL_PixelFormatEnum lhs,
                                        const pixel_format rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not the two pixel format values aren't the same.
 *
 * \param lhs the left-hand side pixel format value.
 * \param rhs the right-hand side pixel format value.
 *
 * \return `true` if the pixel format values aren't the same; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto operator!=(const pixel_format lhs,
                                        const SDL_PixelFormatEnum rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(pixel_format, SDL_PixelFormatEnum)
[[nodiscard]] constexpr auto operator!=(const SDL_PixelFormatEnum lhs,
                                        const pixel_format rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of pixel format comparison operators

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_PIXEL_FORMAT_HEADER