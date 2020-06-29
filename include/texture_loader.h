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

#ifndef CENTURION_IMAGE_GENERATOR_HEADER
#define CENTURION_IMAGE_GENERATOR_HEADER

#include <memory>
#include <type_traits>

#include "area.h"
#include "centurion_api.h"
#include "texture.h"

namespace centurion {

class Renderer;

/**
 * The TextureLoader class is a utility class designed to make it easier to
 * create instances of the Texture class without passing a renderer instance
 * around. This can make it easier to keep renderer instances out of
 * logic-related code.
 *
 * @see Renderer
 * @see Texture
 * @since 3.0.0
 */
class TextureLoader final {
 public:
  /**
   * @param renderer a shared pointer to the associated renderer instance, may
   * not be null.
   * @throws CenturionException if the supplied renderer is null.
   * @since 3.0.0
   */
  CENTURION_API explicit TextureLoader(const SharedPtr<Renderer>& renderer);

  CENTURION_API ~TextureLoader() noexcept;

  /**
   * Creates and returns a unique pointer to a texture.
   *
   * @param file the file path of the texture that will be loaded, may not be
   * null.
   * @return a unique pointer to a texture.
   * @throws CenturionException if the texture cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API UniquePtr<Texture> unique_img(CZString file) const;

  /**
   * Creates and returns a unique pointer to a texture with the specified
   * characteristics.
   *
   * @param format the pixel format of the texture.
   * @param access the texture access of the texture.
   * @param size the size of the texture.
   * @return a unique pointer to a texture.
   * @throws CenturionException if the texture cannot be created.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API UniquePtr<Texture> unique_img(PixelFormat format,
                                              Texture::Access access,
                                              IArea size) const;

  /**
   * Creates and returns a shared pointer to a texture.
   *
   * @param file the file path of the texture that will be loaded, may not be
   * null.
   * @return a shared pointer to a texture.
   * @throws CenturionException if the texture cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API SharedPtr<Texture> shared_img(CZString file) const;

  /**
   * Creates and returns a shared pointer to a texture with the specified
   * characteristics.
   *
   * @param format the pixel format of the texture.
   * @param access the texture access of the texture.
   * @param size the size of the texture..
   * @return a shared pointer to a texture.
   * @throws CenturionException if the texture cannot be created.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API SharedPtr<Texture> shared_img(PixelFormat format,
                                              Texture::Access access,
                                              IArea size) const;

 private:
  SharedPtr<Renderer> m_renderer;
};

#ifdef CENTURION_HAS_IS_FINAL_TYPE_TRAIT
static_assert(std::is_final<TextureLoader>::value,
              "ImageGenerator isn't final!");
#endif

static_assert(std::is_nothrow_copy_assignable<TextureLoader>::value,
              "ImageGenerator isn't nothrow copy assignable!");

static_assert(std::is_nothrow_copy_constructible<TextureLoader>::value,
              "ImageGenerator isn't nothrow copy constructible!");

static_assert(std::is_nothrow_move_assignable<TextureLoader>::value,
              "ImageGenerator isn't nothrow move assignable!");

static_assert(std::is_nothrow_move_constructible<TextureLoader>::value,
              "ImageGenerator isn't nothrow move constructible!");

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "texture_loader.cpp"
#endif

#endif  // CENTURION_IMAGE_GENERATOR_HEADER