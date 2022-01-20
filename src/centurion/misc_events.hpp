#ifndef CENTURION_MISC_EVENTS_HPP_
#define CENTURION_MISC_EVENTS_HPP_

#include <SDL.h>

#include <array>        // array
#include <ostream>      // ostream
#include <string_view>  // string_view
#include <utility>      // move

#include "common.hpp"
#include "controller.hpp"
#include "detail/array_utils.hpp"
#include "detail/stdlib.hpp"
#include "event_base.hpp"
#include "input.hpp"
#include "keyboard.hpp"
#include "mouse.hpp"
#include "sensor.hpp"

namespace cen {

/// \addtogroup event
/// \{

class quit_event final : public event_base<SDL_QuitEvent> {
 public:
  quit_event() : event_base{event_type::quit} {}

  explicit quit_event(const SDL_QuitEvent& event) noexcept : event_base{event} {}
};

template <>
inline auto as_sdl_event(const event_base<SDL_QuitEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.quit = event.get();
  return e;
}

#if SDL_VERSION_ATLEAST(2, 0, 14)

enum class display_event_id {
  none = SDL_DISPLAYEVENT_NONE,
  orientation = SDL_DISPLAYEVENT_ORIENTATION,
  connected = SDL_DISPLAYEVENT_CONNECTED,
  disconnected = SDL_DISPLAYEVENT_DISCONNECTED,
};

/// \name Display event ID functions
/// \{

[[nodiscard]] constexpr auto to_string(const display_event_id id) -> std::string_view
{
  switch (id) {
    case display_event_id::none:
      return "none";

    case display_event_id::orientation:
      return "orientation";

    case display_event_id::connected:
      return "connected";

    case display_event_id::disconnected:
      return "disconnected";

    default:
      throw exception{"Did not recognize display event ID!"};
  }
}

inline auto operator<<(std::ostream& stream, const display_event_id id) -> std::ostream&
{
  return stream << to_string(id);
}

/// \} End of display event ID functions

class display_event final : public event_base<SDL_DisplayEvent> {
 public:
  display_event() : event_base{event_type::display} {}

  explicit display_event(const SDL_DisplayEvent& event) noexcept : event_base{event} {}

  void set_event_id(const display_event_id id) noexcept
  {
    mEvent.event = static_cast<uint8>(to_underlying(id));
  }

  void set_index(const uint32 index) noexcept { mEvent.display = index; }

  void set_data1(const int32 data) noexcept { mEvent.data1 = data; }

  [[nodiscard]] auto event_id() const noexcept -> display_event_id
  {
    return static_cast<display_event_id>(mEvent.event);
  }

  [[nodiscard]] auto index() const noexcept -> uint32 { return mEvent.display; }

  [[nodiscard]] auto data1() const noexcept -> int32 { return mEvent.data1; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_DisplayEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.display = event.get();
  return e;
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

class dollar_gesture_event final : public event_base<SDL_DollarGestureEvent> {
 public:
  dollar_gesture_event() : event_base{event_type::dollar_gesture} {}

  explicit dollar_gesture_event(const SDL_DollarGestureEvent& event) noexcept
      : event_base{event}
  {}

  void set_touch_id(const SDL_TouchID id) noexcept { mEvent.touchId = id; }

  void set_gesture_id(const SDL_GestureID id) noexcept { mEvent.gestureId = id; }

  void set_fingers(const uint32 fingers) noexcept { mEvent.numFingers = fingers; }

  void set_error(const float error) noexcept { mEvent.error = error; }

  void set_x(const float x) noexcept { mEvent.x = x; }

  void set_y(const float y) noexcept { mEvent.y = y; }

  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID { return mEvent.touchId; }

  [[nodiscard]] auto gesture_id() const noexcept -> SDL_GestureID { return mEvent.gestureId; }

  [[nodiscard]] auto finger_count() const noexcept -> uint32 { return mEvent.numFingers; }

  [[nodiscard]] auto error() const noexcept -> float { return mEvent.error; }

  [[nodiscard]] auto x() const noexcept -> float { return mEvent.x; }

  [[nodiscard]] auto y() const noexcept -> float { return mEvent.y; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_DollarGestureEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.dgesture = event.get();
  return e;
}

class drop_event final : public event_base<SDL_DropEvent> {
 public:
  drop_event() : event_base{event_type::drop_file} {}

  explicit drop_event(const SDL_DropEvent& event) noexcept : event_base{event} {}

  ~drop_event() noexcept { maybe_destroy_file(); }

  void set_will_free_file(const bool freeFile) noexcept { mFreeFile = freeFile; }

  void set_file(char* file) noexcept
  {
    maybe_destroy_file();
    mEvent.file = file;
  }

  void set_window_id(const uint32 id) noexcept { mEvent.windowID = id; }

  [[nodiscard]] auto will_free_file() const noexcept -> bool { return mFreeFile; }

  [[nodiscard]] auto file() const noexcept -> char* { return mEvent.file; }

  [[nodiscard]] auto window_id() const noexcept -> uint32 { return mEvent.windowID; }

 private:
  bool mFreeFile{false};

  void maybe_destroy_file() noexcept
  {
    if (mEvent.file && mFreeFile) {
      SDL_free(mEvent.file);
    }
  }
};

template <>
inline auto as_sdl_event(const event_base<SDL_DropEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.drop = event.get();
  return e;
}

class keyboard_event final : public event_base<SDL_KeyboardEvent> {
 public:
  keyboard_event() : event_base{event_type::key_down} {}

  explicit keyboard_event(const SDL_KeyboardEvent& event) noexcept : event_base{event} {}

  void set_scan(const scan_code code) noexcept { mEvent.keysym.scancode = code.get(); }

  void set_key(const key_code code) noexcept { mEvent.keysym.sym = code.get(); }

  void set_state(const button_state state) noexcept { mEvent.state = to_underlying(state); }

  void set_modifier(const key_mod mod, const bool active) noexcept
  {
    if (active) {
      mEvent.keysym.mod |= to_underlying(mod);
    }
    else {
      mEvent.keysym.mod &= ~to_underlying(mod);
    }
  }

  void set_repeated(const bool repeated) noexcept { mEvent.repeat = repeated; }

  void set_window_id(const uint32 id) noexcept { mEvent.windowID = id; }

  [[nodiscard]] auto is_active(const scan_code& code) const noexcept -> bool
  {
    return mEvent.keysym.scancode == code.get();
  }

  [[nodiscard]] auto is_active(const key_code& code) const noexcept -> bool
  {
    return static_cast<SDL_KeyCode>(mEvent.keysym.sym) == code.get();
  }

  [[nodiscard]] auto is_active(const key_mod mod) const noexcept -> bool
  {
    return detail::is_active(mod, mEvent.keysym.mod);
  }

  [[nodiscard]] auto is_only_active(const key_mod mod) const noexcept -> bool
  {
    return detail::is_only_active(mod, mEvent.keysym.mod);
  }

  [[nodiscard]] auto is_only_subset_active(const key_mod mod) const noexcept -> bool
  {
    return detail::is_only_subset_active(mod, mEvent.keysym.mod);
  }

  [[nodiscard]] auto repeated() const noexcept -> bool { return mEvent.repeat; }

  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(mEvent.state);
  }

  [[nodiscard]] auto released() const noexcept -> bool
  {
    return state() == button_state::released;
  }

  [[nodiscard]] auto pressed() const noexcept -> bool
  {
    return state() == button_state::pressed;
  }

  [[nodiscard]] auto scan() const noexcept -> scan_code { return mEvent.keysym.scancode; }

  [[nodiscard]] auto key() const noexcept -> key_code
  {
    return static_cast<SDL_KeyCode>(mEvent.keysym.sym);
  }

  [[nodiscard]] auto window_id() const noexcept -> uint32 { return mEvent.windowID; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_KeyboardEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.key = event.get();
  return e;
}

class multi_gesture_event final : public event_base<SDL_MultiGestureEvent> {
 public:
  multi_gesture_event() : event_base{event_type::multi_gesture} {}

  explicit multi_gesture_event(const SDL_MultiGestureEvent& event) noexcept : event_base{event}
  {}

  void set_touch_id(const SDL_TouchID id) noexcept { mEvent.touchId = id; }

  void set_delta_theta(const float dTheta) noexcept { mEvent.dTheta = dTheta; }

  void set_delta_distance(const float dDistance) noexcept { mEvent.dDist = dDistance; }

  void set_center_x(const float centerX) noexcept { mEvent.x = centerX; }

  void set_center_y(const float centerY) noexcept { mEvent.y = centerY; }

  void set_finger_count(const uint16 count) noexcept { mEvent.numFingers = count; }

  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID { return mEvent.touchId; }

  [[nodiscard]] auto delta_theta() const noexcept -> float { return mEvent.dTheta; }

  [[nodiscard]] auto delta_distance() const noexcept -> float { return mEvent.dDist; }

  [[nodiscard]] auto center_x() const noexcept -> float { return mEvent.x; }

  [[nodiscard]] auto center_y() const noexcept -> float { return mEvent.y; }

  [[nodiscard]] auto finger_count() const noexcept -> uint16 { return mEvent.numFingers; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_MultiGestureEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.mgesture = event.get();
  return e;
}

class sensor_event final : public event_base<SDL_SensorEvent> {
 public:
  using data_type = std::array<float, 6>;

  sensor_event() : event_base{event_type::sensor_update} {}

  explicit sensor_event(const SDL_SensorEvent& event) noexcept : event_base{event} {}

  void set_which(const int32 id) noexcept { mEvent.which = id; }

  void set_data(const data_type& values) { detail::assign(values, mEvent.data); }

  [[nodiscard]] auto which() const noexcept -> int32 { return mEvent.which; }

  [[nodiscard]] auto data() const -> data_type { return detail::to_array(mEvent.data); }
};

template <>
inline auto as_sdl_event(const event_base<SDL_SensorEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.sensor = event.get();
  return e;
}

class text_editing_event final : public event_base<SDL_TextEditingEvent> {
 public:
  text_editing_event() : event_base{event_type::text_editing} { check_length(); }

  explicit text_editing_event(const SDL_TextEditingEvent& event) noexcept : event_base{event}
  {
    check_length();
  }

  void set_window_id(const uint32 id) noexcept { mEvent.windowID = id; }

  void set_start(const int32 start) noexcept { mEvent.start = start; }

  void set_length(const int32 length) noexcept
  {
    mEvent.length = detail::clamp(length, 0, 32);
  }

  [[nodiscard]] auto window_id() const noexcept -> uint32 { return mEvent.windowID; }

  [[nodiscard]] auto text() const noexcept -> std::string_view
  {
    return std::string_view{static_cast<const char*>(mEvent.text)};
  }

  [[nodiscard]] auto start() const noexcept -> int32 { return mEvent.start; }

  [[nodiscard]] auto length() const noexcept -> int32 { return mEvent.length; }

 private:
  void check_length() noexcept { mEvent.length = detail::clamp(mEvent.length, 0, 32); }
};

template <>
inline auto as_sdl_event(const event_base<SDL_TextEditingEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.edit = event.get();
  return e;
}

class text_input_event final : public event_base<SDL_TextInputEvent> {
 public:
  text_input_event() : event_base{event_type::text_input} {}

  explicit text_input_event(const SDL_TextInputEvent& event) noexcept : event_base{event} {}

  void set_window_id(const uint32 id) noexcept { mEvent.windowID = id; }

  [[nodiscard]] auto window_id() const noexcept -> uint32 { return mEvent.windowID; }

  [[nodiscard]] auto text_utf8() const noexcept -> std::string_view
  {
    return std::string_view{static_cast<const char*>(mEvent.text)};
  }
};

template <>
inline auto as_sdl_event(const event_base<SDL_TextInputEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.text = event.get();
  return e;
}

class touch_finger_event final : public event_base<SDL_TouchFingerEvent> {
 public:
  touch_finger_event() : event_base{event_type::finger_down} {}

  explicit touch_finger_event(const SDL_TouchFingerEvent& event) noexcept : event_base{event}
  {}

  void set_touch_id(const SDL_TouchID id) noexcept { mEvent.touchId = id; }

  void set_finger_id(const SDL_FingerID id) noexcept { mEvent.fingerId = id; }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  void set_window_id(const uint32 id) noexcept { mEvent.windowID = id; }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  void set_x(const float x) noexcept { mEvent.x = detail::clamp(x, 0.0f, 1.0f); }

  void set_y(const float y) noexcept { mEvent.y = detail::clamp(y, 0.0f, 1.0f); }

  void set_dx(const float dx) noexcept { mEvent.dx = detail::clamp(dx, -1.0f, 1.0f); }

  void set_dy(const float dy) noexcept { mEvent.dy = detail::clamp(dy, -1.0f, 1.0f); }

  void set_pressure(const float pressure) noexcept
  {
    mEvent.pressure = detail::clamp(pressure, 0.0f, 1.0f);
  }

  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID { return mEvent.touchId; }

  [[nodiscard]] auto finger_id() const noexcept -> SDL_FingerID { return mEvent.fingerId; }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto window_id() const noexcept -> uint32 { return mEvent.windowID; }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  [[nodiscard]] auto x() const noexcept -> float { return mEvent.x; }

  [[nodiscard]] auto y() const noexcept -> float { return mEvent.y; }

  [[nodiscard]] auto dx() const noexcept -> float { return mEvent.dx; }

  [[nodiscard]] auto dy() const noexcept -> float { return mEvent.dy; }

  [[nodiscard]] auto pressure() const noexcept -> float { return mEvent.pressure; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_TouchFingerEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.tfinger = event.get();
  return e;
}

class user_event final : public event_base<SDL_UserEvent> {
 public:
  user_event() : event_base{event_type::user} {}

  explicit user_event(const SDL_UserEvent& event) noexcept : event_base{event} {}

  void set_window_id(const uint32 id) noexcept { mEvent.windowID = id; }

  void set_code(const int32 code) noexcept { mEvent.code = code; }

  void set_data1(void* data) noexcept { mEvent.data1 = data; }

  void set_data2(void* data) noexcept { mEvent.data2 = data; }

  [[nodiscard]] auto window_id() const noexcept -> uint32 { return mEvent.windowID; }

  [[nodiscard]] auto code() const noexcept -> int32 { return mEvent.code; }

  [[nodiscard]] auto data1() noexcept -> void* { return mEvent.data1; }

  [[nodiscard]] auto data1() const noexcept -> const void* { return mEvent.data1; }

  [[nodiscard]] auto data2() noexcept -> void* { return mEvent.data2; }

  [[nodiscard]] auto data2() const noexcept -> const void* { return mEvent.data2; }
};

template <>
inline auto as_sdl_event(const event_base<SDL_UserEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.user = event.get();
  return e;
}

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_MISC_EVENTS_HPP_
