#include "hints.hpp"

#include <gtest/gtest.h>

#include "window.hpp"

using boolean_hints =
    testing::Types<cen::hint::double_buffer,
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
                   cen::hint::video_external_context,
                   cen::hint::disable_high_dpi,
                   cen::hint::minimize_on_focus_loss,
                   cen::hint::window_frame_usable_while_cursor_hidden,
                   cen::hint::mouse_touch_events,
                   cen::hint::render_batching,
                   cen::hint::return_key_hides_ime,
                   cen::hint::touch_mouse_events,
                   cen::hint::tv_remote_as_joystick,
                   cen::hint::appletv::controller_ui_events,
                   cen::hint::appletv::remote_allow_rotation,
                   cen::hint::xinput::is_enabled,
                   cen::hint::xinput::use_old_joystick_mapping,
                   cen::hint::mouse::focus_clickthrough,
                   cen::hint::mouse::relative_mode_warp,
                   cen::hint::d3d::v11_debug,
                   cen::hint::d3d::thread_safe,
                   cen::hint::gamecontroller::use_button_labels,
                   cen::hint::winrt::handle_back_button,
                   cen::hint::windows::no_thread_naming,
                   cen::hint::windows::enable_message_loop,
                   cen::hint::windows::no_close_on_alt_f4,
                   cen::hint::mac::background_app,
                   cen::hint::mac::ctrl_click_emulate_right_click,
                   cen::hint::mac::fullscreen_spaces,
                   cen::hint::android::block_on_pause,
                   cen::hint::android::trap_back_button,
                   cen::hint::joystick::allow_background_events,
                   cen::hint::joystick::use_hidapi,
                   cen::hint::joystick::use_hidapi_ps4,
                   cen::hint::joystick::use_hidapi_ps4_rumble,
                   cen::hint::joystick::use_hidapi_steam,
                   cen::hint::joystick::use_hidapi_switch,
                   cen::hint::joystick::use_hidapi_xbox,
                   cen::hint::joystick::use_hidapi_game_cube,
                   cen::hint::x11::net_wm_ping,
                   cen::hint::x11::net_wm_bypass_compositor,
                   cen::hint::x11::force_egl,
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

  if (optPrev) {
    cen::set_hint<Hint, cen::hint_priority::low>(*optPrev);
  }
}

template <typename Hint>
void test_string_hint(cen::czstring str)
{
  test_hint<Hint>([str] {
    ASSERT_TRUE(cen::set_hint<Hint>(str));
    EXPECT_STREQ(str, cen::get_hint<Hint>().value());
  });
}

template <typename T>
class HintTest : public testing::Test
{};

template <typename T>
using BoolHintTest = HintTest<T>;

template <typename T>
using IntHintTest = HintTest<T>;

template <typename T>
using UnsignedHintTest = HintTest<T>;

template <typename T>
using FloatHintTest = HintTest<T>;

template <typename T>
using StringHintTest = HintTest<T>;

TYPED_TEST_SUITE_P(BoolHintTest);
TYPED_TEST_SUITE_P(IntHintTest);
TYPED_TEST_SUITE_P(UnsignedHintTest);
TYPED_TEST_SUITE_P(FloatHintTest);
TYPED_TEST_SUITE_P(StringHintTest);

TYPED_TEST_P(BoolHintTest, SetHint)
{
  test_hint<TypeParam>([] {
    ASSERT_TRUE(cen::set_hint<TypeParam>(true));
    EXPECT_TRUE(cen::get_hint<TypeParam>().value());

    ASSERT_TRUE(cen::set_hint<TypeParam>(false));
    EXPECT_FALSE(cen::get_hint<TypeParam>().value());
  });
}

TYPED_TEST_P(IntHintTest, SetHint)
{
  test_hint<TypeParam>([] {
    ASSERT_TRUE(cen::set_hint<TypeParam>(1));
    EXPECT_EQ(1, cen::get_hint<TypeParam>().value());

    ASSERT_TRUE(cen::set_hint<TypeParam>(0));
    EXPECT_EQ(0, cen::get_hint<TypeParam>().value());
  });
}

TYPED_TEST_P(FloatHintTest, SetHint)
{
  test_hint<TypeParam>([] {
    ASSERT_TRUE(cen::set_hint<TypeParam>(1.0f));
    EXPECT_EQ(1.0f, cen::get_hint<TypeParam>().value());

    ASSERT_TRUE(cen::set_hint<TypeParam>(0.75f));
    EXPECT_EQ(0.75f, cen::get_hint<TypeParam>().value());
  });
}

TYPED_TEST_P(UnsignedHintTest, SetHint)
{
  test_hint<TypeParam>([] {
    ASSERT_TRUE(cen::set_hint<TypeParam>(1u));
    EXPECT_EQ(1u, cen::get_hint<TypeParam>().value());

    ASSERT_TRUE(cen::set_hint<TypeParam>(0u));
    EXPECT_EQ(0u, cen::get_hint<TypeParam>().value());
  });
}

REGISTER_TYPED_TEST_SUITE_P(BoolHintTest, SetHint);
REGISTER_TYPED_TEST_SUITE_P(IntHintTest, SetHint);
REGISTER_TYPED_TEST_SUITE_P(UnsignedHintTest, SetHint);
REGISTER_TYPED_TEST_SUITE_P(FloatHintTest, SetHint);

INSTANTIATE_TYPED_TEST_SUITE_P(BooleanHints, BoolHintTest, boolean_hints);
INSTANTIATE_TYPED_TEST_SUITE_P(IntegerHints, IntHintTest, integer_hints);
INSTANTIATE_TYPED_TEST_SUITE_P(UnsignedHints, UnsignedHintTest, unsigned_hints);
INSTANTIATE_TYPED_TEST_SUITE_P(FloatHints, FloatHintTest, float_hints);

TEST(Hints, DisplayUsableBounds)
{
  using cen::hint::display_usable_bounds;
  test_string_hint<display_usable_bounds>("10, 20, 30, 40");
}

TEST(Hints, WindowSharePixelFormat)
{
  using cen::hint::window_share_pixel_format;

  cen::window window;
  const auto str = cen::detail::address_of(window.get());

  test_string_hint<window_share_pixel_format>(str.c_str());
}

TEST(Hints, KeyboardElement)
{
  using cen::hint::emscripten::keyboard_element;
  test_string_hint<keyboard_element>("#window");
  test_string_hint<keyboard_element>("#document");
  test_string_hint<keyboard_element>("#screen");
  test_string_hint<keyboard_element>("#canvas");
}

TEST(Hints, WindowFlags)
{
  using cen::hint::qtwayland::window_flags;
  test_string_hint<window_flags>("OverridesSystemGestures StaysOnTop");
  test_string_hint<window_flags>("BypassWindowManager");
  test_string_hint<window_flags>("");
}

TEST(Hints, ConfigFile)
{
  using cen::hint::gamecontroller::config_file;
  test_string_hint<config_file>("foo");
}

TEST(Hints, IgnoreDevices)
{
  using cen::hint::gamecontroller::ignore_devices;
  test_string_hint<ignore_devices>("0xAAAA");
}

TEST(Hints, IgnoreDevicesExcept)
{
  using cen::hint::gamecontroller::ignore_devices_except;
  test_string_hint<ignore_devices_except>("0xBBBB, 0xCCCC");
}

TEST(Hints, PrivacyPolicyLabel)
{
  using cen::hint::winrt::privacy_policy_label;
  test_string_hint<privacy_policy_label>("foo");
}

TEST(Hints, PrivacyPolicyURL)
{
  using cen::hint::winrt::privacy_policy_url;
  test_string_hint<privacy_policy_url>("bar");
}

TEST(Hints, IntResourceIcon)
{
  using cen::hint::windows::int_resource_icon;
  test_string_hint<int_resource_icon>("foo");
}

TEST(Hints, IntResourceIconSmall)
{
  using cen::hint::windows::int_resource_icon_small;
  test_string_hint<int_resource_icon_small>("bar");
}

TEST(Hints, WindowVisualID)
{
  using cen::hint::x11::window_visual_id;
  test_string_hint<window_visual_id>("foo");
}

TEST(Hints, AddHintCallback)
{
  using cen::hint::render_driver;
  cen::set_hint<render_driver>(render_driver::value::software);

  int data = 7;
  auto handle = cen::add_hint_callback<render_driver>(
      [](void* data,
         cen::czstring hint,
         cen::czstring oldVal,
         cen::czstring newVal) {
        static bool first = true;
        if (first) {
          first = false;
        } else {
          const auto ptr = reinterpret_cast<int*>(data);

          ASSERT_TRUE(ptr);
          EXPECT_EQ(7, *ptr);

          EXPECT_STREQ(SDL_HINT_RENDER_DRIVER, hint);
          EXPECT_STREQ("software", oldVal);
          EXPECT_STREQ("opengl", newVal);
        }
      },
      &data);
  EXPECT_EQ(&data, handle.user_data());

  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::software);

  handle.disconnect();

  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::opengl);
}

TEST(Hints, HintPriority)
{
  using prio = cen::hint_priority;
  EXPECT_EQ(prio::low, static_cast<prio>(SDL_HINT_DEFAULT));
  EXPECT_EQ(prio::normal, static_cast<prio>(SDL_HINT_NORMAL));
  EXPECT_EQ(prio::override, static_cast<prio>(SDL_HINT_OVERRIDE));

  EXPECT_EQ(static_cast<prio>(SDL_HINT_DEFAULT), prio::low);
  EXPECT_EQ(static_cast<prio>(SDL_HINT_NORMAL), prio::normal);
  EXPECT_EQ(static_cast<prio>(SDL_HINT_OVERRIDE), prio::override);
}
