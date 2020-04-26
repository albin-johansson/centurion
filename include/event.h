#ifndef CENTURION_NEW_EVENT_HEADER
#define CENTURION_NEW_EVENT_HEADER

#include <SDL_events.h>

#include <cstdint>
#include <utility>
#include <variant>

#include "base_event.h"
#include "button_state.h"
#include "centurion_api.h"
#include "keyboard_event.h"
#include "quit_event.h"

namespace centurion {
namespace event {

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

class SysWMEvent : public TEvent<SDL_SysWMEvent> {
};

class TextEditingEvent : public TEvent<SDL_TextEditingEvent> {
};

class TextInputEvent : public TEvent<SDL_TextInputEvent> {
};

class UserEvent : public TEvent<SDL_UserEvent> {
};

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_NEW_EVENT_HEADER // TODO fix this include guard name