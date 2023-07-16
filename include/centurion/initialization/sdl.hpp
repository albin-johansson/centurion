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

#ifndef CENTURION_INITIALIZATION_SDL_HPP_
#define CENTURION_INITIALIZATION_SDL_HPP_

#include <SDL3/SDL.h>

#include <centurion/common/errors.hpp>
#include <centurion/common/macros.hpp>
#include <centurion/common/primitives.hpp>

namespace cen {

class SDL final {
 public:
  CEN_CANNOT_COPY(SDL);
  CEN_CANNOT_MOVE(SDL);

  [[nodiscard]] explicit SDL(const uint32 flags = SDL_INIT_EVERYTHING)
  {
    if (SDL_Init(flags) != 0) {
      throw SDLError {};
    }
  }

  ~SDL() noexcept { SDL_Quit(); }
};

}  // namespace cen

#endif  // CENTURION_INITIALIZATION_SDL_HPP_
