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

#include <centurion/common/errors.hpp>
#include <gtest/gtest.h>

TEST(Errors, ErrorWithNoReason)
{
  const cen::Error error;
  EXPECT_STREQ(error.what(), "?");
}

TEST(Errors, ErrorWithReason)
{
  const char* reason = "This is a test";
  const cen::Error error {reason};
  EXPECT_STREQ(error.what(), reason);
}

TEST(Errors, SDLError)
{
  const char* reason = "SDLError test";
  SDL_SetError(reason);

  const cen::SDLError error;
  EXPECT_STREQ(error.what(), reason);

  SDL_ClearError();
}

#if CEN_USE_SDL_IMAGE

TEST(Errors, SDLImageError)
{
  const char* reason = "SDLImageError test";
  IMG_SetError(reason);

  const cen::SDLImageError error;
  EXPECT_STREQ(error.what(), reason);

  SDL_ClearError();
}

#endif  // CEN_USE_SDL_IMAGE

#if CEN_USE_SDL_MIXER

TEST(Errors, SDLMixerError)
{
  const char* reason = "SDLMixerError test";
  Mix_SetError(reason);

  const cen::SDLMixerError error;
  EXPECT_STREQ(error.what(), reason);

  SDL_ClearError();
}

#endif  // CEN_USE_SDL_MIXER

#if CEN_USE_SDL_TTF

TEST(Errors, SDLTTFError)
{
  const char* reason = "SDLTTFError test";
  TTF_SetError(reason);

  const cen::SDLTTFError error;
  EXPECT_STREQ(error.what(), reason);

  SDL_ClearError();
}

#endif  // CEN_USE_SDL_TTF
