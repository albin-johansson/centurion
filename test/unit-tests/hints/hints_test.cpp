#include "hints/hints.hpp"

#include <gtest/gtest.h>

#include "hints/android_hints.hpp"
#include "hints/apple_tv_hints.hpp"
#include "hints/common_hints.hpp"
#include "hints/controller_hints.hpp"
#include "hints/d3d_hints.hpp"
#include "hints/emscripten_hints.hpp"
#include "hints/enum_hint.hpp"
#include "hints/joystick_hints.hpp"
#include "hints/mac_hints.hpp"
#include "hints/mouse_hints.hpp"
#include "hints/qtwayland_hints.hpp"
#include "hints/raspberry_pi_hints.hpp"
#include "hints/windows_hints.hpp"
#include "hints/winrt_hints.hpp"
#include "hints/x11_hints.hpp"
#include "hints/xinput_hints.hpp"
#include "typed_test_macros.hpp"
#include "video/window.hpp"

using boolean_hints = testing::Types<cen::hint::double_buffer,
                                     cen::hint::accelerometer_as_joystick,
                                     cen::hint::allow_top_most,
                                     cen::hint::bmp_save_legacy_format,
                                     cen::hint::enable_steam_controllers,
                                     cen::hint::grab_keyboard,
                                     cen::hint::idle_timer_disabled,
                                     cen::hint::ime_internal_editing,
                                     cen::hint::no_signal_handlers,
                                     cen::hint::enable_opengl_shaders,
                                     cen::hint::vsync,
                                     cen::hint::opengl_es_driver,
                                     cen::hint::allow_screensaver,
#if SDL_VERSION_ATLEAST(2, 0, 12)
                                     cen::hint::video_external_context,
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
                                     cen::hint::disable_high_dpi,
                                     cen::hint::minimize_on_focus_loss,
                                     cen::hint::window_frame_usable_while_cursor_hidden,
                                     cen::hint::mouse_touch_events,
                                     cen::hint::render_batching,
                                     cen::hint::return_key_hides_ime,
                                     cen::hint::touch_mouse_events,
                                     cen::hint::tv_remote_as_joystick,
#if SDL_VERSION_ATLEAST(2, 0, 14)
                                     cen::hint::treat_time_critical_as_real_time,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
                                     cen::hint::appletv::controller_ui_events,
                                     cen::hint::appletv::remote_allow_rotation,
#if SDL_VERSION_ATLEAST(2, 0, 14)
                                     cen::hint::emscripten::asyncify,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
                                     cen::hint::xinput::is_enabled,
                                     cen::hint::xinput::use_old_joystick_mapping,
                                     cen::hint::mouse::focus_clickthrough,
                                     cen::hint::mouse::relative_mode_warp,
#if SDL_VERSION_ATLEAST(2, 0, 14)
                                     cen::hint::mouse::relative_scaling,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
                                     cen::hint::d3d::v11_debug,
                                     cen::hint::d3d::thread_safe,
#if SDL_VERSION_ATLEAST(2, 0, 12)
                                     cen::hint::controller::use_button_labels,
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)
                                     cen::hint::winrt::handle_back_button,
                                     cen::hint::windows::no_thread_naming,
                                     cen::hint::windows::enable_message_loop,
                                     cen::hint::windows::no_close_on_alt_f4,
                                     cen::hint::mac::background_app,
                                     cen::hint::mac::ctrl_click_emulate_right_click,
                                     cen::hint::mac::fullscreen_spaces,
                                     cen::hint::android::block_on_pause,
                                     cen::hint::android::trap_back_button,

#if SDL_VERSION_ATLEAST(2, 0, 14)
                                     cen::hint::android::pause_background_audio,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

                                     cen::hint::joystick::allow_background_events,
                                     cen::hint::joystick::use_hidapi,

#if SDL_VERSION_ATLEAST(2, 0, 14)
                                     cen::hint::joystick::use_hidapi_ps5,
                                     cen::hint::joystick::use_raw_input,
                                     cen::hint::joystick::hidapi_correlate_xinput,
                                     cen::hint::joystick::linux_use_deadzones,
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

                                     cen::hint::joystick::use_hidapi_ps4,
                                     cen::hint::joystick::use_hidapi_ps4_rumble,
                                     cen::hint::joystick::use_hidapi_steam,
                                     cen::hint::joystick::use_hidapi_switch,
                                     cen::hint::joystick::use_hidapi_xbox,

#if SDL_VERSION_ATLEAST(2, 0, 12)
                                     cen::hint::joystick::use_hidapi_game_cube,
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

                                     cen::hint::x11::net_wm_ping,
                                     cen::hint::x11::net_wm_bypass_compositor,

#if SDL_VERSION_ATLEAST(2, 0, 12)
                                     cen::hint::x11::force_egl,
#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

                                     cen::hint::x11::xinerama,
                                     cen::hint::x11::xrandr,
                                     cen::hint::x11::xvidmode>;

using integer_hints =
    testing::Types<cen::hint::event_logging,
                   cen::hint::raspberrypi::video_layer,
                   cen::hint::mouse::double_click_time,
                   cen::hint::mouse::double_click_radius,
                   cen::hint::android::apk_expansion_main_file_version,
                   cen::hint::android::apk_expansion_patch_file_version>;

using unsigned_hints =
    testing::Types<cen::hint::thread_stack_size, cen::hint::timer_resolution>;

using float_hints = testing::Types<cen::hint::mouse::normal_speed_scale,
                                   cen::hint::mouse::relative_speed_scale>;

template <typename Hint, typename T>
void test_hint(T&& callable)
{
  const auto optPrev = cen::get_hint<Hint>();

  callable();

  if (optPrev)
  {
    cen::set_hint<Hint, cen::hint_priority::low>(*optPrev);
  }
}

template <typename Hint>
void test_string_hint(cen::str str)
{
  test_hint<Hint>([str] {
    ASSERT_TRUE(cen::set_hint<Hint>(str));
    ASSERT_STREQ(str, cen::get_hint<Hint>().value());
  });
}

template <typename Hint, typename T>
void test_enum_value(const T& value)
{
  ASSERT_TRUE(cen::set_hint<Hint>(value));
  ASSERT_EQ(value, cen::get_hint<Hint>());
}

template <typename Hint, typename... T>
void test_enum_hint(T&&... value)
{
  test_hint<Hint>([=] { (test_enum_value<Hint>(value), ...); });
}

template <typename T>
class HintTest : public testing::Test
{
 public:
  [[maybe_unused]] static void TearDownTestSuite()
  {
    // Reset our changes so that other tests don't break
    cen::clear_hints();
  }
};

CENTURION_DEFINE_TYPED_TEST_FROM_CLASS(BoolHintTest, HintTest, boolean_hints)
{
  ASSERT_TRUE(TypeParam::from_string("1"));
  ASSERT_FALSE(TypeParam::from_string("0"));

  test_hint<TypeParam>([] {
    ASSERT_TRUE(cen::set_hint<TypeParam>(true));
    ASSERT_TRUE(cen::get_hint<TypeParam>().value());

    ASSERT_TRUE(cen::set_hint<TypeParam>(false));
    ASSERT_FALSE(cen::get_hint<TypeParam>().value());
  });
}

CENTURION_DEFINE_TYPED_TEST_FROM_CLASS(IntHintTest, HintTest, integer_hints)
{
  ASSERT_EQ(123, TypeParam::from_string("123"));

  test_hint<TypeParam>([] {
    ASSERT_TRUE(cen::set_hint<TypeParam>(1));
    ASSERT_EQ(1, cen::get_hint<TypeParam>().value());

    ASSERT_TRUE(cen::set_hint<TypeParam>(0));
    ASSERT_EQ(0, cen::get_hint<TypeParam>().value());
  });
}

CENTURION_DEFINE_TYPED_TEST_FROM_CLASS(UnsignedHintTest, HintTest, unsigned_hints)
{
  ASSERT_EQ(42, TypeParam::from_string("42"));

  test_hint<TypeParam>([] {
    ASSERT_TRUE(cen::set_hint<TypeParam>(1u));
    ASSERT_EQ(1u, cen::get_hint<TypeParam>().value());

    ASSERT_TRUE(cen::set_hint<TypeParam>(0u));
    ASSERT_EQ(0u, cen::get_hint<TypeParam>().value());
  });
}

CENTURION_DEFINE_TYPED_TEST_FROM_CLASS(FloatHintTest, HintTest, float_hints)
{
  ASSERT_FLOAT_EQ(12.3f, TypeParam::from_string("12.3"));

  test_hint<TypeParam>([] {
    ASSERT_TRUE(cen::set_hint<TypeParam>(1.0f));
    ASSERT_EQ(1.0f, cen::get_hint<TypeParam>().value());

    ASSERT_TRUE(cen::set_hint<TypeParam>(0.75f));
    ASSERT_EQ(0.75f, cen::get_hint<TypeParam>().value());
  });
}

CENTURION_REGISTER_TYPED_TEST(BoolHintTest, boolean_hints);
CENTURION_REGISTER_TYPED_TEST(IntHintTest, integer_hints);
CENTURION_REGISTER_TYPED_TEST(UnsignedHintTest, unsigned_hints);
CENTURION_REGISTER_TYPED_TEST(FloatHintTest, float_hints);

using BasicHintTest = HintTest<void>;

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(BasicHintTest, DisplayUsableBounds)
{
  using cen::hint::display_usable_bounds;
  test_string_hint<display_usable_bounds>("10, 20, 30, 40");
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(BasicHintTest, WindowSharePixelFormat)
{
  using cen::hint::window_share_pixel_format;

  cen::window window;
  const auto str = cen::detail::address_of(window.get());

  test_string_hint<window_share_pixel_format>(str.c_str());
}

TEST_F(BasicHintTest, KeyboardElement)
{
  using cen::hint::emscripten::keyboard_element;
  test_string_hint<keyboard_element>("#window");
  test_string_hint<keyboard_element>("#document");
  test_string_hint<keyboard_element>("#screen");
  test_string_hint<keyboard_element>("#canvas");
}

TEST_F(BasicHintTest, WindowFlags)
{
  using cen::hint::qtwayland::window_flags;
  test_string_hint<window_flags>("OverridesSystemGestures StaysOnTop");
  test_string_hint<window_flags>("BypassWindowManager");
  test_string_hint<window_flags>("");
}

TEST_F(BasicHintTest, ConfigFile)
{
  using cen::hint::controller::config_file;
  test_string_hint<config_file>("foo");
}

TEST_F(BasicHintTest, IgnoreDevices)
{
  using cen::hint::controller::ignore_devices;
  test_string_hint<ignore_devices>("0xAAAA");
}

TEST_F(BasicHintTest, IgnoreDevicesExcept)
{
  using cen::hint::controller::ignore_devices_except;
  test_string_hint<ignore_devices_except>("0xBBBB, 0xCCCC");
}

TEST_F(BasicHintTest, PrivacyPolicyLabel)
{
  using cen::hint::winrt::privacy_policy_label;
  test_string_hint<privacy_policy_label>("foo");
}

TEST_F(BasicHintTest, PrivacyPolicyURL)
{
  using cen::hint::winrt::privacy_policy_url;
  test_string_hint<privacy_policy_url>("bar");
}

TEST_F(BasicHintTest, IntResourceIcon)
{
  using cen::hint::windows::int_resource_icon;
  test_string_hint<int_resource_icon>("foo");
}

TEST_F(BasicHintTest, IntResourceIconSmall)
{
  using cen::hint::windows::int_resource_icon_small;
  test_string_hint<int_resource_icon_small>("bar");
}

#if SDL_VERSION_ATLEAST(2, 0, 12)

TEST_F(BasicHintTest, WindowVisualID)
{
  using cen::hint::x11::window_visual_id;
  test_string_hint<window_visual_id>("foo");
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

#if SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(BasicHintTest, PreferredLocales)
{
  using cen::hint::preferred_locales;
  test_string_hint<preferred_locales>("en_GB,en_US,se");
}

TEST_F(BasicHintTest, ThreadPriorityPolicy)
{
  using cen::hint::thread_priority_policy;
  test_string_hint<thread_priority_policy>("current");
}

TEST_F(BasicHintTest, AudioDeviceAppName)
{
  using cen::hint::audio_device_app_name;
  test_string_hint<audio_device_app_name>("Centurion");
}

TEST_F(BasicHintTest, AudioDeviceStreamName)
{
  using cen::hint::audio_device_stream_name;
  test_string_hint<audio_device_stream_name>("Audio Stream");
}

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

TEST_F(BasicHintTest, RenderDriver)
{
  using cen::hint::render_driver;
  test_enum_hint<render_driver>(render_driver::value::direct3d,
                                render_driver::value::opengl,
                                render_driver::value::opengles,
                                render_driver::value::opengles2,
                                render_driver::value::metal,
                                render_driver::value::software);

  ASSERT_EQ(render_driver::value::direct3d, render_driver::from_string("direct3d"));
}

TEST_F(BasicHintTest, AudioResamplingMode)
{
  using cen::hint::audio_resampling_mode;
  test_enum_hint<audio_resampling_mode>(audio_resampling_mode::value::normal,
                                        audio_resampling_mode::value::fast,
                                        audio_resampling_mode::value::medium,
                                        audio_resampling_mode::value::best);

  ASSERT_EQ(audio_resampling_mode::value::medium,
            audio_resampling_mode::from_string("medium"));
}

TEST_F(BasicHintTest, ScaleQuality)
{
  using cen::hint::scale_quality;
  test_enum_hint<scale_quality>(scale_quality::value::nearest,
                                scale_quality::value::linear,
                                scale_quality::value::best);
}

TEST_F(BasicHintTest, FramebufferAcceleration)
{
  using cen::hint::framebuffer_acceleration;
  test_enum_hint<framebuffer_acceleration>(framebuffer_acceleration::value::off,
                                           framebuffer_acceleration::value::on,
                                           framebuffer_acceleration::value::direct3d,
                                           framebuffer_acceleration::value::opengl,
                                           framebuffer_acceleration::value::opengles,
                                           framebuffer_acceleration::value::opengles2,
                                           framebuffer_acceleration::value::metal,
                                           framebuffer_acceleration::value::software);
}

TEST_F(BasicHintTest, AudioCategory)
{
  using cen::hint::audio_category;
  test_enum_hint<audio_category>(audio_category::value::ambient,
                                 audio_category::value::playback);
}

TEST_F(BasicHintTest, WaveRIFFChunkSize)
{
  using cen::hint::wave_riff_chunk_size;
  test_enum_hint<wave_riff_chunk_size>(wave_riff_chunk_size::value::force,
                                       wave_riff_chunk_size::value::ignore,
                                       wave_riff_chunk_size::value::ignore_zero,
                                       wave_riff_chunk_size::value::maximum);
}

TEST_F(BasicHintTest, WaveTruncation)
{
  using cen::hint::wave_truncation;
  test_enum_hint<wave_truncation>(wave_truncation::value::drop_block,
                                  wave_truncation::value::drop_frame,
                                  wave_truncation::value::strict,
                                  wave_truncation::value::very_strict);
}

TEST_F(BasicHintTest, WaveFactChunk)
{
  using cen::hint::wave_fact_chunk;
  test_enum_hint<wave_fact_chunk>(wave_fact_chunk::value::strict,
                                  wave_fact_chunk::value::ignore_zero,
                                  wave_fact_chunk::value::ignore,
                                  wave_fact_chunk::value::truncate);
}

TEST_F(BasicHintTest, LogicalSizeMode)
{
  using cen::hint::logical_size_mode;
  test_enum_hint<logical_size_mode>(logical_size_mode::value::letterbox,
                                    logical_size_mode::value::overscan);
}

TEST_F(BasicHintTest, ContentOrientation)
{
  using cen::hint::qtwayland::content_orientation;
  test_enum_hint<content_orientation>(content_orientation::value::primary,
                                      content_orientation::value::portrait,
                                      content_orientation::value::landscape,
                                      content_orientation::value::inverted_portrait,
                                      content_orientation::value::inverted_landscape);
}

TEST_F(BasicHintTest, D3DCompiler)
{
  using cen::hint::windows::d3d_compiler;
  test_enum_hint<d3d_compiler>(d3d_compiler::value::v46,
                               d3d_compiler::value::v43,
                               d3d_compiler::value::none);
}

TEST_F(BasicHintTest, AddHintCallback)
{
  using cen::hint::render_driver;
  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::software);

  const auto callable =
      [](void* data, const cen::str hint, const cen::str oldVal, const cen::str newVal) {
        static bool first = true;
        if (first)
        {
          first = false;
        }
        else
        {
          const auto ptr = reinterpret_cast<int*>(data);

          ASSERT_TRUE(ptr);
          ASSERT_EQ(7, *ptr);

          ASSERT_STREQ(SDL_HINT_RENDER_DRIVER, hint);
          ASSERT_STREQ("software", oldVal);
          ASSERT_STREQ("opengl", newVal);
        }
      };

  int data = 7;
  auto handle = cen::add_hint_callback<render_driver>(callable, &data);
  ASSERT_EQ(&data, handle.user_data());

  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::software);

  handle.disconnect();

  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::opengl);
}

#if CENTURION_HAS_FEATURE_CONCEPTS

TEST_F(BasicHintTest, AddHintCallbackExFull)
{
  using cen::hint::render_driver;
  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::software);

  const auto callable = [](int* ptr,
                           const cen::str name,
                           const render_driver::value oldValue,
                           const render_driver::value newValue) {
    static bool first = true;
    if (first)
    {
      first = false;
    }
    else
    {
      ASSERT_TRUE(ptr);
      ASSERT_EQ(42, *ptr);

      ASSERT_STREQ(SDL_HINT_RENDER_DRIVER, name);

      ASSERT_EQ(render_driver::value::software, oldValue);
      ASSERT_EQ(render_driver::value::opengl, newValue);
    }
  };

  int data = 42;
  auto handle = cen::add_hint_callback_ex<render_driver>(callable, &data);
  ASSERT_EQ(&data, handle.user_data());

  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::software);

  handle.disconnect();

  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::opengl);
}

#endif  // CENTURION_HAS_FEATURE_CONCEPTS

TEST_F(BasicHintTest, HintPriority)
{
  using prio = cen::hint_priority;
  ASSERT_EQ(prio::low, static_cast<prio>(SDL_HINT_DEFAULT));
  ASSERT_EQ(prio::normal, static_cast<prio>(SDL_HINT_NORMAL));
  ASSERT_EQ(prio::override, static_cast<prio>(SDL_HINT_OVERRIDE));

  ASSERT_EQ(static_cast<prio>(SDL_HINT_DEFAULT), prio::low);
  ASSERT_EQ(static_cast<prio>(SDL_HINT_NORMAL), prio::normal);
  ASSERT_EQ(static_cast<prio>(SDL_HINT_OVERRIDE), prio::override);
}
