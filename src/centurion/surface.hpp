/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

template <typename T>
class basic_surface;

using surface = basic_surface<detail::owner_tag>;
using surface_handle = basic_surface<detail::handle_tag>;

/**
 * Represents a non-accelerated image.
 *
 * Surfaces are often used for icons and snapshots, or as an intermediate representation that
 * can be manipulated, unlike textures. There is no support for directly rendering surfaces.
 * However, surfaces can be converted to textures, which in turn can be rendered.
 *
 * Note, unlike most other Centurion classes, surfaces may be copied.
 *
 * \see surface
 * \see surface_handle
 */
template <typename T>
class basic_surface final
{
 public:
  /**
   * Creates a surface from an SDL surface.
   *
   * Ownership of the surface is only claimed by owning surfaces!
   *
   * \param surface a pointer to the associated surface.
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

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_surface(const char* file) : mSurface{IMG_Load(file)}
  {
    if (!mSurface) {
      throw img_error{};
    }
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_surface(const std::string& file) : basic_surface{file.c_str()}
  {}

#endif  // CENTURION_NO_SDL_IMAGE

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

#ifndef CENTURION_NO_SDL_IMAGE

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

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto with_format(const std::string& file,
                                        const blend_mode mode,
                                        const pixel_format format) -> surface
  {
    return with_format(file.c_str(), mode, format);
  }

#endif  // CENTURION_NO_SDL_IMAGE

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto from_bmp(const char* file) -> surface
  {
    assert(file);
    return surface{SDL_LoadBMP(file)};
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] static auto from_bmp(const std::string& file) -> surface
  {
    return from_bmp(file.c_str());
  }

  auto save_as_bmp(const char* file) const noexcept -> result
  {
    assert(file);
    return SDL_SaveBMP(get(), file) != -1;
  }

  auto save_as_bmp(const std::string& file) const noexcept -> result
  {
    return save_as_bmp(file.c_str());
  }

#ifndef CENTURION_NO_SDL_IMAGE

  auto save_as_png(const char* file) const noexcept -> result
  {
    assert(file);
    return IMG_SavePNG(get(), file) != -1;
  }

  auto save_as_png(const std::string& file) const noexcept -> result
  {
    return save_as_png(file.c_str());
  }

  auto save_as_jpg(const char* file, const int quality) const noexcept -> result
  {
    assert(file);
    return IMG_SaveJPG(get(), file, quality) != -1;
  }

  auto save_as_jpg(const std::string& file, const int quality) const noexcept -> result
  {
    return save_as_jpg(file.c_str(), quality);
  }

#endif  // CENTURION_NO_SDL_IMAGE

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

  /// Attempts to lock the surface, so that the associated pixel data can be modified.
  auto lock() noexcept -> result
  {
    if (must_lock()) {
      return SDL_LockSurface(mSurface) == 0;
    }
    else {
      return success;
    }
  }

  void unlock() noexcept
  {
    if (must_lock()) {
      SDL_UnlockSurface(mSurface);
    }
  }

  [[nodiscard]] auto must_lock() const noexcept -> bool { return SDL_MUSTLOCK(mSurface); }

  [[nodiscard]] auto pixel_data() noexcept -> void* { return mSurface->pixels; }
  [[nodiscard]] auto pixel_data() const noexcept -> const void* { return mSurface->pixels; }

  void set_alpha_mod(const uint8 alpha) noexcept { SDL_SetSurfaceAlphaMod(mSurface, alpha); }

  void set_color_mod(const color& color) noexcept
  {
    SDL_SetSurfaceColorMod(mSurface, color.red(), color.green(), color.blue());
  }

  void set_blend_mode(const blend_mode mode) noexcept
  {
    SDL_SetSurfaceBlendMode(mSurface, static_cast<SDL_BlendMode>(mode));
  }

  auto set_rle(const bool enabled) noexcept -> result
  {
    return SDL_SetSurfaceRLE(mSurface, enabled ? 1 : 0) == 0;
  }

  [[nodiscard]] auto alpha() const noexcept -> uint8
  {
    uint8 alpha{0xFF};
    SDL_GetSurfaceAlphaMod(mSurface, &alpha);
    return alpha;
  }

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

  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetSurfaceBlendMode(mSurface, &mode);
    return static_cast<blend_mode>(mode);
  }

  [[nodiscard]] auto width() const noexcept -> int { return mSurface->w; }

  [[nodiscard]] auto height() const noexcept -> int { return mSurface->h; }

  [[nodiscard]] auto size() const noexcept -> iarea { return {width(), height()}; }

  /// Returns the size of a row of pixels in bytes.
  [[nodiscard]] auto pitch() const noexcept -> int { return mSurface->pitch; }

  [[nodiscard]] auto format_info() const noexcept -> pixel_format_info_handle
  {
    return pixel_format_info_handle{mSurface->format};
  }

  [[nodiscard]] auto clip() const noexcept -> irect { return irect{mSurface->clip_rect}; }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto has_rle() const noexcept -> bool
  {
    return SDL_HasSurfaceRLE(mSurface) == SDL_TRUE;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /// Indicates whether the handle holds a non-null pointer.
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mSurface != nullptr;
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Surface* { return mSurface.get(); }

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

}  // namespace cen

#endif  // CENTURION_SURFACE_HPP_
