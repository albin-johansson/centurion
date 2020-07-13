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
 * @brief Provides utilities related to managing hints.
 *
 * @details Provides utilities related to managing hints ("configuration
 * variables" on the SDL2 wiki). Refer to the official SDL2 wiki or the
 * <code>SDL_hints.hpp</code> header for details regarding any specific hint
 * type.
 *
 * @todo `WindowsIntResourceIcon`, `WindowsIntResourceIconSmall`,
 * `X11WindowVisualID` are string hints because the types of their values
 * isn't known. Should be fixed if the type isn't actually string.
 *
 * @todo C++20: Make callback signature depend on the `UserData` and the type
 * of the associated hint, so that the values supplied to the callback aren't
 * always strings.
 *
 * @file hints.hpp
 * @since 4.1.0
 * @author Albin Johansson
 * @date 2019-2020
 * @copyright MIT License
 */

#ifndef CENTURION_HINTS_HEADER
#define CENTURION_HINTS_HEADER

#include <SDL_hints.h>

#include <cstring>
#include <log.hpp>

#include "centurion_api.hpp"
#include "centurion_exception.hpp"
#include "centurion_utils.hpp"

namespace centurion {

/// @cond FALSE

namespace detail {

template <typename Derived, typename Arg>
class CRTPHint {
 public:
  template <typename T>
  [[nodiscard]] static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Arg>;
  }

  [[nodiscard]] static constexpr auto name() noexcept -> czstring
  {
    return Derived::name();
  }

  [[nodiscard]] static auto value() noexcept -> std::optional<Arg>
  {
    return Derived::current_value();
  }

  [[nodiscard]] static auto to_string(Arg value) noexcept -> std::string
  {
    return std::to_string(value);
  }
};

// A hint class that only accepts booleans
template <typename Hint>
class BoolHint : public CRTPHint<BoolHint<Hint>, bool> {
 public:
  template <typename T>
  [[nodiscard]] static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, bool>;
  }

  [[nodiscard]] static auto current_value() noexcept -> std::optional<bool>
  {
    return static_cast<bool>(SDL_GetHintBoolean(Hint::name(), SDL_FALSE));
  }

  [[nodiscard]] static auto to_string(bool value) noexcept -> std::string
  {
    return value ? "1" : "0";
  }
};

// A hint class that only accepts strings
template <typename Hint>
class StringHint : public CRTPHint<StringHint<Hint>, czstring> {
 public:
  template <typename T>
  [[nodiscard]] static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_convertible_v<T, czstring>;
  }

  [[nodiscard]] static auto current_value() noexcept -> std::optional<czstring>
  {
    const czstring value = SDL_GetHint(Hint::name());
    if (!value) {
      return nothing;
    } else {
      return value;
    }
  }

  [[nodiscard]] static auto to_string(czstring value) -> std::string
  {
    return value;
  }
};

// A hint class that only accepts integers
template <typename Hint>
class IntHint : public CRTPHint<IntHint<Hint>, int> {
 public:
  template <typename T>
  [[nodiscard]] static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, int>;
  }

  [[nodiscard]] static auto current_value() noexcept -> std::optional<int>
  {
    const czstring value = SDL_GetHint(Hint::name());
    if (!value) {
      return nothing;
    } else {
      return std::stoi(value);
    }
  }
};

// A hint class that only accepts unsigned integers
template <typename Hint>
class UnsignedIntHint : public CRTPHint<IntHint<Hint>, unsigned int> {
 public:
  template <typename T>
  [[nodiscard]] static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, unsigned int>;
  }

  [[nodiscard]] static auto current_value() noexcept
      -> std::optional<unsigned int>
  {
    const czstring value = SDL_GetHint(Hint::name());
    if (!value) {
      return nothing;
    } else {
      return static_cast<unsigned int>(std::stoul(value));
    }
  }
};

// A hint class that only accepts floats
template <typename Hint>
class FloatHint : public CRTPHint<FloatHint<Hint>, float> {
 public:
  template <typename T>
  [[nodiscard]] static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, float>;
  }

  [[nodiscard]] static auto current_value() noexcept -> std::optional<float>
  {
    const czstring value = SDL_GetHint(Hint::name());
    if (!value) {
      return nothing;
    } else {
      return std::stof(value);
    }
  }
};

}  // namespace detail

/// @endcond

/**
 * @namespace centurion::hint
 *
 * @brief Contains components related to hints (configuration variables).
 *
 * @since 4.1.0
 */
namespace hint {

/// @cond FALSE

class RenderDriver final {
 public:
  enum Value { Direct3D, OpenGL, OpenGLES, OpenGLES2, Metal, Software };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_RENDER_DRIVER;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "direct3d")) {
      return Direct3D;
    } else if (equal(hint, "opengl")) {
      return OpenGL;
    } else if (equal(hint, "opengles")) {
      return OpenGLES;
    } else if (equal(hint, "opengles2")) {
      return OpenGLES2;
    } else if (equal(hint, "metal")) {
      return Metal;
    } else {
      return Software;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
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
      default:
        /* FALLTHROUGH */
      case Software:
        return "software";
    }
  }
};

class AudioResamplingMode final {
 public:
  enum Value { Default = 0, Fast = 1, Medium = 2, Best = 3 };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_AUDIO_RESAMPLING_MODE;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "default")) {
      return Default;
    } else if (equal(hint, "fast")) {
      return Fast;
    } else if (equal(hint, "medium")) {
      return Medium;
    } else /*if (equal(hint, "best"))*/ {
      return Best;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
  {
    switch (value) {
      case Default:
      default:
        return "default";
      case Fast:
        return "fast";
      case Medium:
        return "medium";
      case Best:
        return "best";
    }
  }
};

class ScaleQuality final {
 public:
  enum Value { Nearest = 0, Linear = 1, Best = 2 };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_RENDER_SCALE_QUALITY;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "nearest")) {
      return Nearest;
    } else if (equal(hint, "linear")) {
      return Linear;
    } else /*if (equal(hint, "best"))*/ {
      return Best;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
  {
    switch (value) {
      default:
      case Nearest:
        return "nearest";
      case Linear:
        return "linear";
      case Best:
        return "best";
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
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_FRAMEBUFFER_ACCELERATION;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "0")) {
      return Off;
    } else if (equal(hint, "1")) {
      return On;
    } else if (equal(hint, "direct3d")) {
      return Direct3D;
    } else if (equal(hint, "opengl")) {
      return OpenGL;
    } else if (equal(hint, "opengles")) {
      return OpenGLES;
    } else if (equal(hint, "opengles2")) {
      return OpenGLES2;
    } else if (equal(hint, "metal")) {
      return Metal;
    } else {
      return Software;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
  {
    switch (value) {
      default:
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
    }
  }
};

class AudioCategory final {
 public:
  enum Value { Ambient, Playback };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_AUDIO_CATEGORY;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "ambient")) {
      return Ambient;
    } else /*if (equal(hint, "playback"))*/ {
      return Playback;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
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

class WinD3DCompiler final {
 public:
  enum Value { D3DCompiler46, D3DCompiler43, None };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_VIDEO_WIN_D3DCOMPILER;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "d3dcompiler_46.dll")) {
      return D3DCompiler46;
    } else if (equal(hint, "d3dcompiler_43.dll")) {
      return D3DCompiler43;
    } else {
      return None;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
  {
    switch (value) {
      default:
        /* FALLTHROUGH */
      case None:
        return "none";
      case D3DCompiler43:
        return "d3dcompiler_43.dll";
      case D3DCompiler46:
        return "d3dcompiler_46.dll";
    }
  }
};

class WAVERIFFChunkSize final {
 public:
  enum Value { Force, IgnoreZero, Ignore, Maximum };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_WAVE_RIFF_CHUNK_SIZE;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "force")) {
      return Force;
    } else if (equal(hint, "ignorezero")) {
      return IgnoreZero;
    } else if (equal(hint, "ignore")) {
      return Ignore;
    } else /* if (equal(hint, "maximum")) */ {
      return Maximum;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
  {
    switch (value) {
      default:
        /* FALLTHROUGH */
      case IgnoreZero:
        return "ignorezero";
      case Ignore:
        return "ignore";
      case Force:
        return "force";
      case Maximum:
        return "maximum";
    }
  }
};

class WAVETruncation final {
 public:
  enum Value { VeryStrict, Strict, DropFrame, DropBlock };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_WAVE_TRUNCATION;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "verystrict")) {
      return VeryStrict;
    } else if (equal(hint, "strict")) {
      return Strict;
    } else if (equal(hint, "dropframe")) {
      return DropFrame;
    } else /* if (equal(hint, "dropblock")) */ {
      return DropBlock;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
  {
    switch (value) {
      default:
        /* FALLTHROUGH */
      case DropBlock:
        return "dropblock";
      case DropFrame:
        return "dropframe";
      case VeryStrict:
        return "verystrict";
      case Strict:
        return "strict";
    }
  }
};

class WAVEFactChunk final {
 public:
  enum Value { Truncate, Strict, IgnoreZero, Ignore };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_WAVE_FACT_CHUNK;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "truncate")) {
      return Truncate;
    } else if (equal(hint, "strict")) {
      return Strict;
    } else if (equal(hint, "ignorezero")) {
      return IgnoreZero;
    } else /* if (equal(hint, "ignore")) */ {
      return Ignore;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
  {
    switch (value) {
      default:
        /* FALLTHROUGH */
      case Ignore:
        return "ignore";
      case IgnoreZero:
        return "ignorezero";
      case Truncate:
        return "truncate";
      case Strict:
        return "strict";
    }
  }
};

class LogicalSizeMode final {
 public:
  enum Value { Letterbox, Overscan };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_RENDER_LOGICAL_SIZE_MODE;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "0") || equal(hint, "letterbox")) {
      return Letterbox;
    } else /*if (equal(hint, "1") || equal(hint, "overscan"))*/ {
      return Overscan;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
  {
    switch (value) {
      default:
        /* FALLTHROUGH */
      case Letterbox:
        return "letterbox";
      case Overscan:
        return "overscan";
    }
  }
};

class QtWaylandContentOrientation final {
 public:
  enum Value {
    Primary,
    Portrait,
    Landscape,
    InvertedPortrait,
    InvertedLandscape
  };

  template <typename T>
  static constexpr auto valid_arg() noexcept -> bool
  {
    return std::is_same_v<T, Value>;
  }

  static constexpr auto name() noexcept -> czstring
  {
    return SDL_HINT_QTWAYLAND_CONTENT_ORIENTATION;
  }

  static auto current_value() noexcept -> std::optional<Value>
  {
    const czstring hint = SDL_GetHint(name());
    if (!hint) {
      return nothing;
    }

    using detail::equal;
    if (equal(hint, "primary")) {
      return Primary;
    } else if (equal(hint, "portrait")) {
      return Portrait;
    } else if (equal(hint, "landscape")) {
      return Landscape;
    } else if (equal(hint, "inverted-portrait")) {
      return InvertedPortrait;
    } else /*if (equal(hint, "inverted-landscape"))*/ {
      return InvertedLandscape;
    }
  }

  static auto to_string(Value value) noexcept -> std::string
  {
    switch (value) {
      default:
        /* FALLTHROUGH */
      case Primary:
        return "primary";
      case Portrait:
        return "portrait";
      case Landscape:
        return "landscape";
      case InvertedPortrait:
        return "inverted-portrait";
      case InvertedLandscape:
        return "inverted-landscape";
    }
  }
};

#define CENTURION_HINT(Name, SDLName, Type)                 \
  class Name final : public detail::Type<Name> {            \
   public:                                                  \
    [[nodiscard]] static constexpr czstring name() noexcept \
    {                                                       \
      return SDLName;                                       \
    }                                                       \
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

CENTURION_HINT(Orientations, SDL_HINT_ORIENTATIONS, StringHint)

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

CENTURION_HINT(MouseNormalSpeedScale,
               SDL_HINT_MOUSE_NORMAL_SPEED_SCALE,
               FloatHint)

CENTURION_HINT(MouseRelativeSpeedScale,
               SDL_HINT_MOUSE_RELATIVE_SPEED_SCALE,
               FloatHint)

CENTURION_HINT(X11NetWMPing, SDL_HINT_VIDEO_X11_NET_WM_PING, BoolHint)

CENTURION_HINT(X11XNetWMBypassCompositor,
               SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR,
               BoolHint)

CENTURION_HINT(X11ForceEGL, SDL_HINT_VIDEO_X11_FORCE_EGL, BoolHint)

CENTURION_HINT(X11Xinerama, SDL_HINT_VIDEO_X11_XINERAMA, BoolHint)

CENTURION_HINT(X11XRandR, SDL_HINT_VIDEO_X11_XRANDR, BoolHint)

CENTURION_HINT(X11XVidMode, SDL_HINT_VIDEO_X11_XVIDMODE, BoolHint)

CENTURION_HINT(X11WindowVisualID,
               SDL_HINT_VIDEO_X11_WINDOW_VISUALID,
               StringHint)

CENTURION_HINT(WindowsDisableThreadNaming,
               SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING,
               BoolHint)

CENTURION_HINT(WindowSharePixelFormat,
               SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT,
               StringHint)

CENTURION_HINT(WindowsEnableMessageLoop,
               SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP,
               BoolHint)

CENTURION_HINT(WindowsNoCloseOnAltF4,
               SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4,
               BoolHint)

CENTURION_HINT(WindowFrameUsableWhileCursorHidden,
               SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN,
               BoolHint)

CENTURION_HINT(WindowsIntResourceIcon,
               SDL_HINT_WINDOWS_INTRESOURCE_ICON,
               StringHint)

CENTURION_HINT(WindowsIntResourceIconSmall,
               SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL,
               StringHint)

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

CENTURION_HINT(RaspberryPIVideoLayer, SDL_HINT_RPI_VIDEO_LAYER, IntHint)

CENTURION_HINT(RenderBatching, SDL_HINT_RENDER_BATCHING, BoolHint)

CENTURION_HINT(ReturnKeyHidesIME, SDL_HINT_RETURN_KEY_HIDES_IME, BoolHint)

CENTURION_HINT(TouchMouseEvents, SDL_HINT_TOUCH_MOUSE_EVENTS, BoolHint)

CENTURION_HINT(ThreadStackSize, SDL_HINT_THREAD_STACK_SIZE, UnsignedIntHint)

CENTURION_HINT(TimerResolution, SDL_HINT_TIMER_RESOLUTION, UnsignedIntHint)

CENTURION_HINT(TVRemoteAsJoystick, SDL_HINT_TV_REMOTE_AS_JOYSTICK, BoolHint)

CENTURION_HINT(QtWaylandWindowFlags,
               SDL_HINT_QTWAYLAND_WINDOW_FLAGS,
               StringHint)

CENTURION_HINT(XinputEnabled, SDL_HINT_XINPUT_ENABLED, BoolHint)

CENTURION_HINT(XinputUseOldJoystickMapping,
               SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING,
               BoolHint)

/// @endcond

/**
 * @enum hint_prio
 *
 * @brief Provides three different priorities that can be specified when
 * setting the value of a hint.
 *
 * @since 4.1.0
 *
 * @see `SDL_HintPriority`
 *
 * @headerfile hints.hpp
 */
enum class hint_prio {
  low = SDL_HINT_DEFAULT,   /**< The lowest priority, used for default values.*/
  normal = SDL_HINT_NORMAL, /**< The priority used by default by
                             * <code>set_hint</code>.*/
  override = SDL_HINT_OVERRIDE /**< The highest priority.*/
};

/**
 * @brief Sets the value of the specified hint.
 *
 * @details This method will only accept values that are related to the
 * specified hint, supplying the wrong kind of value causes a compile-time
 * error. See the related hint class for more details about the associated
 * value type. However, whilst this method is type-safe, it doesn't ensure
 * that *correct* values are specified for the hints.
 *
 * @par Examples
 * The following is an example of how you could use this method to
 * specify the render driver that SDL should use, and the value is specified
 * with an enum value associated with the <code>RenderDriver</code> class.
 * @code{.cpp}
 *   set_hint<RenderDriver>(RenderDriver::OpenGL);
 * @endcode
 * Most hints only accept boolean or integer values. As in the following
 * example.
 * @code{.cpp}
 *   set_hint<EnableVSync>(true);
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
 * @tparam priority the priority that will be used, defaults to `Normal`.
 * @tparam Value the type of the hint value.
 *
 * @param value the new value that will be set for the specified hint.
 *
 * @return `true` if the hint was successfully set; `false` otherwise.
 *
 * @since 4.1.0
 */
template <typename Hint,
          hint_prio priority = hint_prio::normal,
          typename Value,
          typename = std::enable_if_t<Hint::template valid_arg<Value>()>>
auto set_hint(const Value& value) noexcept -> bool
{
  return static_cast<bool>(
      SDL_SetHintWithPriority(Hint::name(),
                              Hint::to_string(value).c_str(),
                              static_cast<SDL_HintPriority>(priority)));
}

/**
 * @brief Returns the current value of the specified hint.
 *
 * @note The returned value is a `std::optional` of the hint value type.
 *
 * @par Examples
 * Many hints aren't actually set by default, so if the specified hint
 * doesn't have a set value, then this method will return a null optional.
 * @code{.cpp}
 *  if (const auto value = get_hint<RenderDriver>(); value) {
 *    // the hint was set!
 *  } else {
 *    // the hint had no set value!
 *  }
 * @endcode
 *
 * @tparam Hint the type of the Hint to obtain the value of.
 *
 * @return the current value of the specified hint; `nothing` if there is no
 * value set for the hint.
 *
 * @since 4.1.0
 */
template <typename Hint>
[[nodiscard]] decltype(auto) get_hint() noexcept
{
  return Hint::current_value();
}

/**
 * @class Callback
 *
 * @brief Represents a handle for dealing with hint callbacks.
 *
 * @details This class provides methods for easily connecting and disconnecting
 * a callback from receiving updates.
 *
 * @tparam Hint the type of the associated hint. Should be one of the hint
 * types defined in the `hints.hpp` header.
 *
 * @tparam UserData the type of the user data, defaults to `void`.
 *
 * @since 4.1.0
 *
 * @headerfile hints.hpp
 */
template <typename Hint, typename UserData = void>
class callback final {
 public:
  /**
   * @brief Creates a `HintCallback`.
   *
   * @param callback the function object that will be called whenever the
   * associated hint is updated. The signature should be `void(void*,
   * czstring, czstring, czstring)`.
   * @param userData a pointer to some user data. Defaults to `nullptr`.
   *
   * @throws centurion_exception if the supplied function pointer is null.
   *
   * @since 4.1.0
   */
  callback(SDL_HintCallback callback, UserData* userData = nullptr)
      : m_callback{callback}, m_userData{userData}
  {
    if (!callback) {
      const auto* msg = "Can't create HintCallback from null function pointer!";
      throw centurion_exception{msg};
    }
  }

  /**
   * @brief Registers the callback to be invoked whenever the associated hint is
   * updated.
   *
   * @see `SDL_AddHintCallback`
   *
   * @since 4.1.0
   */
  void connect() noexcept
  {
    SDL_AddHintCallback(
        Hint::name(), m_callback, static_cast<void*>(m_userData));
  }

  /**
   * @brief Unregisters the callback from being updated whenever the associated
   * hint is updated.
   *
   * @see `SDL_DelHintCallback`
   *
   * @since 4.1.0
   */
  void disconnect() noexcept
  {
    SDL_DelHintCallback(
        Hint::name(), m_callback, static_cast<void*>(m_userData));
  }

  /**
   * @brief Returns a pointer to the function that is invoked when the
   * associated hint is updated.
   *
   * @return a pointer to the function that is invoked when the associated
   * hint is updated.
   *
   * @since 4.1.0
   */
  [[nodiscard]] auto get() noexcept -> SDL_HintCallback { return m_callback; }

  /**
   * @brief Returns a pointer to the user data associated with the callback.
   *
   * @return a pointer to the user data associated with the callback, can be
   * null.
   *
   * @since 4.1.0
   */
  [[nodiscard]] auto user_data() const noexcept -> UserData*
  {
    return m_userData;
  }

 private:
  SDL_HintCallback m_callback;
  UserData* m_userData;
};

/**
 * @brief Adds a callback to observe changes of the value of the specified
 * hint is updated.
 *
 * @details A callback handle object is returned, which can be used to easily
 * disconnect the callback later.
 *
 * @note The callback will be immediately invoked with the current value of
 * the hint.
 *
 * @note In a future version of centurion (that supports C++20), the
 * signature of the function object will be dependent on the `UserData` type.
 * Unfortunately, this isn't really doable with C++17. Since it requires
 * default-constructible stateless lambdas.
 *
 * @par Examples
 * This method can be used with any function object that is stateless, such
 * as traditional function pointers and lambdas. The simplest way to add a
 * callback is with a lambda and no explicit user data.
 * @code{.cpp}
 *   auto handle = add_callback([](void* userData,
 *                                 czstring hint,
 *                                 czstring oldValue,
 *                                 czstring newValue) {
 *     // code that handles the update
 *   });
 * @endcode
 * It's also possible to supply a pointer to some data that you want to
 * associate with the callback. As always, beware of the lifetime of the data!
 * @code{.cpp}
 *   int data = 8; // shouldn't be local in real code
 *   auto handle = add_callback([](void* userData,
 *                                 czstring hint,
 *                                 czstring oldValue,
 *                                 czstring newValue) {
 *     // code that handles the update
 *   },
 *   &data);
 * @endcode
 *
 * @tparam Hint should one of the many hint types defined in this header.
 * However, all it requires is that the type provides a static method that
 * returns a `czstring`.
 * @tparam UserData the type of the user data, defaults to void.
 *
 * @param fun the function object that will be invoked when the hint is
 * updated. The signature should be `void(void*, czstring, czstring, czstring)`.
 * @param userData the user data to associate with the callback, defaults to
 * `nullptr`.
 *
 * @return a handle to the added callback.
 *
 * @since 4.1.0
 */
template <typename Hint, typename UserData = void>
auto add_callback(SDL_HintCallback fun, UserData* userData = nullptr) noexcept
    -> callback<Hint, UserData>
{
  callback<Hint, UserData> hintCallback{fun, userData};
  hintCallback.connect();
  return hintCallback;
}

/**
 * @brief Clears all stored hints.
 *
 * @see `SDL_ClearHints`
 *
 * @since 4.1.0
 */
inline void clear_all() noexcept
{
  SDL_ClearHints();
}

}  // namespace hint
}  // namespace centurion

#undef CENTURION_BOOL_HINT
#endif  // CENTURION_HINTS_HEADER
