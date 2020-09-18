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
 * @file texture_access.hpp
 *
 * @ingroup input
 *
 * @brief Provides the `texture_access` enum.
 *
 * @author Albin Johansson
 *
 * @copyright MIT License
 *
 * @date 2019-2020
 */

#ifndef CENTURION_TEXTURE_ACCESS_HEADER
#define CENTURION_TEXTURE_ACCESS_HEADER

#include <SDL_render.h>

#include "centurion_api.hpp"

namespace cen {

/**
 * @enum texture_access
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
 * @headerfile texture_access.hpp
 */
enum class texture_access {
  no_lock = SDL_TEXTUREACCESS_STATIC, /**< Indicates that the texture changes
                                       * rarely, and isn't lockable. */
  streaming =
      SDL_TEXTUREACCESS_STREAMING,  /**< Indicates that the texture changes
                                     * frequently, and is lockable. */
  target = SDL_TEXTUREACCESS_TARGET /**< Indicates that the texture can be used
                                     * as a render target. */
};

}  // namespace cen

#endif  // CENTURION_TEXTURE_ACCESS_HEADER
