/*
 * MIT License
 *
 * Copyright (c) 2019-2021 Albin Johansson
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

#include "centurion_cfg.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace cen {

/// \addtogroup input
/// \{

/**
 * \enum key_modifier
 *
 * \brief Mirrors the values of the `SDL_Keymod` enum.
 *
 * \see `SDL_Keymod`
 *
 * \since 3.1.0
 *
 * \headerfile key_modifier.hpp
 */
enum class key_modifier
{
  none = KMOD_NONE,
  left_shift = KMOD_LSHIFT,
  right_shift = KMOD_RSHIFT,
  left_ctrl = KMOD_LCTRL,
  right_ctrl = KMOD_RCTRL,
  left_alt = KMOD_LALT,
  right_alt = KMOD_RALT,
  left_gui = KMOD_LGUI,
  right_gui = KMOD_RGUI,
  num = KMOD_NUM,
  caps = KMOD_CAPS,
  mode = KMOD_MODE
};

/// \}

}  // namespace cen

#endif  // CENTURION_KEY_MODIFIER_HEADER