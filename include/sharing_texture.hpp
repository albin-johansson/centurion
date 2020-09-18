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
 * @file sharing_texture.hpp
 *
 * @brief Provides the `sharing_texture` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_SHARING_TEXTURE_HEADER
#define CENTURION_SHARING_TEXTURE_HEADER

#include <memory>

#include "basic_texture.hpp"
#include "centurion_api.hpp"
#include "centurion_fwd.hpp"
#include "exception.hpp"
#include "surface.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURUION_USE_PRAGMA_ONCE

namespace cen {

class sharing_texture;

template <>
class texture_traits<sharing_texture> final
{
 public:
  using storage_type = std::shared_ptr<SDL_Texture>;
};

/**
 * @class sharing_texture
 *
 * @brief Represents a hardware-accelerated texture with implicit sharing
 * semantics.
 *
 * @details This class uses a shared pointer as the internal representation,
 * which means that instances of this class are both movable and copyable,
 * unlike `texture`. The implicit sharing semantics means that copies are
 * *shallow*, and changes made to a copy will affect the original, as they
 * share resources.
 *
 * @since 5.0.0
 *
 * @see `basic_texture`
 * @see `texture`
 *
 * @headerfile sharing_texture.hpp
 */
class sharing_texture final : public basic_texture<sharing_texture>
{
 public:
  /**
   * @brief Creates a sharing texture from a pre-existing SDL texture.
   *
   * @note The created texture will claim ownership of the supplied pointer.
   *
   * @param sdlTexture a pointer to the SDL_Texture that will be claimed, can't
   * be null.
   *
   * @throws exception if the supplied pointer is null.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit sharing_texture(owner<SDL_Texture*> sdlTexture);

  /**
   * @brief Creates a sharing texture from an ordinary texture.
   *
   * @details The created sharing texture will steal the SDL texture from the
   * supplied `texture` instance.
   *
   * @param texture the `texture` instance that provides the SDL texture that
   * will be claimed.
   *
   * @since 5.0.0
   */
  CENTURION_API
  explicit sharing_texture(texture&& texture) noexcept;

  /**
   * @brief Creates a sharing texture based the image at the specified path.
   *
   * @tparam Renderer the type of the renderer, e.g. `renderer` or
   * `renderer_handle`.
   *
   * @param renderer the renderer that will be used to create the texture.
   * @param path the file path of the texture, can't be null.
   *
   * @throws img_error if the texture cannot be loaded.
   *
   * @since 5.0.0
   */
  template <typename Renderer>
  sharing_texture(const Renderer& renderer, nn_czstring path);

  /**
   * @brief Creates a sharing texture that is a copy of the supplied surface.
   *
   * @tparam Renderer the type of the renderer, e.g. `renderer` or
   * `renderer_handle`.
   *
   * @param renderer the renderer that will be used to create the texture.
   * @param surface the surface that the texture will be based on.
   *
   * @throws sdl_error if the texture cannot be loaded.
   *
   * @since 5.0.0
   */
  template <typename Renderer>
  sharing_texture(const Renderer& renderer, const surface& surface);

  /**
   * @brief Creates a sharing texture with the specified characteristics.
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
   * @since 5.0.0
   */
  template <typename Renderer>
  sharing_texture(const Renderer& renderer,
                  pixel_format format,
                  texture_access access,
                  const iarea& size);

 private:
  [[nodiscard]] constexpr static auto get_deleter() noexcept
  {
    return [](SDL_Texture* texture) noexcept { SDL_DestroyTexture(texture); };
  }
};

template <typename Renderer>
sharing_texture::sharing_texture(const Renderer& renderer, nn_czstring path)
    : basic_texture{IMG_LoadTexture(renderer.get(), path), get_deleter()}
{
  if (!get()) {
    throw img_error{"Failed to load sharing_texture from file"};
  }
}

template <typename Renderer>
sharing_texture::sharing_texture(const Renderer& renderer,
                                 const surface& surface)
    : basic_texture{SDL_CreateTextureFromSurface(renderer.get(), surface.get()),
                    get_deleter()}
{
  if (!get()) {
    throw sdl_error{"Failed to create sharing_texture from surface"};
  }
}

template <typename Renderer>
sharing_texture::sharing_texture(const Renderer& renderer,
                                 pixel_format format,
                                 texture_access access,
                                 const iarea& size)
    : basic_texture{SDL_CreateTexture(renderer.get(),
                                      static_cast<u32>(format),
                                      static_cast<int>(access),
                                      size.width,
                                      size.height),
                    get_deleter()}
{
  if (!get()) {
    throw sdl_error{"Failed to create sharing_texture"};
  }
}

}  // namespace cen

#endif  // CENTURION_SHARING_TEXTURE_HEADER
