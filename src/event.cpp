#ifndef CENTURION_EVENT_SOURCE
#define CENTURION_EVENT_SOURCE

#include "event.h"

namespace centurion {
namespace event {

// ** WINDOW EVENT *************************************************************

CENTURION_DEF
WindowEvent::WindowEvent(const SDL_WindowEvent& sdlEvent) noexcept
    : event{sdlEvent}
{}

CENTURION_DEF
uint32_t WindowEvent::get_window_id() const noexcept
{
  return event.windowID;
}

CENTURION_DEF
uint32_t WindowEvent::get_time() const noexcept
{
  return event.timestamp;
}

// ** KEY EVENT ****************************************************************

CENTURION_DEF
KeyEvent::KeyEvent(SDL_KeyboardEvent keyEvent) noexcept : event{keyEvent}
{}

CENTURION_DEF
bool KeyEvent::is_key_active(SDL_Keycode keycode) const noexcept
{
  return event.keysym.sym == keycode;
}

CENTURION_DEF
bool KeyEvent::is_key_active(SDL_Scancode scancode) const noexcept
{
  return event.keysym.scancode == scancode;
}

CENTURION_DEF
bool KeyEvent::is_modifier_active(KeyModifier modifier) const noexcept
{
  return event.keysym.mod & static_cast<SDL_Keymod>(modifier);
}

CENTURION_DEF
bool KeyEvent::is_control_active() const noexcept
{
  return is_modifier_active(KeyModifier::LeftControl) ||
         is_modifier_active(KeyModifier::RightControl);
}

CENTURION_DEF
bool KeyEvent::is_shift_active() const noexcept
{
  return is_modifier_active(KeyModifier::LeftShift) ||
         is_modifier_active(KeyModifier::RightShift);
}

CENTURION_DEF
bool KeyEvent::is_alt_active() const noexcept
{
  return is_modifier_active(KeyModifier::LeftAlt) ||
         is_modifier_active(KeyModifier::RightAlt);
}

CENTURION_DEF
bool KeyEvent::is_gui_active() const noexcept
{
  return is_modifier_active(KeyModifier::LeftGUI) ||
         is_modifier_active(KeyModifier::RightGUI);
}

CENTURION_DEF
uint32_t KeyEvent::get_window_id() const noexcept
{
  return event.windowID;
}

CENTURION_DEF
uint32_t KeyEvent::get_time() const noexcept
{
  return event.timestamp;
}

CENTURION_DEF
bool KeyEvent::is_repeated() const noexcept
{
  return event.repeat;
}

CENTURION_DEF
ButtonState KeyEvent::get_state() const noexcept
{
  return static_cast<ButtonState>(event.state);
}

// ** MOUSE BUTTON EVENT *******************************************************

CENTURION_DEF
MouseButtonEvent::MouseButtonEvent(SDL_MouseButtonEvent buttonEvent) noexcept
    : event{buttonEvent}
{}

CENTURION_DEF
MouseButton MouseButtonEvent::get_button() const noexcept
{
  return static_cast<MouseButton>(event.button);
}

CENTURION_DEF
int MouseButtonEvent::get_x() const noexcept
{
  return event.x;
}

CENTURION_DEF
int MouseButtonEvent::get_y() const noexcept
{
  return event.y;
}

CENTURION_DEF
bool MouseButtonEvent::was_single_click() const noexcept
{
  return event.clicks == 1;
}

CENTURION_DEF
bool MouseButtonEvent::was_double_click() const noexcept
{
  return event.clicks == 2;
}

CENTURION_DEF
bool MouseButtonEvent::was_touch() const noexcept
{
  return event.which == SDL_TOUCH_MOUSEID;
}

CENTURION_DEF
ButtonState MouseButtonEvent::get_state() const noexcept
{
  return static_cast<ButtonState>(event.state);
}

CENTURION_DEF
uint32_t MouseButtonEvent::get_window_id() const noexcept
{
  return event.windowID;
}

CENTURION_DEF
uint32_t MouseButtonEvent::get_time() const noexcept
{
  return event.timestamp;
}

// ** MOUSE MOTION EVENT *******************************************************

CENTURION_DEF
MouseMotionEvent::MouseMotionEvent(SDL_MouseMotionEvent motionEvent) noexcept
    : event{motionEvent}
{}

CENTURION_DEF
int MouseMotionEvent::get_x() const noexcept
{
  return event.x;
}

CENTURION_DEF
int MouseMotionEvent::get_y() const noexcept
{
  return event.y;
}

CENTURION_DEF
int MouseMotionEvent::get_x_movement() const noexcept
{
  return event.xrel;
}

CENTURION_DEF
int MouseMotionEvent::get_y_movement() const noexcept
{
  return event.yrel;
}

CENTURION_DEF
bool MouseMotionEvent::was_touch() const noexcept
{
  return event.which == SDL_TOUCH_MOUSEID;
}

CENTURION_DEF
bool MouseMotionEvent::is_button_down(MouseButton button) const noexcept
{
  return event.state & static_cast<unsigned>(button);
}

CENTURION_DEF
uint32_t MouseMotionEvent::get_window_id() const noexcept
{
  return event.windowID;
}

CENTURION_DEF
uint32_t MouseMotionEvent::get_time() const noexcept
{
  return event.timestamp;
}

// ** MOUSE WHEEL EVENT ********************************************************

CENTURION_DEF
MouseWheelEvent::MouseWheelEvent(SDL_MouseWheelEvent wheelEvent) noexcept
    : event{wheelEvent}
{}

CENTURION_DEF
int MouseWheelEvent::get_horizontal_scroll() const noexcept
{
  return event.x;
}

CENTURION_DEF
int MouseWheelEvent::get_vertical_scroll() const noexcept
{
  return event.y;
}

CENTURION_DEF
MouseWheelDirection MouseWheelEvent::get_wheel_direction() const noexcept
{
  return static_cast<MouseWheelDirection>(event.direction);
}

CENTURION_DEF
bool MouseWheelEvent::was_touch() const noexcept
{
  return event.which == SDL_TOUCH_MOUSEID;
}

CENTURION_DEF
uint32_t MouseWheelEvent::get_window_id() const noexcept
{
  return event.windowID;
}

CENTURION_DEF
uint32_t MouseWheelEvent::get_time() const noexcept
{
  return event.timestamp;
}

// ** QUIT EVENT ***************************************************************

CENTURION_DEF
QuitEvent::QuitEvent(SDL_QuitEvent quitEvent) noexcept
    : time{quitEvent.timestamp}
{}

CENTURION_DEF
uint32_t QuitEvent::get_time() const noexcept
{
  return time;
}

// ** EVENT ********************************************************************

CENTURION_DEF
Event::Event(const SDL_Event& sdlEvent) noexcept : event{sdlEvent}
{}

CENTURION_DEF
void Event::refresh() noexcept
{
  SDL_PumpEvents();
}

CENTURION_DEF
void Event::push(Event& event) noexcept
{
  SDL_Event& sdlEvent = event;
  SDL_PushEvent(&sdlEvent);
}

CENTURION_DEF
void Event::flush() noexcept
{
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

CENTURION_DEF
void Event::flush_all() noexcept
{
  SDL_PumpEvents();
  SDL_FlushEvents(SDL_FIRSTEVENT, SDL_LASTEVENT);
}

CENTURION_DEF
bool Event::poll() noexcept
{
  return SDL_PollEvent(&event);
}

CENTURION_DEF
EventType Event::get_type() const noexcept
{
  return static_cast<EventType>(event.type);
}

CENTURION_DEF
KeyEvent Event::as_key_event() const noexcept
{
  return KeyEvent{event.key};
}

CENTURION_DEF
MouseButtonEvent Event::as_mouse_button_event() const noexcept
{
  return MouseButtonEvent{event.button};
}

CENTURION_DEF
MouseMotionEvent Event::as_mouse_motion_event() const noexcept
{
  return MouseMotionEvent{event.motion};
}

CENTURION_DEF
MouseWheelEvent Event::as_mouse_wheel_event() const noexcept
{
  return MouseWheelEvent{event.wheel};
}

CENTURION_DEF
QuitEvent Event::as_quit_event() const noexcept
{
  return QuitEvent{event.quit};
}

CENTURION_DEF
Event::operator SDL_Event&() noexcept
{
  return event;
}

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_EVENT_SOURCE