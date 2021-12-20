#include <gtest/gtest.h>

#include <iostream>  // clog

#include "common.hpp"
#include "event.hpp"

using Type = cen::EventType;

TEST(EventType, Values)
{
  ASSERT_EQ(ToUnderlying(Type::Quit), SDL_QUIT);

  ASSERT_EQ(ToUnderlying(Type::AppTerminating), SDL_APP_TERMINATING);
  ASSERT_EQ(ToUnderlying(Type::AppLowMemory), SDL_APP_LOWMEMORY);
  ASSERT_EQ(ToUnderlying(Type::AppWillEnterBackground), SDL_APP_WILLENTERBACKGROUND);
  ASSERT_EQ(ToUnderlying(Type::AppDidEnterBackground), SDL_APP_DIDENTERBACKGROUND);
  ASSERT_EQ(ToUnderlying(Type::AppDidEnterForeground), SDL_APP_DIDENTERFOREGROUND);

  ASSERT_EQ(ToUnderlying(Type::Display), SDL_DISPLAYEVENT);
  ASSERT_EQ(ToUnderlying(Type::Window), SDL_WINDOWEVENT);
  ASSERT_EQ(ToUnderlying(Type::System), SDL_SYSWMEVENT);

  ASSERT_EQ(ToUnderlying(Type::KeyDown), SDL_KEYDOWN);
  ASSERT_EQ(ToUnderlying(Type::KeyUp), SDL_KEYUP);
  ASSERT_EQ(ToUnderlying(Type::TextEditing), SDL_TEXTEDITING);
  ASSERT_EQ(ToUnderlying(Type::TextInput), SDL_TEXTINPUT);
  ASSERT_EQ(ToUnderlying(Type::KeymapChanged), SDL_KEYMAPCHANGED);

  ASSERT_EQ(ToUnderlying(Type::MouseMotion), SDL_MOUSEMOTION);
  ASSERT_EQ(ToUnderlying(Type::MouseButtonDown), SDL_MOUSEBUTTONDOWN);
  ASSERT_EQ(ToUnderlying(Type::MouseButtonUp), SDL_MOUSEBUTTONUP);
  ASSERT_EQ(ToUnderlying(Type::MouseWheel), SDL_MOUSEWHEEL);

  ASSERT_EQ(ToUnderlying(Type::JoyAxisMotion), SDL_JOYAXISMOTION);
  ASSERT_EQ(ToUnderlying(Type::JoyBallMotion), SDL_JOYBALLMOTION);
  ASSERT_EQ(ToUnderlying(Type::JoyHatMotion), SDL_JOYHATMOTION);
  ASSERT_EQ(ToUnderlying(Type::JoyButtonDown), SDL_JOYBUTTONDOWN);
  ASSERT_EQ(ToUnderlying(Type::JoyButtonUp), SDL_JOYBUTTONUP);
  ASSERT_EQ(ToUnderlying(Type::JoyDeviceAdded), SDL_JOYDEVICEADDED);
  ASSERT_EQ(ToUnderlying(Type::JoyDeviceRemoved), SDL_JOYDEVICEREMOVED);

  ASSERT_EQ(ToUnderlying(Type::ControllerAxisMotion), SDL_CONTROLLERAXISMOTION);
  ASSERT_EQ(ToUnderlying(Type::ControllerButtonDown), SDL_CONTROLLERBUTTONDOWN);
  ASSERT_EQ(ToUnderlying(Type::ControllerButtonUp), SDL_CONTROLLERBUTTONUP);
  ASSERT_EQ(ToUnderlying(Type::ControllerDeviceAdded), SDL_CONTROLLERDEVICEADDED);
  ASSERT_EQ(ToUnderlying(Type::ControllerDeviceRemoved), SDL_CONTROLLERDEVICEREMOVED);
  ASSERT_EQ(ToUnderlying(Type::ControllerDeviceRemapped), SDL_CONTROLLERDEVICEREMAPPED);

  ASSERT_EQ(ToUnderlying(Type::FingerDown), SDL_FINGERDOWN);
  ASSERT_EQ(ToUnderlying(Type::FingerUp), SDL_FINGERUP);
  ASSERT_EQ(ToUnderlying(Type::FingerMotion), SDL_FINGERMOTION);

  ASSERT_EQ(ToUnderlying(Type::DollarGesture), SDL_DOLLARGESTURE);
  ASSERT_EQ(ToUnderlying(Type::DollarRecord), SDL_DOLLARRECORD);
  ASSERT_EQ(ToUnderlying(Type::MultiGesture), SDL_MULTIGESTURE);

  ASSERT_EQ(ToUnderlying(Type::ClipboardUpdate), SDL_CLIPBOARDUPDATE);

  ASSERT_EQ(ToUnderlying(Type::DropFile), SDL_DROPFILE);
  ASSERT_EQ(ToUnderlying(Type::DropText), SDL_DROPTEXT);
  ASSERT_EQ(ToUnderlying(Type::DropBegin), SDL_DROPBEGIN);
  ASSERT_EQ(ToUnderlying(Type::DropComplete), SDL_DROPCOMPLETE);

  ASSERT_EQ(ToUnderlying(Type::AudioDeviceAdded), SDL_AUDIODEVICEADDED);
  ASSERT_EQ(ToUnderlying(Type::AudioDeviceRemoved), SDL_AUDIODEVICEREMOVED);

  ASSERT_EQ(ToUnderlying(Type::SensorUpdate), SDL_SENSORUPDATE);

  ASSERT_EQ(ToUnderlying(Type::RenderTargetsReset), SDL_RENDER_TARGETS_RESET);
  ASSERT_EQ(ToUnderlying(Type::RenderDeviceReset), SDL_RENDER_DEVICE_RESET);

  ASSERT_EQ(ToUnderlying(Type::User), SDL_USEREVENT);

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ(ToUnderlying(Type::LocaleChanged), SDL_LOCALECHANGED);

  ASSERT_EQ(ToUnderlying(Type::ControllerTouchpadDown), SDL_CONTROLLERTOUCHPADDOWN);
  ASSERT_EQ(ToUnderlying(Type::ControllerTouchpadUp), SDL_CONTROLLERTOUCHPADUP);
  ASSERT_EQ(ToUnderlying(Type::ControllerTouchpadMotion), SDL_CONTROLLERTOUCHPADMOTION);
  ASSERT_EQ(ToUnderlying(Type::ControllerSensorUpdate), SDL_CONTROLLERSENSORUPDATE);
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
}

TEST(EventType, ToString)
{
  ASSERT_EQ("Quit", to_string(Type::Quit));

  ASSERT_EQ("AppTerminating", to_string(Type::AppTerminating));
  ASSERT_EQ("AppLowMemory", to_string(Type::AppLowMemory));
  ASSERT_EQ("AppWillEnterBackground", to_string(Type::AppWillEnterBackground));
  ASSERT_EQ("AppDidEnterBackground", to_string(Type::AppDidEnterBackground));
  ASSERT_EQ("AppDidEnterForeground", to_string(Type::AppDidEnterForeground));

  ASSERT_EQ("Display", to_string(Type::Display));
  ASSERT_EQ("Window", to_string(Type::Window));
  ASSERT_EQ("System", to_string(Type::System));

  ASSERT_EQ("KeyDown", to_string(Type::KeyDown));
  ASSERT_EQ("KeyUp", to_string(Type::KeyUp));
  ASSERT_EQ("TextEditing", to_string(Type::TextEditing));
  ASSERT_EQ("TextInput", to_string(Type::TextInput));
  ASSERT_EQ("KeymapChanged", to_string(Type::KeymapChanged));

  ASSERT_EQ("MouseMotion", to_string(Type::MouseMotion));
  ASSERT_EQ("MouseButtonDown", to_string(Type::MouseButtonDown));
  ASSERT_EQ("MouseButtonUp", to_string(Type::MouseButtonUp));
  ASSERT_EQ("MouseWheel", to_string(Type::MouseWheel));

  ASSERT_EQ("JoyAxisMotion", to_string(Type::JoyAxisMotion));
  ASSERT_EQ("JoyBallMotion", to_string(Type::JoyBallMotion));
  ASSERT_EQ("JoyHatMotion", to_string(Type::JoyHatMotion));
  ASSERT_EQ("JoyButtonDown", to_string(Type::JoyButtonDown));
  ASSERT_EQ("JoyButtonUp", to_string(Type::JoyButtonUp));
  ASSERT_EQ("JoyDeviceAdded", to_string(Type::JoyDeviceAdded));
  ASSERT_EQ("JoyDeviceRemoved", to_string(Type::JoyDeviceRemoved));

  ASSERT_EQ("ControllerAxisMotion", to_string(Type::ControllerAxisMotion));
  ASSERT_EQ("ControllerButtonDown", to_string(Type::ControllerButtonDown));
  ASSERT_EQ("ControllerButtonUp", to_string(Type::ControllerButtonUp));
  ASSERT_EQ("ControllerDeviceAdded", to_string(Type::ControllerDeviceAdded));
  ASSERT_EQ("ControllerDeviceRemoved", to_string(Type::ControllerDeviceRemoved));
  ASSERT_EQ("ControllerDeviceRemapped", to_string(Type::ControllerDeviceRemapped));

  ASSERT_EQ("FingerDown", to_string(Type::FingerDown));
  ASSERT_EQ("FingerUp", to_string(Type::FingerUp));
  ASSERT_EQ("FingerMotion", to_string(Type::FingerMotion));

  ASSERT_EQ("DollarGesture", to_string(Type::DollarGesture));
  ASSERT_EQ("DollarRecord", to_string(Type::DollarRecord));
  ASSERT_EQ("MultiGesture", to_string(Type::MultiGesture));

  ASSERT_EQ("ClipboardUpdate", to_string(Type::ClipboardUpdate));

  ASSERT_EQ("DropFile", to_string(Type::DropFile));
  ASSERT_EQ("DropText", to_string(Type::DropText));
  ASSERT_EQ("DropBegin", to_string(Type::DropBegin));
  ASSERT_EQ("DropComplete", to_string(Type::DropComplete));

  ASSERT_EQ("AudioDeviceAdded", to_string(Type::AudioDeviceAdded));
  ASSERT_EQ("AudioDeviceRemoved", to_string(Type::AudioDeviceRemoved));

  ASSERT_EQ("SensorUpdate", to_string(Type::SensorUpdate));

  ASSERT_EQ("RenderTargetsReset", to_string(Type::RenderTargetsReset));
  ASSERT_EQ("RenderDeviceReset", to_string(Type::RenderDeviceReset));

  ASSERT_EQ("User", to_string(Type::User));

#if SDL_VERSION_ATLEAST(2, 0, 14)
  ASSERT_EQ("LocaleChanged", to_string(Type::LocaleChanged));

  ASSERT_EQ("ControllerTouchpadDown", to_string(Type::ControllerTouchpadDown));
  ASSERT_EQ("ControllerTouchpadUp", to_string(Type::ControllerTouchpadUp));
  ASSERT_EQ("ControllerTouchpadMotion", to_string(Type::ControllerTouchpadMotion));
  ASSERT_EQ("ControllerSensorUpdate", to_string(Type::ControllerSensorUpdate));
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  std::clog << "Event type example: " << Type::AppLowMemory << '\n';
}
