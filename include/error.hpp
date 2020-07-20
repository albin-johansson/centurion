//! @cond FALSE

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

#include <string_view>

#include "centurion_api.hpp"
#include "centurion_exception.hpp"
#include "centurion_utils.hpp"

#ifdef CENTURION_USE_PRAGMA_ONCE
#pragma once
#endif  // CENTURION_USE_PRAGMA_ONCE

namespace centurion::detail {

/**
 * @brief Returns an exception with the supplied message along with the latest
 * error obtained from `SDL_GetError()`.
 *
 * @param message the message that will be included in the exception.
 *
 * @return a centurion_exception with the supplied message along with the
 * latest `SDL_GetError()` message.
 *
 * @since 4.0.0
 */
CENTURION_QUERY
auto core_error(std::string_view message) -> centurion_exception;

/**
 * @brief Returns an exception with the supplied message along with the latest
 * error obtained from `IMG_GetError()`.
 *
 * @param message the message that will be included in the exception.
 *
 * @return a centurion_exception with the supplied message along with the
 * latest `IMG_GetError()` message.
 *
 * @since 4.0.0
 */
CENTURION_QUERY
auto img_error(std::string_view message) -> centurion_exception;

/**
 * @brief Returns an exception with the supplied message along with the latest
 * error obtained from `TTF_GetError()`.
 *
 * @param message the message that will be included in the exception.
 *
 * @return a centurion_exception with the supplied message along with the
 * latest `TTF_GetError()` message.
 *
 * @since 4.0.0
 */
CENTURION_QUERY
auto ttf_error(std::string_view message) -> centurion_exception;

/**
 * @brief Returns an exception with the supplied message along with the latest
 * error obtained from `Mix_GetError()`.
 *
 * @param message the message that will be included in the exception.
 *
 * @return a centurion_exception with the supplied message along with the
 * latest `Mix_GetError()` message.
 *
 * @since 4.0.0
 */
CENTURION_QUERY
auto mix_error(std::string_view message) -> centurion_exception;

}  // namespace centurion::detail

#endif  // CENTURION_ERROR_HEADER

//! @endcond
