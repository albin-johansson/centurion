/*
 * MIT License
 *
 * Copyright (c) 2019 Albin Johansson
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

#pragma once
#include <string>
#include <memory>
#include <cstdint>
#include <gsl>
#include <SDL_render.h>
#include "color.h"
#include "blend_mode.h"
#include "centurion_api.h"

namespace centurion {

/**
 * The TextureAccess enum mirrors the SDL_TextureAccess enum.
 *
 * @see SDL_TextureAccess
 * @since 3.0.0
 */
enum class TextureAccess {
  Static = SDL_TEXTUREACCESS_STATIC,
  Streaming = SDL_TEXTUREACCESS_STREAMING,
  Target = SDL_TEXTUREACCESS_TARGET
};

/**
 * Indicates whether or not the two texture access values are the same.
 *
 * @param a the lhs Centurion texture access.
 * @param b the rhs SDL texture access.
 * @return true if the texture access values are the same; false otherwise.
 * @since 3.0.0
 */
[[nodiscard]]
CENTURION_API bool operator==(TextureAccess a, SDL_TextureAccess b) noexcept;

/**
 * Indicates whether or not the two texture access values are the same.
 *
 * @param a the lhs SDL texture access.
 * @param b the rhs Centurion texture access.
 * @return true if the texture access values are the same; false otherwise.
 * @since 3.0.0
 */
[[nodiscard]]
CENTURION_API bool operator==(SDL_TextureAccess a, TextureAccess b) noexcept;

/**
 * Indicates whether or not the two texture access values aren't the same.
 *
 * @param a the lhs Centurion texture access.
 * @param b the rhs SDL texture access.
 * @return true if the texture access values aren't the same; false otherwise.
 * @since 3.0.0
 */
[[nodiscard]]
CENTURION_API bool operator!=(TextureAccess a, SDL_TextureAccess b) noexcept;

/**
 * Indicates whether or not the two texture access values aren't the same.
 *
 * @param a the lhs SDL texture access.
 * @param b the rhs Centurion texture access.
 * @return true if the texture access values aren't the same; false otherwise.
 * @since 3.0.0
 */
[[nodiscard]]
CENTURION_API bool operator!=(SDL_TextureAccess a, TextureAccess b) noexcept;

/**
 * The Image class represents an image that is hardware-accelerated. Instances of the Image class
 * can be implicitly converted to SDL_Texture*.
 *
 * @see SDL_Texture
 * @since 3.0.0
 */
class CENTURION_API Image final {
 private:
  SDL_Texture* texture = nullptr;

 public:
  /**
   * Creates an image from a pre-existing SDL texture. The created image WILL claim ownership of
   * the supplied pointer!
   *
   * @param texture a pointer to the SDL_Texture that will be claimed, may not be null.
   * @throws CenturionException if the supplied pointer is null.
   * @since 3.0.0
   */
  CENTURION_API explicit Image(gsl::owner<SDL_Texture*> texture);

  /**
   * Creates an image by loading it from a file.
   *
   * @param renderer a pointer to the SDL_Renderer used to create the image, must not be null.
   * @param path the file path of the image that will be loaded.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_API Image(gsl::not_null<SDL_Renderer*> renderer, const std::string& path);

  /**
   * Creates an image that is a copy of the supplied SDL surface.
   *
   * @param renderer the associated renderer instance, may not be null.
   * @param surface the SDL surface that the image will be based on, may not be null
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_API Image(gsl::not_null<SDL_Renderer*> renderer, gsl::not_null<SDL_Surface*> surface);

  /**
   * Creates an image with the specified characteristics.
   *
   * @param renderer the associated renderer instance, may not be null.
   * @param format the format of the created image.
   * @param access one of the SDL_TextureAccess values.
   * @param width the width of the created image.
   * @param height the height of the created image.
   * @throws CenturionException if the image cannot be created.
   * @since 3.0.0
   */
  CENTURION_API Image(gsl::not_null<SDL_Renderer*> renderer,
                      uint32_t format,
                      TextureAccess access,
                      int width,
                      int height);

  /**
   * Creates an image by moving the supplied image.
   *
   * @param other the image that will be moved.
   * @since 3.0.0
   */
  CENTURION_API Image(Image&& other) noexcept;

  Image(const Image&) noexcept = delete;

  CENTURION_API ~Image() noexcept;

  Image& operator=(const Image&) noexcept = delete;

  /**
   * Moves the supplied image into this image.
   *
   * @param other the image that will be moved.
   * @return the changed image.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API Image& operator=(Image&& other) noexcept;

  /**
   * Creates and returns a unique image from a pre-existing SDL texture. The created image WILL
   * claim ownership of the supplied pointer!
   *
   * @param texture a pointer to the SDL_Texture that will be claimed, may not be null.
   * @returns a unique pointer to the created image.
   * @throws CenturionException if the supplied pointer is null.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Image> unique(gsl::owner<SDL_Texture*> texture);

  /**
   * Creates and returns a unique image by loading it from a file.
   *
   * @param renderer the renderer that will be used when loading the image.
   * @param path the file path of the image.
   * @return a unique pointer to the created image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Image> unique(gsl::not_null<SDL_Renderer*> renderer,
                                                     const std::string& path);

  /**
   * Creates and returns a unique image that is a copy of the supplied SDL surface.
   *
   * @param renderer the associated renderer instance, may not be null.
   * @param surface the SDL surface that the image will be based on, may not be null
   * @return a unique pointer to the created image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Image> unique(gsl::not_null<SDL_Renderer*> renderer,
                                                     gsl::not_null<SDL_Surface*> surface);

  /**
   * Creates and returns a unique pointer to an image with the specified characteristics.
   *
   * @param renderer the associated renderer instance, may not be null.
   * @param format the format of the created image.
   * @param access one of the SDL_TextureAccess values.
   * @param width the width of the created image.
   * @param height the height of the created image.
   * @return a unique pointer to an image.
   * @throws CenturionException if the image cannot be created.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::unique_ptr<Image> unique(gsl::not_null<SDL_Renderer*> renderer,
                                                     uint32_t format,
                                                     TextureAccess access,
                                                     int width,
                                                     int height);

  /**
   * Creates and returns a shared image from a pre-existing SDL texture. The created image WILL
   * claim ownership of the supplied pointer!
   *
   * @param texture a pointer to the SDL_Texture that will be claimed, may not be null.
   * @returns a shared pointer to the created image.
   * @throws CenturionException if the supplied pointer is null.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Image> shared(gsl::owner<SDL_Texture*> texture);

  /**
   * Creates and returns a shared image by loading it from a file.
   *
   * @param renderer the renderer that will be used when loading the image.
   * @param path the file path of the image.
   * @return a shared pointer to the created image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Image> shared(gsl::not_null<SDL_Renderer*> renderer,
                                                     const std::string& path);

  /**
   * Creates and returns a shared image that is a copy of the supplied SDL surface.
   *
   * @param renderer the associated renderer instance, may not be null.
   * @param surface the SDL surface that the image will be based on, may not be null
   * @return a shared pointer to the created image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Image> shared(gsl::not_null<SDL_Renderer*> renderer,
                                                     gsl::not_null<SDL_Surface*> surface);

  /**
   * Creates and returns a shared pointer to an image with the specified characteristics.
   *
   * @param renderer the associated renderer instance, may not be null.
   * @param format the format of the created image.
   * @param access one of the SDL_TextureAccess values.
   * @param width the width of the created image.
   * @param height the height of the created image.
   * @return a shared pointer to an image.
   * @throws CenturionException if the image cannot be created.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API static std::shared_ptr<Image> shared(gsl::not_null<SDL_Renderer*> renderer,
                                                     uint32_t format,
                                                     TextureAccess access,
                                                     int width,
                                                     int height);

  /**
   * Sets the alpha value of the image.
   *
   * @param alpha the alpha value, in the range [0, 255].
   * @since 3.0.0
   */
  CENTURION_API void set_alpha(uint8_t alpha) noexcept;

  /**
   * Sets the blend mode that will be used by the image.
   *
   * @param mode the blend mode that will be used.
   * @since 3.0.0
   */
  CENTURION_API void set_blend_mode(BlendMode mode) noexcept;

  /**
   * Sets the color modulation of the image. Note, the alpha component in the color struct is
   * ignored by this method.
   *
   * @param color the color that will be used to modulate the color of the image.
   * @since 3.0.0
   */
  CENTURION_API void set_color_mod(Color color) noexcept;

  /**
   * Returns the format of the internal SDL_Texture.
   *
   * @return the format of the internal SDL_Texture.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API uint32_t get_format() const noexcept;

  /**
   * Returns the texture access of the internal SDL_Texture.
   *
   * @return the texture access of the internal SDL_Texture.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API TextureAccess get_access() const noexcept;

  /**
   * Returns the width of the image.
   *
   * @return the width of the image.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_width() const noexcept;

  /**
   * Returns the height of the image.
   *
   * @return the height of the image.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API int get_height() const noexcept;

  /**
   * Indicates whether or not the image is a possible render target.
   *
   * @return true if the image is a possible render target; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_target() const noexcept;

  /**
   * Indicates whether or not the image has static texture access.
   *
   * @return true if the image has static texture access.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_static() const noexcept;

  /**
   * Indicates whether or not the image has streaming texture access.
   *
   * @return true if the image has streaming texture access; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API bool is_streaming() const noexcept;

  /**
   * Returns the alpha value of the texture.
   *
   * @return the alpha value of the texture.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API uint8_t get_alpha() const noexcept;

  /**
   * Returns the blend mode of the texture.
   *
   * @return the blend mode of the texture.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API BlendMode get_blend_mode() const noexcept;

  /**
   * Returns the color modulation of the image.
   *
   * @return the modulation of the image.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API Color get_color_mod() const noexcept;

  /**
   * Returns a pointer to the internal SDL_Texture of the image.
   *
   * @return a pointer to the internal SDL_Texture of the image.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API SDL_Texture* get_texture() noexcept;

  /**
   * Returns a string representation of the image.
   *
   * @return a string representation of the image.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::string to_string() const;

  /**
   * Returns a pointer to the internal SDL_Texture.
   *
   * @return a pointer to the internal SDL_Texture.
   * @since 3.0.0
   */
  CENTURION_API /*implicit*/ operator SDL_Texture*() const noexcept;
};

}
