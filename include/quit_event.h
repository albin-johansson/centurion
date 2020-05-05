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

#ifndef CENTURION_QUIT_EVENT_HEADER
#define CENTURION_QUIT_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 * The QuitEvent class represents the event of the user wanting to close the
 * application, usually by pressing the "X"-button on the window frame.
 *
 * @see SDL_QuitEvent
 * @since 4.0.0
 */
class QuitEvent : public CommonEvent<SDL_QuitEvent> {
 public:
  /**
   * Creates a default-initialized quit event.
   *
   * @since 4.0.0
   */
  CENTURION_API QuitEvent() noexcept;

  /**
   * Creates a quit event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API explicit QuitEvent(const SDL_QuitEvent& event) noexcept;

  /**
   * Creates a quit event based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API explicit QuitEvent(SDL_QuitEvent&& event) noexcept;
};

static_assert(validate_event<QuitEvent, SDL_QuitEvent>(),
              "QuitEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "quit_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_QUIT_EVENT_HEADER