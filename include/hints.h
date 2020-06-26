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

/**
 * The <code>hints.h</code> header provides utilities related to managing
 * hints ("configuration variables" on the SDL2 wiki). Refer to the official
 * SDL2 wiki or the <code>SDL_hints.h</code> header for details regarding any
 * specific hint type.
 *
 * @file hints.h
 * @since 4.1.0
 */

#ifndef CENTURION_HINTS_HEADER
#define CENTURION_HINTS_HEADER

#include <SDL_hints.h>
#include <log.h>

#include <cstring>

#include "centurion_api.h"
#include "centurion_exception.h"
#include "centurion_utils.h"

namespace centurion {

/**
 * The <code>hint</code> namespace contains all of the Centurion components
 * related to hints (configuration variables).
 *
 * @namespace centurion::hint
 * @since 4.1.0
 */
namespace hint {

/// @cond FALSE

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
    return static_cast<bool>(SDL_GetHintBoolean(Hint::name(), SDL_FALSE));
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

class AudioCategory final {
 public:
  enum Value { Ambient, Playback };

  template <typename T>
  static constexpr bool valid_arg() noexcept
  {
    return std::is_same<T, Value>::value;
  }

  static constexpr CZString name() noexcept { return SDL_HINT_AUDIO_CATEGORY; }

  static Optional<Value> current_value() noexcept
  {
    const CZString hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    if (std::strcmp(hint, "ambient") == 0) {
      return Ambient;
    } else /*if (current == "playback")*/ {
      return Playback;
    }
  }

  static std::string to_string(Value value) noexcept
  {
    switch (value) {
      default:
        /* FALLTHROUGH */
      case Ambient:
        return "ambient";
      case Playback:
        return "playback";
    }
  }
};

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

CENTURION_HINT(AndroidAPKExpansionMainFileVersion,
               SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION,
               IntHint)

CENTURION_HINT(AndroidAPKExpansionPatchFileVersion,
               SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION,
               IntHint)

CENTURION_HINT(AppleTVControllerUIEvents,
               SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS,
               BoolHint)

CENTURION_HINT(AppleTVRemoteAllowRotation,
               SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION,
               BoolHint)

CENTURION_HINT(BMPSaveLegacyFormat, SDL_HINT_BMP_SAVE_LEGACY_FORMAT, BoolHint)

CENTURION_HINT(DoubleBuffer, SDL_HINT_VIDEO_DOUBLE_BUFFER, BoolHint)

CENTURION_HINT(DisplayUsableBounds, SDL_HINT_DISPLAY_USABLE_BOUNDS, StringHint)

CENTURION_HINT(EmscriptenKeyboardElement,
               SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT,
               StringHint)

CENTURION_HINT(EventLogging, SDL_HINT_EVENT_LOGGING, IntHint)

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

CENTURION_HINT(MouseDoubleClickTime, SDL_HINT_MOUSE_DOUBLE_CLICK_TIME, IntHint)

CENTURION_HINT(MouseDoubleClickRadius,
               SDL_HINT_MOUSE_DOUBLE_CLICK_RADIUS,
               IntHint)

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

CENTURION_HINT(WinRTHandleBackButton,
               SDL_HINT_WINRT_HANDLE_BACK_BUTTON,
               IntHint)

CENTURION_HINT(MouseTouchEvents, SDL_HINT_MOUSE_TOUCH_EVENTS, BoolHint)

CENTURION_HINT(RenderBatching, SDL_HINT_RENDER_BATCHING, BoolHint)

CENTURION_HINT(ReturnKeyHidesIME, SDL_HINT_RETURN_KEY_HIDES_IME, BoolHint)

CENTURION_HINT(TouchMouseEvents, SDL_HINT_TOUCH_MOUSE_EVENTS, BoolHint)

CENTURION_HINT(TVRemoteAsJoystick, SDL_HINT_TV_REMOTE_AS_JOYSTICK, BoolHint)

CENTURION_HINT(XinputEnabled, SDL_HINT_XINPUT_ENABLED, BoolHint)

CENTURION_HINT(XinputUseOldJoystickMapping,
               SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING,
               BoolHint)

/// @endcond

/**
 * The <code>Prio</code> enum class provides three different priorities that
 * can be specified when setting the value of a hint.
 *
 * @since 4.1.0
 * @see SDL_HintPriority
 */
enum class Prio {
  Default =
      SDL_HINT_DEFAULT,     /**< The lowest priority, used for default values.*/
  Normal = SDL_HINT_NORMAL, /**< The priority used by default by
                             * <code>set_hint</code>.*/
  Override = SDL_HINT_OVERRIDE /**< The highest priority.*/
};

/**
 * Sets the value of the specified hint. This method will only accept values
 * that are related to the specified hint, supplying the wrong kind of value
 * causes a compile-time error. See the related hint class for more details
 * about the associated value type. However, whilst this method is type-safe,
 * it doesn't ensure that <i>correct</i> values are specified for the hints.
 *
 * \par Examples
 * The following is an example of how you could use this method to
 * specify the render driver that SDL should use, and the value is specified
 * with an enum value associated with the <code>RenderDriver</code> class.
 * @code{.cpp}
 *   set_hint<RenderDriver>(RenderDriver::OpenGL);
 * @endcode
 * Most hints only accept boolean or integer values. As in the following
 * examples.
 * @code{.cpp}
 *   set_hint<EnableVSync>(true);
 * @endcode
 * @code{.cpp}
 *   set_hint<EventLogging>(2);
 * @endcode
 * Sometimes, it's useful to know whether or not the hint was actually set
 * to the desired value. This can be done according to the following example.
 * @code{.cpp}
 *   const bool success = set_hint<DoubleBuffer>(true);
 *   if (success) {
 *     // the hint was actually set!
 *   } else {
 *     // something went wrong!
 *   }
 * @endcode
 *
 * @tparam Hint the type of the hint that will be modified.
 * @tparam priority the priority that will be used, defaults to
 * <code>Normal</code>.
 * @tparam Value the type of the hint value.
 * @param value the new value that will be set for the specified hint.
 * @return true if the hint was successfully set; false otherwise.
 * @since 4.1.0
 */
template <
    typename Hint,
    Prio priority = Prio::Normal,
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
 * @par Examples
 * Many hints aren't actually set by default, so if the specified hint
 * doesn't have a set value, then this method will return a null optional.
 * @code{.cpp}
 *  const auto value = get_hint<RenderDriver>();
 *  if (value) {
 *    // the hint was set!
 *  } else {
 *    // the hint had no set value!
 *  }
 * @endcode
 * With C++17 checking if there is a set value can be made more elegant using
 * the if-with-initializer statement.
 * @code{.cpp}
 *  if (const auto value = get_hint<RenderDriver>(); value) {
 *    // the hint was set!
 *  } else {
 *    // the hint had no set value!
 *  }
 * @endcode
 *
 * @tparam Hint the type of the Hint to obtain the value of.
 * @return the current value of the specified hint; nothing if there is no
 * value set for the hint.
 * @since 4.1.0
 */
template <typename Hint>
CENTURION_NODISCARD decltype(auto) get_hint() noexcept
{
  return Hint::current_value();
}

/**
 * The <code>Callback</code> class is a simple handle object for dealing
 * with callbacks related to hints. It provides means for easily connecting
 * and disconnecting a callback from receiving updates.
 *
 * @tparam Hint the type of the associated hint. Should be one of the hint
 * types defined in the <code>hints.h</code> header.
 * @tparam UserData the type of the user data, defaults to void.
 * @since 4.1.0
 */
template <typename Hint, typename UserData = void>
class Callback final {
  // TODO in future version, possible to supply UserData* to function ptr?
  //  using safe_callback =
  //      typename std::add_pointer<void(UserData*, CZString, CZString)>::type;

 public:
  /**
   * Creates a <code>HintCallback</code>.
   *
   * @param callback the function object that will be called whenever the
   * associated hint is updated. The signature should be <code>void(void*
   * userData, CZString hint, CZString oldValue, CZString newValue)</code>.
   * @param userData a pointer to some user data. Defaults to null.
   * @throws CenturionException if the supplied function pointer is null.
   * @since 4.1.0
   */
  Callback(SDL_HintCallback callback, UserData* userData = nullptr)
      : m_callback{callback}, m_userData{userData}
  {
    if (!callback) {
      const auto* msg = "Can't create HintCallback from null function pointer!";
      throw CenturionException{msg};
    }
  }

  //  HintCallback(simple_callback callback) {}

  /**
   * Registers the callback to be invoked whenever the associated hint is
   * updated.
   *
   * @since 4.1.0
   * @see SDL_AddHintCallback
   */
  void connect() noexcept
  {
    SDL_AddHintCallback(
        Hint::name(), m_callback, static_cast<void*>(m_userData));
  }

  /**
   * Unregisters the callback from being updated whenever the associated hint
   * is updated.
   *
   * @since 4.1.0
   */
  void disconnect() noexcept
  {
    SDL_DelHintCallback(
        Hint::name(), m_callback, static_cast<void*>(m_userData));
  }

  /**
   * Returns a pointer to the function that is invoked when the associated
   * hint is updated.
   *
   * @return a pointer to the function that is invoked when the associated
   * hint is updated.
   * @since 4.1.0
   */
  CENTURION_NODISCARD SDL_HintCallback get() noexcept { return m_callback; }

  /**
   * Returns a pointer to the user data associated with the callback.
   *
   * @return a pointer to the user data associated with the callback, can be
   * null.
   * @since 4.1.0
   */
  CENTURION_NODISCARD UserData* user_data() const noexcept
  {
    return m_userData;
  }

 private:
  SDL_HintCallback m_callback;
  //  simple_callback m_simpleCallback{nullptr};
  UserData* m_userData;
};

/**
 * Adds a callback that will be connected to observe changes of the value of
 * the specified hint is updated. A callback handle object is returned, which
 * can be used to easily disconnect the callback later. Note! The callback
 * will be immediately invoked with the current value of the hint.
 *
 * @par Examples
 * This method can be used with any function object that is stateless, such
 * as traditional function pointers and lambdas. The simplest way to add a
 * callback is with a lambda and no explicit user data.
 * @code{.cpp}
 *   auto handle = add_callback([](void* userData,
 *                                 CZString hint,
 *                                 CZString oldValue,
 *                                 CZString newValue) {
 *     // code that handles the update
 *   });
 * @endcode
 * It's also possible to supply a pointer to some data that you want to
 * associate with the callback. As always, beware of the lifetime of the data!
 * @code{.cpp}
 *   int data = 8; // shouldn't be local in real code
 *   auto handle = add_callback([](void* userData,
 *                                 CZString hint,
 *                                 CZString oldValue,
 *                                 CZString newValue) {
 *     // code that handles the update
 *   },
 *   &data);
 * @endcode
 *
 * @tparam Hint should one of the many hint types defined in this header.
 * However, all it requires is that the type provides a static method that
 * returns a <code>CZString</code>.
 * @tparam UserData the type of the user data, defaults to void.
 *
 * @param callback the function object that will be invoked when the hint is
 * updated. The signature should be <code>void(void* userData, CZString hint,
 * CZString oldValue, CZString newValue)</code>.
 * @param userData the user data to associate with the callback, defaults to
 * null.
 * @return a handle to the added callback.
 *
 * @note In a future version of Centurion (that supports C++20), the
 * signature of the function object will be dependent of the
 * <code>UserData</code> type. Unfortunately, this isn't really doable with
 * C++11, C++14 nor C++17. Since it requires default-constructible stateless
 * lambdas.
 * @since 4.1.0
 */
template <typename Hint, typename UserData = void>
Callback<Hint, UserData> add_callback(SDL_HintCallback callback,
                                      UserData* userData = nullptr) noexcept
{
  Callback<Hint, UserData> hintCallback{callback, userData};
  hintCallback.connect();
  return hintCallback;
}

/**
 * Clears all stored hints.
 *
 * @since 4.1.0
 * @see SDL_ClearHints
 */
void clear_all() noexcept
{
  SDL_ClearHints();
}

// TODO with C++20 it'll be possible to add a simple hint callback mechanism
// template<typename Lambda>
// void f(void*, CZString, CZString oldValue, CZString newValue) {
//  Lambda lambda; // requires C++20 and a stateless lambda
//  lambda(oldValue, newValue);
//}

}  // namespace hint
}  // namespace centurion

#undef CENTURION_BOOL_HINT
#endif  // CENTURION_HINTS_HEADER
