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

#ifndef CENTURION_CURSOR_HEADER
#define CENTURION_CURSOR_HEADER

#include <SDL.h>

#include <gsl-lite.hpp>
#include <type_traits>

#include "centurion_api.h"
#include "point.h"

namespace centurion {

enum class CursorID {
  Arrow = SDL_SYSTEM_CURSOR_ARROW,
  IBeam = SDL_SYSTEM_CURSOR_IBEAM,
  Wait = SDL_SYSTEM_CURSOR_WAIT,
  Crosshair = SDL_SYSTEM_CURSOR_CROSSHAIR,
  WaitArrow = SDL_SYSTEM_CURSOR_WAITARROW,
  Arrow_NW_SE = SDL_SYSTEM_CURSOR_SIZENWSE,
  Arrow_NE_SW = SDL_SYSTEM_CURSOR_SIZENESW,
  Arrow_W_E = SDL_SYSTEM_CURSOR_SIZEWE,
  Arrow_N_S = SDL_SYSTEM_CURSOR_SIZENS,
  ArrowAll = SDL_SYSTEM_CURSOR_SIZEALL,
  No = SDL_SYSTEM_CURSOR_NO,
  Hand = SDL_SYSTEM_CURSOR_HAND
};

class Cursor final {
 private:
  SDL_Cursor* cursor = nullptr;

 public:
  CENTURION_API Cursor();

  CENTURION_API explicit Cursor(CursorID id);

  CENTURION_API explicit Cursor(SDL_Cursor* cursor);

  CENTURION_API explicit Cursor(SDL_Surface* surface, math::IPoint hotspot);

  CENTURION_API ~Cursor() noexcept;

  CENTURION_API static void set_visible(bool visible) noexcept;

  CENTURION_API static bool is_visible() noexcept;
};

};  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "cursor.cpp"
#endif

#endif  // CENTURION_CURSOR_HEADER