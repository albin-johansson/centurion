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

#ifndef CENTURION_KEY_MODIFIER_HEADER
#define CENTURION_KEY_MODIFIER_HEADER

#include <SDL.h>

#include "centurion_api.h"

namespace centurion {

/**
 * The KeyModifier enum class mirrors the values of the SDL_Keymod enum.
 *
 * @see SDL_Keymod
 * @since 3.1.0
 */
enum class KeyModifier {
  None = KMOD_NONE,
  LeftShift = KMOD_LSHIFT,
  RightShift = KMOD_RSHIFT,
  LeftControl = KMOD_LCTRL,
  RightControl = KMOD_RCTRL,
  LeftAlt = KMOD_LALT,
  RightAlt = KMOD_RALT,
  LeftGUI = KMOD_LGUI,
  RightGUI = KMOD_RGUI,
  Num = KMOD_NUM,
  Caps = KMOD_CAPS,
  Mode = KMOD_MODE
};

}  // namespace centurion

#endif  // CENTURION_KEY_MODIFIER_HEADER