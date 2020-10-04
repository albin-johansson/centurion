/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * @file surface.hpp
 *
 * @brief Provides the `surface` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_SURFACE_HEADER
#define CENTURION_SURFACE_HEADER

#include <SDL.h>
#include <SDL_image.h>

#include <memory>       // unique_ptr
#include <ostream>      // ostream
#include <string>       // string
#include <type_traits>  // enable_if_t, true_type, false_type, conditional_t

#include "blend_mode.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "color.hpp"
#include "detail/to_string.hpp"
#include "detail/utils.hpp"
#include "exception.hpp"
#include "pixel_format.hpp"
#include "rect.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

template <typename T>
using is_surface_owning =
    std::enable_if_t<std::is_same_v<T, std::true_type>, bool>;

template <typename T>
using is_surface_handle =
    std::enable_if_t<std::is_same_v<T, std::false_type>, bool>;

/**
 * @class basic_surface
 *
 * @ingroup graphics
 *
 * @brief Represents a non-accelerated image.
 *
 * @tparam T `std::true_type` for owning surfaces; `std::false_type` for
 * non-owning surfaces.
 *
 * @since 4.0.0
 *
 * @headerfile surface.hpp
 */
template <typename T>
class basic_surface final
{
  [[nodiscard]] constexpr static auto is_owning() noexcept -> bool
  {
    return std::is_same_v<T, std::true_type>;
  }

 public:
  /**
   * @brief Creates a surface from a pointer to an SDL surface.
   *
   * @note Depending on the type of the surface, ownership of the supplied SDL
   * surface might be claimed.
   *
   * @param surface a pointer to the associated surface.
   *
   * @since 4.0.0
   */
  explicit basic_surface(SDL_Surface* surface) noexcept(!is_owning())
      : m_surface{surface}
  {
    if constexpr (is_owning()) {
      if (!m_surface) {
        throw exception{"Cannot create surface from null pointer!"};
      }
    }
  }

  /**
   * @brief Creates a surface based on the image at the specified path.
   *
   * @param file the file path of the image file that will be loaded, can't
   * be null.
   *
   * @throws img_error if the surface cannot be created.
   *
   * @since 4.0.0
   */
  template <typename T_ = T, is_surface_owning<T_> = true>
  explicit basic_surface(nn_czstring file) : m_surface{IMG_Load(file)}
  {
    if (!m_surface) {
      throw img_error{"Failed to create surface from file"};
    }
  }

  /**
   * @brief Creates a copy of the supplied surface.
   *
   * @param other the surface that will be copied.
   *
   * @since 4.0.0
   */
  basic_surface(const basic_surface& other) noexcept(!is_owning())
  {
    if constexpr (is_owning()) {
      copy(other);
    } else {
      m_surface = other.get();
    }
  }

  /**
   * @brief Creates a surface by moving the supplied surface.
   *
   * @param other the surface that will be moved.
   *
   * @since 4.0.0
   */
  basic_surface(basic_surface&& other) noexcept = default;

  /**
   * @brief Copies the supplied surface.
   *
   * @param other the surface that will be copied.
   *
   * @throws sdl_error if the supplied surface couldn't be copied.
   *
   * @since 4.0.0
   */
  auto operator=(const basic_surface& other) noexcept(!is_owning())
      -> basic_surface&
  {
    if (this != &other) {
      if constexpr (is_owning()) {
        copy(other);
      } else {
        m_surface = other.get();
      }
    }
    return *this;
  }

  /**
   * @brief Moves the supplied surface into this surface.
   *
   * @param other the surface that will be moved.
   *
   * @return the surface that claimed the supplied surface.
   *
   * @since 4.0.0
   */
  auto operator=(basic_surface&& other) noexcept -> basic_surface& = default;

  /**
   * @brief Sets the color of the pixel at the specified coordinate.
   *
   * @details This method has no effect if the coordinate is out-of-bounds or if
   * something goes wrong when attempting to modify the pixel data.
   *
   * @param pixel the pixel that will be changed.
   * @param color the new color of the pixel.
   *
   * @since 4.0.0
   */
  void set_pixel(const ipoint& pixel, const color& color) noexcept
  {
    if (!in_bounds(pixel)) {
      return;
    }

    const auto success = lock();
    if (!success) {
      return;
    }

    const int nPixels = (get()->pitch / 4) * height();
    const int index = (pixel.y() * width()) + pixel.x();

    if ((index >= 0) && (index < nPixels)) {
      const auto value = SDL_MapRGBA(get()->format,
                                     color.red(),
                                     color.green(),
                                     color.blue(),
                                     color.alpha());
      auto* pixels = reinterpret_cast<u32*>(get()->pixels);
      pixels[index] = value;
    }

    unlock();
  }

  /**
   * @brief Sets the alpha component modulation value.
   *
   * @param alpha the new alpha component value, in the range [0, 255].
   *
   * @since 4.0.0
   */
  void set_alpha(u8 alpha) noexcept
  {
    SDL_SetSurfaceAlphaMod(get(), alpha);
  }

  /**
   * @brief Sets the color modulation that will be used by the surface.
   *
   * @param color the color that represents the color modulation that will be
   * used.
   *
   * @since 4.0.0
   */
  void set_color_mod(const color& color) noexcept
  {
    SDL_SetSurfaceColorMod(get(), color.red(), color.green(), color.blue());
  }

  /**
   * @brief Sets the blend mode that will be used by the surface.
   *
   * @param mode the blend mode that will be used.
   *
   * @since 4.0.0
   */
  void set_blend_mode(blend_mode mode) noexcept
  {
    SDL_SetSurfaceBlendMode(get(), static_cast<SDL_BlendMode>(mode));
  }

  /**
   * @brief Returns the alpha component modulation of the surface.
   *
   * @return the alpha modulation value, in the range [0, 255].
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto alpha() const noexcept -> u8
  {
    u8 alpha{0xFF};
    SDL_GetSurfaceAlphaMod(get(), &alpha);
    return alpha;
  }

  /**
   * @brief Returns the color modulation of the surface.
   *
   * @return a color that represents the color modulation of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto color_mod() const noexcept -> color
  {
    u8 red{};
    u8 green{};
    u8 blue{};
    SDL_GetSurfaceColorMod(get(), &red, &green, &blue);
    return color{red, green, blue};
  }

  /**
   * @brief Returns the blend mode that is being used by the surface.
   *
   * @return the blend mode that the surface uses.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get_blend_mode() const noexcept -> blend_mode
  {
    SDL_BlendMode mode{};
    SDL_GetSurfaceBlendMode(get(), &mode);
    return static_cast<blend_mode>(mode);
  }

  /**
   * @brief Creates and returns a surface based on this surface with the
   * specified pixel format.
   *
   * @param format the pixel format that will be used by the new surface.
   *
   * @return a surface based on this surface with the specified
   * pixel format.
   *
   * @throws sdl_error if the surface cannot be created.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto convert(pixel_format format) const -> basic_surface
  {
    const auto pixelFormat = static_cast<u32>(format);
    if (auto* s = SDL_ConvertSurfaceFormat(get(), pixelFormat, 0)) {
      basic_surface converted{s};
      converted.set_blend_mode(get_blend_mode());
      return converted;
    } else {
      throw sdl_error{"Failed to convert surface"};
    }
  }

  /**
   * @brief Returns the width of the surface.
   *
   * @return the width of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return get()->w;
  }

  /**
   * @brief Returns the height of the surface.
   *
   * @return the height of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return get()->h;
  }

  /**
   * @brief Returns the pitch (the length of a row of pixels in bytes) of the
   * surface.
   *
   * @return the pitch of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto pitch() const noexcept -> int
  {
    return get()->pitch;
  }

  /**
   * @brief Returns a pointer to the pixel data of the surface.
   *
   * @details It's possible to modify the surface through the returned pointer.
   *
   * @return a pointer to the pixel data of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto pixels() noexcept -> void*
  {
    return get()->pixels;
  }

  /**
   * @brief Returns a const pointer to the pixel data of the surface.
   *
   * @return a const pointer to the pixel data of the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto pixels() const noexcept -> const void*
  {
    return get()->pixels;
  }

  /**
   * @brief Returns the clipping information associated with the surface.
   *
   * @return the clipping information associated with the surface.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto clip() const noexcept -> irect
  {
    const auto rect = get()->clip_rect;
    return {{rect.x, rect.y}, {rect.w, rect.h}};
  }

  /**
   * @brief Returns a pointer to the associated `SDL_Surface`.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However it is useful since many SDL calls use
   * non-const pointers even when no change will be applied. Don't take
   * ownership of the returned pointer, or bad things will happen.
   *
   * @return a pointer to the associated `SDL_Surface`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Surface*
  {
    if constexpr (is_owning()) {
      return m_surface.get();
    } else {
      return m_surface;
    }
  }

  /**
   * @brief Indicates whether or not a surface handle holds a non-null pointer.
   *
   * @tparam T_ dummy parameter for SFINAE.
   *
   * @return `true` if the surface handle holds a non-null pointer; `false`
   * otherwise.
   *
   * @since 5.0.0
   */
  template <typename T_ = T, is_surface_handle<T_> = true>
  explicit operator bool() const noexcept
  {
    return m_surface != nullptr;
  }

  /**
   * @brief Converts to `SDL_Surface*`.
   *
   * @return a pointer to the associated `SDL_Surface`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator SDL_Surface*() noexcept
  {
    return get();
  }

  /**
   * @brief Converts to `const SDL_Surface*`.
   *
   * @return a pointer to the associated `SDL_Surface`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] explicit operator const SDL_Surface*() const noexcept
  {
    return get();
  }

 private:
  struct deleter final
  {
    void operator()(SDL_Surface* surface) noexcept
    {
      SDL_FreeSurface(surface);
    }
  };

  using rep_t = std::conditional_t<T::value,
                                   std::unique_ptr<SDL_Surface, deleter>,
                                   SDL_Surface*>;
  rep_t m_surface;

  /**
   * @brief Copies the contents of the supplied surface instance into this
   * instance.
   *
   * @param other the instance that will be copied.
   *
   * @throws sdl_error if the surface cannot be copied.
   *
   * @since 4.0.0
   */
  void copy(const basic_surface& other)
  {
    m_surface.reset(other.copy_surface());
  }

  /**
   * @brief Indicates whether or not the supplied point is within the bounds of
   * the surface.
   *
   * @param point the point that will be checked.
   *
   * @return `true` if the point is within the bounds of the surface; `false`
   * otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto in_bounds(const ipoint& point) const noexcept -> bool
  {
    return !(point.x() < 0 || point.y() < 0 || point.x() >= width() ||
             point.y() >= height());
  }

  /**
   * @brief Indicates whether or not the surface must be locked before modifying
   * the pixel data associated with the surface.
   *
   * @return `true` if the surface must be locked before modification; `false`
   * otherwise.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto must_lock() const noexcept -> bool
  {
    return SDL_MUSTLOCK(m_surface);
  }

  /**
   * @brief Attempts to lock the surface, so that the associated pixel data can
   * be modified.
   *
   * @details This method has no effect if `must_lock()` returns `false`.
   *
   * @return `true` if the locking of the surface was successful or if locking
   * isn't required for modifying the surface; `false` if something went wrong.
   *
   * @since 4.0.0
   */
  auto lock() noexcept -> bool
  {
    if (must_lock()) {
      const auto result = SDL_LockSurface(m_surface.get());
      return result == 0;
    } else {
      return true;
    }
  }

  /**
   * @brief Unlocks the surface.
   *
   * @details This method has no effect if `must_lock()` returns `false`.
   *
   * @since 4.0.0
   */
  void unlock() noexcept
  {
    if (must_lock()) {
      SDL_UnlockSurface(m_surface.get());
    }
  }

  /**
   * @brief Creates and returns copy of the associated `SDL_Surface`.
   *
   * @return a copy of the associated `SDL_Surface`, the returned pointer won't
   * be null.
   *
   * @throws sdl_error if the copy couldn't be created.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto copy_surface() const -> owner<SDL_Surface*>
  {
    if (auto* copy = SDL_DuplicateSurface(m_surface.get())) {
      return copy;
    } else {
      throw sdl_error{"Failed to duplicate surface"};
    }
  }
};

/**
 * @typedef surface
 *
 * @brief Represents an owning surface.
 *
 * @since 5.0.0
 */
using surface = basic_surface<std::true_type>;

/**
 * @typedef surface_handle
 *
 * @brief Represents a non-owning surface.
 *
 * @since 5.0.0
 */
using surface_handle = basic_surface<std::false_type>;

/**
 * @brief Returns a textual representation of a surface.
 *
 * @ingroup graphics
 *
 * @param surface the surface that will be converted.
 *
 * @return a textual representation of the surface.
 *
 * @since 5.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_surface<T>& surface) -> std::string
{
  using namespace std::string_literals;
  using detail::to_string;
  return "[surface | ptr: "s + detail::address_of(surface.get()) +
         ", width: "s + to_string(surface.width()).value() + ", height: "s +
         to_string(surface.height()).value() + "]";
}

/**
 * @brief Prints a textual representation of a surface.
 *
 * @ingroup graphics
 *
 * @param stream the stream that will be used.
 * @param surface the surface that will be printed.
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_surface<T>& surface)
    -> std::ostream&
{
  stream << to_string(surface);
  return stream;
}

}  // namespace cen

#endif  // CENTURION_SURFACE_HEADER