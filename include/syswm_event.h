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

#ifndef CENTURION_SYSWM_EVENT_HEADER
#define CENTURION_SYSWM_EVENT_HEADER

#include <SDL_events.h>
#include <SDL_syswm.h>

#include "centurion_api.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 * The SysWMEvent is a simple wrapper around SDL_SysWMEvent, only really in
 * the Centurion library to be accessible through the use of
 * <code>Event::poll()</code>.
 *
 * @see SDL_SysWMEvent
 * @since 4.0.0
 */
class SysWMEvent : public CommonEvent<SDL_SysWMEvent> {
 public:
  /**
   * Creates a default-initialized SysWMEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API SysWMEvent() noexcept;

  /**
   * Creates a SysWMEvent based on the supplied event.
   *
   * @param event the event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API SysWMEvent(const SDL_SysWMEvent& event) noexcept;

  /**
   * Creates a SysWMEvent based on the supplied event.
   *
   * @param event the event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API SysWMEvent(SDL_SysWMEvent&& event) noexcept;

  /**
   * Returns the message associated with the event.
   *
   * @return a pointer to the message associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API SDL_SysWMmsg* message() const noexcept;
};

static_assert(validate_event<SysWMEvent, SDL_SysWMEvent>(),
              "SysWMEvent failed the event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "syswm_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_SYSWM_EVENT_HEADER