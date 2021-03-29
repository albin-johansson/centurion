#ifndef CENTURION_SURFACE_HEADER
#define CENTURION_SURFACE_HEADER

#include <SDL.h>
#include <SDL_image.h>

#include <cassert>  // assert
#include <ostream>  // ostream
#include <string>   // string

#include "../centurion_cfg.hpp"
#include "../detail/address_of.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../detail/to_string.hpp"
#include "../math/area.hpp"
#include "../math/rect.hpp"
#include "../misc/czstring.hpp"
#include "../misc/exception.hpp"
#include "../misc/integers.hpp"
#include "../misc/not_null.hpp"
#include "../misc/owner.hpp"
#include "blend_mode.hpp"
#include "color.hpp"
#include "pixel_format.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup graphics
/// \{

template <typename T>
class basic_surface;

/**
 * \typedef surface
 *
 * \brief Represents an owning surface.
 *
 * \since 5.0.0
 */
using surface = basic_surface<detail::owning_type>;

/**
 * \typedef surface_handle
 *
 * \brief Represents a non-owning surface.
 *
 * \since 5.0.0
 */
using surface_handle = basic_surface<detail::handle_type>;

/**
 * \class basic_surface
 *
 * \brief Represents a non-accelerated collection of pixels that constitute an
 * image.
 *
 * \details Surfaces are often used for icons and snapshots, as an "intermediate"
 * representation that can be manually manipulated, unlike textures. There is no
 * support for directly rendering surfaces, but they can be converted to
 * textures, which in turn can be rendered.
 *
 * \tparam B Used to determine the ownership semantics of the class.
 *
 * \since 4.0.0
 *
 * \headerfile surface.hpp
 */
template <typename T>
class basic_surface final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a surface from a pointer to an SDL surface.
   *
   * \note Depending on the type of the surface, ownership of the supplied SDL
   * surface might be claimed.
   *
   * \param surface a pointer to the associated surface.
   *
   * \since 4.0.0
   */
  explicit basic_surface(SDL_Surface* surface) noexcept(!detail::is_owning<T>())
      : m_surface{surface}
  {
    if constexpr (detail::is_owning<T>())
    {
      if (!m_surface)
      {
        throw cen_error{"Cannot create surface from null pointer!"};
      }
    }
  }

  /**
   * \brief Creates a surface based on the image at the specified path.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param file the file path of the image file that will be loaded, can't
   * be null.
   *
   * \throws img_error if the surface cannot be created.
   *
   * \since 4.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = true>
  explicit basic_surface(const not_null<czstring> file)
      : m_surface{IMG_Load(file)}
  {
    if (!m_surface)
    {
      throw img_error{};
    }
  }

  /**
   * \brief Creates a surface based on the image at the specified path.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param file the file path of the image file that will be loaded.
   *
   * \throws img_error if the surface cannot be created.
   *
   * \since 5.3.0
   */
  template <typename TT = T, detail::is_owner<TT> = true>
  explicit basic_surface(const std::string& file) : basic_surface{file.c_str()}
  {}

  /**
   * \brief Creates a surface with the specified dimensions and pixel format.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param size the size of the surface.
   * \param pixelFormat the pixel format that will be used by the surface.
   *
   * \throws sdl_error if the surface cannot be created.
   *
   * \since 5.3.0
   */
  template <typename TT = T, detail::is_owner<TT> = true>
  basic_surface(const iarea size, const pixel_format pixelFormat)
      : m_surface{SDL_CreateRGBSurfaceWithFormat(0,
                                                 size.width,
                                                 size.height,
                                                 0,
                                                 static_cast<u32>(pixelFormat))}
  {
    if (!m_surface)
    {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates and returns a surface with the specified characteristics.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param file the file path of the image that the surface will be based on.
   * \param blendMode the blend mode that will be used.
   * \param pixelFormat the pixel format that will be used.
   *
   * \return an owning surface, with the specified blend mode and pixel format.
   *
   * \since 5.2.0
   */
  template <typename TT = T, detail::is_owner<TT> = true>
  [[nodiscard]] static auto with_format(const not_null<czstring> file,
                                        const blend_mode blendMode,
                                        const pixel_format pixelFormat)
      -> basic_surface
  {
    assert(file);

    basic_surface source{file};
    source.set_blend_mode(blendMode);

    return source.convert(pixelFormat);
  }

  /**
   * \see with_format()
   */
  template <typename TT = T, detail::is_owner<TT> = true>
  [[nodiscard]] static auto with_format(const std::string& file,
                                        const blend_mode blendMode,
                                        const pixel_format pixelFormat)
      -> basic_surface
  {
    return with_format(file.c_str(), blendMode, pixelFormat);
  }

  /**
   * \brief Creates and returns a surface based on a BMP file.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \param file the path to the BMP file that contains the surface data.
   *
   * \return the created surface.
   *
   * \throws sdl_error if the surface couldn't be loaded.
   *
   * \since 5.3.0
   */
  template <typename TT = T, detail::is_owner<TT> = true>
  [[nodiscard]] static auto from_bmp(const not_null<czstring> file)
      -> basic_surface
  {
    assert(file);
    return basic_surface{SDL_LoadBMP(file)};
  }

  /**
   * \see from_bmp()
   */
  template <typename TT = T, detail::is_owner<TT> = true>
  [[nodiscard]] static auto from_bmp(const std::string& file) -> basic_surface
  {
    return from_bmp(file.c_str());
  }

  /**
   * \brief Creates a copy of the supplied surface.
   *
   * \param other the surface that will be copied.
   *
   * \since 4.0.0
   */
  basic_surface(const basic_surface& other) noexcept(!detail::is_owning<T>())
  {
    if constexpr (detail::is_owning<T>())
    {
      copy(other);
    }
    else
    {
      m_surface = other.get();
    }
  }

  /**
   * \brief Creates a surface by moving the supplied surface.
   *
   * \param other the surface that will be moved.
   *
   * \since 4.0.0
   */
  basic_surface(basic_surface&& other) noexcept = default;

  /// \} End of construction

  /**
   * \brief Copies the supplied surface.
   *
   * \param other the surface that will be copied.
   *
   * \throws sdl_error if the supplied surface couldn't be copied.
   *
   * \since 4.0.0
   */
  auto operator=(const basic_surface& other) noexcept(!detail::is_owning<T>())
      -> basic_surface&
  {
    if (this != &other)
    {
      if constexpr (detail::is_owning<T>())
      {
        copy(other);
      }
      else
      {
        m_surface = other.get();
      }
    }
    return *this;
  }

  /**
   * \brief Moves the supplied surface into this surface.
   *
   * \param other the surface that will be moved.
   *
   * \return the surface that claimed the supplied surface.
   *
   * \since 4.0.0
   */
  auto operator=(basic_surface&& other) noexcept -> basic_surface& = default;

  /// \name Save functions
  /// \{

  /**
   * \brief Saves the surface as a BMP image.
   *
   * \param file the file path that the surface data will be saved at.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 5.3.0
   */
  auto save_as_bmp(const not_null<czstring> file) const noexcept -> bool
  {
    assert(file);
    const auto result = SDL_SaveBMP(get(), file);
    return result != -1;
  }

  /**
   * \see save_as_bmp()
   * \since 6.0.0
   */
  auto save_as_bmp(const std::string& file) const noexcept -> bool  // NOLINT
  {
    return save_as_bmp(file.c_str());
  }

  /**
   * \brief Saves the surface as a PNG image.
   *
   * \param file the file path that the surface data will be saved at.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 6.0.0
   */
  auto save_as_png(const not_null<czstring> file) const noexcept -> bool
  {
    assert(file);
    const auto result = IMG_SavePNG(get(), file);
    return result != -1;
  }

  /**
   * \see save_as_png()
   * \since 6.0.0
   */
  auto save_as_png(const std::string& file) const noexcept -> bool  // NOLINT
  {
    return save_as_png(file.c_str());
  }

  /**
   * \brief Saves the surface as a JPG image.
   *
   * \note The quality parameter is supplied to libjpeg in the SDL
   * implementation, but the limitations on its values are unknown at the time
   * of writing.
   *
   * \param file the file path that the surface data will be saved at.
   * \param quality the quality of the JPG image.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \since 6.0.0
   */
  auto save_as_jpg(const not_null<czstring> file,
                   const int quality) const noexcept -> bool
  {
    assert(file);
    const auto result = IMG_SaveJPG(get(), file, quality);
    return result != -1;
  }

  /**
   * \see save_as_jpg()
   * \since 6.0.0
   */
  auto save_as_jpg(const std::string& file, const int quality) const noexcept
      -> bool
  {
    return save_as_jpg(file.c_str(), quality);
  }

  /// \} End of save functions

  /// \name Locking
  /// \{

  /**
   * \brief Attempts to lock the surface, so that the associated pixel data can
   * be modified.
   *
   * \details This method has no effect if `must_lock()` returns `false`.
   *
   * \return `true` if the locking of the surface was successful or if locking
   * isn't required for modifying the surface; `false` if something went wrong.
   *
   * \since 4.0.0
   */
  auto lock() noexcept -> bool
  {
    if (must_lock())
    {
      const auto result = SDL_LockSurface(m_surface);
      return result == 0;
    }
    else
    {
      return true;
    }
  }

  /**
   * \brief Unlocks the surface.
   *
   * \details This method has no effect if `must_lock()` returns `false`.
   *
   * \since 4.0.0
   */
  void unlock() noexcept
  {
    if (must_lock())
    {
      SDL_UnlockSurface(m_surface);
    }
  }

  /**
   * \brief Indicates whether or not the surface must be locked before modifying
   * the pixel data associated with the surface.
   *
   * \return `true` if the surface must be locked before modification; `false`
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto must_lock() const noexcept -> bool
  {
    return SDL_MUSTLOCK(m_surface);
  }

  /// \} End of locking

  /// \name Setters
  /// \{

  /**
   * \brief Sets the color of the pixel at the specified coordinate.
   *
   * \details This method has no effect if the coordinate is out-of-bounds or if
   * something goes wrong when attempting to modify the pixel data.
   *
   * \param pixel the pixel that will be changed.
   * \param color the new color of the pixel.
   *
   * \since 4.0.0
   */
  void set_pixel(const ipoint& pixel, const color& color) noexcept
  {
    if (!in_bounds(pixel) || !lock())
    {
      return;
    }

    const int nPixels = (m_surface->pitch / 4) * height();
    const int index = (pixel.y() * width()) + pixel.x();

    if ((index >= 0) && (index < nPixels))
    {
      const auto info = format_info();
      auto* pixels = reinterpret_cast<u32*>(m_surface->pixels);
      pixels[index] = info.rgba_to_pixel(color);
    }

    unlock();
  }

  /**
   * \brief Sets the alpha component modulation value.
   *
   * \param alpha the new alpha component value, in the range [0, 255].
   *
   * \since 4.0.0
   */
  void set_alpha(const u8 alpha) noexcept
  {
    SDL_SetSurfaceAlphaMod(m_surface, alpha);
  }

  /**
   * \brief Sets the color modulation that will be used by the surface.
   *
   * \param color the color that represents the color modulation that will be
   * used.
   *
   * \since 4.0.0
   */
  void set_color_mod(const color& color) noexcept
  {
    SDL_SetSurfaceColorMod(m_surface, color.red(), color.green(), color.blue());
  }

  /**
   * \brief Sets the blend mode that will be used by the surface.
   *
   * \param mode the blend mode that will be used.
   *
   * \since 4.0.0
   */
  void set_blend_mode(const blend_mode mode) noexcept
  {
    SDL_SetSurfaceBlendMode(m_surface, static_cast<SDL_BlendMode>(mode));
  }

  /**
   * \brief Sets the value of the RLE acceleration hint.
   *
   * \param enabled `true` if the RLE optimization hint should be enabled;
   * `false` otherwise.
   *
   * \return `true` on success; `false` otherwise.
   *
   * \see is_rle_enabled()
   *
   * \since 5.2.0
   */
  auto set_rle_hint(const bool enabled) noexcept -> bool
  {
    return SDL_SetSurfaceRLE(m_surface, enabled ? 1 : 0) == 0;
  }

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the alpha component modulation of the surface.
   *
   * \return the alpha modulation value, in the range [0, 255].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto alpha() const noexcept -> u8
  {
    u8 alpha{0xFF};
    SDL_GetSurfaceAlphaMod(m_surface, &alpha);
    return alpha;
  }

  /**
   * \brief Returns the color modulation of the surface.
   *
   * \return a color that represents the color modulation of the surface.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto color_mod() const noexcept -> color
  {
    u8 red{};
    u8 green{};
    u8 blue{};
    SDL_GetSurfaceColorMod(m_surface, &red, &green, &blue);
    return color{red, green, blue};
  }

  /**
   * \brief Returns the blend mode that is being used by the surface.
   *
   * \return the blend mode that the surface uses.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetSurfaceBlendMode(m_surface, &mode);
    return static_cast<blend_mode>(mode);
  }

  /**
   * \brief Creates and returns a surface based on this surface with the
   * specified pixel format.
   *
   * \param format the pixel format that will be used by the new surface.
   *
   * \return a surface based on this surface with the specified
   * pixel format.
   *
   * \throws sdl_error if the surface cannot be created.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto convert(const pixel_format format) const -> basic_surface
  {
    const auto rawFormat = static_cast<u32>(format);
    if (auto* ptr = SDL_ConvertSurfaceFormat(m_surface, rawFormat, 0))
    {
      basic_surface result{ptr};
      result.set_blend_mode(get_blend_mode());
      return result;
    }
    else
    {
      throw sdl_error{};
    }
  }

  /**
   * \brief Returns the width of the surface.
   *
   * \return the width of the surface.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return m_surface->w;
  }

  /**
   * \brief Returns the height of the surface.
   *
   * \return the height of the surface.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return m_surface->h;
  }

  /**
   * \brief Returns the size of the surface.
   *
   * \return the size of the surface.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto size() const noexcept -> iarea
  {
    return iarea{width(), height()};
  }

  /**
   * \brief Returns the pitch (the length of a row of pixels in bytes) of the
   * surface.
   *
   * \return the pitch of the surface.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto pitch() const noexcept -> int
  {
    return m_surface->pitch;
  }

  /**
   * \brief Returns a pointer to the pixel data of the surface.
   *
   * \details It's possible to modify the surface through the returned pointer.
   *
   * \return a pointer to the pixel data of the surface.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto pixels() noexcept -> void*
  {
    return m_surface->pixels;
  }

  /**
   * \brief Returns a pointer to the pixel data of the surface.
   *
   * \return a pointer to the pixel data of the surface.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto pixels() const noexcept -> const void*
  {
    return m_surface->pixels;
  }

  /**
   * \brief Returns a pointer to the pixel data of the surface.
   *
   * \return a pointer to the pixel data of the surface.
   *
   * \since 5.3.0
   */
  [[nodiscard]] auto data() noexcept -> void*
  {
    return pixels();
  }

  /**
   * \copydoc data()
   */
  [[nodiscard]] auto data() const noexcept -> const void*
  {
    return pixels();
  }

  /**
   * \brief Returns the pixel format info associated with the surface.
   *
   * \return the associated pixel format info.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto format_info() const noexcept -> pixel_format_info_handle
  {
    return pixel_format_info_handle{m_surface->format};
  }

  /**
   * \brief Returns the clipping information associated with the surface.
   *
   * \return the clipping information associated with the surface.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto clip() const noexcept -> irect
  {
    const auto rect = m_surface->clip_rect;
    return {{rect.x, rect.y}, {rect.w, rect.h}};
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Indicates whether or not the surface is RLE-enabled.
   *
   * \return `true` if the surface is RLE-enabled; `false` otherwise.
   *
   * \since 5.2.0
   */
  [[nodiscard]] auto is_rle_enabled() const noexcept -> bool
  {
    return SDL_HasSurfaceRLE(m_surface) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Returns a pointer to the associated `SDL_Surface`.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated `SDL_Surface`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Surface*
  {
    return m_surface.get();
  }

  /// \} End of getters

  /// \name Conversions
  /// \{

  /**
   * \brief Indicates whether or not a surface handle holds a non-null pointer.
   *
   * \tparam BB dummy parameter for SFINAE.
   *
   * \return `true` if the surface handle holds a non-null pointer; `false`
   * otherwise.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = true>
  explicit operator bool() const noexcept
  {
    return m_surface != nullptr;
  }

  /**
   * \brief Converts to `SDL_Surface*`.
   *
   * \return a pointer to the associated `SDL_Surface`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] explicit operator SDL_Surface*() noexcept
  {
    return get();
  }

  /**
   * \brief Converts to `const SDL_Surface*`.
   *
   * \return a pointer to the associated `SDL_Surface`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] explicit operator const SDL_Surface*() const noexcept
  {
    return get();
  }

  /// \} End of conversions

 private:
  struct deleter final
  {
    void operator()(SDL_Surface* surface) noexcept
    {
      SDL_FreeSurface(surface);
    }
  };
  detail::pointer_manager<T, SDL_Surface, deleter> m_surface;

  /**
   * \brief Copies the contents of the supplied surface instance into this
   * instance.
   *
   * \param other the instance that will be copied.
   *
   * \throws sdl_error if the surface cannot be copied.
   *
   * \since 4.0.0
   */
  void copy(const basic_surface& other)
  {
    m_surface.reset(other.copy_surface());
  }

  /**
   * \brief Indicates whether or not the supplied point is within the bounds of
   * the surface.
   *
   * \param point the point that will be checked.
   *
   * \return `true` if the point is within the bounds of the surface; `false`
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto in_bounds(const ipoint& point) const noexcept -> bool
  {
    return !(point.x() < 0 || point.y() < 0 || point.x() >= width() ||
             point.y() >= height());
  }

  /**
   * \brief Creates and returns copy of the associated `SDL_Surface`.
   *
   * \return a copy of the associated `SDL_Surface`, the returned pointer won't
   * be null.
   *
   * \throws sdl_error if the copy couldn't be created.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto copy_surface() const -> owner<SDL_Surface*>
  {
    if (auto* copy = SDL_DuplicateSurface(m_surface))
    {
      return copy;
    }
    else
    {
      throw sdl_error{};
    }
  }

#ifdef CENTURION_MOCK_FRIENDLY_MODE
 public:
  basic_surface() = default;
#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/**
 * \brief Returns a textual representation of a surface.
 *
 * \param surface the surface that will be converted.
 *
 * \return a textual representation of the surface.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_surface<T>& surface) -> std::string
{
  return "surface{ptr: " + detail::address_of(surface.get()) +
         ", width: " + detail::to_string(surface.width()).value() +
         ", height: " + detail::to_string(surface.height()).value() + "}";
}

/**
 * \brief Prints a textual representation of a surface.
 *
 * \param stream the stream that will be used.
 * \param surface the surface that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_surface<T>& surface)
    -> std::ostream&
{
  stream << to_string(surface);
  return stream;
}

/// \}

}  // namespace cen

#endif  // CENTURION_SURFACE_HEADER
