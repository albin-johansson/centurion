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

#ifndef CENTURION_TEXTURE_HEADER
#define CENTURION_TEXTURE_HEADER

#include <SDL_render.h>

#include <gsl-lite.hpp>
#include <memory>
#include <string>
#include <type_traits>

#include "blend_mode.h"
#include "centurion_api.h"
#include "color.h"
#include "pixel_format.h"

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
CENTURION_NODISCARD
CENTURION_API bool operator==(TextureAccess a, SDL_TextureAccess b) noexcept;

/**
 * Indicates whether or not the two texture access values are the same.
 *
 * @param a the lhs SDL texture access.
 * @param b the rhs Centurion texture access.
 * @return true if the texture access values are the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_TextureAccess a, TextureAccess b) noexcept;

/**
 * Indicates whether or not the two texture access values aren't the same.
 *
 * @param a the lhs Centurion texture access.
 * @param b the rhs SDL texture access.
 * @return true if the texture access values aren't the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(TextureAccess a, SDL_TextureAccess b) noexcept;

/**
 * Indicates whether or not the two texture access values aren't the same.
 *
 * @param a the lhs SDL texture access.
 * @param b the rhs Centurion texture access.
 * @return true if the texture access values aren't the same; false otherwise.
 * @since 3.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_TextureAccess a, TextureAccess b) noexcept;

class Renderer;
class Surface;

/**
 * The Texture class represents an texture that is hardware-accelerated.
 * Instances of the Texture class can be implicitly converted to SDL_Texture*.
 *
 * @see SDL_Texture
 * @since 3.0.0
 */
class Texture final {
 public:
  /**
   * Creates an texture from a pre-existing SDL texture. The created texture
   * WILL claim ownership of the supplied pointer!
   *
   * @param texture a pointer to the SDL_Texture that will be claimed, may not
   * be null.
   * @throws CenturionException if the supplied pointer is null.
   * @since 3.0.0
   */
  CENTURION_API explicit Texture(gsl::owner<SDL_Texture*> texture);

  /**
   * @param renderer the renderer that will be used to create the texture.
   * @param path the file path of the texture, may not be null.
   * @throws CenturionException if the texture cannot be loaded.
   * @since 4.0.0
   */
  CENTURION_API Texture(const Renderer& renderer, const char* path);

  /**
   * Creates an texture that is a copy of the supplied surface.
   *
   * @param renderer the renderer that will be used to create the texture.
   * @param surface the surface that the texture will be based on.
   * @throws CenturionException if the texture cannot be loaded.
   * @since 4.0.0
   */
  CENTURION_API Texture(const Renderer& renderer, const Surface& surface);

  /**
   * Creates an texture with the specified characteristics.
   *
   * @param renderer the associated renderer instance.
   * @param format the pixel format of the created texture.
   * @param access the texture access of the created texture.
   * @param width the width of the texture.
   * @param height the height of the texture.
   * @throws CenturionException if the texture cannot be created.
   * @since 4.0.0
   */
  CENTURION_API Texture(const Renderer& renderer,
                        PixelFormat format,
                        TextureAccess access,
                        int width,
                        int height);

  /**
   * Creates an texture by moving the supplied texture.
   *
   * @param other the texture that will be moved.
   * @since 3.0.0
   */
  CENTURION_API Texture(Texture&& other) noexcept;

  Texture(const Texture&) noexcept = delete;

  CENTURION_API ~Texture() noexcept;

  Texture& operator=(const Texture&) noexcept = delete;

  /**
   * Moves the supplied texture into this texture.
   *
   * @param other the texture that will be moved.
   * @return the changed texture.
   * @since 3.0.0
   */
  CENTURION_API Texture& operator=(Texture&& other) noexcept;

  /**
   * Creates and returns a unique texture from a pre-existing SDL texture. The
   * created texture WILL claim ownership of the supplied pointer!
   *
   * @param texture a pointer to the SDL_Texture that will be claimed, may not
   * be null.
   * @returns a unique pointer to the created texture.
   * @throws CenturionException if the supplied pointer is null.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::unique_ptr<Texture> unique(gsl::owner<SDL_Texture*> texture);

  /**
   * Creates and returns a unique texture by loading it from a file.
   *
   * @param renderer the renderer that will be used when loading the texture.
   * @param path the file path of the texture, may not be null.
   * @return a unique pointer to the created texture.
   * @throws CenturionException if the texture cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::unique_ptr<Texture> unique(const Renderer& renderer,
                                         const char* path);

  /**
   * Creates and returns a unique texture that is a copy of the supplied
   * surface.
   *
   * @param renderer the associated renderer instance.
   * @param surface the surface that the texture will be based on.
   * @return a unique pointer to the created texture.
   * @throws CenturionException if the texture cannot be loaded.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::unique_ptr<Texture> unique(const Renderer& renderer,
                                         const Surface& surface);

  /**
   * Creates and returns a unique pointer to an texture with the supplied
   * characteristics.
   *
   * @param renderer the associated renderer that will be used.
   * @param format the pixel format of the texture.
   * @param access the texture access of the texture.
   * @param width the width of the texture.
   * @param height the height of the texture.
   * @return a unique pointer to an texture.
   * @throws CenturionException if the texture cannot be created.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::unique_ptr<Texture> unique(const Renderer& renderer,
                                         PixelFormat format,
                                         TextureAccess access,
                                         int width,
                                         int height);

  /**
   * Creates and returns a shared texture from a pre-existing SDL texture. The
   * created texture WILL claim ownership of the supplied pointer!
   *
   * @param texture a pointer to the SDL_Texture that will be claimed, may not
   * be null.
   * @returns a shared pointer to the created texture.
   * @throws CenturionException if the supplied pointer is null.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::shared_ptr<Texture> shared(gsl::owner<SDL_Texture*> texture);

  /**
   * Creates and returns a shared texture by loading it from a file.
   *
   * @param renderer the renderer that will be used when loading the texture.
   * @param path the file path of the texture, may not be null.
   * @return a shared pointer to the created texture.
   * @throws CenturionException if the texture cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::shared_ptr<Texture> shared(const Renderer& renderer,
                                         const char* path);

  /**
   * Creates and returns a shared texture that is a copy of the supplied
   * surface.
   *
   * @param renderer the associated renderer instance.
   * @param surface the surface that the texture will be based on.
   * @return a shared pointer to the created texture.
   * @throws CenturionException if the texture cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::shared_ptr<Texture> shared(const Renderer& renderer,
                                         const Surface& surface);

  /**
   * Creates and returns a shared pointer to an texture with the supplied
   * characteristics.
   *
   * @param renderer the associated renderer that will be used.
   * @param format the pixel format of the texture.
   * @param access the texture access of the texture.
   * @param width the width of the texture.
   * @param height the height of the texture.
   * @return a shared pointer to an texture.
   * @throws CenturionException if the texture cannot be created.
   * @since 3.1.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  static std::shared_ptr<Texture> shared(const Renderer& renderer,
                                         PixelFormat format,
                                         TextureAccess access,
                                         int width,
                                         int height);

  /**
   * Sets the alpha value of the texture.
   *
   * @param alpha the alpha value, in the range [0, 255].
   * @since 3.0.0
   */
  CENTURION_API void set_alpha(Uint8 alpha) noexcept;

  /**
   * Sets the blend mode that will be used by the texture.
   *
   * @param mode the blend mode that will be used.
   * @since 3.0.0
   */
  CENTURION_API void set_blend_mode(BlendMode mode) noexcept;

  /**
   * Sets the color modulation of the texture. Note, the alpha component in the
   * color struct is ignored by this method.
   *
   * @param color the color that will be used to modulate the color of the
   * texture.
   * @since 3.0.0
   */
  CENTURION_API void set_color_mod(Color color) noexcept;

  /**
   * Returns the format of the internal SDL_Texture.
   *
   * @return the format of the internal SDL_Texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API PixelFormat format() const noexcept;

  /**
   * Returns the texture access of the internal SDL_Texture.
   *
   * @return the texture access of the internal SDL_Texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API TextureAccess access() const noexcept;

  /**
   * Returns the width of the texture.
   *
   * @return the width of the texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int width() const noexcept;

  /**
   * Returns the height of the texture.
   *
   * @return the height of the texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int height() const noexcept;

  /**
   * Indicates whether or not the texture is a possible render target.
   *
   * @return true if the texture is a possible render target; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_target() const noexcept;

  /**
   * Indicates whether or not the texture has static texture access.
   *
   * @return true if the texture has static texture access.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_static() const noexcept;

  /**
   * Indicates whether or not the texture has streaming texture access.
   *
   * @return true if the texture has streaming texture access; false otherwise.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool is_streaming() const noexcept;

  /**
   * Returns the alpha value of the texture.
   *
   * @return the alpha value of the texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint8 alpha() const noexcept;

  /**
   * Returns the blend mode of the texture.
   *
   * @return the blend mode of the texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API BlendMode blend_mode() const noexcept;

  /**
   * Returns the color modulation of the texture.
   *
   * @return the modulation of the texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Color color_mod() const noexcept;

  /**
   * Returns a string representation of the texture.
   *
   * @return a string representation of the texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API std::string to_string() const;

  /**
   * Returns a pointer to the internal SDL_Texture. Use of this method is
   * not recommended, since it purposefully breaks const-correctness. However
   * it is useful since many SDL calls use non-const pointers even when no
   * change will be applied.
   *
   * @return a pointer to the internal SDL_Texture.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  SDL_Texture* get() const noexcept { return m_texture; }

  /**
   * Returns a pointer to the internal SDL_Texture.
   *
   * @return a pointer to the internal SDL_Texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  operator SDL_Texture*() noexcept { return m_texture; }

  /**
   * Returns a pointer to the internal SDL_Texture.
   *
   * @return a pointer to the internal SDL_Texture.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  operator const SDL_Texture*() const noexcept { return m_texture; }

 private:
  SDL_Texture* m_texture = nullptr;

  /**
   * Destroys the internal texture instance. This method has no effect if the
   * associated texture is already null.
   *
   * @since 4.0.0
   */
  void destroy() noexcept;

  /**
   * Moves the contents of the supplied texture instance into this instance.
   *
   * @param other the instance that will be moved.
   * @since 4.0.0
   */
  void move(Texture&& other) noexcept;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<Texture>::value, "Texture isn't final!");
#endif

static_assert(std::is_nothrow_move_constructible<Texture>::value,
              "Texture isn't nothrow move constructible!");

static_assert(std::is_nothrow_move_assignable<Texture>::value,
              "Texture isn't nothrow move assignable!");

static_assert(!std::is_nothrow_copy_constructible<Texture>::value,
              "Texture is copyable!");

static_assert(!std::is_nothrow_copy_assignable<Texture>::value,
              "Texture is assignable!");

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "texture.cpp"
#endif

#endif  // CENTURION_TEXTURE_HEADER