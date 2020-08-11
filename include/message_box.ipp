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

/**
 * @file message_box.ipp
 *
 * @brief Provides the implementation of the templates in the `message_box`
 * class.
 *
 * @author Albin Johansson
 *
 * @date 2019-2020
 *
 * @copyright MIT License
 */

#ifndef CENTURION_MESSAGE_BOX_IMPLEMENTATION
#define CENTURION_MESSAGE_BOX_IMPLEMENTATION

#include "centurion_api.hpp"
#include "message_box.hpp"

namespace centurion {

template <typename Traits>
void message_box::show(const basic_window<Traits>& parent,
                       const std::string& title,
                       const std::string& message,
                       type type,
                       button_order buttonOrder)
{
  show(parent.ptr(), title, message, type, buttonOrder);
}

template <typename Traits>
auto message_box::show(const basic_window<Traits>& parent)
    -> std::optional<button_id>
{
  return show(parent.ptr());
}

}  // namespace centurion

#endif  // CENTURION_MESSAGE_BOX_IMPLEMENTATION
