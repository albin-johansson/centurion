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
 * @file texture.hpp
 *
 * @brief Provides the `texture` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_TEXTURE_HEADER
#define CENTURION_TEXTURE_HEADER

#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_video.h>

#include <memory>

#include "area.hpp"
#include "blend_mode.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "centurion_types.hpp"
#include "pixel_format.hpp"
#include "point.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/// @cond FALSE

namespace detail {

class texture_deleter final {
 public:
  void operator()(SDL_Texture* texture) noexcept
  {
    if (texture) {
      SDL_DestroyTexture(texture);
    }
  }
};

}  // namespace detail

/// @endcond

/**
 * @class texture
 *
 * @ingroup graphics
 *
 * @brief Represents an hardware-accelerated image.
 *
 * @since 3.0.0
 *
 * @see `SDL_Texture`
 *
 * @headerfile texture.hpp
 */
class texture final {
 public:
  /**
   * @typedef uptr
   *
   * @brief Simple alias for a unique pointer to a texture.
   *
   * @since 5.0.0
   */
  using uptr = std::unique_ptr<texture>;

  /**
   * @typedef sptr
   *
   * @brief Simple alias for a shared pointer to a texture.
   *
   * @since 5.0.0
   */
  using sptr = std::shared_ptr<texture>;

  /**
   * @typedef wptr
   *
   * @brief Simple alias for a weak pointer to a texture.
   *
   * @since 5.0.0
   */
  using wptr = std::weak_ptr<texture>;

  /**
   * @enum access
   *
   * @brief Mirrors the `SDL_TextureAccess` enum.
   *
   * @note The `no_lock` enumerator is also referred to as "static" texture
   * access.
   *
   * @since 3.0.0
   *
   * @see `SDL_TextureAccess`
   *
   * @headerfile graphics.hpp
   */
  enum class access {
    no_lock = SDL_TEXTUREACCESS_STATIC, /**< Indicates that the texture changes
                                          rarely, and isn't lockable. */
    streaming =
        SDL_TEXTUREACCESS_STREAMING, /**< Indicates that the texture
                                      * changes frequently, and is lockable. */

    target = SDL_TEXTUREACCESS_TARGET /**< Indicates that the texture can be
                                       * used as a render target. */
  };

  /**
   * @enum scale_mode
   *
   * @brief Mirrors the `SDL_ScaleMode` enum.
   *
   * @since 4.0.0
   *
   * @see `SDL_ScaleMode`
   *
   * @headerfile graphics.hpp
   */
  enum class scale_mode {
    nearest = SDL_ScaleModeNearest,  ///< Represents nearest pixel sampling.
    linear = SDL_ScaleModeLinear,    ///< Represents linear filtering.
    best = SDL_ScaleModeBest         ///< Represents anisotropic filtering.
  };

  /**
   * @brief Creates an texture from a pre-existing SDL texture.
   *
   * @pre `sdlTexture` mustn't be null.
   *
   * @note The created texture will claim ownership of the supplied pointer.
   *
   * @param sdlTexture a pointer to the SDL_Texture that will be claimed, can't
   * be null.
   *
   * @since 3.0.0
   */
  CENTURION_API
  explicit texture(nn_owner<SDL_Texture*> sdlTexture);

  /**
   * @brief Creates a texture based the image at the specified path.
   *
   * @param renderer the renderer that will be used to create the texture.
   * @param path the file path of the texture, can't be null.
   *
   * @throws centurion_exception if the texture cannot be loaded.
   *
   * @since 4.0.0
   */
  CENTURION_API
  texture(const renderer& renderer, nn_czstring path);

  /**
   * @brief Creates an texture that is a copy of the supplied surface.
   *
   * @param renderer the renderer that will be used to create the texture.
   * @param surface the surface that the texture will be based on.
   *
   * @throws centurion_exception if the texture cannot be loaded.
   *
   * @since 4.0.0
   */
  CENTURION_API
  texture(const renderer& renderer, const surface& surface);

  /**
   * @brief Creates an texture with the specified characteristics.
   *
   * @param renderer the associated renderer instance.
   * @param format the pixel format of the created texture.
   * @param access the access of the created texture.
   * @param size the size of the texture.
   *
   * @throws centurion_exception if the texture cannot be created.
   *
   * @since 4.0.0
   */
  CENTURION_API
  texture(const renderer& renderer,
          pixel_format format,
          access access,
          const area_i& size);

  /**
   * @copydoc texture(nn_owner<SDL_Texture*>)
   */
  CENTURION_QUERY
  static auto unique(nn_owner<SDL_Texture*> sdlTexture) -> uptr;

  /**
   * @copydoc texture(const renderer&, nn_czstring)
   */
  CENTURION_QUERY
  static auto unique(const renderer& renderer, nn_czstring path) -> uptr;

  /**
   * @copydoc texture(const renderer&, const surface&)
   */
  CENTURION_QUERY
  static auto unique(const renderer& renderer, const surface& surface) -> uptr;

  /**
   * @copydoc texture(const renderer&, pixel_format, access, const area_i&)
   */
  CENTURION_QUERY
  static auto unique(const renderer& renderer,
                     pixel_format format,
                     access access,
                     const area_i& size) -> uptr;

  /**
   * @copydoc texture(nn_owner<SDL_Texture*>)
   */
  CENTURION_QUERY
  static auto shared(nn_owner<SDL_Texture*> sdlTexture) -> sptr;

  /**
   * @copydoc texture(const renderer&, nn_czstring)
   */
  CENTURION_QUERY
  static auto shared(const renderer& renderer, nn_czstring path) -> sptr;

  /**
   * @copydoc texture(const renderer&, const surface&)
   */
  CENTURION_QUERY
  static auto shared(const renderer& renderer, const surface& surface) -> sptr;

  /**
   * @copydoc texture(const renderer&, pixel_format, access, const area_i&)
   */
  CENTURION_QUERY
  static auto shared(const renderer& renderer,
                     pixel_format format,
                     access access,
                     const area_i& size) -> sptr;

  /**
   * @brief Creates and returns a unique pointer to a texture.
   *
   * @details The create texture is based on the image at the specified path
   * with the `streaming` texture access.
   *
   * @param renderer the renderer that will be used to create the texture.
   * @param path the path of the image file to base the texture on, can't be
   * null.
   * @param format the pixel format that will be used by the texture.
   *
   * @throws centurion_exception if something goes wrong.
   *
   * @return a unique pointer to a texture with `streaming` texture access.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  static auto streaming(const renderer& renderer,
                        nn_czstring path,
                        pixel_format format) -> uptr;

  /**
   * @brief Sets the color of the pixel at the specified coordinate.
   *
   * @details This method has no effect if the texture access isn't
   * `Streaming` or if the coordinate is out-of-bounds.
   *
   * @param pixel the pixel that will be changed.
   * @param color the new color of the pixel.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_pixel(point_i pixel, const color& color) noexcept;

  /**
   * @brief Sets the alpha value of the texture.
   *
   * @param alpha the alpha value, in the range [0, 255].
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_alpha(u8 alpha) noexcept;

  /**
   * @brief Sets the blend mode that will be used by the texture.
   *
   * @param mode the blend mode that will be used.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_blend_mode(blend_mode mode) noexcept;

  /**
   * @brief Sets the color modulation of the texture.
   *
   * @note The alpha component in the color struct is ignored by this method.
   *
   * @param color the color that will be used to modulate the color of the
   * texture.
   *
   * @since 3.0.0
   */
  CENTURION_API
  void set_color_mod(color color) noexcept;

  /**
   * @brief Sets the scale mode that will be used by the texture.
   *
   * @param mode the scale mode that will be used.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void set_scale_mode(scale_mode mode) noexcept;

  /**
   * @brief Returns the pixel format that is used by the texture.
   *
   * @return the pixel format that is used by the texture.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto format() const noexcept -> pixel_format;

  /**
   * @brief Returns the texture access of the texture.
   *
   * @return the texture access of the texture.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto get_access() const noexcept -> access;

  /**
   * @brief Returns the width of the texture.
   *
   * @return the width of the texture.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto width() const noexcept -> int;

  /**
   * @brief Returns the height of the texture.
   *
   * @return the height of the texture.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto height() const noexcept -> int;

  /**
   * @brief Returns the size of the texture.
   *
   * @return the size of the texture.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto size() const noexcept -> area_i;

  /**
   * @brief Indicates whether or not the texture is a possible render target.
   *
   * @return `true` if the texture is a possible render target; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto is_target() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the texture has static texture access.
   *
   * @return `true` if the texture has static texture access.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto is_static() const noexcept -> bool;

  /**
   * @brief Indicates whether or not the texture has streaming texture access.
   *
   * @return `true` if the texture has streaming texture access; `false`
   * otherwise.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto is_streaming() const noexcept -> bool;

  /**
   * @brief Returns the alpha value of the texture.
   *
   * @return the alpha value of the texture.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto alpha() const noexcept -> u8;

  /**
   * @brief Returns the blend mode of the texture.
   *
   * @return the blend mode of the texture.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto get_blend_mode() const noexcept -> blend_mode;

  /**
   * @brief Returns the color modulation of the texture.
   *
   * @return the modulation of the texture.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto color_mod() const noexcept -> color;

  /**
   * @brief Returns the scale mode that is used by the texture.
   *
   * @return the scale mode that is used by the texture.
   *
   * @since 4.0.0
   */
  CENTURION_QUERY
  auto get_scale_mode() const noexcept -> scale_mode;

  /**
   * @brief Returns a string representation of the texture.
   *
   * @return a string representation of the texture.
   *
   * @since 3.0.0
   */
  CENTURION_QUERY
  auto to_string() const -> std::string;

  /**
   * @brief Returns a pointer to the associated `SDL_Texture`.
   *
   * @warning Use of this method is not recommended, since it purposefully
   * breaks const-correctness. However it's useful since many SDL calls use
   * non-const pointers even when no change will be applied.
   *
   * @return a pointer to the associated `SDL_Texture`.
   *
   * @since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Texture*
  {
    return m_texture.get();
  }

  /**
   * @brief Converts to `SDL_Texture*`.
   *
   * @return a pointer to the associated `SDL_Texture`.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Texture*() noexcept
  {
    return m_texture.get();
  }

  /**
   * @brief Converts to `const SDL_Texture*`.
   *
   * @return a pointer to the associated `SDL_Texture`.
   *
   * @since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Texture*() const noexcept
  {
    return m_texture.get();
  }

 private:
  std::unique_ptr<SDL_Texture, detail::texture_deleter> m_texture;

  /**
   * @brief Locks the texture for write-only pixel access.
   *
   * @remarks This method is only applicable if the texture access of the
   * texture is `Streaming`.
   *
   * @param pixels this will be filled with a pointer to the locked pixels.
   * @param pitch This is filled in with the pitch of the locked pixels, can
   * safely be null if it isn't needed.
   *
   * @return `true` if all went well; `false` otherwise.
   *
   * @since 4.0.0
   */
  CENTURION_API
  auto lock(u32** pixels, int* pitch = nullptr) noexcept -> bool;

  /**
   * @brief Unlocks the texture.
   *
   * @since 4.0.0
   */
  CENTURION_API
  void unlock() noexcept;
};

static_assert(std::is_final_v<texture>);
static_assert(std::is_nothrow_move_constructible_v<texture>);
static_assert(std::is_nothrow_move_assignable_v<texture>);
static_assert(!std::is_nothrow_copy_constructible_v<texture>);
static_assert(!std::is_nothrow_copy_assignable_v<texture>);

/**
 * @brief Indicates whether or not the two texture access values are the same.
 *
 * @ingroup graphics
 *
 * @param lhs the lhs texture access value.
 * @param rhs the rhs texture access value.
 *
 * @return `true` if the texture access values are the same; `false` otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator==(enum texture::access lhs,
                                               SDL_TextureAccess rhs) noexcept
    -> bool
{
  return static_cast<SDL_TextureAccess>(lhs) == rhs;
}

/**
 * @copydoc operator==(texture::access, SDL_TextureAccess)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator==(
    SDL_TextureAccess lhs,
    enum texture::access rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not the two texture access values aren't the
 * same.
 *
 * @ingroup graphics
 *
 * @param lhs the lhs texture access value.
 * @param rhs the rhs texture access value.
 *
 * @return `true` if the texture access values aren't the same; `false`
 * otherwise.
 *
 * @since 3.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(enum texture::access lhs,
                                               SDL_TextureAccess rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(texture::access, SDL_TextureAccess)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator!=(
    SDL_TextureAccess lhs,
    enum texture::access rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/**
 * @brief Indicates whether or not the two scale mode values are the same.
 *
 * @ingroup graphics
 *
 * @param lhs the lhs scale mode value.
 * @param rhs the rhs scale mode value.
 *
 * @return `true` if the scale mode values are the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator==(enum texture::scale_mode lhs,
                                               SDL_ScaleMode rhs) noexcept
    -> bool
{
  return static_cast<SDL_ScaleMode>(lhs) == rhs;
}

/**
 * @copydoc operator==(texture::scale_mode, SDL_ScaleMode)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator==(
    SDL_ScaleMode lhs,
    enum texture::scale_mode rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * @brief Indicates whether or not the two scale mode values aren't the same.
 *
 * @ingroup graphics
 *
 * @param lhs the lhs scale mode value.
 * @param rhs the rhs scale mode value.
 *
 * @return `true` if the scale mode values aren't the same; `false` otherwise.
 *
 * @since 4.0.0
 */
[[nodiscard]] inline constexpr auto operator!=(enum texture::scale_mode lhs,
                                               SDL_ScaleMode rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/**
 * @copydoc operator!=(texture::scale_mode, SDL_ScaleMode)
 *
 * @ingroup graphics
 */
[[nodiscard]] inline constexpr auto operator!=(
    SDL_ScaleMode lhs,
    enum texture::scale_mode rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

}  // namespace centurion

#endif  // CENTURION_TEXTURE_HEADER