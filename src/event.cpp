#include "event.h"

namespace centurion::event {

// ** KEY EVENT ************************************************************************************

KeyEvent::KeyEvent(SDL_KeyboardEvent keyEvent) noexcept: event{keyEvent} {}

bool KeyEvent::is_key_active(SDL_Keycode keycode) const noexcept {
  return event.keysym.sym == keycode;
}

bool KeyEvent::is_key_active(SDL_Scancode scancode) const noexcept {
  return event.keysym.scancode == scancode;
}

bool KeyEvent::is_modifier_active(KeyModifier modifier) const noexcept {
  return event.keysym.mod & static_cast<SDL_Keymod>(modifier);
}

bool KeyEvent::is_control_active() const noexcept {
  return is_modifier_active(KeyModifier::LeftControl)
      || is_modifier_active(KeyModifier::RightControl);
}

bool KeyEvent::is_shift_active() const noexcept {
  return is_modifier_active(KeyModifier::LeftShift)
      || is_modifier_active(KeyModifier::RightShift);
}

bool KeyEvent::is_alt_active() const noexcept {
  return is_modifier_active(KeyModifier::LeftAlt)
      || is_modifier_active(KeyModifier::RightAlt);
}

bool KeyEvent::is_gui_active() const noexcept {
  return is_modifier_active(KeyModifier::LeftGUI)
      || is_modifier_active(KeyModifier::RightGUI);
}

uint32_t KeyEvent::get_window_id() const noexcept {
  return event.windowID;
}

uint32_t KeyEvent::get_time() const noexcept {
  return event.timestamp;
}

bool KeyEvent::is_repeated() const noexcept {
  return event.repeat;
}

ButtonState KeyEvent::get_state() const noexcept {
  return static_cast<ButtonState>(event.state);
}

// ** MOUSE BUTTON EVENT ***************************************************************************

MouseButtonEvent::MouseButtonEvent(SDL_MouseButtonEvent buttonEvent) noexcept
    : event{buttonEvent} {}

MouseButton MouseButtonEvent::get_button() const noexcept {
  return static_cast<MouseButton>(event.button);
}

int MouseButtonEvent::get_x() const noexcept {
  return event.x;
}

int MouseButtonEvent::get_y() const noexcept {
  return event.y;
}

bool MouseButtonEvent::was_single_click() const noexcept {
  return event.clicks == 1;
}

bool MouseButtonEvent::was_double_click() const noexcept {
  return event.clicks == 2;
}

bool MouseButtonEvent::was_touch() const noexcept {
  return event.which == SDL_TOUCH_MOUSEID;
}

ButtonState MouseButtonEvent::get_state() const noexcept {
  return static_cast<ButtonState>(event.state);
}

uint32_t MouseButtonEvent::get_window_id() const noexcept {
  return event.windowID;
}

uint32_t MouseButtonEvent::get_time() const noexcept {
  return event.timestamp;
}

// ** MOUSE MOTION EVENT ***************************************************************************

MouseMotionEvent::MouseMotionEvent(SDL_MouseMotionEvent motionEvent) noexcept
    : event{motionEvent} {}

int MouseMotionEvent::get_x() const noexcept {
  return event.x;
}

int MouseMotionEvent::get_y() const noexcept {
  return event.y;
}

int MouseMotionEvent::get_x_movement() const noexcept {
  return event.xrel;
}

int MouseMotionEvent::get_y_movement() const noexcept {
  return event.yrel;
}

bool MouseMotionEvent::was_touch() const noexcept {
  return event.which == SDL_TOUCH_MOUSEID;
}

bool MouseMotionEvent::is_button_down(MouseButton button) const noexcept {
  return event.state & static_cast<unsigned>(button);
}

uint32_t MouseMotionEvent::get_window_id() const noexcept {
  return event.windowID;
}

uint32_t MouseMotionEvent::get_time() const noexcept {
  return event.timestamp;
}

// ** MOUSE WHEEL EVENT ****************************************************************************

MouseWheelEvent::MouseWheelEvent(SDL_MouseWheelEvent wheelEvent) noexcept
    : event{wheelEvent} {}

int MouseWheelEvent::get_horizontal_scroll() const noexcept {
  return event.x;
}

int MouseWheelEvent::get_vertical_scroll() const noexcept {
  return event.y;
}

MouseWheelDirection MouseWheelEvent::get_wheel_direction() const noexcept {
  return static_cast<MouseWheelDirection>(event.direction);
}

bool MouseWheelEvent::was_touch() const noexcept {
  return event.which == SDL_TOUCH_MOUSEID;
}

uint32_t MouseWheelEvent::get_window_id() const noexcept {
  return event.windowID;
}

uint32_t MouseWheelEvent::get_time() const noexcept {
  return event.timestamp;
}

// ** QUIT EVENT ***********************************************************************************

QuitEvent::QuitEvent(SDL_QuitEvent quitEvent) noexcept
    : time{quitEvent.timestamp} {}

uint32_t QuitEvent::get_time() const noexcept {
  return time;
}

// ** EVENT ****************************************************************************************

Event::Event(const SDL_Event& sdlEvent) noexcept
    : event{sdlEvent} {}

void Event::refresh() noexcept {
  SDL_PumpEvents();
}

void Event::push(Event& event) noexcept {
  SDL_Event& sdlEvent = event;
  SDL_PushEvent(&sdlEvent);
}

void Event::flush() noexcept {
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

void Event::flush_all() noexcept {
  SDL_PumpEvents();
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

bool Event::poll() noexcept {
  return SDL_PollEvent(&event);
}

EventType Event::get_type() const noexcept {
  return static_cast<EventType>(event.type);
}

KeyEvent Event::as_key_event() const noexcept {
  return KeyEvent{event.key};
}

MouseButtonEvent Event::as_mouse_button_event() const noexcept {
  return MouseButtonEvent{event.button};
}

MouseMotionEvent Event::as_mouse_motion_event() const noexcept {
  return MouseMotionEvent{event.motion};
}

MouseWheelEvent Event::as_mouse_wheel_event() const noexcept {
  return MouseWheelEvent{event.wheel};
}

QuitEvent Event::as_quit_event() const noexcept {
  return QuitEvent{event.quit};
}

Event::operator SDL_Event&() noexcept {
  return event;
}

}
