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

#ifndef CENTURION_DROP_EVENT_HEADER
#define CENTURION_DROP_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 * The DropEvent class represents the event of requesting a file to be opened.
 *
 * @see SDL_DropEvent
 * @since 4.0.0
 */
class DropEvent : public CommonEvent<SDL_DropEvent> {
 public:
  /**
   * Creates a default-initialized drop event.
   *
   * @since 4.0.0
   */
  CENTURION_API DropEvent() noexcept;

  /**
   * Creates a drop event based on the supplied event.
   *
   * @param event the SDL drop event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API DropEvent(const SDL_DropEvent& event) noexcept;

  /**
   * Creates a drop event based on the supplied event.
   *
   * @param event the SDL drop event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API DropEvent(SDL_DropEvent&& event) noexcept;

  /**
   * Destroys the drop event. The associated file will be freed depending on
   * the value returned from the <code>will_free_file()</code> method.
   *
   * @since 4.0.0
   */
  CENTURION_API ~DropEvent() noexcept;

  /**
   * Sets whether or not the associated file will be freed upon the
   * destruction of this instance. If you set this property to false, you
   * must remember to call <code>SDL_free</code> on the file pointer by
   * yourself. Otherwise, you'll end up with a memory leak.
   *
   * @param freeFile true if the associated file should be freed upon
   * destruction; false otherwise.
   * @since 4.0.0
   */
  CENTURION_API void set_will_free_file(bool freeFile) noexcept;

  /**
   * Sets the file associated with the drop event. The ownership of the
   * supplied pointer will, by default, not be claimed by this event. Note
   * that the supplied pointer will be freed using <code>SDL_free</code> upon
   * the destruction of the event, if the <code>will_free_file</code>
   * property is set to <b>true</b>.
   *
   * <p> Note! If the <code>will_free_file</code> property is true, then <b>the
   * previously set file pointer will be freed</b> by calling this method.
   * However, if the <code>will_free_file</code> property is false, then the
   * old file pointer is simply overridden. This may, if you're not careful,
   * introduce a memory leak in your program.
   *
   * <p> In other words, be careful when using this method.
   *
   * @param file a pointer to a file, can safely be null.
   * @since 4.0.0
   */
  CENTURION_API void set_file(char* file) noexcept;

  /**
   * Sets the ID of the window that is the target of the drop event.
   *
   * @param id the ID of the window that is the target of the drop event.
   * @since 4.0.0
   */
  CENTURION_API void set_window_id(Uint32 id) noexcept;

  /**
   * Indicates whether or not the file associated with the event will be
   * freed upon the destruction of this instance. By default, this property
   * is set to <b>false</b>.
   *
   * @return true if the associated file will be freed upon destruction;
   * false otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool will_free_file() const noexcept;

  /**
   * Returns a pointer to the associated file. Do <b>NOT</b> claim ownership
   * of the returned pointer without setting the <code>will_free_file</code>
   * property to <b>false</b>. The returned pointer is null for
   * <code>DropBegin</code> and <code>DropComplete</code> type drop events.
   *
   * @return a pointer to the file associated with the event, might be null.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API char* file() const noexcept;

  /**
   * Returns the ID of the window that is the target of the drop event, if
   * there even is one.
   *
   * @return the ID of the window that is the target of the drop event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 window_id() const noexcept;

 private:
  bool m_willFreeFile = false;
};

static_assert(validate_event<DropEvent, SDL_DropEvent>(),
              "DropEvent failed the event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "drop_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_DROP_EVENT_HEADER