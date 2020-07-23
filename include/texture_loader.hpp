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
 * @file texture_loader.hpp
 *
 * @brief Provides the `texture_loader` class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_TEXTURE_LOADER_HEADER
#define CENTURION_TEXTURE_LOADER_HEADER

#include <memory>

#include "centurion_api.hpp"
#include "renderer.hpp"
#include "texture.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion {

/**
 * @class texture_loader
 *
 * @ingroup graphics
 *
 * @brief A small helper class useful for keeping renderers out of
 * logic-related code.
 *
 * @details
 *
 * This class is really just a wrapper around a pointer to a
 * renderer. Which means that you shouldn't really store away
 * `texture_loader`, unless you can guarantee that the internal pointer won't
 * become a dangling pointer.
 *
 * The following snippet demonstrates how this class can be used.
 * @code{.cpp}
 *   #include <centurion_as_ctn.hpp>
 *   #include <window.hpp>
 *   #include <renderer.hpp>
 *   #include <texture_loader.hpp>
 *
 *   void demo()
 *   {
 *     ctn::window window;
 *     ctn::renderer renderer{window};
 *     ctn::texture_loader loader{renderer};
 *
 *     // creates a unique pointer to a texture
 *     auto unique = loader.unique("resources/some_image.png");
 *
 *     // creates a shared pointer to a texture
 *     auto shared = loader.shared("resources/other_image.png");
 *
 *     // creates a local texture instance
 *     auto local = loader.create("resources/last_image.png");
 *   }
 * @endcode
 *
 * @since 3.0.0
 *
 * @headerfile texture_loader.hpp
 */
class texture_loader final {
 public:
  /**
   * @brief Creates a texture loader.
   *
   * @param renderer the renderer that will be stored and used.
   *
   * @since 5.0.0
   */
  explicit texture_loader(renderer& renderer) noexcept : m_renderer{&renderer}
  {}

  /**
   * @brief Creates and returns a unique pointer to a texture.
   *
   * @tparam Args the types of the arguments that will be forwarded.
   *
   * @param args the arguments that will be forwarded to an appropriate
   * constructor.
   *
   * @return a unique pointer to a texture.
   *
   * @since 5.0.0
   */
  template <typename... Args>
  [[nodiscard]] auto unique(Args&&... args) -> texture::uptr
  {
    return texture::unique(*m_renderer, std::forward<Args>(args)...);
  }

  /**
   * @brief Creates and returns a shared pointer to a texture.
   *
   * @tparam Args the types of the arguments that will be forwarded.
   *
   * @param args the arguments that will be forwarded to an appropriate
   * constructor.
   *
   * @return a shared pointer to a texture.
   *
   * @since 5.0.0
   */
  template <typename... Args>
  [[nodiscard]] auto shared(Args&&... args) -> texture::sptr
  {
    return texture::shared(*m_renderer, std::forward<Args>(args)...);
  }

  /**
   * @brief Creates and returns a texture.
   *
   * @tparam Args the types of the arguments that will be forwarded.
   *
   * @param args the arguments that will be forwarded to an appropriate
   * constructor.
   *
   * @return a valid texture.
   *
   * @since 5.0.0
   */
  template <typename... Args>
  [[nodiscard]] auto create(Args&&... args) -> texture
  {
    return texture{*m_renderer, std::forward<Args>(args)...};
  }

 private:
  renderer* m_renderer;
};

}  // namespace centurion

#endif  // CENTURION_TEXTURE_LOADER_HEADER
