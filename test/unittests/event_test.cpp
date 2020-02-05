#include "catch.hpp"
#include "event.h"
#include <SDL.h>

using namespace centurion::event;

TEST_CASE("EventType enum values", "[EventType]") {
  CHECK(EventType::Quit == SDL_QUIT);
  CHECK(EventType::AppTerminating == SDL_APP_TERMINATING);
  CHECK(EventType::AppLowMemory == SDL_APP_LOWMEMORY);
  CHECK(EventType::AppWillEnterBackground == SDL_APP_WILLENTERBACKGROUND);
  CHECK(EventType::AppDidEnterBackground == SDL_APP_DIDENTERBACKGROUND);
  CHECK(EventType::AppDidEnterForeground == SDL_APP_DIDENTERFOREGROUND);
  CHECK(EventType::Display == SDL_DISPLAYEVENT);
  CHECK(EventType::Window == SDL_WINDOWEVENT);
  CHECK(EventType::System == SDL_SYSWMEVENT);
  CHECK(EventType::KeyDown == SDL_KEYDOWN);
  CHECK(EventType::KeyUp == SDL_KEYUP);
  CHECK(EventType::TextEditing == SDL_TEXTEDITING);
  CHECK(EventType::TextInput == SDL_TEXTINPUT);
  CHECK(EventType::KeymapChanged == SDL_KEYMAPCHANGED);
  CHECK(EventType::MouseMotion == SDL_MOUSEMOTION);
  CHECK(EventType::MouseButtonDown == SDL_MOUSEBUTTONDOWN);
  CHECK(EventType::MouseButtonUp == SDL_MOUSEBUTTONUP);
  CHECK(EventType::MouseWheel == SDL_MOUSEWHEEL);
  CHECK(EventType::JoystickAxisMotion == SDL_JOYAXISMOTION);
  CHECK(EventType::JoystickBallMotion == SDL_JOYBALLMOTION);
  CHECK(EventType::JoystickHatMotion == SDL_JOYHATMOTION);
  CHECK(EventType::JoystickButtonDown == SDL_JOYBUTTONDOWN);
  CHECK(EventType::JoystickButtonUp == SDL_JOYBUTTONUP);
  CHECK(EventType::JoystickDeviceAdded == SDL_JOYDEVICEADDED);
  CHECK(EventType::JoystickDeviceRemoved == SDL_JOYDEVICEREMOVED);
  CHECK(EventType::ControllerAxisMotion == SDL_CONTROLLERAXISMOTION);
  CHECK(EventType::ControllerButtonDown == SDL_CONTROLLERBUTTONDOWN);
  CHECK(EventType::ControllerButtonUp == SDL_CONTROLLERBUTTONUP);
  CHECK(EventType::ControllerDeviceAdded == SDL_CONTROLLERDEVICEADDED);
  CHECK(EventType::ControllerDeviceRemoved == SDL_CONTROLLERDEVICEREMOVED);
  CHECK(EventType::ControllerDeviceRemapped == SDL_CONTROLLERDEVICEREMAPPED);
  CHECK(EventType::TouchDown == SDL_FINGERDOWN);
  CHECK(EventType::TouchUp == SDL_FINGERUP);
  CHECK(EventType::TouchMotion == SDL_FINGERMOTION);
  CHECK(EventType::DollarGesture == SDL_DOLLARGESTURE);
  CHECK(EventType::DollarRecord == SDL_DOLLARRECORD);
  CHECK(EventType::MultiGesture == SDL_MULTIGESTURE);
  CHECK(EventType::ClipboardUpdate == SDL_CLIPBOARDUPDATE);
  CHECK(EventType::DropFile == SDL_DROPFILE);
  CHECK(EventType::DropText == SDL_DROPTEXT);
  CHECK(EventType::DropBegin == SDL_DROPBEGIN);
  CHECK(EventType::DropComplete == SDL_DROPCOMPLETE);
  CHECK(EventType::AudioDeviceAdded == SDL_AUDIODEVICEADDED);
  CHECK(EventType::AudioDeviceRemoved == SDL_AUDIODEVICEREMOVED);
  CHECK(EventType::SensorUpdate == SDL_SENSORUPDATE);
  CHECK(EventType::RenderTargetsReset == SDL_RENDER_TARGETS_RESET);
  CHECK(EventType::RenderDeviceReset == SDL_RENDER_DEVICE_RESET);
  CHECK(EventType::User == SDL_USEREVENT);
}

TEST_CASE("KeyModifier enum values", "[KeyModifier]") {
  CHECK(KeyModifier::None == KMOD_NONE);
  CHECK(KeyModifier::LeftShift == KMOD_LSHIFT);
  CHECK(KeyModifier::RightShift == KMOD_RSHIFT);
  CHECK(KeyModifier::LeftControl == KMOD_LCTRL);
  CHECK(KeyModifier::RightControl == KMOD_RCTRL);
  CHECK(KeyModifier::LeftAlt == KMOD_LALT);
  CHECK(KeyModifier::RightAlt == KMOD_RALT);
  CHECK(KeyModifier::LeftGUI == KMOD_LGUI);
  CHECK(KeyModifier::RightGUI == KMOD_RGUI);
  CHECK(KeyModifier::Num == KMOD_NUM);
  CHECK(KeyModifier::Caps == KMOD_CAPS);
  CHECK(KeyModifier::Mode == KMOD_MODE);

  CHECK(KMOD_NONE == KeyModifier::None);
  CHECK(KMOD_LSHIFT == KeyModifier::LeftShift);
  CHECK(KMOD_RSHIFT == KeyModifier::RightShift);
  CHECK(KMOD_LCTRL == KeyModifier::LeftControl);
  CHECK(KMOD_RCTRL == KeyModifier::RightControl);
  CHECK(KMOD_LALT == KeyModifier::LeftAlt);
  CHECK(KMOD_RALT == KeyModifier::RightAlt);
  CHECK(KMOD_LGUI == KeyModifier::LeftGUI);
  CHECK(KMOD_RGUI == KeyModifier::RightGUI);
  CHECK(KMOD_NUM == KeyModifier::Num);
  CHECK(KMOD_CAPS == KeyModifier::Caps);
  CHECK(KMOD_MODE == KeyModifier::Mode);
}

TEST_CASE("MouseButton enum values", "[MouseButton]") {
  CHECK(static_cast<int>(MouseButton::Left) == SDL_BUTTON_LEFT);
  CHECK(static_cast<int>(MouseButton::Middle) == SDL_BUTTON_MIDDLE);
  CHECK(static_cast<int>(MouseButton::Right) == SDL_BUTTON_RIGHT);
  CHECK(static_cast<int>(MouseButton::X1) == SDL_BUTTON_X1);
  CHECK(static_cast<int>(MouseButton::X2) == SDL_BUTTON_X2);
}