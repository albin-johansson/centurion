#include "hints.hpp"

#include <catch.hpp>

#include "cen.hpp"
#include "detail/utils.hpp"
#include "window.hpp"

namespace {

template <typename Hint, typename Lambda>
void test_hint(Lambda&& lambda)
{
  const auto optPrev = cen::get_hint<Hint>();

  lambda();

  if (optPrev) {
    cen::set_hint<Hint, cen::hint_priority::low>(*optPrev);
  }
}

template <typename Hint>
void test_bool_hint()
{
  test_hint<Hint>([] {
    CHECK(cen::set_hint<Hint>(true));
    CHECK(cen::get_hint<Hint>().value());

    CHECK(cen::set_hint<Hint>(false));
    CHECK(!cen::get_hint<Hint>().value());
  });
}

TEMPLATE_TEST_CASE("set_hint boolean hints",
                   "[hint]",
                   cen::hint::double_buffer,
                   cen::hint::accelerometer_as_joystick,
                   cen::hint::allow_top_most,
                   cen::hint::bmp_save_legacy_format,
                   cen::hint::enable_steam_controllers,
                   cen::hint::grab_keyboard,
                   cen::hint::idle_timer_disabled,
                   cen::hint::ime_internal_editing,
                   cen::hint::no_signal_handlers,
                   cen::hint::enable_opengl_shaders,
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
                   cen::hint::x11::xvidmode)
{
  test_bool_hint<TestType>();
}

}  // namespace

TEST_CASE("hint_prio", "[hint]")
{
  using prio = cen::hint_priority;
  CHECK(prio::low == static_cast<prio>(SDL_HINT_DEFAULT));
  CHECK(prio::normal == static_cast<prio>(SDL_HINT_NORMAL));
  CHECK(prio::override == static_cast<prio>(SDL_HINT_OVERRIDE));

  CHECK(static_cast<prio>(SDL_HINT_DEFAULT) == prio::low);
  CHECK(static_cast<prio>(SDL_HINT_NORMAL) == prio::normal);
  CHECK(static_cast<prio>(SDL_HINT_OVERRIDE) == prio::override);
}

TEST_CASE("set_hint", "[hint]")
{
  SECTION("audio_resampling_mode")
  {
    using hint = cen::hint::audio_resampling_mode;
    using value = hint::value;
    test_hint<hint>([] {
      cen::set_hint<hint>(value::normal);
      CHECK(cen::get_hint<hint>().value() == value::normal);

      cen::set_hint<hint>(value::fast);
      CHECK(cen::get_hint<hint>().value() == value::fast);

      cen::set_hint<hint>(value::medium);
      CHECK(cen::get_hint<hint>().value() == value::medium);

      cen::set_hint<hint>(value::best);
      CHECK(cen::get_hint<hint>().value() == value::best);
    });
  }

  SECTION("audio_category")
  {
    using cen::hint::audio_category;
    using value = audio_category::value;
    test_hint<audio_category>([] {
      CHECK(cen::set_hint<audio_category>(value::ambient));
      CHECK(cen::get_hint<audio_category>() == value::ambient);

      CHECK(cen::set_hint<audio_category>(value::playback));
      CHECK(cen::get_hint<audio_category>() == value::playback);
    });
  }

  SECTION("display_usable_bounds")
  {
    using cen::hint::display_usable_bounds;
    test_hint<display_usable_bounds>([] {
      cen::czstring str = "10, 20, 30, 40";
      CHECK(cen::set_hint<display_usable_bounds>(str));
      CHECK_THAT(cen::get_hint<display_usable_bounds>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("event_logging")
  {
    using cen::hint::event_logging;
    test_hint<event_logging>([] {
      cen::set_hint<event_logging>(0);
      CHECK(cen::get_hint<event_logging>().value() == 0);

      cen::set_hint<event_logging>(1);
      CHECK(cen::get_hint<event_logging>().value() == 1);

      cen::set_hint<event_logging>(2);
      CHECK(cen::get_hint<event_logging>().value() == 2);
    });

    cen::set_hint<event_logging>(0);
  }

  SECTION("framebuffer_acceleration")
  {
    using hint = cen::hint::framebuffer_acceleration;
    using value = hint::value;
    test_hint<hint>([] {
      cen::set_hint<hint>(value::off);
      CHECK(cen::get_hint<hint>().value() == value::off);

      cen::set_hint<hint>(value::on);
      CHECK(cen::get_hint<hint>().value() == value::on);

      cen::set_hint<hint>(value::opengl);
      CHECK(cen::get_hint<hint>().value() == value::opengl);

      cen::set_hint<hint>(value::opengles);
      CHECK(cen::get_hint<hint>().value() == value::opengles);

      cen::set_hint<hint>(value::opengles2);
      CHECK(cen::get_hint<hint>().value() == value::opengles2);

      cen::set_hint<hint>(value::direct3d);
      CHECK(cen::get_hint<hint>().value() == value::direct3d);

      cen::set_hint<hint>(value::metal);
      CHECK(cen::get_hint<hint>().value() == value::metal);

      cen::set_hint<hint>(value::software);
      CHECK(cen::get_hint<hint>().value() == value::software);
    });
  }

  SECTION("logical_size_mode")
  {
    using cen::hint::logical_size_mode;
    using value = logical_size_mode::value;
    test_hint<logical_size_mode>([] {
      CHECK(cen::set_hint<logical_size_mode>(value::letterbox));
      CHECK(cen::get_hint<logical_size_mode>().value() == value::letterbox);

      CHECK(cen::set_hint<logical_size_mode>(value::overscan));
      CHECK(cen::get_hint<logical_size_mode>().value() == value::overscan);
    });
  }

  SECTION("orientations")
  {
    using cen::hint::orientations;
    test_hint<orientations>([] {
      CHECK(cen::set_hint<orientations>("LandscapeLeft"));
      CHECK_THAT(cen::get_hint<orientations>().value(),
                 Catch::Equals("LandscapeLeft"));

      CHECK(cen::set_hint<orientations>("LandscapeRight"));
      CHECK_THAT(cen::get_hint<orientations>().value(),
                 Catch::Equals("LandscapeRight"));

      CHECK(cen::set_hint<orientations>("Portrait"));
      CHECK_THAT(cen::get_hint<orientations>().value(),
                 Catch::Equals("Portrait"));

      CHECK(cen::set_hint<orientations>("PortraitUpsideDown"));
      CHECK_THAT(cen::get_hint<orientations>().value(),
                 Catch::Equals("PortraitUpsideDown"));

      CHECK(cen::set_hint<orientations>("PortraitUpsideDown LandscapeRight"));
      CHECK_THAT(cen::get_hint<orientations>().value(),
                 Catch::Equals("PortraitUpsideDown LandscapeRight"));
    });
  }

  SECTION("vsync")
  {
    using cen::hint::vsync;
    test_bool_hint<vsync>();
    cen::set_hint<vsync>(true);
  }

  SECTION("scale_quality")
  {
    using cen::hint::scale_quality;
    using value = scale_quality::value;
    test_hint<scale_quality>([] {
      cen::set_hint<scale_quality>(value::nearest);
      CHECK(cen::get_hint<scale_quality>() == value::nearest);

      cen::set_hint<scale_quality>(value::linear);
      CHECK(cen::get_hint<scale_quality>() == value::linear);

      cen::set_hint<scale_quality>(value::best);
      CHECK(cen::get_hint<scale_quality>() == value::best);
    });
  }

  SECTION("wave_riff_chunk_size")
  {
    using cen::hint::wave_riff_chunk_size;
    using value = wave_riff_chunk_size::value;
    test_hint<wave_riff_chunk_size>([] {
      CHECK(cen::set_hint<wave_riff_chunk_size>(value::force));
      CHECK(cen::get_hint<wave_riff_chunk_size>() == value::force);

      CHECK(cen::set_hint<wave_riff_chunk_size>(value::ignore_zero));
      CHECK(cen::get_hint<wave_riff_chunk_size>() == value::ignore_zero);

      CHECK(cen::set_hint<wave_riff_chunk_size>(value::ignore));
      CHECK(cen::get_hint<wave_riff_chunk_size>() == value::ignore);

      CHECK(cen::set_hint<wave_riff_chunk_size>(value::maximum));
      CHECK(cen::get_hint<wave_riff_chunk_size>() == value::maximum);
    });
  }

  SECTION("wave_truncation")
  {
    using cen::hint::wave_truncation;
    using value = wave_truncation::value;
    test_hint<wave_truncation>([] {
      CHECK(cen::set_hint<wave_truncation>(value::very_strict));
      CHECK(cen::get_hint<wave_truncation>() == value::very_strict);

      CHECK(cen::set_hint<wave_truncation>(value::strict));
      CHECK(cen::get_hint<wave_truncation>() == value::strict);

      CHECK(cen::set_hint<wave_truncation>(value::drop_frame));
      CHECK(cen::get_hint<wave_truncation>() == value::drop_frame);

      CHECK(cen::set_hint<wave_truncation>(value::drop_block));
      CHECK(cen::get_hint<wave_truncation>() == value::drop_block);
    });
  }

  SECTION("wave_fact_chunk")
  {
    using cen::hint::wave_fact_chunk;
    using value = wave_fact_chunk::value;
    test_hint<wave_fact_chunk>([] {
      CHECK(cen::set_hint<wave_fact_chunk>(value::truncate));
      CHECK(cen::get_hint<wave_fact_chunk>() == value::truncate);

      CHECK(cen::set_hint<wave_fact_chunk>(value::ignore));
      CHECK(cen::get_hint<wave_fact_chunk>() == value::ignore);

      CHECK(cen::set_hint<wave_fact_chunk>(value::ignore_zero));
      CHECK(cen::get_hint<wave_fact_chunk>() == value::ignore_zero);

      CHECK(cen::set_hint<wave_fact_chunk>(value::strict));
      CHECK(cen::get_hint<wave_fact_chunk>() == value::strict);
    });
  }

  SECTION("window_share_pixel_format")
  {
    using cen::hint::window_share_pixel_format;
    test_hint<window_share_pixel_format>([] {
      cen::window window;
      const auto str = centurion::detail::address_of(window.get());

      CHECK(cen::set_hint<window_share_pixel_format>(str.c_str()));
      CHECK_THAT(cen::get_hint<window_share_pixel_format>().value(),
                 Catch::Equals(str));
    });
  }

  SECTION("thread_stack_size")
  {
    using cen::hint::thread_stack_size;
    test_hint<thread_stack_size>([] {
      CHECK(cen::set_hint<thread_stack_size>(47U));
      CHECK(cen::get_hint<thread_stack_size>().value() == 47U);

      cen::set_hint<thread_stack_size>(0U);
    });
  }

  SECTION("timer_resolution")
  {
    using cen::hint::timer_resolution;
    test_hint<timer_resolution>([] {
      CHECK(cen::set_hint<timer_resolution>(68U));
      CHECK(cen::get_hint<timer_resolution>().value() == 68U);

      cen::set_hint<timer_resolution>(1U);
    });
  }

  SECTION("render_driver")
  {
    using cen::hint::render_driver;
    test_hint<render_driver>([] {
      CHECK(cen::set_hint<render_driver>(render_driver::value::opengl));
      CHECK(cen::get_hint<render_driver>().value() ==
            render_driver::value::opengl);

      CHECK(cen::set_hint<render_driver>(render_driver::value::opengles));
      CHECK(cen::get_hint<render_driver>().value() ==
            render_driver::value::opengles);

      CHECK(cen::set_hint<render_driver>(render_driver::value::opengles2));
      CHECK(cen::get_hint<render_driver>().value() ==
            render_driver::value::opengles2);

      CHECK(cen::set_hint<render_driver>(render_driver::value::metal));
      CHECK(cen::get_hint<render_driver>().value() ==
            render_driver::value::metal);

      CHECK(cen::set_hint<render_driver>(render_driver::value::direct3d));
      CHECK(cen::get_hint<render_driver>().value() ==
            render_driver::value::direct3d);

      CHECK(cen::set_hint<render_driver>(render_driver::value::software));
      CHECK(cen::get_hint<render_driver>().value() ==
            render_driver::value::software);
    });

    cen::set_hint<render_driver>(render_driver::value::opengl);
  }

  SECTION("raspberrypi::")
  {
    SECTION("video_layer")
    {
      using cen::hint::raspberrypi::video_layer;
      test_hint<video_layer>([] {
        CHECK(cen::set_hint<video_layer>(8'000));
        CHECK(cen::get_hint<video_layer>().value() == 8'000);
      });
    }
  }

  SECTION("emscripten::")
  {
    SECTION("keyboard_element")
    {
      using cen::hint::emscripten::keyboard_element;
      test_hint<keyboard_element>([] {
        CHECK(cen::set_hint<keyboard_element>("#window"));
        CHECK_THAT(cen::get_hint<keyboard_element>().value(),
                   Catch::Equals("#window"));

        CHECK(cen::set_hint<keyboard_element>("#document"));
        CHECK_THAT(cen::get_hint<keyboard_element>().value(),
                   Catch::Equals("#document"));

        CHECK(cen::set_hint<keyboard_element>("#screen"));
        CHECK_THAT(cen::get_hint<keyboard_element>().value(),
                   Catch::Equals("#screen"));

        CHECK(cen::set_hint<keyboard_element>("#canvas"));
        CHECK_THAT(cen::get_hint<keyboard_element>().value(),
                   Catch::Equals("#canvas"));
      });
    }
  }

  SECTION("qtwayland::")
  {
    SECTION("content_orientation")
    {
      using hint = cen::hint::qtwayland::content_orientation;
      using value = hint::value;
      test_hint<hint>([] {
        CHECK(cen::set_hint<hint>(value::primary));
        CHECK(cen::get_hint<hint>() == value::primary);

        CHECK(cen::set_hint<hint>(value::portrait));
        CHECK(cen::get_hint<hint>() == value::portrait);

        CHECK(cen::set_hint<hint>(value::landscape));
        CHECK(cen::get_hint<hint>() == value::landscape);

        CHECK(cen::set_hint<hint>(value::inverted_portrait));
        CHECK(cen::get_hint<hint>() == value::inverted_portrait);

        CHECK(cen::set_hint<hint>(value::inverted_landscape));
        CHECK(cen::get_hint<hint>() == value::inverted_landscape);
      });
    }

    SECTION("window_flags")
    {
      using hint = cen::hint::qtwayland::window_flags;
      test_hint<hint>([] {
        CHECK(cen::set_hint<hint>("OverridesSystemGestures StaysOnTop"));
        CHECK_THAT(cen::get_hint<hint>().value(),
                   Catch::Equals("OverridesSystemGestures StaysOnTop"));

        CHECK(cen::set_hint<hint>("BypassWindowManager"));
        CHECK_THAT(cen::get_hint<hint>().value(),
                   Catch::Equals("BypassWindowManager"));

        CHECK(cen::set_hint<hint>(""));
      });
    }
  }

  SECTION("mouse::")
  {
    SECTION("normal_speed_scale")
    {
      using cen::hint::mouse::normal_speed_scale;
      test_hint<normal_speed_scale>([] {
        CHECK(cen::set_hint<normal_speed_scale>(2.3f));
        CHECK(cen::get_hint<normal_speed_scale>().value() == 2.3f);
      });
    }

    SECTION("relative_speed_scale")
    {
      using cen::hint::mouse::relative_speed_scale;
      test_hint<relative_speed_scale>([] {
        CHECK(cen::set_hint<relative_speed_scale>(6.7f));
        CHECK(cen::get_hint<relative_speed_scale>().value() == 6.7f);
      });
    }

    SECTION("double_click_radius")
    {
      using cen::hint::mouse::double_click_radius;
      test_hint<double_click_radius>([] {
        cen::set_hint<double_click_radius>(5);
        CHECK(cen::get_hint<double_click_radius>().value() == 5);

        cen::set_hint<double_click_radius>(20);
        CHECK(cen::get_hint<double_click_radius>().value() == 20);
      });
    }

    SECTION("double_click_time")
    {
      using cen::hint::mouse::double_click_time;
      test_hint<double_click_time>([] {
        cen::set_hint<double_click_time>(25);
        CHECK(cen::get_hint<double_click_time>().value() == 25);

        cen::set_hint<double_click_time>(178);
        CHECK(cen::get_hint<double_click_time>().value() == 178);
      });
    }
  }

  SECTION("gamecontroller::")
  {
    SECTION("type")
    {
      using cen::hint::gamecontroller::type;
      test_hint<type>([] {
        cen::czstring str = "0x00FD/0xAAC3=PS4";
        cen::set_hint<type>(str);
        CHECK_THAT(cen::get_hint<type>().value(), Catch::Equals(str));
      });
    }

    SECTION("config")
    {
      using cen::hint::gamecontroller::config;
      test_hint<config>([] {
        cen::czstring str = "asd\nasd";
        cen::set_hint<config>(str);
        CHECK_THAT(cen::get_hint<config>().value(), Catch::Equals(str));
      });
    }

    SECTION("config_file")
    {
      using cen::hint::gamecontroller::config_file;
      test_hint<config_file>([] {
        cen::czstring str = "foo";
        cen::set_hint<config_file>(str);
        CHECK_THAT(cen::get_hint<config_file>().value(), Catch::Equals(str));
      });
    }

    SECTION("ignore_devices")
    {
      using cen::hint::gamecontroller::ignore_devices;
      test_hint<ignore_devices>([] {
        cen::czstring str = "0xAAAA/0xBBBB, 0xCCCC/0xDDDD";
        cen::set_hint<ignore_devices>(str);
        CHECK_THAT(cen::get_hint<ignore_devices>().value(), Catch::Equals(str));
      });
    }

    SECTION("ignore_devices_except")
    {
      using cen::hint::gamecontroller::ignore_devices_except;
      test_hint<ignore_devices_except>([] {
        cen::czstring str = "0xAAAA/0xBBBB, 0xCCCC/0xDDDD";
        cen::set_hint<ignore_devices_except>(str);
        CHECK_THAT(cen::get_hint<ignore_devices_except>().value(),
                   Catch::Equals(str));
      });
    }
  }

  SECTION("winrt::")
  {
    SECTION("privacy_policy_label")
    {
      using cen::hint::winrt::privacy_policy_label;
      test_hint<privacy_policy_label>([] {
        cen::czstring str = "Hello this is GDPR speaking";
        cen::set_hint<privacy_policy_label>(str);
        CHECK_THAT(cen::get_hint<privacy_policy_label>().value(),
                   Catch::Equals(str));
      });
    }

    SECTION("privacy_policy_url")
    {
      using cen::hint::winrt::privacy_policy_url;
      test_hint<privacy_policy_url>([] {
        cen::czstring str = "Hello this is GDPR URL speaking";
        cen::set_hint<privacy_policy_url>(str);
        CHECK_THAT(cen::get_hint<privacy_policy_url>().value(),
                   Catch::Equals(str));
      });
    }
  }

  SECTION("windows::")
  {
    SECTION("d3d_compiler")
    {
      using cen::hint::windows::d3d_compiler;
      using value = d3d_compiler::value;
      test_hint<d3d_compiler>([] {
        CHECK(cen::set_hint<d3d_compiler>(value::none));
        CHECK(cen::get_hint<d3d_compiler>() == value::none);

        CHECK(cen::set_hint<d3d_compiler>(value::v46));
        CHECK(cen::get_hint<d3d_compiler>() == value::v46);

        CHECK(cen::set_hint<d3d_compiler>(value::v43));
        CHECK(cen::get_hint<d3d_compiler>() == value::v43);
      });
    }

    SECTION("int_resource_icon")
    {
      using cen::hint::windows::int_resource_icon;
      test_hint<int_resource_icon>([] {
        CHECK(cen::set_hint<int_resource_icon>("foo"));
        CHECK_THAT(cen::get_hint<int_resource_icon>().value(),
                   Catch::Equals("foo"));

        cen::set_hint<int_resource_icon>("");
      });
    }

    SECTION("int_resource_icon_small")
    {
      using cen::hint::windows::int_resource_icon_small;
      test_hint<int_resource_icon_small>([] {
        CHECK(cen::set_hint<int_resource_icon_small>("bar"));
        CHECK_THAT(cen::get_hint<int_resource_icon_small>().value(),
                   Catch::Equals("bar"));

        cen::set_hint<int_resource_icon_small>("");
      });
    }
  }

  SECTION("android::")
  {
    SECTION("apk_expansion_main_file_version")
    {
      using cen::hint::android::apk_expansion_main_file_version;
      test_hint<apk_expansion_main_file_version>([] {
        CHECK(cen::set_hint<apk_expansion_main_file_version>(1));
        CHECK(cen::get_hint<apk_expansion_main_file_version>() == 1);
      });
    }

    SECTION("apk_expansion_patch_file_version")
    {
      using cen::hint::android::apk_expansion_patch_file_version;
      test_hint<apk_expansion_patch_file_version>([] {
        CHECK(cen::set_hint<apk_expansion_patch_file_version>(1));
        CHECK(cen::get_hint<apk_expansion_patch_file_version>() == 1);
      });
    }
  }

  SECTION("x11::")
  {
    SECTION("window_visual_id")
    {
      using cen::hint::x11::window_visual_id;
      test_hint<window_visual_id>([] {
        CHECK(cen::set_hint<window_visual_id>("foo"));
        CHECK_THAT(cen::get_hint<window_visual_id>().value(),
                   Catch::Equals("foo"));

        cen::set_hint<window_visual_id>("");
      });
    }
  }
}

TEST_CASE("add_hint_callback", "[hint]")
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
          CHECK(*ptr == 7);
          CHECK_THAT(SDL_HINT_RENDER_DRIVER, Catch::Equals(hint));
          CHECK_THAT("software", Catch::Equals(oldVal));
          CHECK_THAT("opengl", Catch::Equals(newVal));
        }
      },
      &data);

  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::software);

  handle.disconnect();

  cen::set_hint<render_driver, cen::hint_priority::override>(
      render_driver::value::opengl);
}

TEST_CASE("clear_hints", "[hint]")
{
  CHECK_NOTHROW(cen::clear_hints());
}

TEST_CASE("hint user data", "[hint]")
{
  using cen::hint::render_driver;

  int i = 123;

  cen::hint_callback<render_driver> callback{
      [](void*, cen::czstring, cen::czstring, cen::czstring) {}, &i};

  CHECK(callback.user_data() == &i);
}