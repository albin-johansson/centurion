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
class crtp_hint {
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

  [[nodiscard]] static auto to_string(Arg value) -> std::string
  {
    return std::to_string(value);
  }
};

// A hint class that only accepts booleans
template <typename Hint>
class bool_hint : public crtp_hint<bool_hint<Hint>, bool> {
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

  [[nodiscard]] static auto to_string(bool value) -> std::string
  {
    return value ? "1" : "0";
  }
};

// A hint class that only accepts strings
template <typename Hint>
class string_hint : public crtp_hint<string_hint<Hint>, czstring> {
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
class int_hint : public crtp_hint<int_hint<Hint>, int> {
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
class unsigned_int_hint : public crtp_hint<int_hint<Hint>, unsigned int> {
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
class float_hint : public crtp_hint<float_hint<Hint>, float> {
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

class render_driver final {
 public:
  enum Value { direct_3d, open_gl, open_gles, open_gles2, metal, software };

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
      return direct_3d;
    } else if (equal(hint, "opengl")) {
      return open_gl;
    } else if (equal(hint, "opengles")) {
      return open_gles;
    } else if (equal(hint, "opengles2")) {
      return open_gles2;
    } else if (equal(hint, "metal")) {
      return metal;
    } else {
      return software;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      case direct_3d:
        return "direct3d";
      case open_gl:
        return "opengl";
      case open_gles:
        return "opengles";
      case open_gles2:
        return "opengles2";
      case metal:
        return "metal";
      default:
        /* FALLTHROUGH */
      case software:
        return "software";
    }
  }
};

class audio_resampling_mode final {
 public:
  enum Value { normal = 0, fast = 1, medium = 2, best = 3 };

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
      return normal;
    } else if (equal(hint, "fast")) {
      return fast;
    } else if (equal(hint, "medium")) {
      return medium;
    } else /*if (equal(hint, "best"))*/ {
      return best;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      case normal:
      default:
        return "default";
      case fast:
        return "fast";
      case medium:
        return "medium";
      case best:
        return "best";
    }
  }
};

class scale_quality final {
 public:
  enum Value { nearest = 0, linear = 1, best = 2 };

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
      return nearest;
    } else if (equal(hint, "linear")) {
      return linear;
    } else /*if (equal(hint, "best"))*/ {
      return best;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      default:
      case nearest:
        return "nearest";
      case linear:
        return "linear";
      case best:
        return "best";
    }
  }
};

class framebuffer_acceleration final {
 public:
  enum Value {
    off,
    on,
    direct_3d,
    open_gl,
    open_gles,
    open_gles2,
    metal,
    software
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
      return off;
    } else if (equal(hint, "1")) {
      return on;
    } else if (equal(hint, "direct3d")) {
      return direct_3d;
    } else if (equal(hint, "opengl")) {
      return open_gl;
    } else if (equal(hint, "opengles")) {
      return open_gles;
    } else if (equal(hint, "opengles2")) {
      return open_gles2;
    } else if (equal(hint, "metal")) {
      return metal;
    } else {
      return software;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      default:
        [[fallthrough]];
      case off:
        return "0";
      case on:
        return "1";
      case direct_3d:
        return "direct3d";
      case open_gl:
        return "opengl";
      case open_gles:
        return "opengles";
      case open_gles2:
        return "opengles2";
      case metal:
        return "metal";
      case software:
        return "software";
    }
  }
};

class audio_category final {
 public:
  enum Value { ambient, playback };

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
      return ambient;
    } else /*if (equal(hint, "playback"))*/ {
      return playback;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      default:
        [[fallthrough]];
      case ambient:
        return "ambient";
      case playback:
        return "playback";
    }
  }
};

class win_d3d_compiler final {
 public:
  enum Value { d3d_compiler_46, d3d_compiler_43, none };

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
      return d3d_compiler_46;
    } else if (equal(hint, "d3dcompiler_43.dll")) {
      return d3d_compiler_43;
    } else {
      return none;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      default:
        [[fallthrough]];
      case none:
        return "none";
      case d3d_compiler_43:
        return "d3dcompiler_43.dll";
      case d3d_compiler_46:
        return "d3dcompiler_46.dll";
    }
  }
};

class wave_riff_chunk_size final {
 public:
  enum Value { force, ignore_zero, ignore, maximum };

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
      return force;
    } else if (equal(hint, "ignorezero")) {
      return ignore_zero;
    } else if (equal(hint, "ignore")) {
      return ignore;
    } else /* if (equal(hint, "maximum")) */ {
      return maximum;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      default:
        [[fallthrough]];
      case ignore_zero:
        return "ignorezero";
      case ignore:
        return "ignore";
      case force:
        return "force";
      case maximum:
        return "maximum";
    }
  }
};

class wave_truncation final {
 public:
  enum Value { very_strict, strict, drop_frame, drop_block };

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
      return very_strict;
    } else if (equal(hint, "strict")) {
      return strict;
    } else if (equal(hint, "dropframe")) {
      return drop_frame;
    } else /* if (equal(hint, "dropblock")) */ {
      return drop_block;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      default:
        [[fallthrough]];
      case drop_block:
        return "dropblock";
      case drop_frame:
        return "dropframe";
      case very_strict:
        return "verystrict";
      case strict:
        return "strict";
    }
  }
};

class wave_fact_chunk final {
 public:
  enum Value { truncate, strict, ignore_zero, ignore };

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
      return truncate;
    } else if (equal(hint, "strict")) {
      return strict;
    } else if (equal(hint, "ignorezero")) {
      return ignore_zero;
    } else /* if (equal(hint, "ignore")) */ {
      return ignore;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      default:
        [[fallthrough]];
      case ignore:
        return "ignore";
      case ignore_zero:
        return "ignorezero";
      case truncate:
        return "truncate";
      case strict:
        return "strict";
    }
  }
};

class logical_size_mode final {
 public:
  enum Value { letterbox, overscan };

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
      return letterbox;
    } else /*if (equal(hint, "1") || equal(hint, "overscan"))*/ {
      return overscan;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      default:
        [[fallthrough]];
      case letterbox:
        return "letterbox";
      case overscan:
        return "overscan";
    }
  }
};

class qt_wayland_content_orientation final {
 public:
  enum Value {
    primary,
    portrait,
    landscape,
    inverted_portrait,
    inverted_landscape
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
      return primary;
    } else if (equal(hint, "portrait")) {
      return portrait;
    } else if (equal(hint, "landscape")) {
      return landscape;
    } else if (equal(hint, "inverted-portrait")) {
      return inverted_portrait;
    } else /*if (equal(hint, "inverted-landscape"))*/ {
      return inverted_landscape;
    }
  }

  static auto to_string(Value value) -> std::string
  {
    switch (value) {
      default:
        [[fallthrough]];
      case primary:
        return "primary";
      case portrait:
        return "portrait";
      case landscape:
        return "landscape";
      case inverted_portrait:
        return "inverted-portrait";
      case inverted_landscape:
        return "inverted-landscape";
    }
  }
};

#define CENTURION_HINT(Name, SDLName, Type)                         \
  class Name final : public detail::Type<Name> {                    \
   public:                                                          \
    [[nodiscard]] static constexpr auto name() noexcept -> czstring \
    {                                                               \
      return SDLName;                                               \
    }                                                               \
  };

CENTURION_HINT(accelerometer_as_joystick,
               SDL_HINT_ACCELEROMETER_AS_JOYSTICK,
               bool_hint)

CENTURION_HINT(allow_top_most, SDL_HINT_ALLOW_TOPMOST, bool_hint)

CENTURION_HINT(android_block_on_pause,
               SDL_HINT_ANDROID_BLOCK_ON_PAUSE,
               bool_hint)

CENTURION_HINT(android_trap_back_button,
               SDL_HINT_ANDROID_TRAP_BACK_BUTTON,
               bool_hint)

CENTURION_HINT(android_apk_expansion_main_file_version,
               SDL_HINT_ANDROID_APK_EXPANSION_MAIN_FILE_VERSION,
               int_hint)

CENTURION_HINT(android_apk_expansion_patch_file_version,
               SDL_HINT_ANDROID_APK_EXPANSION_PATCH_FILE_VERSION,
               int_hint)

CENTURION_HINT(apple_tv_controller_ui_events,
               SDL_HINT_APPLE_TV_CONTROLLER_UI_EVENTS,
               bool_hint)

CENTURION_HINT(apple_tv_remote_allow_rotation,
               SDL_HINT_APPLE_TV_REMOTE_ALLOW_ROTATION,
               bool_hint)

CENTURION_HINT(bmp_save_legacy_format,
               SDL_HINT_BMP_SAVE_LEGACY_FORMAT,
               bool_hint)

CENTURION_HINT(double_buffer, SDL_HINT_VIDEO_DOUBLE_BUFFER, bool_hint)

CENTURION_HINT(display_usable_bounds,
               SDL_HINT_DISPLAY_USABLE_BOUNDS,
               string_hint)

CENTURION_HINT(emscripten_keyboard_element,
               SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT,
               string_hint)

CENTURION_HINT(event_logging, SDL_HINT_EVENT_LOGGING, int_hint)

CENTURION_HINT(enable_steam_controllers,
               SDL_HINT_ENABLE_STEAM_CONTROLLERS,
               bool_hint)

CENTURION_HINT(game_controller_use_button_labels,
               SDL_HINT_GAMECONTROLLER_USE_BUTTON_LABELS,
               bool_hint)

CENTURION_HINT(game_controller_type, SDL_HINT_GAMECONTROLLERTYPE, string_hint)

CENTURION_HINT(game_controller_config,
               SDL_HINT_GAMECONTROLLERCONFIG,
               string_hint)

CENTURION_HINT(game_controller_config_file,
               SDL_HINT_GAMECONTROLLERCONFIG_FILE,
               string_hint)

CENTURION_HINT(game_controller_ignore_devices,
               SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES,
               string_hint)

CENTURION_HINT(game_controller_ignore_devices_except,
               SDL_HINT_GAMECONTROLLER_IGNORE_DEVICES_EXCEPT,
               string_hint)

CENTURION_HINT(grab_keyboard, SDL_HINT_GRAB_KEYBOARD, bool_hint)

CENTURION_HINT(idle_timer_disabled, SDL_HINT_IDLE_TIMER_DISABLED, bool_hint)

CENTURION_HINT(ime_internal_editing, SDL_HINT_IME_INTERNAL_EDITING, bool_hint)

CENTURION_HINT(joystick_allow_background_events,
               SDL_HINT_JOYSTICK_ALLOW_BACKGROUND_EVENTS,
               bool_hint)

CENTURION_HINT(joystick_use_hidapi, SDL_HINT_JOYSTICK_HIDAPI, bool_hint)

CENTURION_HINT(joystick_use_hidapi_ps4, SDL_HINT_JOYSTICK_HIDAPI_PS4, bool_hint)

CENTURION_HINT(JoystickUseHIDAPIRumble,
               SDL_HINT_JOYSTICK_HIDAPI_PS4_RUMBLE,
               bool_hint)

CENTURION_HINT(joystick_use_hidapi_steam,
               SDL_HINT_JOYSTICK_HIDAPI_STEAM,
               bool_hint)

CENTURION_HINT(joystick_use_hidapi_switch,
               SDL_HINT_JOYSTICK_HIDAPI_SWITCH,
               bool_hint)

CENTURION_HINT(joystick_use_hidapi_xbox,
               SDL_HINT_JOYSTICK_HIDAPI_XBOX,
               bool_hint)

CENTURION_HINT(joystick_use_hidapi_game_cube,
               SDL_HINT_JOYSTICK_HIDAPI_GAMECUBE,
               bool_hint)

CENTURION_HINT(mac_background_app, SDL_HINT_MAC_BACKGROUND_APP, bool_hint)

CENTURION_HINT(mac_ctrl_click_emulate_right_click,
               SDL_HINT_MAC_CTRL_CLICK_EMULATE_RIGHT_CLICK,
               bool_hint)

CENTURION_HINT(mouse_focus_clickthrough,
               SDL_HINT_MOUSE_FOCUS_CLICKTHROUGH,
               bool_hint)

CENTURION_HINT(mouse_relative_mode_warp,
               SDL_HINT_MOUSE_RELATIVE_MODE_WARP,
               bool_hint)

CENTURION_HINT(mouse_double_click_time,
               SDL_HINT_MOUSE_DOUBLE_CLICK_TIME,
               int_hint)

CENTURION_HINT(mouse_double_click_radius,
               SDL_HINT_MOUSE_DOUBLE_CLICK_RADIUS,
               int_hint)

CENTURION_HINT(no_signal_handlers, SDL_HINT_NO_SIGNAL_HANDLERS, bool_hint)

CENTURION_HINT(direct_3d_11_debug, SDL_HINT_RENDER_DIRECT3D11_DEBUG, bool_hint)

CENTURION_HINT(direct_3D_thread_safe,
               SDL_HINT_RENDER_DIRECT3D_THREADSAFE,
               bool_hint)

CENTURION_HINT(opengl_es_driver, SDL_HINT_OPENGL_ES_DRIVER, bool_hint)

CENTURION_HINT(orientations, SDL_HINT_ORIENTATIONS, string_hint)

CENTURION_HINT(enable_opengl_shaders, SDL_HINT_RENDER_OPENGL_SHADERS, bool_hint)

CENTURION_HINT(enable_vsync, SDL_HINT_RENDER_VSYNC, bool_hint)

CENTURION_HINT(allow_screensaver, SDL_HINT_VIDEO_ALLOW_SCREENSAVER, bool_hint)

CENTURION_HINT(video_external_context,
               SDL_HINT_VIDEO_EXTERNAL_CONTEXT,
               bool_hint)

CENTURION_HINT(disable_high_dpi, SDL_HINT_VIDEO_HIGHDPI_DISABLED, bool_hint)

CENTURION_HINT(mac_fullscreen_spaces,
               SDL_HINT_VIDEO_MAC_FULLSCREEN_SPACES,
               bool_hint)

CENTURION_HINT(minimize_on_focus_loss,
               SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS,
               bool_hint)

CENTURION_HINT(mouse_normal_speed_scale,
               SDL_HINT_MOUSE_NORMAL_SPEED_SCALE,
               float_hint)

CENTURION_HINT(mouse_relative_speed_scale,
               SDL_HINT_MOUSE_RELATIVE_SPEED_SCALE,
               float_hint)

CENTURION_HINT(x11_net_wm_ping, SDL_HINT_VIDEO_X11_NET_WM_PING, bool_hint)

CENTURION_HINT(x11_net_wm_bypass_compositor,
               SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR,
               bool_hint)

CENTURION_HINT(x11_force_egl, SDL_HINT_VIDEO_X11_FORCE_EGL, bool_hint)

CENTURION_HINT(x11_xinerama, SDL_HINT_VIDEO_X11_XINERAMA, bool_hint)

CENTURION_HINT(x11_xrandr, SDL_HINT_VIDEO_X11_XRANDR, bool_hint)

CENTURION_HINT(x11_xvidmode, SDL_HINT_VIDEO_X11_XVIDMODE, bool_hint)

CENTURION_HINT(x11_window_visual_id,
               SDL_HINT_VIDEO_X11_WINDOW_VISUALID,
               string_hint)

CENTURION_HINT(windows_disable_thread_naming,
               SDL_HINT_WINDOWS_DISABLE_THREAD_NAMING,
               bool_hint)

CENTURION_HINT(window_share_pixel_format,
               SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT,
               string_hint)

CENTURION_HINT(windows_enable_message_loop,
               SDL_HINT_WINDOWS_ENABLE_MESSAGELOOP,
               bool_hint)

CENTURION_HINT(windows_no_close_on_alt_f4,
               SDL_HINT_WINDOWS_NO_CLOSE_ON_ALT_F4,
               bool_hint)

CENTURION_HINT(window_frame_usable_while_cursor_hidden,
               SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN,
               bool_hint)

CENTURION_HINT(windows_int_resource_icon,
               SDL_HINT_WINDOWS_INTRESOURCE_ICON,
               string_hint)

CENTURION_HINT(windows_int_resource_icon_small,
               SDL_HINT_WINDOWS_INTRESOURCE_ICON_SMALL,
               string_hint)

CENTURION_HINT(win_rt_privacy_policy_label,
               SDL_HINT_WINRT_PRIVACY_POLICY_LABEL,
               string_hint)

CENTURION_HINT(win_rt_privacy_policy_url,
               SDL_HINT_WINRT_PRIVACY_POLICY_URL,
               string_hint)

CENTURION_HINT(WinRTHandleBackButton,
               SDL_HINT_WINRT_HANDLE_BACK_BUTTON,
               int_hint)

CENTURION_HINT(mouse_touch_events, SDL_HINT_MOUSE_TOUCH_EVENTS, bool_hint)

CENTURION_HINT(raspberry_pi_video_layer, SDL_HINT_RPI_VIDEO_LAYER, int_hint)

CENTURION_HINT(render_batching, SDL_HINT_RENDER_BATCHING, bool_hint)

CENTURION_HINT(return_key_hides_ime, SDL_HINT_RETURN_KEY_HIDES_IME, bool_hint)

CENTURION_HINT(touch_mouse_events, SDL_HINT_TOUCH_MOUSE_EVENTS, bool_hint)

CENTURION_HINT(thread_stack_size, SDL_HINT_THREAD_STACK_SIZE, unsigned_int_hint)

CENTURION_HINT(timer_resolution, SDL_HINT_TIMER_RESOLUTION, unsigned_int_hint)

CENTURION_HINT(tv_remote_as_joystick, SDL_HINT_TV_REMOTE_AS_JOYSTICK, bool_hint)

CENTURION_HINT(qt_wayland_window_flags,
               SDL_HINT_QTWAYLAND_WINDOW_FLAGS,
               string_hint)

CENTURION_HINT(xinput_enabled, SDL_HINT_XINPUT_ENABLED, bool_hint)

CENTURION_HINT(xinput_use_old_joystick_mapping,
               SDL_HINT_XINPUT_USE_OLD_JOYSTICK_MAPPING,
               bool_hint)

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
 * @tparam priority the priority that will be used, defaults to `normal`.
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
auto set_hint(const Value& value) -> bool
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
 * @class callback
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
