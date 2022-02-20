#ifndef CENTURION_SURFACE_HPP_
#define CENTURION_SURFACE_HPP_

#include <SDL.h>

#include "color.hpp"
#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
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
class basic_surface;

using surface = basic_surface<detail::owner_tag>;          ///< An owning surface.
using surface_handle = basic_surface<detail::handle_tag>;  ///< A non-owning surface.

/**
 * \brief Represents a non-accelerated image.
 *
 * \ownerhandle `surface`/`surface_handle`
 *
 * \details Surfaces are often used for icons and snapshots, or as an intermediate
 * representation that can be manipulated, unlike textures. There is no support for directly
 * rendering surfaces. However, surfaces can be converted to textures, which in turn can be
 * rendered.
 *
 * \remarks Unlike most other Centurion components, surfaces can be copied.
 *
 * \see `surface`
 * \see `surface_handle`
 */
template <typename T>
class basic_surface final
{
 public:
  /**
   * \brief Creates a surface from an SDL surface.
   *
   * \note Ownership of the surface is claimed by owning surfaces!
   *
   * \param surface a pointer to the associated surface.
   *
   * \throws exception if the surface is owning and the supplied pointer is null.
   */
  explicit basic_surface(maybe_owner<SDL_Surface*> surface) noexcept(detail::is_handle<T>)
      : mSurface{surface}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mSurface) {
        throw exception{"Cannot create owning surface from null pointer!"};
      }
    }
  }

#ifndef CENTURION_NO_SDL_IMAGE

  /**
   * \brief Creates a surface based on the image at the specified path.
   *
   * \param file the file path of the image file.
   *
   * \throws img_error if the surface cannot be created.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_surface(const char* file) : mSurface{IMG_Load(file)}
  {
    if (!mSurface) {
      throw img_error{};
    }
  }

  /// \copydoc basic_surface(const char*)
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_surface(const std::string& file) : basic_surface{file.c_str()}
  {}

#endif  // CENTURION_NO_SDL_IMAGE

  /**
   * \brief Creates a surface with the specified dimensions and pixel format.
   *
   * \param size the size of the surface.
   * \param format the pixel format that will be used by the surface.
   *
   * \throws sdl_error if the surface cannot be created.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  basic_surface(const iarea& size, const pixel_format format)
      : mSurface{SDL_CreateRGBSurfaceWithFormat(0,
                                                size.width,
                                                size.height,
                                                0,
                                                to_underlying(format))}
  {
    if (!mSurface) {
      throw sdl_error{};
    }
  }

  basic_surface(const basic_surface& other) noexcept(detail::is_handle<T>)
  {
    if constexpr (detail::is_owner<T>) {
      copy(other);
    }
    else {
      mSurface = other.get();
    }
  }

  basic_surface(basic_surface&& other) noexcept = default;

  auto operator=(const basic_surface& other) noexcept(detail::is_handle<T>) -> basic_surface&
  {
    if (this != &other) {
      if constexpr (detail::is_owner<T>) {
        copy(other);
      }
      else {
        mSurface = other.get();
      }
    }

    return *this;
  }

  auto operator=(basic_surface&& other) noexcept -> basic_surface& = default;

  /// \name Factory functions
  /// \{

  /**
   * \brief Creates a blank surface with the specified characteristics.
   *
   * \param file the file path of the source image.
   * \param mode the blend mode to be used.
   * \param format the pixel format to be used.
   *
   * \return the resulting surface.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto with_format(const char* file,
                                        const blend_mode mode,
                                        const pixel_format format) -> surface
  {
    assert(file);

    surface source{file};
    source.set_blend_mode(mode);

    return source.convert_to(format);
  }

  /// \copydoc with_format()
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto with_format(const std::string& file,
                                        const blend_mode mode,
                                        const pixel_format format) -> surface
  {
    return with_format(file.c_str(), mode, format);
  }

  /**
   * \brief Creates and returns a surface based on a BMP file.
   *
   * \param file the path to the source BMP file.
   *
   * \return the created surface.
   *
   * \throws sdl_error if the surface cannot be loaded.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto from_bmp(const char* file) -> surface
  {
    assert(file);
    return surface{SDL_LoadBMP(file)};
  }

  /// \copydoc from_bmp()
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto from_bmp(const std::string& file) -> surface
  {
    return from_bmp(file.c_str());
  }

  /// \} End of factory functions

  /// \name Export functions
  /// \{

  /**
   * \brief Exports the surface as a BMP image.
   *
   * \param file the destination file path.
   *
   * \return `success` if the surface was successfully saved; `failure` otherwise.
   */
  auto save_as_bmp(const char* file) const noexcept -> result
  {
    assert(file);
    return SDL_SaveBMP(get(), file) != -1;
  }

  /// \copydoc save_as_bmp()
  auto save_as_bmp(const std::string& file) const noexcept -> result
  {
    return save_as_bmp(file.c_str());
  }

#ifndef CENTURION_NO_SDL_IMAGE

  /**
   * \brief Exports the surface as a PNG image.
   *
   * \param file the destination file path.
   *
   * \return `success` if the surface was successfully saved; `failure` otherwise.
   */
  auto save_as_png(const char* file) const noexcept -> result
  {
    assert(file);
    return IMG_SavePNG(get(), file) != -1;
  }

  /// \copydoc save_as_png()
  auto save_as_png(const std::string& file) const noexcept -> result
  {
    return save_as_png(file.c_str());
  }

  /**
   * \brief Exports the surface as a JPEG image.
   *
   * \param file the destination file path.
   * \param quality the quality hint, passed on to libjpeg by SDL.
   *
   * \return `success` if the surface was successfully saved; `failure` otherwise.
   */
  auto save_as_jpg(const char* file, const int quality) const noexcept -> result
  {
    assert(file);
    return IMG_SaveJPG(get(), file, quality) != -1;
  }

  /// \copydoc save_as_jpg()
  auto save_as_jpg(const std::string& file, const int quality) const noexcept -> result
  {
    return save_as_jpg(file.c_str(), quality);
  }

#endif  // CENTURION_NO_SDL_IMAGE

  /// \} End of export functions

  /// \name Conversion functions
  /// \{

  /**
   * \brief Creates a copy of the surface that uses another pixel format.
   *
   * \param format the pixel format used by the copy.
   *
   * \return the copy of the surface.
   */
  [[nodiscard]] auto convert_to(const pixel_format format) const -> surface
  {
    if (auto* converted = SDL_ConvertSurfaceFormat(mSurface, to_underlying(format), 0)) {
      surface result{converted};
      result.set_blend_mode(get_blend_mode());
      return result;
    }
    else {
      throw sdl_error{};
    }
  }

  /// \} End of conversion functions

  /// \name Pixel access functions
  /// \{

  /**
   * \brief Attempts to lock the surface, so that the associated pixel data can be modified.
   *
   * \details This function has no effect if `must_lock()` returns `false`.
   *
   * \return `success` if the locking of the surface was successful or if locking isn't
   * required for modifying the surface; `failure` if something went wrong.
   *
   * \see `unlock()`
   * \see `must_lock()`
   */
  auto lock() noexcept -> result
  {
    if (must_lock()) {
      return SDL_LockSurface(mSurface) == 0;
    }
    else {
      return true;
    }
  }

  /**
   * \brief Unlocks the surface.
   *
   * \details This function has no effect if `must_lock()` returns `false`.
   *
   * \see `lock()`
   * \see `must_lock()`
   */
  void unlock() noexcept
  {
    if (must_lock()) {
      SDL_UnlockSurface(mSurface);
    }
  }

  /**
   * \brief Indicates whether the surface must be locked before modification of the pixel data.
   *
   * \return `true` if the surface must be locked before modification; `false` otherwise.
   */
  [[nodiscard]] auto must_lock() const noexcept -> bool { return SDL_MUSTLOCK(mSurface); }

  /**
   * \brief Returns a pointer to the surface pixel data.
   *
   * \details It is possible to modify the surface through the returned pointer.
   *
   * \return a pointer to the pixel data.
   */
  [[nodiscard]] auto pixel_data() noexcept -> void* { return mSurface->pixels; }

  /**
   * \brief Returns a pointer to the surface pixel data.
   *
   * \return a pointer to the pixel data.
   */
  [[nodiscard]] auto pixel_data() const noexcept -> const void* { return mSurface->pixels; }

  /// \} End of pixel access functions

  /// \name Setters
  /// \{

  /**
   * \brief Sets the alpha component modulation of the surface.
   *
   * \param alpha the new alpha modulation, in the range [0, 255].
   */
  void set_alpha_mod(const uint8 alpha) noexcept { SDL_SetSurfaceAlphaMod(mSurface, alpha); }

  /**
   * \brief Sets the color modulation of the surface.
   *
   * \note The alpha component of the color is ignored, see `set_alpha_mod()`.
   *
   * \param color the new color modulation.
   */
  void set_color_mod(const color& color) noexcept
  {
    SDL_SetSurfaceColorMod(mSurface, color.red(), color.green(), color.blue());
  }

  /**
   * \brief Sets the blend mode of the surface.
   *
   * \param mode the new blend mode.
   */
  void set_blend_mode(const blend_mode mode) noexcept
  {
    SDL_SetSurfaceBlendMode(mSurface, static_cast<SDL_BlendMode>(mode));
  }

  /**
   * \brief Sets the value of the RLE acceleration hint.
   *
   * \param enabled `true` if the RLE optimization hint should be enabled; `false` otherwise.
   *
   * \return `success` if the hint was successfully set; `failure` otherwise.
   */
  auto set_rle(const bool enabled) noexcept -> result
  {
    return SDL_SetSurfaceRLE(mSurface, enabled ? 1 : 0) == 0;
  }

  /// \} End of setters

  /// \name Getters
  /// \{

  /**
   * \brief Returns the alpha component modulation of the surface.
   *
   * \return the surface alpha modulation, in the range [0, 255].
   */
  [[nodiscard]] auto alpha() const noexcept -> uint8
  {
    uint8 alpha{0xFF};
    SDL_GetSurfaceAlphaMod(mSurface, &alpha);
    return alpha;
  }

  /**
   * \brief Returns the color modulation of the surface.
   *
   * \return the surface color modulation.
   */
  [[nodiscard]] auto color_mod() const noexcept -> color
  {
    uint8 red{};
    uint8 green{};
    uint8 blue{};
    if (SDL_GetSurfaceColorMod(mSurface, &red, &green, &blue) == 0) {
      return {red, green, blue};
    }
    else {
      return colors::white;
    }
  }

  /**
   * \brief Returns the blend mode that is being used by the surface.
   *
   * \return the surface blend mode.
   */
  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetSurfaceBlendMode(mSurface, &mode);
    return static_cast<blend_mode>(mode);
  }

  /**
   * \brief Returns the width of the surface.
   *
   * \return the surface width.
   */
  [[nodiscard]] auto width() const noexcept -> int { return mSurface->w; }

  /**
   * \brief Returns the height of the surface.
   *
   * \return the surface height.
   */
  [[nodiscard]] auto height() const noexcept -> int { return mSurface->h; }

  /**
   * \brief Returns the size of the surface.
   *
   * \return the surface size.
   */
  [[nodiscard]] auto size() const noexcept -> iarea { return {width(), height()}; }

  /**
   * \brief Returns the pitch, i.e. the size of a row of pixels in bytes, of the surface.
   *
   * \return the surface pitch.
   */
  [[nodiscard]] auto pitch() const noexcept -> int { return mSurface->pitch; }

  /**
   * \brief Returns information about the surface pixel format.
   *
   * \return the surface pixel format info.
   */
  [[nodiscard]] auto format_info() const noexcept -> pixel_format_info_handle
  {
    return pixel_format_info_handle{mSurface->format};
  }

  /**
   * \brief Returns the surface clipping information.
   *
   * \return the surface clipping information.
   */
  [[nodiscard]] auto clip() const noexcept -> irect { return irect{mSurface->clip_rect}; }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Indicates whether the surface is RLE-enabled.
   *
   * \return `true` if the surface is RLE-enabled; `false` otherwise.
   *
   * \atleastsdl 2.0.14
   */
  [[nodiscard]] auto has_rle() const noexcept -> bool
  {
    return SDL_HasSurfaceRLE(mSurface) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// \} End of getters

  /// \name Misc functions
  /// \{

  /**
   * \brief Indicates whether a handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mSurface != nullptr;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Surface* { return mSurface.get(); }

  /// \} End of misc functions

 private:
  detail::pointer<T, SDL_Surface> mSurface;

  void copy(const basic_surface& other) { mSurface.reset(other.duplicate_surface()); }

  [[nodiscard]] auto duplicate_surface() const -> owner<SDL_Surface*>
  {
    if (auto* copy = SDL_DuplicateSurface(mSurface)) {
      return copy;
    }
    else {
      throw sdl_error{};
    }
  }

#ifdef CENTURION_MOCK_FRIENDLY_MODE

 public:
  basic_surface() = default;

#endif  // CENTURION_MOCK_FRIENDLY_MODE
};

/// \name Surface functions
/// \{

template <typename T>
[[nodiscard]] auto to_string(const basic_surface<T>& surface) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("surface(data: {}, width: {}, height: {})",
                     detail::address_of(surface.get()),
                     surface.width(),
                     surface.height());
#else
  return "surface(data: " + detail::address_of(surface.get()) +
         ", width: " + std::to_string(surface.width()) +
         ", height: " + std::to_string(surface.height()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_surface<T>& surface) -> std::ostream&
{
  return stream << to_string(surface);
}

/// \} End of surface functions

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_SURFACE_HPP_
