#ifndef CENTURION_NEW_EVENT_HEADER
#define CENTURION_NEW_EVENT_HEADER

#include <SDL_events.h>

#include <cstdint>
#include <utility>

#include "centurion_api.h"

namespace centurion {

/**
 * This is the templated base class of all Centurion events. This class
 * provides the common API of all events and the storage of the SDL2 event.
 *
 * @tparam T the SDL2 event type that the Centurion version represents.
 * @since 4.0.0
 */
template <typename T>
class TEvent {
 public:
  /**
   * Creates a TEvent and default-initializes the internal event.
   *
   * @since 4.0.0
   */
  TEvent() noexcept : m_event{} {}

  /**
   * Creates a TEvent and copies the supplied event.
   *
   * @param event the event that will be copied.
   * @since 4.0.0
   */
  explicit TEvent(const T& event) : m_event{event} {}

  /**
   * Creates a TEvent and moves the contents of the supplied event.
   *
   * @param event the event that will be moved.
   * @since 4.0.0
   */
  explicit TEvent(T&& event) : m_event{std::move(event)} {}

  /**
   * Default virtual destructor.
   *
   * @since 4.0.0
   */
  virtual ~TEvent() noexcept {};

  /**
   * Returns the ID of the window associated with the event.
   *
   * @return the ID of the window associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD uint32_t window_id() const noexcept
  {
    return m_event.windowID;
  }

  /**
   * Returns the timestamp associated with the creation of the event.
   *
   * @return the timestamp associated with the creation of the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD uint32_t time() const noexcept
  {
    return m_event.timestamp;
  }

 protected:
  T m_event;
};

class AudioDeviceEvent : public TEvent<SDL_AudioDeviceEvent> {
 public:
};

class ControllerAxisEvent : public TEvent<SDL_ControllerAxisEvent> {
};

class ControllerButtonEvent : public TEvent<SDL_ControllerButtonEvent> {
};

class ControllerDeviceEvent : public TEvent<SDL_ControllerDeviceEvent> {
};

class DollarGestureEvent : public TEvent<SDL_DollarGestureEvent> {
};

class DropEvent : public TEvent<SDL_DropEvent> {
};

class TouchFingerEvent : public TEvent<SDL_TouchFingerEvent> {
};

class KeyboardEvent : public TEvent<SDL_KeyboardEvent> {
};

class JoyAxisEvent : public TEvent<SDL_JoyAxisEvent> {
};

class JoyBallEvent : public TEvent<SDL_JoyBallEvent> {
};

class JoyHatEvent : public TEvent<SDL_JoyHatEvent> {
};

class JoyButtonEvent : public TEvent<SDL_JoyButtonEvent> {
};

class JoyDeviceEvent : public TEvent<SDL_JoyDeviceEvent> {
};

class MouseMotionEvent : public TEvent<SDL_MouseMotionEvent> {
};

class MouseButtonEvent : public TEvent<SDL_MouseButtonEvent> {
};

class MouseWheelEvent : public TEvent<SDL_MouseWheelEvent> {
};

class MultiGestureEvent : public TEvent<SDL_MultiGestureEvent> {
};

class QuitEvent : public TEvent<SDL_QuitEvent> {
 public:
  CENTURION_API QuitEvent() noexcept;

  CENTURION_API explicit QuitEvent(const SDL_QuitEvent& event) noexcept;

  CENTURION_API explicit QuitEvent(SDL_QuitEvent&& event) noexcept;
};

class SysWMEvent : public TEvent<SDL_SysWMEvent> {
};

class TextEditingEvent : public TEvent<SDL_TextEditingEvent> {
};

class TextInputEvent : public TEvent<SDL_TextInputEvent> {
};

class UserEvent : public TEvent<SDL_UserEvent> {
};

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
 * TEvent&lt;SDL_WindowEvent&gt;.
 *
 * @see SDL_WindowEvent
 * @since 4.0.0
 */
class WindowEvent : public TEvent<SDL_WindowEvent> {
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
  CENTURION_API int32_t data_1() const noexcept;

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
  CENTURION_API int32_t data_2() const noexcept;
};

}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "quit_event.cpp"
#endif

#endif  // CENTURION_NEW_EVENT_HEADER // TODO fix this include guard name