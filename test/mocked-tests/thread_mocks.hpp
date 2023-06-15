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

#include <SDL.h>
#include <fff.h>

extern "C" {
// Mutex
DECLARE_FAKE_VOID_FUNC(SDL_DestroyMutex, SDL_mutex*)
DECLARE_FAKE_VALUE_FUNC(SDL_mutex*, SDL_CreateMutex)
DECLARE_FAKE_VALUE_FUNC(int, SDL_LockMutex, SDL_mutex*)
DECLARE_FAKE_VALUE_FUNC(int, SDL_UnlockMutex, SDL_mutex*)

// Semaphore
DECLARE_FAKE_VOID_FUNC(SDL_DestroySemaphore, SDL_sem*)
DECLARE_FAKE_VALUE_FUNC(SDL_sem*, SDL_CreateSemaphore, Uint32)

// Condition
DECLARE_FAKE_VOID_FUNC(SDL_DestroyCond, SDL_cond*)
DECLARE_FAKE_VALUE_FUNC(SDL_cond*, SDL_CreateCond)
}

namespace mocks {

void reset_thread();

}  // namespace mocks