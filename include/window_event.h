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

#ifndef CENTURION_WINDOW_EVENT_HEADER
#define CENTURION_WINDOW_EVENT_HEADER

#include <SDL_events.h>

#include "button_state.h"
#include "centurion_api.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 *
 * The WindowEventID enum class mirrors the SDL_WindowEventID enum. Depending
 * on the event ID of a WindowEvent instance, the <code>data_1()</code> and
 * <code>data_2()</code> methods have special meanings.
 *
 * <table style="width:100%">
 *   <tr>
 *     <th>Value</th>
 *     <th>data_1</th>
 *     <th>data_2</th>
 *   </tr>
 *   <tr>
 *    <td><code>None</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Shown</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Hidden</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Exposed</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Moved</code></td>
 *    <td>X</td>
 *    <td>Y</td>
 *   </tr>
 *   <tr>
 *    <td><code>Resized</code></td>
 *    <td>Width</td>
 *    <td>Height</td>
 *   </tr>
 *   <tr>
 *    <td><code>SizeChanged</code></td>
 *    <td>Width</td>
 *    <td>Height</td>
 *   </tr>
 *   <tr>
 *    <td><code>Minimized</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Maximized</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Restored</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Enter</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Leave</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>FocusGained</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>FocusLost</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>Close</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>TakeFocus</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 *   <tr>
 *    <td><code>HitTest</code></td>
 *    <td>N/A</td>
 *    <td>N/A</td>
 *   </tr>
 * </table>
 *
 * @since 4.0.0
 */
enum class WindowEventID {
  None = SDL_WINDOWEVENT_NONE,
  Shown = SDL_WINDOWEVENT_SHOWN,
  Hidden = SDL_WINDOWEVENT_HIDDEN,
  Exposed = SDL_WINDOWEVENT_EXPOSED,
  Moved = SDL_WINDOWEVENT_MOVED,
  Resized = SDL_WINDOWEVENT_RESIZED,
  SizeChanged = SDL_WINDOWEVENT_SIZE_CHANGED,
  Minimized = SDL_WINDOWEVENT_MINIMIZED,
  Maximized = SDL_WINDOWEVENT_MAXIMIZED,
  Restored = SDL_WINDOWEVENT_RESTORED,
  Enter = SDL_WINDOWEVENT_ENTER,
  Leave = SDL_WINDOWEVENT_LEAVE,
  FocusGained = SDL_WINDOWEVENT_FOCUS_GAINED,
  FocusLost = SDL_WINDOWEVENT_FOCUS_LOST,
  Close = SDL_WINDOWEVENT_CLOSE,
  TakeFocus = SDL_WINDOWEVENT_TAKE_FOCUS,
  HitTest = SDL_WINDOWEVENT_HIT_TEST
};

/**
 * Indicates whether or not two window event ID values are the same.
 *
 * @param eventId the Centurion window event ID.
 * @param sdlEventId the SDL window event ID.
 * @return true if the window event ID values are the same; false otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(WindowEventID eventId,
                              SDL_WindowEventID sdlEventId) noexcept;

/**
 * Indicates whether or not two window event ID values are the same.
 *
 * @param eventId the SDL window event ID.
 * @param sdlEventId the Centurion window event ID.
 * @return true if the window event ID values are the same; false otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_WindowEventID sdlEventId,
                              WindowEventID eventId) noexcept;

/**
 * Indicates whether or not two window event ID values aren't the same.
 *
 * @param eventId the Centurion window event ID.
 * @param sdlEventId the SDL window event ID.
 * @return true if the window event ID values aren't the same; false otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(WindowEventID eventId,
                              SDL_WindowEventID sdlEventId) noexcept;

/**
 * Indicates whether or not two window event ID values aren't the same.
 *
 * @param eventId the SDL window event ID.
 * @param sdlEventId the Centurion window event ID.
 * @return true if the window event ID values aren't the same; false otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_WindowEventID sdlEventId,
                              WindowEventID eventId) noexcept;

/**
 * The WindowEvent class represents an event that is associated with an
 * action related to a window. This class is a subclass of
 * BaseEvent&lt;SDL_WindowEvent&gt;.
 *
 * @see SDL_WindowEvent
 * @since 4.0.0
 */
class WindowEvent : public CommonEvent<SDL_WindowEvent> {
 public:
  /**
   * Creates a default-initialized window event.
   *
   * @since 4.0.0
   */
  CENTURION_API WindowEvent() noexcept;

  /**
   * Creates a window event based on the supplied SDL window event.
   *
   * @param event the SDL window event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API explicit WindowEvent(const SDL_WindowEvent& event) noexcept;

  /**
   * Creates a window event based on the supplied SDL window event.
   *
   * @param event the SDL window event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API explicit WindowEvent(SDL_WindowEvent&& event) noexcept;

  /**
   * Returns the event ID of this window event. There are many different
   * kinds of window events, use this method to check what kind of action
   * that triggered this event.
   *
   * @return the event ID of this window event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API WindowEventID event_id() const noexcept;

  /**
   * Returns the value of the first data value. The meaning of this value is
   * dependent on the window event ID of this window event.
   *
   * <p> For instance, if the event ID is <code>SizeChanged</code>, then
   * data1 and data2 represent the new width and height of the window
   * respectively. See the <code>WindowEventID</code> documentation for more
   * details about whether the value returned from this method is meaningful
   * in regard to the window event ID.
   *
   * @return the value of the first data value.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint32 data_1() const noexcept;

  /**
   * Returns the value of the second data value. The meaning of this value is
   * dependent on the window event ID of this window event.
   *
   * <p> For instance, if the event ID is <code>SizeChanged</code>, then
   * data1 and data2 represent the new width and height of the window
   * respectively. See the <code>WindowEventID</code> documentation for more
   * details about whether the value returned from this method is meaningful
   * in regard to the window event ID.
   *
   * @return the value of the second data value.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Sint32 data_2() const noexcept;
};

static_assert(validate_event<WindowEvent, SDL_WindowEvent>(),
              "WindowEvent failed the event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "window_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_WINDOW_EVENT_HEADER