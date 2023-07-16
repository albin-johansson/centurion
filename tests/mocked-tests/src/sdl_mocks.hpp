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

#pragma once

#include <cstring>  // memcpy

#include <SDL3/SDL.h>

#include <centurion/common/primitives.hpp>
#include <fff/fff.h>

#define CEN_MOCK_FUNCTIONS(Op)                                                     \
  Op##_FAKE_VALUE_FUNC(const char*, SDL_GetError);                                 \
  Op##_FAKE_VALUE_FUNC(Uint64, SDL_GetTicks);                                      \
  Op##_FAKE_VALUE_FUNC(Uint64, SDL_GetTicksNS);                                    \
  Op##_FAKE_VALUE_FUNC(Uint64, SDL_GetPerformanceCounter);                         \
  Op##_FAKE_VALUE_FUNC(Uint64, SDL_GetPerformanceFrequency);                       \
  Op##_FAKE_VALUE_FUNC(void*, SDL_LoadObject, const char*);                        \
  Op##_FAKE_VALUE_FUNC(SDL_FunctionPointer, SDL_LoadFunction, void*, const char*); \
  Op##_FAKE_VOID_FUNC(SDL_UnloadObject, void*)

CEN_MOCK_FUNCTIONS(DECLARE)

namespace testing {

void reset_mocks();

template <typename Ptr>
[[nodiscard]] auto make_ptr(const cen::usize value) noexcept -> Ptr
{
  static_assert(sizeof(Ptr) == sizeof(cen::usize));

  Ptr ptr;
  std::memcpy(&ptr, &value, sizeof value);
  return ptr;
}

}  // namespace testing

#define CEN_MOCK_FIXTURE(Name)        \
  class Name : public testing::Test { \
   public:                            \
    void TearDown() override          \
    {                                 \
      testing::reset_mocks();         \
    }                                 \
  }
