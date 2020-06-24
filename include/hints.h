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

#ifndef CENTURION_HINTS_HEADER
#define CENTURION_HINTS_HEADER

#include <SDL_hints.h>
#include <log.h>

#include <cstring>

#include "centurion_api.h"
#include "centurion_utils.h"

namespace centurion {
namespace hint {

// TODO finish 4.1

enum class HintPrio {
  Default = SDL_HINT_DEFAULT,
  Normal = SDL_HINT_NORMAL,
  Override = SDL_HINT_OVERRIDE
};

class RenderDriver final {
 public:
  enum Value { Direct3D, OpenGL, OpenGLES, OpenGLES2, Metal, Software };

  template <typename T>
  static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, Value>::value;
  }

  static constexpr CZString name() noexcept { return SDL_HINT_RENDER_DRIVER; }

  static Optional<Value> current_value() noexcept
  {
    CZString hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    const std::string current{hint};
    if (current == "direct3d") {
      return Direct3D;
    } else if (current == "opengl") {
      return OpenGL;
    } else if (current == "opengles") {
      return OpenGLES;
    } else if (current == "opengles2") {
      return OpenGLES2;
    } else if (current == "metal") {
      return Metal;
    } else {
      return Software;
    }
  }

  static std::string to_string(Value value) noexcept
  {
    switch (value) {
      case Direct3D:
        return "direct3d";
      case OpenGL:
        return "opengl";
      case OpenGLES:
        return "opengles";
      case OpenGLES2:
        return "opengles2";
      case Metal:
        return "metal";
      default: {
        Log::warn("Failed to convert RenderDriver value to string: %i",
                  static_cast<int>(value));
      }  // fallthrough
      case Software:
        return "software";
    }
  }
};

class AudioResamplingMode final {
 public:
  enum Value { Default = 0, Fast = 1, Medium = 2, Best = 3 };

  template <typename T>
  static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, Value>::value;
  }

  static constexpr CZString name() noexcept
  {
    return SDL_HINT_AUDIO_RESAMPLING_MODE;
  }

  static Optional<Value> current_value() noexcept
  {
    const CZString hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    if (std::strcmp(hint, "default") == 0) {
      return Default;

    } else if (std::strcmp(hint, "fast") == 0) {
      return Fast;

    } else if (std::strcmp(hint, "medium") == 0) {
      return Medium;

    } else if (std::strcmp(hint, "best") == 0) {
      return Best;

    } else {
      Log::warn("Did not recognize AudioResamplingMode value: %s", hint);
      return Default;
    }
  }

  static std::string to_string(Value value) noexcept
  {
    switch (value) {
      case Default:
        return "default";
      case Fast:
        return "fast";
      case Medium:
        return "medium";
      case Best:
        return "best";
      default: {
        Log::warn(
            "Failed to convert AudioResamplingModeHint value to string: %i",
            static_cast<int>(value));
        return "default";
      }
    }
  }
};

class ScaleQuality final {
 public:
  enum Value { Nearest = 0, Linear = 1, Best = 2 };

  template <typename T>
  static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, Value>::value;
  }

  static constexpr CZString name() noexcept
  {
    return SDL_HINT_RENDER_SCALE_QUALITY;
  }

  static Optional<Value> current_value() noexcept
  {
    const CZString hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    if (std::strcmp(hint, "nearest") == 0) {
      return Nearest;

    } else if (std::strcmp(hint, "linear") == 0) {
      return Linear;

    } else if (std::strcmp(hint, "best") == 0) {
      return Best;

    } else {
      Log::warn("Did not recognize ScaleQuality value: %s", hint);
      return Nearest;
    }
  }

  static std::string to_string(Value value) noexcept
  {
    switch (value) {
      case Nearest:
        return "nearest";
      case Linear:
        return "linear";
      case Best:
        return "best";
      default: {
        Log::warn("Failed to convert ScaleQuality value to string: %i",
                  static_cast<int>(value));
        return "nearest";
      }
    }
  }
};

class FramebufferAcceleration final {
 public:
  enum Value {
    Off,
    On,
    Direct3D,
    OpenGL,
    OpenGLES,
    OpenGLES2,
    Metal,
    Software
  };

  template <typename T>
  static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, Value>::value;
  }

  static constexpr CZString name() noexcept
  {
    return SDL_HINT_FRAMEBUFFER_ACCELERATION;
  }

  static Optional<Value> current_value() noexcept
  {
    const CZString hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    const std::string current{hint};
    if (current == "0") {
      return Off;
    } else if (current == "1") {
      return On;
    } else if (current == "direct3d") {
      return Direct3D;
    } else if (current == "opengl") {
      return OpenGL;
    } else if (current == "opengles") {
      return OpenGLES;
    } else if (current == "opengles2") {
      return OpenGLES2;
    } else if (current == "metal") {
      return Metal;
    } else {
      return Software;
    }
  }

  static std::string to_string(Value value) noexcept
  {
    switch (value) {
      case Off:
        return "0";
      case On:
        return "1";
      case Direct3D:
        return "direct3d";
      case OpenGL:
        return "opengl";
      case OpenGLES:
        return "opengles";
      case OpenGLES2:
        return "opengles2";
      case Metal:
        return "metal";
      case Software:
        return "software";
      default: {
        Log::warn(
            "Failed to convert FramebufferAcceleration value to string: %i",
            static_cast<int>(value));
        return "0";
      }
    }
  }
};

namespace detail {

template <typename Derived, typename Arg>
class CRTPHint {
 public:
  template <typename T>
  CENTURION_NODISCARD static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, Arg>::value;
  }

  CENTURION_NODISCARD static constexpr CZString name() noexcept
  {
    return Derived::name();
  }

  CENTURION_NODISCARD static Optional<Arg> value() noexcept
  {
    return Derived::current_value();
  }

  CENTURION_NODISCARD static std::string to_string(Arg value) noexcept
  {
    return std::to_string(value);
  }
};

// A hint class that only accepts booleans
template <typename Hint>
class BoolHint : public CRTPHint<BoolHint<Hint>, bool> {
 public:
  template <typename T>
  CENTURION_NODISCARD static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, bool>::value;
  }

  CENTURION_NODISCARD
  static Optional<bool> current_value() noexcept
  {
    const CZString value = SDL_GetHint(Hint::name());
    if (!value) {
      return nothing;
    } else {
      return std::strcmp(value, "1") == 0;
    }
  }

  CENTURION_NODISCARD
  static std::string to_string(bool value) noexcept
  {
    return value ? "1" : "0";
  }
};

// A hint class that only accepts strings
template <typename Hint>
class StringHint : public CRTPHint<StringHint<Hint>, CZString> {
 public:
  template <typename T>
  CENTURION_NODISCARD static constexpr bool valid_arg() noexcept
  {
    return std::is_convertible<T, CZString>::value;
  }

  CENTURION_NODISCARD
  static Optional<CZString> current_value() noexcept
  {
    const CZString value = SDL_GetHint(Hint::name());
    if (!value) {
      return nothing;
    } else {
      return value;
    }
  }

  CENTURION_NODISCARD
  static std::string to_string(CZString value) { return value; }
};

// A hint class that only accepts integers
template <typename Hint>
class IntHint : public CRTPHint<IntHint<Hint>, int> {
 public:
  template <typename T>
  CENTURION_NODISCARD static constexpr bool valid_arg() noexcept
  {
    return std::is_convertible<T, int>::value;
  }

  CENTURION_NODISCARD
  static Optional<int> current_value() noexcept
  {
    const CZString value = SDL_GetHint(Hint::name());
    if (!value) {
      return nothing;
    } else {
      return std::stoi(value);
    }
  }
};

}  // namespace detail

#define CENTURION_HINT(Name, SDLName, Type)                       \
  class Name final : public detail::Type<Name> {                  \
   public:                                                        \
    CENTURION_NODISCARD static constexpr CZString name() noexcept \
    {                                                             \
      return SDLName;                                             \
    }                                                             \
  };

CENTURION_HINT(AccelerometerAsJoystick,
               SDL_HINT_ACCELEROMETER_AS_JOYSTICK,
               BoolHint)

CENTURION_HINT(AllowTopMost, SDL_HINT_ALLOW_TOPMOST, BoolHint)

CENTURION_HINT(AndroidBlockOnPause, SDL_HINT_ANDROID_BLOCK_ON_PAUSE, BoolHint)

CENTURION_HINT(AndroidTrapBackButton,
               SDL_HINT_ANDROID_TRAP_BACK_BUTTON,
               BoolHint)

CENTURION_HINT(AppleTVControllerUIEvents,
               SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS,
               BoolHint)

CENTURION_HINT(AppleTVRemoteAllowRotation,
               SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION,
               BoolHint)

CENTURION_HINT(BMPSaveLegacyFormat, SDL_HINT_BMP_SAVE_LEGACY_FORMAT, BoolHint)

CENTURION_HINT(DoubleBuffer, SDL_HINT_VIDEO_DOUBLE_BUFFER, BoolHint)

CENTURION_HINT(DisplayUsableBounds, SDL_HINT_DISPLAY_USABLE_BOUNDS, StringHint)

CENTURION_HINT(EnableSteamControllers,
               SDL_HINT_ENABLE_STEAM_CONTROLLERS,
               BoolHint)

CENTURION_HINT(GameControllerUseButtonLabels,
               SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS,
               BoolHint)

CENTURION_HINT(GameControllerType, SDL_HINT_GAMECONTROLLERTYPE, StringHint)

CENTURION_HINT(GameControllerConfig, SDL_HINT_GAMECONTROLLERCONFIG, StringHint)

CENTURION_HINT(GameControllerConfigFile,
               SDL_HINT_GAMECONTROLLERCONFIG_FILE,
               StringHint)

CENTURION_HINT(GameControllerIgnoreDevices,
               SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES,
               StringHint)

CENTURION_HINT(GameControllerIgnoreDevicesExcept,
               SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT,
               StringHint)

CENTURION_HINT(GrabKeyboard, SDL_HINT_GRAB_KEYBOARD, BoolHint)

CENTURION_HINT(IdleTimerDisabled, SDL_HINT_IDLE_TIMER_DISABLED, BoolHint)

CENTURION_HINT(IMEInternalEditing, SDL_HINT_IME_INTERNAL_EDITING, BoolHint)

CENTURION_HINT(JoystickAllowBackgroundEvents,
               SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,
               BoolHint)

CENTURION_HINT(JoystickUseHIDAPI, SDL_HINT_JOYSTICK_HIDAPI, BoolHint)

CENTURION_HINT(JoystickUseHIDAPIPS4, SDL_HINT_JOYSTICK_HIDAPI_PS4, BoolHint)

CENTURION_HINT(JoystickUseHIDAPIRumble,
               SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE,
               BoolHint)

CENTURION_HINT(JoystickUseHIDAPISteam, SDL_HINT_JOYSTICK_HIDAPI_STEAM, BoolHint)

CENTURION_HINT(JoystickUseHIDAPISwitch,
               SDL_HINT_JOYSTICK_HIDAPI_SWITCH,
               BoolHint)

CENTURION_HINT(JoystickUseHIDAPIXbox, SDL_HINT_JOYSTICK_HIDAPI_XBOX, BoolHint)

CENTURION_HINT(JoystickUseHIDAPIGameCube,
               SDL_HINT_JOYSTICK_HIDAPI_GAMECUBE,
               BoolHint)

CENTURION_HINT(MacBackgroundApp, SDL_HINT_MAC_BACKGROUND_APP, BoolHint)

CENTURION_HINT(MacCTRLClickEmulateRightClick,
               SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK,
               BoolHint)

CENTURION_HINT(MouseFocusClickthrough,
               SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH,
               BoolHint)

CENTURION_HINT(MouseRelativeModeWarp,
               SDL_HINT_MOUSE_RELATIVE_MODE_WARP,
               BoolHint)

CENTURION_HINT(NoSignalHandlers, SDL_HINT_NO_SIGNAL_HANDLERS, BoolHint)

CENTURION_HINT(Direct3D11Debug, SDL_HINT_RENDER_DIRECT3D11_DEBUG, BoolHint)

CENTURION_HINT(Direct3DThreadSafe,
               SDL_HINT_RENDER_DIRECT3D_THREADSAFE,
               BoolHint)

CENTURION_HINT(OpenGLESDriver, SDL_HINT_OPENGL_ES_DRIVER, BoolHint)

CENTURION_HINT(EnableOpenGLShaders, SDL_HINT_RENDER_OPENGL_SHADERS, BoolHint)

CENTURION_HINT(EnableVSync, SDL_HINT_RENDER_VSYNC, BoolHint)

CENTURION_HINT(AllowScreensaver, SDL_HINT_VIDEO_ALLOW_SCREENSAVER, BoolHint)

CENTURION_HINT(VideoExternalContext, SDL_HINT_VIDEO_EXTERNAL_CONTEXT, BoolHint)

CENTURION_HINT(DisableHighDPI, SDL_HINT_VIDEO_HIGHDPI_DISABLED, BoolHint)

CENTURION_HINT(MacFullscreenSpaces,
               SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES,
               BoolHint)

CENTURION_HINT(MinimizeOnFocusLoss,
               SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS,
               BoolHint)

CENTURION_HINT(X11NetWMPing, SDL_HINT_VIDEO_X11_NET_WM_PING, BoolHint)

CENTURION_HINT(X11XNetWMBypassCompositor,
               SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR,
               BoolHint)

CENTURION_HINT(X11ForceEGL, SDL_HINT_VIDEO_X11_FORCE_EGL, BoolHint)

CENTURION_HINT(X11Xinerama, SDL_HINT_VIDEO_X11_XINERAMA, BoolHint)

CENTURION_HINT(X11XRandR, SDL_HINT_VIDEO_X11_XRANDR, BoolHint)

CENTURION_HINT(X11XVidMode, SDL_HINT_VIDEO_X11_XVIDMODE, BoolHint)

CENTURION_HINT(WindowsDisableThreadNaming,
               SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING,
               BoolHint)

CENTURION_HINT(WindowsEnableMessageLoop,
               SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP,
               BoolHint)

CENTURION_HINT(WindowsNoCloseOnAltF4,
               SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4,
               BoolHint)

CENTURION_HINT(WindowFrameUsableWhileCursorHidden,
               SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN,
               BoolHint)

CENTURION_HINT(WinRTPrivacyPolicyLabel,
               SDL_HINT_WINRT_PRIVACY_POLICY_LABEL,
               StringHint)

CENTURION_HINT(WinRTPrivacyPolicyURL,
               SDL_HINT_WINRT_PRIVACY_POLICY_URL,
               StringHint)

CENTURION_HINT(MouseTouchEvents, SDL_HINT_MOUSE_TOUCH_EVENTS, BoolHint)

CENTURION_HINT(RenderBatching, SDL_HINT_RENDER_BATCHING, BoolHint)

CENTURION_HINT(ReturnKeyHidesIME, SDL_HINT_RETURN_KEY_HIDES_IME, BoolHint)

CENTURION_HINT(TouchMouseEvents, SDL_HINT_TOUCH_MOUSE_EVENTS, BoolHint)

CENTURION_HINT(TVRemoteAsJoystick, SDL_HINT_TV_REMOTE_AS_JOYSTICK, BoolHint)

CENTURION_HINT(XinputEnabled, SDL_HINT_XINPUT_ENABLED, BoolHint)

CENTURION_HINT(XinputUseOldJoystickMapping,
               SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING,
               BoolHint)

/**
 * Sets the value of the specified hint. This method will only accept values
 * that are related to the specified hint, supplying the wrong kind of value
 * causes a compile-time error. See the related hint class for more details
 * about the associated value type.
 *
 * @tparam Hint the type of the hint that will be modified.
 * @tparam priority the priority that will be used, defaults to
 * <code>Normal</code>.
 * @tparam Value the type of the hint value.
 * @param value the new value that will be set for the specified hint.
 * @return true if the hint was successfully set; false otherwise.
 * @since 0.1.0
 */
template <
    typename Hint,
    HintPrio priority = HintPrio::Normal,
    typename Value,
    typename = centurion::detail::type_if<Hint::template valid_arg<Value>()>>
bool set_hint(const Value& value) noexcept  // TODO rename type_if -> if_t
{
  return static_cast<bool>(
      SDL_SetHintWithPriority(Hint::name(),
                              Hint::to_string(value).c_str(),
                              static_cast<SDL_HintPriority>(priority)));
}

/**
 * Returns the current value of the specified hint. This method returns an
 * <code>Optional</code> of the hint value type.
 *
 * @tparam Hint the type of the Hint to obtain the value of.
 * @return the current value of the specified hint; nothing if there is no
 * value set for the hint.
 * @since 0.1.0
 */
template <typename Hint>
decltype(auto) get_hint() noexcept
{
  return Hint::current_value();
}

}  // namespace hint
}  // namespace centurion

#undef CENTURION_BOOL_HINT
#endif  // CENTURION_HINTS_HEADER
