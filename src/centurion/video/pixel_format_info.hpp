#ifndef CENTURION_PIXEL_FORMAT_INFO_HEADER
#define CENTURION_PIXEL_FORMAT_INFO_HEADER

#include <SDL.h>

#include <ostream>  // ostream
#include <string>   // string, to_string

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/not_null.hpp"
#include "../core/owner.hpp"
#include "../core/str.hpp"
#include "../core/to_underlying.hpp"
#include "../detail/address_of.hpp"
#include "../detail/owner_handle_api.hpp"
#include "color.hpp"
#include "pixel_format.hpp"

namespace cen {

/// \addtogroup video
/// \{

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
 * \ownerhandle `pixel_format_info`/ `pixel_format_info_handle`
 *
 * \see `pixel_format`
 * \see `pixel_format_info`
 * \see `pixel_format_info_handle`
 * \see `SDL_PixelFormat`
 * \see `SDL_PixelFormatEnum`
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
    if (!m_format) {
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
  [[nodiscard]] auto name() const noexcept -> not_null<str>
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

/// \name String conversions
/// \{

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
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("pixel_format_info{{data: {}, name: {}}}",
                     detail::address_of(info.get()),
                     info.name());
#else
  return "pixel_format_info{data: " + detail::address_of(info.get()) +
         ", name: " + info.name() + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

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
auto operator<<(std::ostream& stream, const basic_pixel_format_info<T>& info) -> std::ostream&
{
  return stream << to_string(info);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_PIXEL_FORMAT_INFO_HEADER
