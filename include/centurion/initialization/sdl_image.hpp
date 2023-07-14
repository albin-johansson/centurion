/*
 * MIT License
 *
 * Copyright (c) 2019-2023 Albin Johansson
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

#ifndef CENTURION_INITIALIZATION_SDL_IMAGE_HPP_
#define CENTURION_INITIALIZATION_SDL_IMAGE_HPP_

#if CEN_USE_SDL_IMAGE

#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>

#include <centurion/common/errors.hpp>
#include <centurion/common/macros.hpp>
#include <centurion/common/primitives.hpp>

namespace cen {

class SDLImage final {
 public:
  CEN_CANNOT_COPY(SDLImage);
  CEN_CANNOT_MOVE(SDLImage);

  [[nodiscard]] explicit SDLImage(const int flags = IMG_INIT_JPG | IMG_INIT_PNG |
                                                    IMG_INIT_TIF | IMG_INIT_WEBP |
                                                    IMG_INIT_JXL | IMG_INIT_AVIF)
  {
    if (IMG_Init(flags) == 0) {
      throw SDLImageError {};
    }
  }

  ~SDLImage() noexcept { IMG_Quit(); }
};

}  // namespace cen

#endif  // CEN_USE_SDL_IMAGE
#endif  // CENTURION_INITIALIZATION_SDL_IMAGE_HPP_
