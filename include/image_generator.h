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
#include <memory>
#include <string>
#include <cstdint>
#include "image.h"
#include "centurion_api.h"

namespace centurion {

class CENTURION_API Renderer;

/**
 * The ImageGenerator class is a utility class designed to make it easier to create instances of
 * the Image class without passing a renderer instance around. This can make it easier to keep
 * renderer instances out of logic-related code.
 *
 * @see Renderer
 * @see Image
 * @since 3.0.0
 * @author Albin Johansson
 */
class CENTURION_API ImageGenerator final {
 private:
  std::shared_ptr<Renderer> renderer;

 public:
  /**
   * @param renderer a shared pointer to the associated renderer instance, may not be null.
   * @throws CenturionException if the supplied renderer is null.
   * @since 3.0.0
   */
  CENTURION_API explicit ImageGenerator(const std::shared_ptr<Renderer>& renderer);

  CENTURION_API ~ImageGenerator() noexcept;

  /**
   * Creates and returns a unique pointer to an image.
   *
   * @param file the file path of the image that will be loaded.
   * @return a unique pointer to an image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::unique_ptr<Image> unique_img(const std::string& file) const;

  /**
   * Creates and returns a unique pointer to an image with the specified characteristics.
   *
   * @param format the format of the created image.
   * @param access one of the SDL_TextureAccess values.
   * @param width the width of the created image.
   * @param height the height of the created image.
   * @return a unique pointer to an image.
   * @throws CenturionException if the image cannot be created.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::unique_ptr<Image> unique_img(uint32_t format,
                                                  TextureAccess access,
                                                  int width,
                                                  int height) const;

  /**
   * Creates and returns a shared pointer to an image.
   *
   * @param file the file path of the image that will be loaded.
   * @return a shared pointer to an image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::shared_ptr<Image> shared_img(const std::string& file) const;

  /**
   * Creates and returns a shared pointer to an image with the specified characteristics.
   *
   * @param format the format of the created image.
   * @param access one of the SDL_TextureAccess values.
   * @param width the width of the created image.
   * @param height the height of the created image.
   * @return a shared pointer to an image.
   * @throws CenturionException if the image cannot be created.
   * @since 3.0.0
   */
  [[nodiscard]]
  CENTURION_API std::shared_ptr<Image> shared_img(uint32_t format,
                                                  TextureAccess access,
                                                  int width,
                                                  int height) const;

};

}
