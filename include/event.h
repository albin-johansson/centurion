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

class AudioDeviceEvent : public BaseEvent<SDL_AudioDeviceEvent> {
 public:
};

class ControllerAxisEvent : public BaseEvent<SDL_ControllerAxisEvent> {
};

class ControllerButtonEvent : public BaseEvent<SDL_ControllerButtonEvent> {
};

class ControllerDeviceEvent : public BaseEvent<SDL_ControllerDeviceEvent> {
};

class DollarGestureEvent : public BaseEvent<SDL_DollarGestureEvent> {
};

class DropEvent : public BaseEvent<SDL_DropEvent> {
};

class TouchFingerEvent : public BaseEvent<SDL_TouchFingerEvent> {
};

class JoyAxisEvent : public BaseEvent<SDL_JoyAxisEvent> {
};

class JoyBallEvent : public BaseEvent<SDL_JoyBallEvent> {
};

class JoyHatEvent : public BaseEvent<SDL_JoyHatEvent> {
};

class JoyButtonEvent : public BaseEvent<SDL_JoyButtonEvent> {
};

class JoyDeviceEvent : public BaseEvent<SDL_JoyDeviceEvent> {
};

class MouseMotionEvent : public BaseEvent<SDL_MouseMotionEvent> {
};

class MouseButtonEvent : public BaseEvent<SDL_MouseButtonEvent> {
};

class MouseWheelEvent : public BaseEvent<SDL_MouseWheelEvent> {
};

class MultiGestureEvent : public BaseEvent<SDL_MultiGestureEvent> {
};

class SysWMEvent : public BaseEvent<SDL_SysWMEvent> {
};

class TextEditingEvent : public BaseEvent<SDL_TextEditingEvent> {
};

class TextInputEvent : public BaseEvent<SDL_TextInputEvent> {
};

class UserEvent : public BaseEvent<SDL_UserEvent> {
};

}  // namespace event
}  // namespace centurion

#endif  // CENTURION_NEW_EVENT_HEADER // TODO fix this include guard name