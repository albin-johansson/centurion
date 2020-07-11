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

#ifndef CENTURION_ERROR_HEADER
#define CENTURION_ERROR_HEADER

#include "centurion_api.hpp"
#include "centurion_exception.hpp"
#include "centurion_utils.hpp"

namespace centurion {
namespace detail {

//! @cond FALSE

/**
 * The Error class is a utility for dealing with SDL errors. The main idea is
 * to provide a simple way to combine error messages from the Centurion
 * library and SDL. The Error class is <b>not</b> meant to be used outside of
 * the implementation of the Centurion library.
 *
 * @since 3.0.0
 */
class Error final {
 public:
  Error() = delete;
  Error(const Error&) = delete;
  Error(Error&&) = delete;
  Error& operator=(const Error&) = delete;
  Error& operator=(Error&&) = delete;

  /**
   * Returns an exception with the supplied message along with the latest
   * error obtained from SDL_GetError().
   *
   * @param message the message that will be included in the exception.
   * @return a centurion_exception with the supplied message along with the
   * latest SDL_GetError() message.
   * @since 4.0.0
   */
  [[nodiscard]] CENTURION_API static centurion_exception from_core(
      std::string message);

  /**
   * Returns an exception with the supplied message along with the latest
   * error obtained from IMG_GetError().
   *
   * @param message the message that will be included in the exception.
   * @return a centurion_exception with the supplied message along with the
   * latest IMG_GetError() message.
   * @since 4.0.0
   */
  [[nodiscard]] CENTURION_API static centurion_exception from_image(
      std::string message);

  /**
   * Returns an exception with the supplied message along with the latest
   * error obtained from TTF_GetError().
   *
   * @param message the message that will be included in the exception.
   * @return a centurion_exception with the supplied message along with the
   * latest TTF_GetError() message.
   * @since 4.0.0
   */
  [[nodiscard]] CENTURION_API static centurion_exception from_ttf(
      std::string message);

  /**
   * Returns an exception with the supplied message along with the latest
   * error obtained from Mix_GetError().
   *
   * @param message the message that will be included in the exception.
   * @return a centurion_exception with the supplied message along with the
   * latest Mix_GetError() message.
   * @since 4.0.0
   */
  [[nodiscard]] CENTURION_API static centurion_exception from_mixer(
      std::string message);
};

static_assert(std::is_final_v<Error>);
static_assert(std::is_nothrow_destructible_v<Error>);
static_assert(!std::is_constructible_v<Error>);
static_assert(!std::is_copy_constructible_v<Error>);
static_assert(!std::is_move_constructible_v<Error>);
static_assert(!std::is_copy_assignable_v<Error>);
static_assert(!std::is_move_assignable_v<Error>);

//! @endcond

}  // namespace detail
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "error.cpp"
#endif

#endif  // CENTURION_ERROR_HEADER
