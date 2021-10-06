#ifndef CENTURION_EVENT_TYPE_HEADER
#define CENTURION_EVENT_TYPE_HEADER

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../core/integers.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \enum event_type
 *
 * \brief Represents the different event types.
 *
 * \see `SDL_EventType`
 *
 * \since 3.1.0
 */
enum class event_type : u32
{
  quit = SDL_QUIT,

  app_terminating = SDL_APP_TERMINATING,
  app_low_memory = SDL_APP_LOWMEMORY,
  app_will_enter_background = SDL_APP_WILLENTERBACKGROUND,
  app_did_enter_background = SDL_APP_DIDENTERBACKGROUND,
  app_will_enter_foreground = SDL_APP_WILLENTERFOREGROUND,
  app_did_enter_foreground = SDL_APP_DIDENTERFOREGROUND,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  locale_changed = SDL_LOCALECHANGED,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  display = SDL_DISPLAYEVENT,

  window = SDL_WINDOWEVENT,
  system = SDL_SYSWMEVENT,

  key_down = SDL_KEYDOWN,
  key_up = SDL_KEYUP,
  text_editing = SDL_TEXTEDITING,
  text_input = SDL_TEXTINPUT,
  keymap_changed = SDL_KEYMAPCHANGED,

  mouse_motion = SDL_MOUSEMOTION,
  mouse_button_down = SDL_MOUSEBUTTONDOWN,
  mouse_button_up = SDL_MOUSEBUTTONUP,
  mouse_wheel = SDL_MOUSEWHEEL,

  joystick_axis_motion = SDL_JOYAXISMOTION,
  joystick_ball_motion = SDL_JOYBALLMOTION,
  joystick_hat_motion = SDL_JOYHATMOTION,
  joystick_button_down = SDL_JOYBUTTONDOWN,
  joystick_button_up = SDL_JOYBUTTONUP,
  joystick_device_added = SDL_JOYDEVICEADDED,
  joystick_device_removed = SDL_JOYDEVICEREMOVED,

  controller_axis_motion = SDL_CONTROLLERAXISMOTION,
  controller_button_down = SDL_CONTROLLERBUTTONDOWN,
  controller_button_up = SDL_CONTROLLERBUTTONUP,
  controller_device_added = SDL_CONTROLLERDEVICEADDED,
  controller_device_removed = SDL_CONTROLLERDEVICEREMOVED,
  controller_device_remapped = SDL_CONTROLLERDEVICEREMAPPED,

#if SDL_VERSION_ATLEAST(2, 0, 14)
  controller_touchpad_down = SDL_CONTROLLERTOUCHPADDOWN,
  controller_touchpad_up = SDL_CONTROLLERTOUCHPADUP,
  controller_touchpad_motion = SDL_CONTROLLERTOUCHPADMOTION,
  controller_sensor_update = SDL_CONTROLLERSENSORUPDATE,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  touch_down = SDL_FINGERDOWN,
  touch_up = SDL_FINGERUP,
  touch_motion = SDL_FINGERMOTION,

  dollar_gesture = SDL_DOLLARGESTURE,
  dollar_record = SDL_DOLLARRECORD,
  multi_gesture = SDL_MULTIGESTURE,

  clipboard_update = SDL_CLIPBOARDUPDATE,

  drop_file = SDL_DROPFILE,
  drop_text = SDL_DROPTEXT,
  drop_begin = SDL_DROPBEGIN,
  drop_complete = SDL_DROPCOMPLETE,

  audio_device_added = SDL_AUDIODEVICEADDED,
  audio_device_removed = SDL_AUDIODEVICEREMOVED,

  sensor_update = SDL_SENSORUPDATE,

  render_targets_reset = SDL_RENDER_TARGETS_RESET,
  render_device_reset = SDL_RENDER_DEVICE_RESET,

  user = SDL_USEREVENT
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual version of the supplied event type.
 *
 * \details This function returns a string that mirrors the name of the enumerator, e.g.
 * `to_string(event_type::mouse_motion) == "mouse_motion"`.
 *
 * \param type the enumerator that will be converted.
 *
 * \return a string that mirrors the name of the enumerator.
 *
 * \throws cen_error if the enumerator is not recognized.
 *
 * \since 6.2.0
 */
[[nodiscard]] constexpr auto to_string(const event_type type) -> std::string_view
{
  switch (type) {
    case event_type::quit:
      return "quit";

    case event_type::app_terminating:
      return "app_terminating";

    case event_type::app_low_memory:
      return "app_low_memory";

    case event_type::app_will_enter_background:
      return "app_will_enter_background";

    case event_type::app_did_enter_background:
      return "app_did_enter_background";

    case event_type::app_will_enter_foreground:
      return "app_will_enter_foreground";

    case event_type::app_did_enter_foreground:
      return "app_did_enter_foreground";

#if SDL_VERSION_ATLEAST(2, 0, 14)
    case event_type::locale_changed:
      return "locale_changed";
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case event_type::display:
      return "display";

    case event_type::window:
      return "window";

    case event_type::system:
      return "system";

    case event_type::key_down:
      return "key_down";

    case event_type::key_up:
      return "key_up";

    case event_type::text_editing:
      return "text_editing";

    case event_type::text_input:
      return "text_input";

    case event_type::keymap_changed:
      return "keymap_changed";

    case event_type::mouse_motion:
      return "mouse_motion";

    case event_type::mouse_button_down:
      return "mouse_button_down";

    case event_type::mouse_button_up:
      return "mouse_button_up";

    case event_type::mouse_wheel:
      return "mouse_wheel";

    case event_type::joystick_axis_motion:
      return "joystick_axis_motion";

    case event_type::joystick_ball_motion:
      return "joystick_ball_motion";

    case event_type::joystick_hat_motion:
      return "joystick_hat_motion";

    case event_type::joystick_button_down:
      return "joystick_button_down";

    case event_type::joystick_button_up:
      return "joystick_button_up";

    case event_type::joystick_device_added:
      return "joystick_device_added";

    case event_type::joystick_device_removed:
      return "joystick_device_removed";

    case event_type::controller_axis_motion:
      return "controller_axis_motion";

    case event_type::controller_button_down:
      return "controller_button_down";

    case event_type::controller_button_up:
      return "controller_button_up";

    case event_type::controller_device_added:
      return "controller_device_added";

    case event_type::controller_device_removed:
      return "controller_device_removed";

    case event_type::controller_device_remapped:
      return "controller_device_remapped";

#if SDL_VERSION_ATLEAST(2, 0, 14)
    case event_type::controller_touchpad_down:
      return "controller_touchpad_down";

    case event_type::controller_touchpad_up:
      return "controller_touchpad_up";

    case event_type::controller_touchpad_motion:
      return "controller_touchpad_motion";

    case event_type::controller_sensor_update:
      return "controller_sensor_update";
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

    case event_type::touch_down:
      return "touch_down";

    case event_type::touch_up:
      return "touch_up";

    case event_type::touch_motion:
      return "touch_motion";

    case event_type::dollar_gesture:
      return "dollar_gesture";

    case event_type::dollar_record:
      return "dollar_record";

    case event_type::multi_gesture:
      return "multi_gesture";

    case event_type::clipboard_update:
      return "clipboard_update";

    case event_type::drop_file:
      return "drop_file";

    case event_type::drop_text:
      return "drop_text";

    case event_type::drop_begin:
      return "drop_begin";

    case event_type::drop_complete:
      return "drop_complete";

    case event_type::audio_device_added:
      return "audio_device_added";

    case event_type::audio_device_removed:
      return "audio_device_removed";

    case event_type::sensor_update:
      return "sensor_update";

    case event_type::render_targets_reset:
      return "render_targets_reset";

    case event_type::render_device_reset:
      return "render_device_reset";

    case event_type::user:
      return "user";

    default:
      throw cen_error{"Did not recognize event type!"};
  }
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of an event type enumerator.
 *
 * \param stream the output stream that will be used.
 * \param type the enumerator that will be printed.
 *
 * \see `to_string(event_type)`
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const event_type type) -> std::ostream&
{
  return stream << to_string(type);
}

/// \} End of streaming

/// \name Event type comparison operators
/// \{

/**
 * \brief Indicates whether or not two event type values are the same.
 *
 * \param lhs the left-hand side event type value
 * \param rhs the right-hand side event type value
 *
 * \return `true` if the values are the same; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto operator==(const event_type lhs, const SDL_EventType rhs) noexcept
    -> bool
{
  return static_cast<SDL_EventType>(lhs) == rhs;
}

/// \copydoc operator==(const event_type, const SDL_EventType)
[[nodiscard]] constexpr auto operator==(const SDL_EventType lhs, const event_type rhs) noexcept
    -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two event type values aren't the same.
 *
 * \param lhs the left-hand side event type value
 * \param rhs the right-hand side event type value
 *
 * \return `true` if the values aren't the same; `false` otherwise.
 *
 * \since 3.1.0
 */
[[nodiscard]] constexpr auto operator!=(const event_type lhs, const SDL_EventType rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(const event_type, const SDL_EventType)
[[nodiscard]] constexpr auto operator!=(const SDL_EventType lhs, const event_type rhs) noexcept
    -> bool
{
  return !(lhs == rhs);
}

/// \} End of event type comparison operators

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENT_TYPE_HEADER