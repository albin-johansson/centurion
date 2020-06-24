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

enum RenderDriverHint {
  Direct3D,
  OpenGL,
  OpenGLES,
  OpenGLES2,
  Metal,
  Software
};

class RenderDriver final {
 public:
  template <typename T>
  static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, RenderDriverHint>::value;
  }

  static constexpr CZString name() noexcept { return SDL_HINT_RENDER_DRIVER; }

  static Optional<RenderDriverHint> current_value() noexcept
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

  static std::string to_string(RenderDriverHint value) noexcept
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
        Log::warn("Failed to convert RenderDriverHint value to string: %i",
                  static_cast<int>(value));
      }  // fallthrough
      case Software:
        return "software";
    }
  }
};  // namespace hint

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

template <typename Hint>
class BoolHint : public CRTPHint<BoolHint<Hint>, bool> {
 public:
  template <typename T>
  CENTURION_NODISCARD static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, bool>::value;
  }

  CENTURION_NODISCARD
  static Optional<bool> current_value()
  {
    CZString value = SDL_GetHint(Hint::name());
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

#define CENTURION_BOOL_HINT(Type, SDLHint)                        \
  class Type final : public detail::BoolHint<Type> {              \
   public:                                                        \
    CENTURION_NODISCARD static constexpr CZString name() noexcept \
    {                                                             \
      return SDLHint;                                             \
    }                                                             \
  };

}  // namespace detail

CENTURION_BOOL_HINT(AccelerometerAsJoystick, SDL_HINT_ACCELEROMETER_AS_JOYSTICK)

CENTURION_BOOL_HINT(AllowTopMost, SDL_HINT_ALLOW_TOPMOST)

CENTURION_BOOL_HINT(AndroidBlockOnPause, SDL_HINT_ANDROID_BLOCK_ON_PAUSE)

CENTURION_BOOL_HINT(AndroidTrapBackButton, SDL_HINT_ANDROID_TRAP_BACK_BUTTON)

CENTURION_BOOL_HINT(AppleTVControllerUIEvents,
                    SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS)

CENTURION_BOOL_HINT(AppleTVRemoteAllowRotation,
                    SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION)

CENTURION_BOOL_HINT(BMPSaveLegacyFormat, SDL_HINT_BMP_SAVE_LEGACY_FORMAT)

CENTURION_BOOL_HINT(DoubleBuffer, SDL_HINT_VIDEO_DOUBLE_BUFFER)

CENTURION_BOOL_HINT(EnableSteamControllers, SDL_HINT_ENABLE_STEAM_CONTROLLERS)

CENTURION_BOOL_HINT(GamecontrollerUseButtonLabels,
                    SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS)

CENTURION_BOOL_HINT(GrabKeyboard, SDL_HINT_GRAB_KEYBOARD)

// CENTURION_BOOL_HINT(FramebufferAcceleration,
// SDL_HINT_FRAMEBUFFER_ACCELERATION)

CENTURION_BOOL_HINT(IdleTimerDisabled, SDL_HINT_IDLE_TIMER_DISABLED)

CENTURION_BOOL_HINT(IMEInternalEditing, SDL_HINT_IME_INTERNAL_EDITING)

CENTURION_BOOL_HINT(JoystickAllowBackgroundEvents,
                    SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS)

CENTURION_BOOL_HINT(JoystickUseHIDAPI, SDL_HINT_JOYSTICK_HIDAPI)

CENTURION_BOOL_HINT(JoystickUseHIDAPIPS4, SDL_HINT_JOYSTICK_HIDAPI_PS4)

CENTURION_BOOL_HINT(JoystickUseHIDAPIRumble,
                    SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE)

CENTURION_BOOL_HINT(JoystickUseHIDAPISteam, SDL_HINT_JOYSTICK_HIDAPI_STEAM)

CENTURION_BOOL_HINT(JoystickUseHIDAPISwitch, SDL_HINT_JOYSTICK_HIDAPI_SWITCH)

CENTURION_BOOL_HINT(JoystickUseHIDAPIXbox, SDL_HINT_JOYSTICK_HIDAPI_XBOX)

CENTURION_BOOL_HINT(JoystickUseHIDAPIGameCube,
                    SDL_HINT_JOYSTICK_HIDAPI_GAMECUBE)

CENTURION_BOOL_HINT(MacBackgroundApp, SDL_HINT_MAC_BACKGROUND_APP)

CENTURION_BOOL_HINT(MacCTRLClickEmulateRightClick,
                    SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK)

CENTURION_BOOL_HINT(MouseFocusClickthrough, SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH)

CENTURION_BOOL_HINT(MouseRelativeModeWarp, SDL_HINT_MOUSE_RELATIVE_MODE_WARP)

CENTURION_BOOL_HINT(NoSignalHandlers, SDL_HINT_NO_SIGNAL_HANDLERS)

CENTURION_BOOL_HINT(Direct3D11Debug, SDL_HINT_RENDER_DIRECT3D11_DEBUG)

CENTURION_BOOL_HINT(Direct3DThreadSafe, SDL_HINT_RENDER_DIRECT3D_THREADSAFE)

CENTURION_BOOL_HINT(OpenGLESDriver, SDL_HINT_OPENGL_ES_DRIVER)

CENTURION_BOOL_HINT(EnableOpenGLShaders, SDL_HINT_RENDER_OPENGL_SHADERS)

CENTURION_BOOL_HINT(EnableVSync, SDL_HINT_RENDER_VSYNC)

CENTURION_BOOL_HINT(AllowScreensaver, SDL_HINT_VIDEO_ALLOW_SCREENSAVER)

CENTURION_BOOL_HINT(VideoExternalContext, SDL_HINT_VIDEO_EXTERNAL_CONTEXT)

CENTURION_BOOL_HINT(DisableHighDPI, SDL_HINT_VIDEO_HIGHDPI_DISABLED)

CENTURION_BOOL_HINT(MacFullscreenSpaces, SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES)

CENTURION_BOOL_HINT(MinimizeOnFocusLoss, SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS)

CENTURION_BOOL_HINT(X11NetWMPing, SDL_HINT_VIDEO_X11_NET_WM_PING)

CENTURION_BOOL_HINT(X11XNetWMBypassCompositor,
                    SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR)

CENTURION_BOOL_HINT(X11ForceEGL, SDL_HINT_VIDEO_X11_FORCE_EGL)

CENTURION_BOOL_HINT(X11Xinerama, SDL_HINT_VIDEO_X11_XINERAMA)

CENTURION_BOOL_HINT(X11XRandR, SDL_HINT_VIDEO_X11_XRANDR)

CENTURION_BOOL_HINT(X11XVidMode, SDL_HINT_VIDEO_X11_XVIDMODE)

CENTURION_BOOL_HINT(WindowsDisableThreadNaming,
                    SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING)

CENTURION_BOOL_HINT(WindowsEnableMessageLoop,
                    SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP)

CENTURION_BOOL_HINT(WindowsNoCloseOnAltF4, SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4)

CENTURION_BOOL_HINT(WindowFrameUsableWhileCursorHidden,
                    SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN)

CENTURION_BOOL_HINT(MouseTouchEvents, SDL_HINT_MOUSE_TOUCH_EVENTS)

CENTURION_BOOL_HINT(RenderBatching, SDL_HINT_RENDER_BATCHING)

CENTURION_BOOL_HINT(ReturnKeyHidesIME, SDL_HINT_RETURN_KEY_HIDES_IME)

CENTURION_BOOL_HINT(TouchMouseEvents, SDL_HINT_TOUCH_MOUSE_EVENTS)

CENTURION_BOOL_HINT(TVRemoteAsJoystick, SDL_HINT_TV_REMOTE_AS_JOYSTICK)

CENTURION_BOOL_HINT(XinputEnabled, SDL_HINT_XINPUT_ENABLED)

CENTURION_BOOL_HINT(XinputUseOldJoystickMapping,
                    SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING)

// class AndroidAPKExpansionMainFileVersion
//    : public CRTPHint<AndroidAPKExpansionMainFileVersion, int> {
// public:
//  CENTURION_NODISCARD static constexpr CZString name() noexcept
//  {
//    return SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION;
//  }
//
//  CENTURION_NODISCARD static constexpr Optional<int> current_value()
//  {
//    return 0;
//  }
//};

// class AndroidAPKExpansionPatchFileVersion final {
// public:
//  template <typename T>
//  CENTURION_NODISCARD static constexpr bool valid_arg() noexcept
//  {
//    return std::is_same<T, int>::value;
//  }
//
//  CENTURION_NODISCARD static constexpr CZString name() noexcept
//  {
//    return SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION;
//  }
//
//  CENTURION_NODISCARD static Optional<int> value() noexcept
//  {
//    return hint_value_as_bool(name());
//  }
//
//  CENTURION_NODISCARD static std::string to_string(int value) noexcept
//  {
//    return std::to_string(value);
//  }
//};

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
