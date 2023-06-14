/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
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

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <fff.h>

#include <array>  // array

#include "centurion/common/utils.hpp"

#define CEN_PREPARE_MOCK_TEST(Fun, ...) \
  std::array values {__VA_ARGS__};      \
  SET_RETURN_SEQ(Fun, values.data(), cen::isize(values))

extern "C" {
// Initialization
DECLARE_FAKE_VALUE_FUNC(int, SDL_Init, Uint32)
DECLARE_FAKE_VALUE_FUNC(int, TTF_Init)
DECLARE_FAKE_VALUE_FUNC(int, IMG_Init, int)
DECLARE_FAKE_VALUE_FUNC(int, Mix_Init, int)
DECLARE_FAKE_VALUE_FUNC(int, Mix_OpenAudio, int, Uint16, int, int)
DECLARE_FAKE_VALUE_FUNC(SDL_Window*, SDL_CreateWindow, const char*, int, int, int, int, Uint32)

// Cleanup
DECLARE_FAKE_VOID_FUNC(SDL_Quit)
DECLARE_FAKE_VOID_FUNC(TTF_Quit)
DECLARE_FAKE_VOID_FUNC(IMG_Quit)
DECLARE_FAKE_VOID_FUNC(Mix_Quit)
DECLARE_FAKE_VOID_FUNC(Mix_CloseAudio)
DECLARE_FAKE_VOID_FUNC(SDL_free, void*)
DECLARE_FAKE_VOID_FUNC(SDL_DestroyWindow, SDL_Window*)
DECLARE_FAKE_VOID_FUNC(SDL_FreeSurface, SDL_Surface*)

// Misc
DECLARE_FAKE_VALUE_FUNC(const char*, SDL_GetError)
DECLARE_FAKE_VALUE_FUNC(SDL_RWops*, SDL_RWFromFile, const char*, const char*)

// Window
DECLARE_FAKE_VALUE_FUNC(Uint32, SDL_GetWindowFlags, SDL_Window*)
}

namespace mocks {

void reset_core();

}  // namespace mocks
