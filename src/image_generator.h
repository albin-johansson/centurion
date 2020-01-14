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

namespace centurion {

class Renderer;
class Image;

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
class ImageGenerator {
 private:
  std::shared_ptr<Renderer> renderer;

 public:
  /**
   * @param renderer a shared pointer to the associated renderer instance, may not be null.
   * @throws CenturionException if the supplied renderer is null.
   * @since 3.0.0
   */
  explicit ImageGenerator(const std::shared_ptr<Renderer>& renderer);

  virtual ~ImageGenerator() noexcept;

  /**
   * Creates and returns a unique pointer to an image.
   *
   * @param file the file path of the image that will be loaded.
   * @return a unique pointer to an image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  [[nodiscard]]
  std::unique_ptr<Image> unique_img(const std::string& file) const;

  /**
   * Creates and returns a shared pointer to an image.
   *
   * @param file the file path of the image that will be loaded.
   * @return a shared pointer to an image.
   * @throws CenturionException if the image cannot be loaded.
   * @since 3.0.0
   */
  [[nodiscard]]
  std::shared_ptr<Image> shared_img(const std::string& file) const;
};

}
