#ifndef CENTURION_COMMON_HINTS_HEADER
#define CENTURION_COMMON_HINTS_HEADER

#include <SDL.h>

#include <utility>  // make_pair

#include "../core/str.hpp"
#include "../detail/hints_impl.hpp"
#include "enum_hint.hpp"

namespace cen::hint {

/// \addtogroup hints
/// \{

/**
 * \class render_driver
 *
 * \brief Used to specify the render driver that will be used.
 */
struct render_driver final : enum_hint<render_driver>
{
  static inline constexpr detail::string_map<value, 6> map{
      std::make_pair(value::direct3d, "direct3d"),
      std::make_pair(value::opengl, "opengl"),
      std::make_pair(value::opengles, "opengles"),
      std::make_pair(value::opengles2, "opengles2"),
      std::make_pair(value::metal, "metal"),
      std::make_pair(value::software, "software")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_RENDER_DRIVER;
  }
};

struct audio_resampling_mode final : enum_hint<audio_resampling_mode>
{
  static inline constexpr detail::string_map<value, 4> map{
      std::make_pair(value::normal, "default"),
      std::make_pair(value::fast, "fast"),
      std::make_pair(value::medium, "medium"),
      std::make_pair(value::best, "best")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_AUDIO_RESAMPLING_MODE;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 16)

struct audio_include_monitors final : detail::bool_hint<audio_include_monitors>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_AUDIO_INCLUDE_MONITORS;
  }
};

struct audio_device_stream_role final : detail::string_hint<audio_device_stream_role>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_AUDIO_DEVICE_STREAM_ROLE;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

struct scale_quality final : enum_hint<scale_quality>
{
  static inline constexpr detail::string_map<value, 3> map{
      std::make_pair(value::nearest, "nearest"),
      std::make_pair(value::linear, "linear"),
      std::make_pair(value::best, "best")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_RENDER_SCALE_QUALITY;
  }
};

struct framebuffer_acceleration final : enum_hint<framebuffer_acceleration>
{
  static inline constexpr detail::string_map<value, 8> map{
      std::make_pair(value::off, "0"),
      std::make_pair(value::on, "1"),
      std::make_pair(value::direct3d, "direct3d"),
      std::make_pair(value::opengl, "opengl"),
      std::make_pair(value::opengles, "opengles"),
      std::make_pair(value::opengles2, "opengles2"),
      std::make_pair(value::metal, "metal"),
      std::make_pair(value::software, "software")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_FRAMEBUFFER_ACCELERATION;
  }
};

struct audio_category final : enum_hint<audio_category>
{
  static inline constexpr detail::string_map<value, 2> map{
      std::make_pair(value::ambient, "ambient"),
      std::make_pair(value::playback, "playback")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_AUDIO_CATEGORY;
  }
};

struct wave_riff_chunk_size final : enum_hint<wave_riff_chunk_size>
{
  static inline constexpr detail::string_map<value, 4> map{
      std::make_pair(value::force, "force"),
      std::make_pair(value::ignore, "ignore"),
      std::make_pair(value::ignore_zero, "ignorezero"),
      std::make_pair(value::maximum, "maximum")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_WAVE_RIFF_CHUNK_SIZE;
  }
};

struct wave_truncation final : enum_hint<wave_truncation>
{
  static inline constexpr detail::string_map<value, 4> map{
      std::make_pair(value::drop_block, "dropblock"),
      std::make_pair(value::drop_frame, "dropframe"),
      std::make_pair(value::strict, "strict"),
      std::make_pair(value::very_strict, "verystrict")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_WAVE_TRUNCATION;
  }
};

struct wave_fact_chunk final : enum_hint<wave_fact_chunk>
{
  static inline constexpr detail::string_map<value, 4> map{
      std::make_pair(value::strict, "strict"),
      std::make_pair(value::ignore_zero, "ignorezero"),
      std::make_pair(value::ignore, "ignore"),
      std::make_pair(value::truncate, "truncate")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_WAVE_FACT_CHUNK;
  }
};

struct logical_size_mode final : enum_hint<logical_size_mode>
{
  static inline constexpr detail::string_map<value, 2> map{
      std::make_pair(value::letterbox, "letterbox"),
      std::make_pair(value::overscan, "overscan")};

  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_RENDER_LOGICAL_SIZE_MODE;
  }
};

struct accelerometer_as_joystick final : detail::bool_hint<accelerometer_as_joystick>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_ACCELEROMETER_AS_JOYSTICK;
  }
};

struct allow_top_most final : detail::bool_hint<allow_top_most>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_ALLOW_TOPMOST;
  }
};

struct bmp_save_legacy_format final : detail::bool_hint<bmp_save_legacy_format>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_BMP_SAVE_LEGACY_FORMAT;
  }
};

struct double_buffer final : detail::bool_hint<double_buffer>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_DOUBLE_BUFFER;
  }
};

struct enable_steam_controllers final : detail::bool_hint<enable_steam_controllers>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_ENABLE_STEAM_CONTROLLERS;
  }
};

struct grab_keyboard final : detail::bool_hint<grab_keyboard>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_GRAB_KEYBOARD;
  }
};

struct idle_timer_disabled final : detail::bool_hint<idle_timer_disabled>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_IDLE_TIMER_DISABLED;
  }
};

struct ime_internal_editing final : detail::bool_hint<ime_internal_editing>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_IME_INTERNAL_EDITING;
  }
};

struct no_signal_handlers final : detail::bool_hint<no_signal_handlers>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_NO_SIGNAL_HANDLERS;
  }
};

struct opengl_es_driver final : detail::bool_hint<opengl_es_driver>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_OPENGL_ES_DRIVER;
  }
};

struct enable_opengl_shaders final : detail::bool_hint<enable_opengl_shaders>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_RENDER_OPENGL_SHADERS;
  }
};

struct vsync final : detail::bool_hint<vsync>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_RENDER_VSYNC;
  }
};

struct allow_screensaver final : detail::bool_hint<allow_screensaver>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_ALLOW_SCREENSAVER;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 12)

struct video_external_context final : detail::bool_hint<video_external_context>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_EXTERNAL_CONTEXT;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

struct disable_high_dpi final : detail::bool_hint<disable_high_dpi>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_HIGHDPI_DISABLED;
  }
};

struct minimize_on_focus_loss final : detail::bool_hint<minimize_on_focus_loss>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_MINIMIZE_ON_FOCUS_LOSS;
  }
};

struct window_frame_usable_while_cursor_hidden final
    : detail::bool_hint<window_frame_usable_while_cursor_hidden>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_WINDOW_FRAME_USABLE_WHILE_CURSOR_HIDDEN;
  }
};

struct render_batching final : detail::bool_hint<render_batching>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_RENDER_BATCHING;
  }
};

struct return_key_hides_ime final : detail::bool_hint<return_key_hides_ime>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_RETURN_KEY_HIDES_IME;
  }
};

struct touch_mouse_events final : detail::bool_hint<touch_mouse_events>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_TOUCH_MOUSE_EVENTS;
  }
};

struct mouse_touch_events final : detail::bool_hint<mouse_touch_events>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_MOUSE_TOUCH_EVENTS;
  }
};

struct tv_remote_as_joystick final : detail::bool_hint<tv_remote_as_joystick>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_TV_REMOTE_AS_JOYSTICK;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 12)

struct display_usable_bounds final : detail::string_hint<display_usable_bounds>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_DISPLAY_USABLE_BOUNDS;
  }
};

#endif  // #if SDL_VERSION_ATLEAST(2, 0, 12)

struct orientations final : detail::string_hint<orientations>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_ORIENTATIONS;
  }
};

struct window_share_pixel_format final : detail::string_hint<window_share_pixel_format>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_VIDEO_WINDOW_SHARE_PIXEL_FORMAT;
  }
};

struct event_logging final : detail::int_hint<event_logging>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_EVENT_LOGGING;
  }
};

struct thread_stack_size final : detail::uint_hint<thread_stack_size>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_THREAD_STACK_SIZE;
  }
};

struct timer_resolution final : detail::uint_hint<timer_resolution>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_TIMER_RESOLUTION;
  }
};

#if SDL_VERSION_ATLEAST(2, 0, 14)

struct preferred_locales final : detail::string_hint<preferred_locales>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_PREFERRED_LOCALES;
  }
};

struct thread_priority_policy final : detail::string_hint<thread_priority_policy>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    // This hint could be enum-based, but it isn't clear whether or not there
    // may be implementation specific identifiers other than those of the listed
    // pthread identifiers. So, we let this be a string-based hint.
    return SDL_HINT_THREAD_PRIORITY_POLICY;
  }
};

struct treat_time_critical_as_real_time final
    : detail::bool_hint<treat_time_critical_as_real_time>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_THREAD_FORCE_REALTIME_TIME_CRITICAL;
  }
};

struct audio_device_app_name final : detail::string_hint<audio_device_app_name>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_AUDIO_DEVICE_APP_NAME;
  }
};

struct audio_device_stream_name final : detail::string_hint<audio_device_stream_name>
{
  [[nodiscard]] constexpr static auto name() noexcept -> str
  {
    return SDL_HINT_AUDIO_DEVICE_STREAM_NAME;
  }
};

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

/// \} End of group hints

}  // namespace cen::hint

#endif  // CENTURION_COMMON_HINTS_HEADER