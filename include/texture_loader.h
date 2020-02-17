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

#include <cstdint>
#include <memory>
#include <type_traits>

#include "centurion_api.h"
#include "texture.h"

namespace centurion {
namespace video {

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
 private:
  std::shared_ptr<Renderer> renderer;

 public:
  /**
   * @param renderer a shared pointer to the associated renderer instance, may
   * not be null.
   * @throws CenturionException if the supplied renderer is null.
   * @since 3.0.0
   */
  CENTURION_API
  explicit TextureLoader(const std::shared_ptr<Renderer>& renderer);

  CENTURION_API
  ~TextureLoader() noexcept;

  /**
   * Creates and returns a unique pointer to an image.
   *
   * @param file the file path of the image that will be loaded, may not be
   * null.
   * @return a unique pointer to an image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  std::unique_ptr<Texture> unique_img(const char* file) const;

  /**
   * Creates and returns a unique pointer to an image with the specified
   * characteristics.
   *
   * @param format the pixel format of the image.
   * @param access the texture access of the image.
   * @param width the width of the created image.
   * @param height the height of the created image.
   * @return a unique pointer to an image.
   * @throws CenturionException if the image cannot be created.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  std::unique_ptr<Texture> unique_img(PixelFormat format, TextureAccess access,
                                      int width, int height) const;

  /**
   * Creates and returns a shared pointer to an image.
   *
   * @param file the file path of the image that will be loaded, may not be
   * null.
   * @return a shared pointer to an image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  std::shared_ptr<Texture> shared_img(const char* file) const;

  /**
   * Creates and returns a shared pointer to an image with the specified
   * characteristics.
   *
   * @param format the pixel format of the image.
   * @param access the texture access of the image.
   * @param width the width of the created image.
   * @param height the height of the created image.
   * @return a shared pointer to an image.
   * @throws CenturionException if the image cannot be created.
   * @since 3.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API
  std::shared_ptr<Texture> shared_img(PixelFormat format, TextureAccess access,
                                      int width, int height) const;
};

using ImageGenerator = TextureLoader;  // for compatibility

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

}  // namespace video
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "image_generator.cpp"
#endif

#endif  // CENTURION_IMAGE_GENERATOR_HEADER