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

#ifndef CENTURION_TEXT_INPUT_EVENT_HEADER
#define CENTURION_TEXT_INPUT_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "centurion_utils.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 * The TextInputEvent class contains information about keyboard text input
 * events.
 *
 * @see SDL_TextInputEvent
 * @since 4.0.0
 */
class TextInputEvent : public CommonEvent<SDL_TextInputEvent> {
 public:
  /**
   * Creates a default-initialized TextInputEvent.
   *
   * @since 4.0.0
   */
  CENTURION_API TextInputEvent() noexcept;

  /**
   * Creates a TextInputEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API TextInputEvent(const SDL_TextInputEvent& event) noexcept;

  /**
   * Creates a TextInputEvent that is based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API TextInputEvent(SDL_TextInputEvent&& event) noexcept;

  /**
   * Sets the window ID associated with the event.
   *
   * @param id the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_window_id(Uint32 id) noexcept;

  /**
   * Returns the window ID associated with the event.
   *
   * @return the window ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 window_id() const noexcept;

  /**
   * Returns the text that will be used, as a null-terminated string in UTF-8
   * encoding.
   *
   * @return the text that will be used.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API CZString text() const noexcept;
};

static_assert(validate_event<TextInputEvent, SDL_TextInputEvent>(),
              "TextInputEvent failed the event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "text_input_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_TEXT_INPUT_EVENT_HEADER