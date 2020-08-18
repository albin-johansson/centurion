#include "hints.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_utils.hpp"
#include "window.hpp"

namespace {

template <typename Hint, typename Lambda>
void test_hint(Lambda&& lambda)
{
  const auto optPrev = ctn::get_hint<Hint>();

  lambda();

  if (optPrev) {
    ctn::set_hint<Hint, ctn::hint_priority::low>(*optPrev);
  }
}

template <typename Hint>
void test_bool_hint()
{
  test_hint<Hint>([] {
    CHECK(ctn::set_hint<Hint>(true));
    CHECK(ctn::get_hint<Hint>().value());

    CHECK(ctn::set_hint<Hint>(false));
    CHECK(!ctn::get_hint<Hint>().value());
  });
}

}  // namespace

TEST_CASE("hint_prio", "[hint]")
{
  using prio = ctn::hint_priority;
  CHECK(prio::low == static_cast<prio>(SDL_HINT_DEFAULT));
  CHECK(prio::normal == static_cast<prio>(SDL_HINT_NORMAL));
  CHECK(prio::override == static_cast<prio>(SDL_HINT_OVERRIDE));

  CHECK(static_cast<prio>(SDL_HINT_DEFAULT) == prio::low);
  CHECK(static_cast<prio>(SDL_HINT_NORMAL) == prio::normal);
  CHECK(static_cast<prio>(SDL_HINT_OVERRIDE) == prio::override);
}

TEST_CASE("set_hint", "[hint]")
{
  SECTION("accelerometer_as_joystick")
  {
    using ctn::hint::accelerometer_as_joystick;
    test_bool_hint<accelerometer_as_joystick>();
  }

  SECTION("allow_top_most")
  {
    using ctn::hint::allow_top_most;
    test_bool_hint<allow_top_most>();
  }

  SECTION("audio_resampling_mode")
  {
    using hint = ctn::hint::audio_resampling_mode;
    test_hint<hint>([] {
      ctn::set_hint<hint>(hint::normal);
      CHECK(ctn::get_hint<hint>().value() == hint::normal);

      ctn::set_hint<hint>(hint::fast);
      CHECK(ctn::get_hint<hint>().value() == hint::fast);

      ctn::set_hint<hint>(hint::medium);
      CHECK(ctn::get_hint<hint>().value() == hint::medium);

      ctn::set_hint<hint>(hint::best);
      CHECK(ctn::get_hint<hint>().value() == hint::best);
    });
  }

  SECTION("audio_category")
  {
    using ctn::hint::audio_category;
    test_hint<audio_category>([] {
      CHECK(ctn::set_hint<audio_category>(audio_category::ambient));
      CHECK(ctn::get_hint<audio_category>() == audio_category::ambient);

      CHECK(ctn::set_hint<audio_category>(audio_category::playback));
      CHECK(ctn::get_hint<audio_category>() == audio_category::playback);
    });
  }

  SECTION("apple_tv_controller_ui_events")
  {
    using ctn::hint::apple_tv_controller_ui_events;
    test_bool_hint<apple_tv_controller_ui_events>();
  }

  SECTION("apple_tv_remote_allow_rotation")
  {
    using ctn::hint::apple_tv_remote_allow_rotation;
    test_bool_hint<apple_tv_remote_allow_rotation>();
  }

  SECTION("bmp_save_legacy_format")
  {
    using ctn::hint::bmp_save_legacy_format;
    test_bool_hint<bmp_save_legacy_format>();
  }

  SECTION("double_buffer")
  {
    using ctn::hint::double_buffer;
    test_bool_hint<double_buffer>();
  }

  SECTION("display_usable_bounds")
  {
    using ctn::hint::display_usable_bounds;
    test_hint<display_usable_bounds>([] {
      ctn::czstring str = "10, 20, 30, 40";
      CHECK(ctn::set_hint<display_usable_bounds>(str));
      CHECK_THAT(ctn::get_hint<display_usable_bounds>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("emscripten_keyboard_element")
  {
    using ctn::hint::emscripten_keyboard_element;
    test_hint<emscripten_keyboard_element>([] {
      CHECK(ctn::set_hint<emscripten_keyboard_element>("#window"));
      CHECK_THAT(ctn::get_hint<emscripten_keyboard_element>().value(),
                 Catch::Equals("#window"));

      CHECK(ctn::set_hint<emscripten_keyboard_element>("#document"));
      CHECK_THAT(ctn::get_hint<emscripten_keyboard_element>().value(),
                 Catch::Equals("#document"));

      CHECK(ctn::set_hint<emscripten_keyboard_element>("#screen"));
      CHECK_THAT(ctn::get_hint<emscripten_keyboard_element>().value(),
                 Catch::Equals("#screen"));

      CHECK(ctn::set_hint<emscripten_keyboard_element>("#canvas"));
      CHECK_THAT(ctn::get_hint<emscripten_keyboard_element>().value(),
                 Catch::Equals("#canvas"));
    });
  }

  SECTION("enable_steam_controllers")
  {
    using ctn::hint::enable_steam_controllers;
    test_bool_hint<enable_steam_controllers>();
  }

  SECTION("event_logging")
  {
    using ctn::hint::event_logging;
    test_hint<event_logging>([] {
      ctn::set_hint<event_logging>(0);
      CHECK(ctn::get_hint<event_logging>().value() == 0);

      ctn::set_hint<event_logging>(1);
      CHECK(ctn::get_hint<event_logging>().value() == 1);

      ctn::set_hint<event_logging>(2);
      CHECK(ctn::get_hint<event_logging>().value() == 2);
    });

    ctn::set_hint<event_logging>(0);
  }

  SECTION("framebuffer_acceleration")
  {
    using fa = ctn::hint::framebuffer_acceleration;
    test_hint<fa>([] {
      ctn::set_hint<fa>(fa::off);
      CHECK(ctn::get_hint<fa>().value() == fa::off);

      ctn::set_hint<fa>(fa::on);
      CHECK(ctn::get_hint<fa>().value() == fa::on);

      ctn::set_hint<fa>(fa::open_gl);
      CHECK(ctn::get_hint<fa>().value() == fa::open_gl);

      ctn::set_hint<fa>(fa::open_gles);
      CHECK(ctn::get_hint<fa>().value() == fa::open_gles);

      ctn::set_hint<fa>(fa::open_gles2);
      CHECK(ctn::get_hint<fa>().value() == fa::open_gles2);

      ctn::set_hint<fa>(fa::direct_3d);
      CHECK(ctn::get_hint<fa>().value() == fa::direct_3d);

      ctn::set_hint<fa>(fa::metal);
      CHECK(ctn::get_hint<fa>().value() == fa::metal);

      ctn::set_hint<fa>(fa::software);
      CHECK(ctn::get_hint<fa>().value() == fa::software);
    });
  }

  SECTION("grab_keyboard")
  {
    using ctn::hint::grab_keyboard;
    test_bool_hint<grab_keyboard>();
  }

  SECTION("idle_timer_disabled")
  {
    using ctn::hint::idle_timer_disabled;
    test_bool_hint<idle_timer_disabled>();
  }

  SECTION("ime_internal_editing")
  {
    using ctn::hint::ime_internal_editing;
    test_bool_hint<ime_internal_editing>();
  }

  SECTION("logical_size_mode")
  {
    using ctn::hint::logical_size_mode;
    test_hint<logical_size_mode>([] {
      CHECK(ctn::set_hint<logical_size_mode>(logical_size_mode::letterbox));
      CHECK(ctn::get_hint<logical_size_mode>().value() ==
            logical_size_mode::letterbox);

      CHECK(ctn::set_hint<logical_size_mode>(logical_size_mode::overscan));
      CHECK(ctn::get_hint<logical_size_mode>().value() ==
            logical_size_mode::overscan);
    });
  }

  SECTION("no_signal_handlers")
  {
    using ctn::hint::no_signal_handlers;
    test_bool_hint<no_signal_handlers>();
  }

  SECTION("enable_opengl_shaders")
  {
    using ctn::hint::enable_opengl_shaders;
    test_bool_hint<enable_opengl_shaders>();
  }

  SECTION("opengl_es_driver")
  {
    using ctn::hint::opengl_es_driver;
    test_bool_hint<opengl_es_driver>();
  }

  SECTION("orientations")
  {
    using ctn::hint::orientations;
    test_hint<orientations>([] {
      CHECK(ctn::set_hint<orientations>("LandscapeLeft"));
      CHECK_THAT(ctn::get_hint<orientations>().value(),
                 Catch::Equals("LandscapeLeft"));

      CHECK(ctn::set_hint<orientations>("LandscapeRight"));
      CHECK_THAT(ctn::get_hint<orientations>().value(),
                 Catch::Equals("LandscapeRight"));

      CHECK(ctn::set_hint<orientations>("Portrait"));
      CHECK_THAT(ctn::get_hint<orientations>().value(),
                 Catch::Equals("Portrait"));

      CHECK(ctn::set_hint<orientations>("PortraitUpsideDown"));
      CHECK_THAT(ctn::get_hint<orientations>().value(),
                 Catch::Equals("PortraitUpsideDown"));

      CHECK(ctn::set_hint<orientations>("PortraitUpsideDown LandscapeRight"));
      CHECK_THAT(ctn::get_hint<orientations>().value(),
                 Catch::Equals("PortraitUpsideDown LandscapeRight"));
    });
  }

  SECTION("vsync")
  {
    using ctn::hint::vsync;
    test_bool_hint<vsync>();
    ctn::set_hint<vsync>(true);
  }

  SECTION("scale_quality")
  {
    using ctn::hint::scale_quality;
    test_hint<scale_quality>([] {
      ctn::set_hint<scale_quality>(scale_quality::nearest);
      CHECK(ctn::get_hint<scale_quality>() == scale_quality::nearest);

      ctn::set_hint<scale_quality>(scale_quality::linear);
      CHECK(ctn::get_hint<scale_quality>() == scale_quality::linear);

      ctn::set_hint<scale_quality>(scale_quality::best);
      CHECK(ctn::get_hint<scale_quality>() == scale_quality::best);
    });
  }

  SECTION("allow_screensaver")
  {
    using ctn::hint::allow_screensaver;
    test_bool_hint<allow_screensaver>();
  }

  SECTION("video_external_context")
  {
    using ctn::hint::video_external_context;
    test_bool_hint<video_external_context>();
  }

  SECTION("disable_high_dpi")
  {
    using ctn::hint::disable_high_dpi;
    test_bool_hint<disable_high_dpi>();
  }

  SECTION("minimize_on_focus_loss")
  {
    using ctn::hint::minimize_on_focus_loss;
    test_bool_hint<minimize_on_focus_loss>();
  }

  SECTION("wave_riff_chunk_size")
  {
    using ctn::hint::wave_riff_chunk_size;
    test_hint<wave_riff_chunk_size>([] {
      CHECK(ctn::set_hint<wave_riff_chunk_size>(wave_riff_chunk_size::force));
      CHECK(ctn::get_hint<wave_riff_chunk_size>() ==
            wave_riff_chunk_size::force);

      CHECK(ctn::set_hint<wave_riff_chunk_size>(
          wave_riff_chunk_size::ignore_zero));
      CHECK(ctn::get_hint<wave_riff_chunk_size>() ==
            wave_riff_chunk_size::ignore_zero);

      CHECK(ctn::set_hint<wave_riff_chunk_size>(wave_riff_chunk_size::ignore));
      CHECK(ctn::get_hint<wave_riff_chunk_size>() ==
            wave_riff_chunk_size::ignore);

      CHECK(ctn::set_hint<wave_riff_chunk_size>(wave_riff_chunk_size::maximum));
      CHECK(ctn::get_hint<wave_riff_chunk_size>() ==
            wave_riff_chunk_size::maximum);
    });
  }

  SECTION("wave_truncation")
  {
    using ctn::hint::wave_truncation;
    test_hint<wave_truncation>([] {
      CHECK(ctn::set_hint<wave_truncation>(wave_truncation::very_strict));
      CHECK(ctn::get_hint<wave_truncation>() == wave_truncation::very_strict);

      CHECK(ctn::set_hint<wave_truncation>(wave_truncation::strict));
      CHECK(ctn::get_hint<wave_truncation>() == wave_truncation::strict);

      CHECK(ctn::set_hint<wave_truncation>(wave_truncation::drop_frame));
      CHECK(ctn::get_hint<wave_truncation>() == wave_truncation::drop_frame);

      CHECK(ctn::set_hint<wave_truncation>(wave_truncation::drop_block));
      CHECK(ctn::get_hint<wave_truncation>() == wave_truncation::drop_block);
    });
  }

  SECTION("wave_fact_chunk")
  {
    using ctn::hint::wave_fact_chunk;
    test_hint<wave_fact_chunk>([] {
      CHECK(ctn::set_hint<wave_fact_chunk>(wave_fact_chunk::truncate));
      CHECK(ctn::get_hint<wave_fact_chunk>() == wave_fact_chunk::truncate);

      CHECK(ctn::set_hint<wave_fact_chunk>(wave_fact_chunk::ignore));
      CHECK(ctn::get_hint<wave_fact_chunk>() == wave_fact_chunk::ignore);

      CHECK(ctn::set_hint<wave_fact_chunk>(wave_fact_chunk::ignore_zero));
      CHECK(ctn::get_hint<wave_fact_chunk>() == wave_fact_chunk::ignore_zero);

      CHECK(ctn::set_hint<wave_fact_chunk>(wave_fact_chunk::strict));
      CHECK(ctn::get_hint<wave_fact_chunk>() == wave_fact_chunk::strict);
    });
  }

  SECTION("window_share_pixel_format")
  {
    using ctn::hint::window_share_pixel_format;
    test_hint<window_share_pixel_format>([] {
      ctn::window window;
      const auto str = centurion::detail::address_of(window.get());

      CHECK(ctn::set_hint<window_share_pixel_format>(str.c_str()));
      CHECK_THAT(ctn::get_hint<window_share_pixel_format>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("window_frame_usable_while_cursor_hidden")
  {
    using ctn::hint::window_frame_usable_while_cursor_hidden;
    test_bool_hint<window_frame_usable_while_cursor_hidden>();
  }

  SECTION("mouse_touch_events")
  {
    using ctn::hint::mouse_touch_events;
    test_bool_hint<mouse_touch_events>();
  }

  SECTION("raspberry_pi_video_layer")
  {
    using ctn::hint::raspberry_pi_video_layer;
    test_hint<raspberry_pi_video_layer>([] {
      CHECK(ctn::set_hint<raspberry_pi_video_layer>(8'000));
      CHECK(ctn::get_hint<raspberry_pi_video_layer>().value() == 8'000);
    });
  }

  SECTION("render_batching")
  {
    using ctn::hint::render_batching;
    test_bool_hint<render_batching>();
  }

  SECTION("return_key_hides_ime")
  {
    using ctn::hint::return_key_hides_ime;
    test_bool_hint<return_key_hides_ime>();
  }

  SECTION("touch_mouse_events")
  {
    using ctn::hint::touch_mouse_events;
    test_bool_hint<touch_mouse_events>();
  }

  SECTION("thread_stack_size")
  {
    using ctn::hint::thread_stack_size;
    test_hint<thread_stack_size>([] {
      CHECK(ctn::set_hint<thread_stack_size>(47U));
      CHECK(ctn::get_hint<thread_stack_size>().value() == 47U);

      ctn::set_hint<thread_stack_size>(0U);
    });
  }

  SECTION("timer_resolution")
  {
    using ctn::hint::timer_resolution;
    test_hint<timer_resolution>([] {
      CHECK(ctn::set_hint<timer_resolution>(68U));
      CHECK(ctn::get_hint<timer_resolution>().value() == 68U);

      ctn::set_hint<timer_resolution>(1U);
    });
  }

  SECTION("tv_remote_as_joystick")
  {
    using ctn::hint::tv_remote_as_joystick;
    test_bool_hint<tv_remote_as_joystick>();
  }

  SECTION("qt_wayland_content_orientation")
  {
    using hint = ctn::hint::qt_wayland_content_orientation;
    test_hint<hint>([] {
      CHECK(ctn::set_hint<hint>(hint::primary));
      CHECK(ctn::get_hint<hint>() == hint::primary);

      CHECK(ctn::set_hint<hint>(hint::portrait));
      CHECK(ctn::get_hint<hint>() == hint::portrait);

      CHECK(ctn::set_hint<hint>(hint::landscape));
      CHECK(ctn::get_hint<hint>() == hint::landscape);

      CHECK(ctn::set_hint<hint>(hint::inverted_portrait));
      CHECK(ctn::get_hint<hint>() == hint::inverted_portrait);

      CHECK(ctn::set_hint<hint>(hint::inverted_landscape));
      CHECK(ctn::get_hint<hint>() == hint::inverted_landscape);
    });
  }

  SECTION("qt_wayland_window_flags")
  {
    using hint = ctn::hint::qt_wayland_window_flags;
    test_hint<hint>([] {
      CHECK(ctn::set_hint<hint>("OverridesSystemGestures StaysOnTop"));
      CHECK_THAT(ctn::get_hint<hint>().value(),
                 Catch::Equals("OverridesSystemGestures StaysOnTop"));

      CHECK(ctn::set_hint<hint>("BypassWindowManager"));
      CHECK_THAT(ctn::get_hint<hint>().value(),
                 Catch::Equals("BypassWindowManager"));

      CHECK(ctn::set_hint<hint>(""));
    });
  }

  SECTION("xinput_enabled")
  {
    using ctn::hint::xinput_enabled;
    test_bool_hint<xinput_enabled>();
  }

  SECTION("xinput_use_old_joystick_mapping")
  {
    using ctn::hint::xinput_use_old_joystick_mapping;
    test_bool_hint<xinput_use_old_joystick_mapping>();
  }

  SECTION("render_driver")
  {
    using ctn::hint::render_driver;
    test_hint<render_driver>([] {
      CHECK(ctn::set_hint<render_driver>(render_driver::open_gl));
      CHECK(ctn::get_hint<render_driver>().value() == render_driver::open_gl);

      CHECK(ctn::set_hint<render_driver>(render_driver::open_gles));
      CHECK(ctn::get_hint<render_driver>().value() == render_driver::open_gles);

      CHECK(ctn::set_hint<render_driver>(render_driver::open_gles2));
      CHECK(ctn::get_hint<render_driver>().value() ==
            render_driver::open_gles2);

      CHECK(ctn::set_hint<render_driver>(render_driver::metal));
      CHECK(ctn::get_hint<render_driver>().value() == render_driver::metal);

      CHECK(ctn::set_hint<render_driver>(render_driver::direct_3d));
      CHECK(ctn::get_hint<render_driver>().value() == render_driver::direct_3d);

      CHECK(ctn::set_hint<render_driver>(render_driver::software));
      CHECK(ctn::get_hint<render_driver>().value() == render_driver::software);
    });

    ctn::set_hint<render_driver>(render_driver::open_gl);
  }

  SECTION("mouse::")
  {
    SECTION("normal_speed_scale")
    {
      using ctn::hint::mouse::normal_speed_scale;
      test_hint<normal_speed_scale>([] {
        CHECK(ctn::set_hint<normal_speed_scale>(2.3f));
        CHECK(ctn::get_hint<normal_speed_scale>().value() == 2.3f);
      });
    }

    SECTION("relative_speed_scale")
    {
      using ctn::hint::mouse::relative_speed_scale;
      test_hint<relative_speed_scale>([] {
        CHECK(ctn::set_hint<relative_speed_scale>(6.7f));
        CHECK(ctn::get_hint<relative_speed_scale>().value() == 6.7f);
      });
    }

    SECTION("focus_clickthrough")
    {
      using ctn::hint::mouse::focus_clickthrough;
      test_bool_hint<focus_clickthrough>();
    }

    SECTION("relative_mode_warp")
    {
      using ctn::hint::mouse::relative_mode_warp;
      test_bool_hint<relative_mode_warp>();
    }

    SECTION("double_click_radius")
    {
      using ctn::hint::mouse::double_click_radius;
      test_hint<double_click_radius>([] {
        ctn::set_hint<double_click_radius>(5);
        CHECK(ctn::get_hint<double_click_radius>().value() == 5);

        ctn::set_hint<double_click_radius>(20);
        CHECK(ctn::get_hint<double_click_radius>().value() == 20);
      });
    }

    SECTION("double_click_time")
    {
      using ctn::hint::mouse::double_click_time;
      test_hint<double_click_time>([] {
        ctn::set_hint<double_click_time>(25);
        CHECK(ctn::get_hint<double_click_time>().value() == 25);

        ctn::set_hint<double_click_time>(178);
        CHECK(ctn::get_hint<double_click_time>().value() == 178);
      });
    }
  }

  SECTION("d3d::")
  {
    SECTION("v11_debug")
    {
      using ctn::hint::d3d::v11_debug;
      test_bool_hint<v11_debug>();
    }

    SECTION("thread_safe")
    {
      using ctn::hint::d3d::thread_safe;
      test_bool_hint<thread_safe>();
    }
  }

  SECTION("gamecontroller::")
  {
    SECTION("use_button_labels")
    {
      using ctn::hint::gamecontroller::use_button_labels;
      test_bool_hint<use_button_labels>();
    }

    SECTION("type")
    {
      using ctn::hint::gamecontroller::type;
      test_hint<type>([] {
        ctn::czstring str = "0x00FD/0xAAC3=PS4";
        ctn::set_hint<type>(str);
        CHECK_THAT(ctn::get_hint<type>().value(), Catch::Equals(str));
      });
    }

    SECTION("config")
    {
      using ctn::hint::gamecontroller::config;
      test_hint<config>([] {
        ctn::czstring str = "asd\nasd";
        ctn::set_hint<config>(str);
        CHECK_THAT(ctn::get_hint<config>().value(), Catch::Equals(str));
      });
    }

    SECTION("config_file")
    {
      using ctn::hint::gamecontroller::config_file;
      test_hint<config_file>([] {
        ctn::czstring str = "foo";
        ctn::set_hint<config_file>(str);
        CHECK_THAT(ctn::get_hint<config_file>().value(), Catch::Equals(str));
      });
    }

    SECTION("ignore_devices")
    {
      using ctn::hint::gamecontroller::ignore_devices;
      test_hint<ignore_devices>([] {
        ctn::czstring str = "0xAAAA/0xBBBB, 0xCCCC/0xDDDD";
        ctn::set_hint<ignore_devices>(str);
        CHECK_THAT(ctn::get_hint<ignore_devices>().value(), Catch::Equals(str));
      });
    }

    SECTION("ignore_devices_except")
    {
      using ctn::hint::gamecontroller::ignore_devices_except;
      test_hint<ignore_devices_except>([] {
        ctn::czstring str = "0xAAAA/0xBBBB, 0xCCCC/0xDDDD";
        ctn::set_hint<ignore_devices_except>(str);
        CHECK_THAT(ctn::get_hint<ignore_devices_except>().value(),
                   Catch::Equals(str));
      });
    }
  }

  SECTION("winrt::")
  {
    SECTION("privacy_policy_label")
    {
      using ctn::hint::winrt::privacy_policy_label;
      test_hint<privacy_policy_label>([] {
        ctn::czstring str = "Hello this is GDPR speaking";
        ctn::set_hint<privacy_policy_label>(str);
        CHECK_THAT(ctn::get_hint<privacy_policy_label>().value(),
                   Catch::Equals(str));
      });
    }

    SECTION("privacy_policy_url")
    {
      using ctn::hint::winrt::privacy_policy_url;
      test_hint<privacy_policy_url>([] {
        ctn::czstring str = "Hello this is GDPR URL speaking";
        ctn::set_hint<privacy_policy_url>(str);
        CHECK_THAT(ctn::get_hint<privacy_policy_url>().value(),
                   Catch::Equals(str));
      });
    }

    SECTION("handle_back_button")
    {
      using ctn::hint::winrt::handle_back_button;
      test_bool_hint<handle_back_button>();
    }
  }

  SECTION("windows::")
  {
    SECTION("d3d_compiler")
    {
      using ctn::hint::windows::d3d_compiler;
      test_hint<d3d_compiler>([] {
        CHECK(ctn::set_hint<d3d_compiler>(d3d_compiler::none));
        CHECK(ctn::get_hint<d3d_compiler>() == d3d_compiler::none);

        CHECK(ctn::set_hint<d3d_compiler>(d3d_compiler::d3d_compiler_46));
        CHECK(ctn::get_hint<d3d_compiler>() == d3d_compiler::d3d_compiler_46);

        CHECK(ctn::set_hint<d3d_compiler>(d3d_compiler::d3d_compiler_43));
        CHECK(ctn::get_hint<d3d_compiler>() == d3d_compiler::d3d_compiler_43);
      });
    }

    SECTION("no_thread_naming")
    {
      using ctn::hint::windows::no_thread_naming;
      test_bool_hint<no_thread_naming>();
    }

    SECTION("int_resource_icon")
    {
      using ctn::hint::windows::int_resource_icon;
      test_hint<int_resource_icon>([] {
        CHECK(ctn::set_hint<int_resource_icon>("foo"));
        CHECK_THAT(ctn::get_hint<int_resource_icon>().value(),
                   Catch::Equals("foo"));

        ctn::set_hint<int_resource_icon>("");
      });
    }

    SECTION("int_resource_icon_small")
    {
      using ctn::hint::windows::int_resource_icon_small;
      test_hint<int_resource_icon_small>([] {
        CHECK(ctn::set_hint<int_resource_icon_small>("bar"));
        CHECK_THAT(ctn::get_hint<int_resource_icon_small>().value(),
                   Catch::Equals("bar"));

        ctn::set_hint<int_resource_icon_small>("");
      });
    }

    SECTION("enable_message_loop")
    {
      using ctn::hint::windows::enable_message_loop;
      test_bool_hint<enable_message_loop>();
    }

    SECTION("no_close_on_alt_f4")
    {
      using ctn::hint::windows::no_close_on_alt_f4;
      test_bool_hint<no_close_on_alt_f4>();
    }
  }

  SECTION("mac::")
  {
    SECTION("background_app")
    {
      using ctn::hint::mac::background_app;
      test_bool_hint<background_app>();
    }

    SECTION("ctrl_click_emulate_right_click")
    {
      using ctn::hint::mac::ctrl_click_emulate_right_click;
      test_bool_hint<ctrl_click_emulate_right_click>();
    }

    SECTION("fullscreen_spaces")
    {
      using ctn::hint::mac::fullscreen_spaces;
      test_bool_hint<fullscreen_spaces>();
    }
  }

  SECTION("android::")
  {
    SECTION("block_on_pause")
    {
      using ctn::hint::android::block_on_pause;
      test_bool_hint<block_on_pause>();
    }

    SECTION("trap_back_button")
    {
      using ctn::hint::android::trap_back_button;
      test_bool_hint<trap_back_button>();
    }

    SECTION("apk_expansion_main_file_version")
    {
      using ctn::hint::android::apk_expansion_main_file_version;
      test_hint<apk_expansion_main_file_version>([] {
        CHECK(ctn::set_hint<apk_expansion_main_file_version>(1));
        CHECK(ctn::get_hint<apk_expansion_main_file_version>() == 1);
      });
    }

    SECTION("apk_expansion_patch_file_version")
    {
      using ctn::hint::android::apk_expansion_patch_file_version;
      test_hint<apk_expansion_patch_file_version>([] {
        CHECK(ctn::set_hint<apk_expansion_patch_file_version>(1));
        CHECK(ctn::get_hint<apk_expansion_patch_file_version>() == 1);
      });
    }
  }

  SECTION("joystick::")
  {
    SECTION("allow_background_events")
    {
      using ctn::hint::joystick::allow_background_events;
      test_bool_hint<allow_background_events>();
    }

    SECTION("use_hidapi")
    {
      using ctn::hint::joystick::use_hidapi;
      test_bool_hint<use_hidapi>();
    }

    SECTION("use_hidapi_ps4")
    {
      using ctn::hint::joystick::use_hidapi_ps4;
      test_bool_hint<use_hidapi_ps4>();
    }

    SECTION("use_hidapi_ps4_rumble")
    {
      using ctn::hint::joystick::use_hidapi_ps4_rumble;
      test_bool_hint<use_hidapi_ps4_rumble>();
    }

    SECTION("use_hidapi_steam")
    {
      using ctn::hint::joystick::use_hidapi_steam;
      test_bool_hint<use_hidapi_steam>();
    }

    SECTION("use_hidapi_switch")
    {
      using ctn::hint::joystick::use_hidapi_switch;
      test_bool_hint<use_hidapi_switch>();
    }

    SECTION("use_hidapi_xbox")
    {
      using ctn::hint::joystick::use_hidapi_xbox;
      test_bool_hint<use_hidapi_xbox>();
    }

    SECTION("use_hidapi_game_cube")
    {
      using ctn::hint::joystick::use_hidapi_game_cube;
      test_bool_hint<use_hidapi_game_cube>();
    }
  }

  SECTION("x11::")
  {
    SECTION("net_wm_ping")
    {
      using ctn::hint::x11::net_wm_ping;
      test_bool_hint<net_wm_ping>();
    }

    SECTION("net_wm_bypass_compositor")
    {
      using ctn::hint::x11::net_wm_bypass_compositor;
      test_bool_hint<net_wm_bypass_compositor>();
    }

    SECTION("force_egl")
    {
      using ctn::hint::x11::force_egl;
      test_bool_hint<force_egl>();
    }

    SECTION("xinerama")
    {
      using ctn::hint::x11::xinerama;
      test_bool_hint<xinerama>();
    }

    SECTION("xrandr")
    {
      using ctn::hint::x11::xrandr;
      test_bool_hint<xrandr>();
    }

    SECTION("xvidmode")
    {
      using ctn::hint::x11::xvidmode;
      test_bool_hint<xvidmode>();
    }

    SECTION("window_visual_id")
    {
      using ctn::hint::x11::window_visual_id;
      test_hint<window_visual_id>([] {
        CHECK(ctn::set_hint<window_visual_id>("foo"));
        CHECK_THAT(ctn::get_hint<window_visual_id>().value(),
                   Catch::Equals("foo"));

        ctn::set_hint<window_visual_id>("");
      });
    }
  }
}

TEST_CASE("add_hint_callback", "[hint]")
{
  using ctn::hint::render_driver;
  ctn::set_hint<render_driver>(render_driver::software);

  int data = 7;
  auto handle = ctn::add_hint_callback<render_driver>(
      [](void* data,
         ctn::czstring hint,
         ctn::czstring oldVal,
         ctn::czstring newVal) {
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

  ctn::set_hint<render_driver, ctn::hint_priority::override>(
      render_driver::software);

  handle.disconnect();

  ctn::set_hint<render_driver, ctn::hint_priority::override>(
      render_driver::open_gl);
}

TEST_CASE("clear_hints", "[hint]")
{
  CHECK_NOTHROW(ctn::clear_hints());
}

TEST_CASE("hint user data", "[hint]")
{
  using ctn::hint::render_driver;

  int i = 123;

  ctn::hint_callback<render_driver> callback{
      [](void*, ctn::czstring, ctn::czstring, ctn::czstring) {}, &i};

  CHECK(callback.user_data() == &i);
}