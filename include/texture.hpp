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
#include <ostream>
#include <string>
#include <type_traits>

#include "area.hpp"
#include "basic_texture.hpp"
#include "blend_mode.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "color.hpp"
#include "pixel_format.hpp"
#include "point.hpp"
#include "types.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

class texture;

template <>
class texture_traits<texture> final
{
 private:
  class deleter final
  {
   public:
    void operator()(SDL_Texture* texture) noexcept
    {
      SDL_DestroyTexture(texture);
    }
  };

 public:
  using storage_type = std::unique_ptr<SDL_Texture, deleter>;
};

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
class texture final : public basic_texture<texture>
{
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
  explicit texture(nn_owner<SDL_Texture*> sdlTexture) noexcept;

  /**
   * @brief Creates a texture based the image at the specified path.
   *
   * @tparam Renderer the type of the renderer, e.g. `renderer` or
   * `renderer_handle`.
   *
   * @param renderer the renderer that will be used to create the texture.
   * @param path the file path of the texture, can't be null.
   *
   * @throws img_error if the texture cannot be loaded.
   *
   * @since 4.0.0
   */
  template <typename Renderer>
  texture(const Renderer& renderer, nn_czstring path);

  /**
   * @brief Creates an texture that is a copy of the supplied surface.
   *
   * @tparam Renderer the type of the renderer, e.g. `renderer` or
   * `renderer_handle`.
   *
   * @param renderer the renderer that will be used to create the texture.
   * @param surface the surface that the texture will be based on.
   *
   * @throws sdl_error if the texture cannot be loaded.
   *
   * @since 4.0.0
   */
  template <typename Renderer>
  texture(const Renderer& renderer, const surface& surface);

  /**
   * @brief Creates an texture with the specified characteristics.
   *
   * @tparam Renderer the type of the renderer, e.g. `renderer` or
   * `renderer_handle`.
   *
   * @param renderer the associated renderer instance.
   * @param format the pixel format of the created texture.
   * @param access the access of the created texture.
   * @param size the size of the texture.
   *
   * @throws sdl_error if the texture cannot be created.
   *
   * @since 4.0.0
   */
  template <typename Renderer>
  texture(const Renderer& renderer,
          pixel_format format,
          texture_access access,
          const iarea& size);

  /**
   * @copydoc texture(nn_owner<SDL_Texture*>)
   */
  CENTURION_QUERY
  static auto unique(nn_owner<SDL_Texture*> sdlTexture) -> uptr;

  /**
   * @copydoc texture(const Renderer&, nn_czstring)
   */
  template <typename Renderer>
  [[nodiscard]] static auto unique(const Renderer& renderer, nn_czstring path)
      -> uptr;

  /**
   * @copydoc texture(const Renderer&, const surface&)
   */
  template <typename Renderer>
  [[nodiscard]] static auto unique(const Renderer& renderer,
                                   const surface& surface) -> uptr;

  // clang-format off
  /**
   * @copydoc texture(const Renderer&, pixel_format, texture_access, const iarea&)
   */
  template <typename Renderer>
  [[nodiscard]] static auto unique(const Renderer& renderer,
                                   pixel_format format,
                                   texture_access access,
                                   const iarea& size) -> uptr;

  // clang-format on

  /**
   * @copydoc texture(nn_owner<SDL_Texture*>)
   */
  CENTURION_QUERY
  static auto shared(nn_owner<SDL_Texture*> sdlTexture) -> sptr;

  /**
   * @copydoc texture(const Renderer&, nn_czstring)
   */
  template <typename Renderer>
  [[nodiscard]] static auto shared(const Renderer& renderer, nn_czstring path)
      -> sptr;

  /**
   * @copydoc texture(const Renderer&, const surface&)
   */
  template <typename Renderer>
  [[nodiscard]] static auto shared(const Renderer& renderer,
                                   const surface& surface) -> sptr;

  // clang-format off
  /**
   * @copydoc texture(const Renderer&, pixel_format, texture_access, const iarea&)
   */
  template <typename Renderer>
  [[nodiscard]] static auto shared(const Renderer& renderer,
                                   pixel_format format,
                                   texture_access access,
                                   const iarea& size) -> sptr;
  // clang-format on

  /**
   * @brief Creates and returns a unique pointer to a texture.
   *
   * @details The create texture is based on the image at the specified path
   * with the `streaming` texture access.
   *
   * @tparam Renderer the type of the renderer, e.g. `renderer` or
   * `renderer_handle`.
   *
   * @param renderer the renderer that will be used to create the texture.
   * @param path the path of the image file to base the texture on, can't be
   * null.
   * @param format the pixel format that will be used by the texture.
   *
   * @throws exception if something goes wrong.
   *
   * @return a unique pointer to a texture with `streaming` texture access.
   *
   * @since 4.0.0
   */
  template <typename Renderer>
  [[nodiscard]] static auto streaming(const Renderer& renderer,
                                      nn_czstring path,
                                      pixel_format format) -> uptr;

  /**
   * @brief Releases ownership of the associated SDL texture and returns a
   * pointer to it.
   *
   * @warning Usage of this function should be considered dangerous, since
   * you might run into memory leak issues. You **must** call
   * `SDL_DestroyTexture` on the returned pointer to free the associated
   * memory.
   *
   * @return a pointer to the associated SDL texture.
   *
   * @since 5.0.0
   */
  [[nodiscard]] auto release() noexcept -> owner<SDL_Texture*>;
};

static_assert(std::is_final_v<texture>);
static_assert(std::is_nothrow_move_constructible_v<texture>);
static_assert(std::is_nothrow_move_assignable_v<texture>);
static_assert(!std::is_nothrow_copy_constructible_v<texture>);
static_assert(!std::is_nothrow_copy_assignable_v<texture>);

/**
 * @brief Returns a textual representation of a texture.
 *
 * @ingroup graphics
 *
 * @param texture the texture that will be converted.
 *
 * @return a string that represents the texture.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto to_string(const texture& texture) -> std::string;

/**
 * @brief Prints a textual representation of a texture.
 *
 * @ingroup graphics
 *
 * @param stream the stream that will be used.
 * @param texture
 *
 * @return the used stream.
 *
 * @since 5.0.0
 */
CENTURION_QUERY
auto operator<<(std::ostream& stream, const texture& texture) -> std::ostream&;

}  // namespace centurion

#include "texture.ipp"

#endif  // CENTURION_TEXTURE_HEADER