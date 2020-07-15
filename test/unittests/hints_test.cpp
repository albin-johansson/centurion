#include "hints.hpp"

#include <catch.hpp>

#include "centurion_utils.hpp"
#include "window.hpp"

using namespace centurion;
using namespace hint;

namespace {

template <typename Hint, typename Lambda>
void test_hint(Lambda&& lambda)
{
  const auto optPrev = get_hint<Hint>();

  lambda();

  if (optPrev) {
    set_hint<Hint, hint_prio::low>(*optPrev);
  }
}

template <typename Hint>
void test_bool_hint()
{
  test_hint<Hint>([] {
    CHECK(set_hint<Hint>(true));
    CHECK(get_hint<Hint>().value());

    CHECK(set_hint<Hint>(false));
    CHECK(!get_hint<Hint>().value());
  });
}

}  // namespace

TEST_CASE("hint_prio", "[Hints]")
{
  CHECK(hint_prio::low == static_cast<hint_prio>(SDL_HINT_DEFAULT));
  CHECK(hint_prio::normal == static_cast<hint_prio>(SDL_HINT_NORMAL));
  CHECK(hint_prio::override == static_cast<hint_prio>(SDL_HINT_OVERRIDE));

  CHECK(static_cast<hint_prio>(SDL_HINT_DEFAULT) == hint_prio::low);
  CHECK(static_cast<hint_prio>(SDL_HINT_NORMAL) == hint_prio::normal);
  CHECK(static_cast<hint_prio>(SDL_HINT_OVERRIDE) == hint_prio::override);
}

TEST_CASE("set_hint", "[Hints]")
{
  SECTION("accelerometer_as_joystick")
  {
    test_bool_hint<accelerometer_as_joystick>();
  }

  SECTION("allow_top_most") { test_bool_hint<allow_top_most>(); }

  SECTION("audio_resampling_mode")
  {
    using hint = audio_resampling_mode;
    test_hint<hint>([] {
      set_hint<hint>(hint::normal);
      CHECK(get_hint<hint>().value() == hint::normal);

      set_hint<hint>(hint::fast);
      CHECK(get_hint<hint>().value() == hint::fast);

      set_hint<hint>(hint::medium);
      CHECK(get_hint<hint>().value() == hint::medium);

      set_hint<hint>(hint::best);
      CHECK(get_hint<hint>().value() == hint::best);
    });
  }

  SECTION("android_block_on_pause")
  {
    test_bool_hint<android_block_on_pause>();
  }

  SECTION("android_trap_back_button")
  {
    test_bool_hint<android_trap_back_button>();
  }

  SECTION("android_apk_expansion_main_file_version")
  {
    test_hint<android_apk_expansion_main_file_version>([] {
      CHECK(set_hint<android_apk_expansion_main_file_version>(1));
      CHECK(get_hint<android_apk_expansion_main_file_version>() == 1);
    });
  }

  SECTION("android_apk_expansion_patch_file_version")
  {
    test_hint<android_apk_expansion_patch_file_version>([] {
      CHECK(set_hint<android_apk_expansion_patch_file_version>(1));
      CHECK(get_hint<android_apk_expansion_patch_file_version>() == 1);
    });
  }

  SECTION("audio_category")
  {
    test_hint<audio_category>([] {
      CHECK(set_hint<audio_category>(audio_category::ambient));
      CHECK(get_hint<audio_category>() == audio_category::ambient);

      CHECK(set_hint<audio_category>(audio_category::playback));
      CHECK(get_hint<audio_category>() == audio_category::playback);
    });
  }

  SECTION("apple_tv_controller_ui_events")
  {
    test_bool_hint<apple_tv_controller_ui_events>();
  }

  SECTION("apple_tv_remote_allow_rotation")
  {
    test_bool_hint<apple_tv_remote_allow_rotation>();
  }

  SECTION("bmp_save_legacy_format")
  {
    test_bool_hint<bmp_save_legacy_format>();
  }

  SECTION("double_buffer") { test_bool_hint<double_buffer>(); }

  SECTION("display_usable_bounds")
  {
    test_hint<display_usable_bounds>([] {
      const czstring str = "10, 20, 30, 40";
      CHECK(set_hint<display_usable_bounds>(str));
      CHECK_THAT(get_hint<display_usable_bounds>().value(), Catch::Equals(str));
    });
  }

  SECTION("emscripten_keyboard_element")
  {
    test_hint<emscripten_keyboard_element>([] {
      CHECK(set_hint<emscripten_keyboard_element>("#window"));
      CHECK_THAT(get_hint<emscripten_keyboard_element>().value(),
                 Catch::Equals("#window"));

      CHECK(set_hint<emscripten_keyboard_element>("#document"));
      CHECK_THAT(get_hint<emscripten_keyboard_element>().value(),
                 Catch::Equals("#document"));

      CHECK(set_hint<emscripten_keyboard_element>("#screen"));
      CHECK_THAT(get_hint<emscripten_keyboard_element>().value(),
                 Catch::Equals("#screen"));

      CHECK(set_hint<emscripten_keyboard_element>("#canvas"));
      CHECK_THAT(get_hint<emscripten_keyboard_element>().value(),
                 Catch::Equals("#canvas"));
    });
  }

  SECTION("enable_steam_controllers")
  {
    test_bool_hint<enable_steam_controllers>();
  }

  SECTION("event_logging")
  {
    test_hint<event_logging>([] {
      set_hint<event_logging>(0);
      CHECK(get_hint<event_logging>().value() == 0);

      set_hint<event_logging>(1);
      CHECK(get_hint<event_logging>().value() == 1);

      set_hint<event_logging>(2);
      CHECK(get_hint<event_logging>().value() == 2);
    });

    set_hint<event_logging>(0);
  }

  SECTION("framebuffer_acceleration")
  {
    using fa = framebuffer_acceleration;
    test_hint<fa>([] {
      set_hint<fa>(fa::off);
      CHECK(get_hint<fa>().value() == fa::off);

      set_hint<fa>(fa::on);
      CHECK(get_hint<fa>().value() == fa::on);

      set_hint<fa>(fa::open_gl);
      CHECK(get_hint<fa>().value() == fa::open_gl);

      set_hint<fa>(fa::open_gles);
      CHECK(get_hint<fa>().value() == fa::open_gles);

      set_hint<fa>(fa::open_gles2);
      CHECK(get_hint<fa>().value() == fa::open_gles2);

      set_hint<fa>(fa::direct_3d);
      CHECK(get_hint<fa>().value() == fa::direct_3d);

      set_hint<fa>(fa::metal);
      CHECK(get_hint<fa>().value() == fa::metal);

      set_hint<fa>(fa::software);
      CHECK(get_hint<fa>().value() == fa::software);
    });
  }

  SECTION("game_controller_use_button_labels")
  {
    test_bool_hint<game_controller_use_button_labels>();
  }

  SECTION("game_controller_type")
  {
    test_hint<game_controller_type>([] {
      const czstring str = "0x00FD/0xAAC3=PS4";
      set_hint<game_controller_type>(str);
      CHECK_THAT(get_hint<game_controller_type>().value(), Catch::Equals(str));
    });
  }

  SECTION("game_controller_config")
  {
    test_hint<game_controller_config>([] {
      const czstring str = "asd\nasd";
      set_hint<game_controller_config>(str);
      CHECK_THAT(get_hint<game_controller_config>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("game_controller_config_file")
  {
    test_hint<game_controller_config_file>([] {
      const czstring str = "foo";
      set_hint<game_controller_config_file>(str);
      CHECK_THAT(get_hint<game_controller_config_file>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("game_controller_ignore_devices")
  {
    test_hint<game_controller_ignore_devices>([] {
      const czstring str = "0xAAAA/0xBBBB, 0xCCCC/0xDDDD";
      set_hint<game_controller_ignore_devices>(str);
      CHECK_THAT(get_hint<game_controller_ignore_devices>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("game_controller_ignore_devices_except")
  {
    test_hint<game_controller_ignore_devices_except>([] {
      const czstring str = "0xAAAA/0xBBBB, 0xCCCC/0xDDDD";
      set_hint<game_controller_ignore_devices_except>(str);
      CHECK_THAT(get_hint<game_controller_ignore_devices_except>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("grab_keyboard") { test_bool_hint<grab_keyboard>(); }

  SECTION("idle_timer_disabled") { test_bool_hint<idle_timer_disabled>(); }

  SECTION("ime_internal_editing") { test_bool_hint<ime_internal_editing>(); }

  SECTION("joystick_allow_background_events")
  {
    test_bool_hint<joystick_allow_background_events>();
  }

  SECTION("joystick_use_hidapi") { test_bool_hint<joystick_use_hidapi>(); }

  SECTION("joystick_use_hidapi_ps4")
  {
    test_bool_hint<joystick_use_hidapi_ps4>();
  }

  SECTION("joystick_use_hidapi_steam")
  {
    test_bool_hint<joystick_use_hidapi_steam>();
  }

  SECTION("joystick_use_hidapi_switch")
  {
    test_bool_hint<joystick_use_hidapi_switch>();
  }

  SECTION("joystick_use_hidapi_xbox")
  {
    test_bool_hint<joystick_use_hidapi_xbox>();
  }

  SECTION("joystick_use_hidapi_game_cube")
  {
    test_bool_hint<joystick_use_hidapi_game_cube>();
  }

  SECTION("logical_size_mode")
  {
    test_hint<logical_size_mode>([] {
      CHECK(set_hint<logical_size_mode>(logical_size_mode::letterbox));
      CHECK(get_hint<logical_size_mode>().value() ==
            logical_size_mode::letterbox);

      CHECK(set_hint<logical_size_mode>(logical_size_mode::overscan));
      CHECK(get_hint<logical_size_mode>().value() ==
            logical_size_mode::overscan);
    });
  }

  SECTION("mac_background_app") { test_bool_hint<mac_background_app>(); }

  SECTION("mac_ctrl_click_emulate_right_click")
  {
    test_bool_hint<mac_ctrl_click_emulate_right_click>();
  }

  SECTION("mouse_focus_clickthrough")
  {
    test_bool_hint<mouse_focus_clickthrough>();
  }

  SECTION("mouse_relative_mode_warp")
  {
    test_bool_hint<mouse_relative_mode_warp>();
  }

  SECTION("mouse_double_click_radius")
  {
    test_hint<mouse_double_click_radius>([] {
      set_hint<mouse_double_click_radius>(5);
      CHECK(get_hint<mouse_double_click_radius>().value() == 5);

      set_hint<mouse_double_click_radius>(20);
      CHECK(get_hint<mouse_double_click_radius>().value() == 20);
    });
  }

  SECTION("mouse_double_click_time")
  {
    test_hint<mouse_double_click_time>([] {
      set_hint<mouse_double_click_time>(25);
      CHECK(get_hint<mouse_double_click_time>().value() == 25);

      set_hint<mouse_double_click_time>(178);
      CHECK(get_hint<mouse_double_click_time>().value() == 178);
    });
  }

  SECTION("no_signal_handlers") { test_bool_hint<no_signal_handlers>(); }

  SECTION("direct_3d_11_debug") { test_bool_hint<direct_3d_11_debug>(); }

  SECTION("direct_3D_thread_safe") { test_bool_hint<direct_3D_thread_safe>(); }

  SECTION("enable_opengl_shaders") { test_bool_hint<enable_opengl_shaders>(); }

  SECTION("opengl_es_driver") { test_bool_hint<opengl_es_driver>(); }

  SECTION("orientations")
  {
    test_hint<orientations>([] {
      CHECK(set_hint<orientations>("LandscapeLeft"));
      CHECK_THAT(get_hint<orientations>().value(),
                 Catch::Equals("LandscapeLeft"));

      CHECK(set_hint<orientations>("LandscapeRight"));
      CHECK_THAT(get_hint<orientations>().value(),
                 Catch::Equals("LandscapeRight"));

      CHECK(set_hint<orientations>("Portrait"));
      CHECK_THAT(get_hint<orientations>().value(), Catch::Equals("Portrait"));

      CHECK(set_hint<orientations>("PortraitUpsideDown"));
      CHECK_THAT(get_hint<orientations>().value(),
                 Catch::Equals("PortraitUpsideDown"));

      CHECK(set_hint<orientations>("PortraitUpsideDown LandscapeRight"));
      CHECK_THAT(get_hint<orientations>().value(),
                 Catch::Equals("PortraitUpsideDown LandscapeRight"));
    });
  }

  SECTION("enable_vsync")
  {
    test_bool_hint<enable_vsync>();
    set_hint<enable_vsync>(true);
  }

  SECTION("scale_quality")
  {
    test_hint<scale_quality>([] {
      set_hint<scale_quality>(scale_quality::nearest);
      CHECK(get_hint<scale_quality>() == scale_quality::nearest);

      set_hint<scale_quality>(scale_quality::linear);
      CHECK(get_hint<scale_quality>() == scale_quality::linear);

      set_hint<scale_quality>(scale_quality::best);
      CHECK(get_hint<scale_quality>() == scale_quality::best);
    });
  }

  SECTION("allow_screensaver") { test_bool_hint<allow_screensaver>(); }

  SECTION("video_external_context")
  {
    test_bool_hint<video_external_context>();
  }

  SECTION("disable_high_dpi") { test_bool_hint<disable_high_dpi>(); }

  SECTION("mac_fullscreen_spaces") { test_bool_hint<mac_fullscreen_spaces>(); }

  SECTION("minimize_on_focus_loss")
  {
    test_bool_hint<minimize_on_focus_loss>();
  }

  SECTION("x11_net_wm_ping") { test_bool_hint<x11_net_wm_ping>(); }

  SECTION("x11_net_wm_bypass_compositor")
  {
    test_bool_hint<x11_net_wm_bypass_compositor>();
  }

  SECTION("x11_force_egl") { test_bool_hint<x11_force_egl>(); }

  SECTION("x11_xinerama") { test_bool_hint<x11_xinerama>(); }

  SECTION("x11_xrandr") { test_bool_hint<x11_xrandr>(); }

  SECTION("x11_xvidmode") { test_bool_hint<x11_xvidmode>(); }

  SECTION("x11_window_visual_id")
  {
    test_hint<x11_window_visual_id>([] {
      CHECK(set_hint<x11_window_visual_id>("foo"));
      CHECK_THAT(get_hint<x11_window_visual_id>().value(),
                 Catch::Equals("foo"));

      set_hint<x11_window_visual_id>("");
    });
  }

  SECTION("wave_riff_chunk_size")
  {
    test_hint<wave_riff_chunk_size>([] {
      CHECK(set_hint<wave_riff_chunk_size>(wave_riff_chunk_size::force));
      CHECK(get_hint<wave_riff_chunk_size>() == wave_riff_chunk_size::force);

      CHECK(set_hint<wave_riff_chunk_size>(wave_riff_chunk_size::ignore_zero));
      CHECK(get_hint<wave_riff_chunk_size>() ==
            wave_riff_chunk_size::ignore_zero);

      CHECK(set_hint<wave_riff_chunk_size>(wave_riff_chunk_size::ignore));
      CHECK(get_hint<wave_riff_chunk_size>() == wave_riff_chunk_size::ignore);

      CHECK(set_hint<wave_riff_chunk_size>(wave_riff_chunk_size::maximum));
      CHECK(get_hint<wave_riff_chunk_size>() == wave_riff_chunk_size::maximum);
    });
  }

  SECTION("wave_truncation")
  {
    test_hint<wave_truncation>([] {
      CHECK(set_hint<wave_truncation>(wave_truncation::very_strict));
      CHECK(get_hint<wave_truncation>() == wave_truncation::very_strict);

      CHECK(set_hint<wave_truncation>(wave_truncation::strict));
      CHECK(get_hint<wave_truncation>() == wave_truncation::strict);

      CHECK(set_hint<wave_truncation>(wave_truncation::drop_frame));
      CHECK(get_hint<wave_truncation>() == wave_truncation::drop_frame);

      CHECK(set_hint<wave_truncation>(wave_truncation::drop_block));
      CHECK(get_hint<wave_truncation>() == wave_truncation::drop_block);
    });
  }

  SECTION("wave_fact_chunk")
  {
    test_hint<wave_fact_chunk>([] {
      CHECK(set_hint<wave_fact_chunk>(wave_fact_chunk::truncate));
      CHECK(get_hint<wave_fact_chunk>() == wave_fact_chunk::truncate);

      CHECK(set_hint<wave_fact_chunk>(wave_fact_chunk::ignore));
      CHECK(get_hint<wave_fact_chunk>() == wave_fact_chunk::ignore);

      CHECK(set_hint<wave_fact_chunk>(wave_fact_chunk::ignore_zero));
      CHECK(get_hint<wave_fact_chunk>() == wave_fact_chunk::ignore_zero);

      CHECK(set_hint<wave_fact_chunk>(wave_fact_chunk::strict));
      CHECK(get_hint<wave_fact_chunk>() == wave_fact_chunk::strict);
    });
  }

  SECTION("windows_disable_thread_naming")
  {
    test_bool_hint<windows_disable_thread_naming>();
  }

  SECTION("windows_int_resource_icon")
  {
    test_hint<windows_int_resource_icon>([] {
      CHECK(set_hint<windows_int_resource_icon>("foo"));
      CHECK_THAT(get_hint<windows_int_resource_icon>().value(),
                 Catch::Equals("foo"));

      set_hint<windows_int_resource_icon>("");
    });
  }

  SECTION("windows_int_resource_icon_small")
  {
    test_hint<windows_int_resource_icon_small>([] {
      CHECK(set_hint<windows_int_resource_icon_small>("bar"));
      CHECK_THAT(get_hint<windows_int_resource_icon_small>().value(),
                 Catch::Equals("bar"));

      set_hint<windows_int_resource_icon_small>("");
    });
  }

  SECTION("win_d3d_compiler")
  {
    test_hint<win_d3d_compiler>([] {
      CHECK(set_hint<win_d3d_compiler>(win_d3d_compiler::none));
      CHECK(get_hint<win_d3d_compiler>() == win_d3d_compiler::none);

      CHECK(set_hint<win_d3d_compiler>(win_d3d_compiler::d3d_compiler_46));
      CHECK(get_hint<win_d3d_compiler>() == win_d3d_compiler::d3d_compiler_46);

      CHECK(set_hint<win_d3d_compiler>(win_d3d_compiler::d3d_compiler_43));
      CHECK(get_hint<win_d3d_compiler>() == win_d3d_compiler::d3d_compiler_43);
    });
  }

  SECTION("windows_enable_message_loop")
  {
    test_bool_hint<windows_enable_message_loop>();
  }

  SECTION("windows_no_close_on_alt_f4")
  {
    test_bool_hint<windows_no_close_on_alt_f4>();
  }

  SECTION("window_share_pixel_format")
  {
    test_hint<window_share_pixel_format>([] {
      window window;
      const auto str = centurion::detail::address_of(window.get());

      CHECK(set_hint<window_share_pixel_format>(str.c_str()));
      CHECK_THAT(get_hint<window_share_pixel_format>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("window_frame_usable_while_cursor_hidden")
  {
    test_bool_hint<window_frame_usable_while_cursor_hidden>();
  }

  SECTION("win_rt_privacy_policy_label")
  {
    test_hint<win_rt_privacy_policy_label>([] {
      const czstring str = "Hello this is GDPR speaking";
      set_hint<win_rt_privacy_policy_label>(str);
      CHECK_THAT(get_hint<win_rt_privacy_policy_label>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("win_rt_privacy_policy_url")
  {
    test_hint<win_rt_privacy_policy_url>([] {
      const czstring str = "Hello this is GDPR URL speaking";
      set_hint<win_rt_privacy_policy_url>(str);
      CHECK_THAT(get_hint<win_rt_privacy_policy_url>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("mouse_touch_events") { test_bool_hint<mouse_touch_events>(); }

  SECTION("mouse_normal_speed_scale")
  {
    test_hint<mouse_normal_speed_scale>([] {
      CHECK(set_hint<mouse_normal_speed_scale>(2.3f));
      CHECK(get_hint<mouse_normal_speed_scale>().value() == 2.3f);
    });
  }

  SECTION("mouse_relative_speed_scale")
  {
    test_hint<mouse_relative_speed_scale>([] {
      CHECK(set_hint<mouse_relative_speed_scale>(6.7f));
      CHECK(get_hint<mouse_relative_speed_scale>().value() == 6.7f);
    });
  }

  SECTION("raspberry_pi_video_layer")
  {
    test_hint<raspberry_pi_video_layer>([] {
      CHECK(set_hint<raspberry_pi_video_layer>(8'000));
      CHECK(get_hint<raspberry_pi_video_layer>().value() == 8'000);
    });
  }

  SECTION("render_batching") { test_bool_hint<render_batching>(); }

  SECTION("return_key_hides_ime") { test_bool_hint<return_key_hides_ime>(); }

  SECTION("touch_mouse_events") { test_bool_hint<touch_mouse_events>(); }

  SECTION("thread_stack_size")
  {
    test_hint<thread_stack_size>([] {
      CHECK(set_hint<thread_stack_size>(47U));
      CHECK(get_hint<thread_stack_size>().value() == 47U);

      set_hint<thread_stack_size>(0U);
    });
  }

  SECTION("timer_resolution")
  {
    test_hint<timer_resolution>([] {
      CHECK(set_hint<timer_resolution>(68U));
      CHECK(get_hint<timer_resolution>().value() == 68U);

      set_hint<timer_resolution>(1U);
    });
  }

  SECTION("tv_remote_as_joystick") { test_bool_hint<tv_remote_as_joystick>(); }

  SECTION("qt_wayland_content_orientation")
  {
    using hint = qt_wayland_content_orientation;
    test_hint<hint>([] {
      CHECK(set_hint<hint>(hint::primary));
      CHECK(get_hint<hint>() == hint::primary);

      CHECK(set_hint<hint>(hint::portrait));
      CHECK(get_hint<hint>() == hint::portrait);

      CHECK(set_hint<hint>(hint::landscape));
      CHECK(get_hint<hint>() == hint::landscape);

      CHECK(set_hint<hint>(hint::inverted_portrait));
      CHECK(get_hint<hint>() == hint::inverted_portrait);

      CHECK(set_hint<hint>(hint::inverted_landscape));
      CHECK(get_hint<hint>() == hint::inverted_landscape);
    });
  }

  SECTION("qt_wayland_window_flags")
  {
    using hint = qt_wayland_window_flags;
    test_hint<hint>([] {
      CHECK(set_hint<hint>("OverridesSystemGestures StaysOnTop"));
      CHECK_THAT(get_hint<hint>().value(),
                 Catch::Equals("OverridesSystemGestures StaysOnTop"));

      CHECK(set_hint<hint>("BypassWindowManager"));
      CHECK_THAT(get_hint<hint>().value(),
                 Catch::Equals("BypassWindowManager"));

      CHECK(set_hint<hint>(""));
    });
  }

  SECTION("xinput_enabled") { test_bool_hint<xinput_enabled>(); }

  SECTION("xinput_use_old_joystick_mapping")
  {
    test_bool_hint<xinput_use_old_joystick_mapping>();
  }

  SECTION("render_driver")
  {
    test_hint<render_driver>([] {
      CHECK(set_hint<render_driver>(render_driver::open_gl));
      CHECK(get_hint<render_driver>().value() == render_driver::open_gl);

      CHECK(set_hint<render_driver>(render_driver::open_gles));
      CHECK(get_hint<render_driver>().value() == render_driver::open_gles);

      CHECK(set_hint<render_driver>(render_driver::open_gles2));
      CHECK(get_hint<render_driver>().value() == render_driver::open_gles2);

      CHECK(set_hint<render_driver>(render_driver::metal));
      CHECK(get_hint<render_driver>().value() == render_driver::metal);

      CHECK(set_hint<render_driver>(render_driver::direct_3d));
      CHECK(get_hint<render_driver>().value() == render_driver::direct_3d);

      CHECK(set_hint<render_driver>(render_driver::software));
      CHECK(get_hint<render_driver>().value() == render_driver::software);
    });

    set_hint<render_driver>(render_driver::open_gl);
  }
}

TEST_CASE("add_callback", "[Hints]")
{
  set_hint<render_driver>(render_driver::software);

  int data = 7;
  auto handle = add_callback<render_driver>(
      [](void* data, czstring hint, czstring oldVal, czstring newVal) {
        static bool first = true;
        if (first) {
          first = false;
        } else {
          const auto ptr = reinterpret_cast<int*>(data);
          CHECK(*ptr == 7);
          CHECK_THAT(SDL_HINT_RENDER_DRIVER, Catch::Equals(hint));
          CHECK_THAT("software", Catch::Equals(oldVal));
          CHECK_THAT("opengl", Catch::Equals(newVal));
        }
      },
      &data);

  set_hint<render_driver, hint_prio::override>(render_driver::software);

  handle.disconnect();

  set_hint<render_driver, hint_prio::override>(render_driver::open_gl);
}

TEST_CASE("clear_all", "[Hints]")
{
  CHECK_NOTHROW(clear_all());
}

TEST_CASE("user_data", "[Hints]")
{
  int i = 123;
  callback<render_driver> callback{[](void*, czstring, czstring, czstring) {},
                                   &i};
  CHECK(callback.user_data() == &i);
}