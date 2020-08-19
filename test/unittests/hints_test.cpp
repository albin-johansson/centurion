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

TEMPLATE_TEST_CASE("set_hint boolean hints",
                   "[hint]",
                   ctn::hint::double_buffer,
                   ctn::hint::accelerometer_as_joystick,
                   ctn::hint::allow_top_most,
                   ctn::hint::bmp_save_legacy_format,
                   ctn::hint::enable_steam_controllers,
                   ctn::hint::grab_keyboard,
                   ctn::hint::idle_timer_disabled,
                   ctn::hint::ime_internal_editing,
                   ctn::hint::no_signal_handlers,
                   ctn::hint::enable_opengl_shaders,
                   ctn::hint::opengl_es_driver,
                   ctn::hint::allow_screensaver,
                   ctn::hint::video_external_context,
                   ctn::hint::disable_high_dpi,
                   ctn::hint::minimize_on_focus_loss,
                   ctn::hint::window_frame_usable_while_cursor_hidden,
                   ctn::hint::mouse_touch_events,
                   ctn::hint::render_batching,
                   ctn::hint::return_key_hides_ime,
                   ctn::hint::touch_mouse_events,
                   ctn::hint::tv_remote_as_joystick,
                   ctn::hint::appletv::controller_ui_events,
                   ctn::hint::appletv::remote_allow_rotation,
                   ctn::hint::xinput::is_enabled,
                   ctn::hint::xinput::use_old_joystick_mapping,
                   ctn::hint::mouse::focus_clickthrough,
                   ctn::hint::mouse::relative_mode_warp,
                   ctn::hint::d3d::v11_debug,
                   ctn::hint::d3d::thread_safe,
                   ctn::hint::gamecontroller::use_button_labels,
                   ctn::hint::winrt::handle_back_button,
                   ctn::hint::windows::no_thread_naming,
                   ctn::hint::windows::enable_message_loop,
                   ctn::hint::windows::no_close_on_alt_f4,
                   ctn::hint::mac::background_app,
                   ctn::hint::mac::ctrl_click_emulate_right_click,
                   ctn::hint::mac::fullscreen_spaces,
                   ctn::hint::android::block_on_pause,
                   ctn::hint::android::trap_back_button,
                   ctn::hint::joystick::allow_background_events,
                   ctn::hint::joystick::use_hidapi,
                   ctn::hint::joystick::use_hidapi_ps4,
                   ctn::hint::joystick::use_hidapi_ps4_rumble,
                   ctn::hint::joystick::use_hidapi_steam,
                   ctn::hint::joystick::use_hidapi_switch,
                   ctn::hint::joystick::use_hidapi_xbox,
                   ctn::hint::joystick::use_hidapi_game_cube,
                   ctn::hint::x11::net_wm_ping,
                   ctn::hint::x11::net_wm_bypass_compositor,
                   ctn::hint::x11::force_egl,
                   ctn::hint::x11::xinerama,
                   ctn::hint::x11::xrandr,
                   ctn::hint::x11::xvidmode)
{
  test_bool_hint<TestType>();
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
  SECTION("audio_resampling_mode")
  {
    using hint = ctn::hint::audio_resampling_mode;
    using value = hint::value;
    test_hint<hint>([] {
      ctn::set_hint<hint>(value::normal);
      CHECK(ctn::get_hint<hint>().value() == value::normal);

      ctn::set_hint<hint>(value::fast);
      CHECK(ctn::get_hint<hint>().value() == value::fast);

      ctn::set_hint<hint>(value::medium);
      CHECK(ctn::get_hint<hint>().value() == value::medium);

      ctn::set_hint<hint>(value::best);
      CHECK(ctn::get_hint<hint>().value() == value::best);
    });
  }

  SECTION("audio_category")
  {
    using ctn::hint::audio_category;
    using value = audio_category::value;
    test_hint<audio_category>([] {
      CHECK(ctn::set_hint<audio_category>(value::ambient));
      CHECK(ctn::get_hint<audio_category>() == value::ambient);

      CHECK(ctn::set_hint<audio_category>(value::playback));
      CHECK(ctn::get_hint<audio_category>() == value::playback);
    });
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
    using hint = ctn::hint::framebuffer_acceleration;
    using value = hint::value;
    test_hint<hint>([] {
      ctn::set_hint<hint>(value::off);
      CHECK(ctn::get_hint<hint>().value() == value::off);

      ctn::set_hint<hint>(value::on);
      CHECK(ctn::get_hint<hint>().value() == value::on);

      ctn::set_hint<hint>(value::opengl);
      CHECK(ctn::get_hint<hint>().value() == value::opengl);

      ctn::set_hint<hint>(value::opengles);
      CHECK(ctn::get_hint<hint>().value() == value::opengles);

      ctn::set_hint<hint>(value::opengles2);
      CHECK(ctn::get_hint<hint>().value() == value::opengles2);

      ctn::set_hint<hint>(value::direct3d);
      CHECK(ctn::get_hint<hint>().value() == value::direct3d);

      ctn::set_hint<hint>(value::metal);
      CHECK(ctn::get_hint<hint>().value() == value::metal);

      ctn::set_hint<hint>(value::software);
      CHECK(ctn::get_hint<hint>().value() == value::software);
    });
  }

  SECTION("logical_size_mode")
  {
    using ctn::hint::logical_size_mode;
    using value = logical_size_mode::value;
    test_hint<logical_size_mode>([] {
      CHECK(ctn::set_hint<logical_size_mode>(value::letterbox));
      CHECK(ctn::get_hint<logical_size_mode>().value() == value::letterbox);

      CHECK(ctn::set_hint<logical_size_mode>(value::overscan));
      CHECK(ctn::get_hint<logical_size_mode>().value() == value::overscan);
    });
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
    using value = scale_quality::value;
    test_hint<scale_quality>([] {
      ctn::set_hint<scale_quality>(value::nearest);
      CHECK(ctn::get_hint<scale_quality>() == value::nearest);

      ctn::set_hint<scale_quality>(value::linear);
      CHECK(ctn::get_hint<scale_quality>() == value::linear);

      ctn::set_hint<scale_quality>(value::best);
      CHECK(ctn::get_hint<scale_quality>() == value::best);
    });
  }

  SECTION("wave_riff_chunk_size")
  {
    using ctn::hint::wave_riff_chunk_size;
    using value = wave_riff_chunk_size::value;
    test_hint<wave_riff_chunk_size>([] {
      CHECK(ctn::set_hint<wave_riff_chunk_size>(value::force));
      CHECK(ctn::get_hint<wave_riff_chunk_size>() == value::force);

      CHECK(ctn::set_hint<wave_riff_chunk_size>(value::ignore_zero));
      CHECK(ctn::get_hint<wave_riff_chunk_size>() == value::ignore_zero);

      CHECK(ctn::set_hint<wave_riff_chunk_size>(value::ignore));
      CHECK(ctn::get_hint<wave_riff_chunk_size>() == value::ignore);

      CHECK(ctn::set_hint<wave_riff_chunk_size>(value::maximum));
      CHECK(ctn::get_hint<wave_riff_chunk_size>() == value::maximum);
    });
  }

  SECTION("wave_truncation")
  {
    using ctn::hint::wave_truncation;
    using value = wave_truncation::value;
    test_hint<wave_truncation>([] {
      CHECK(ctn::set_hint<wave_truncation>(value::very_strict));
      CHECK(ctn::get_hint<wave_truncation>() == value::very_strict);

      CHECK(ctn::set_hint<wave_truncation>(value::strict));
      CHECK(ctn::get_hint<wave_truncation>() == value::strict);

      CHECK(ctn::set_hint<wave_truncation>(value::drop_frame));
      CHECK(ctn::get_hint<wave_truncation>() == value::drop_frame);

      CHECK(ctn::set_hint<wave_truncation>(value::drop_block));
      CHECK(ctn::get_hint<wave_truncation>() == value::drop_block);
    });
  }

  SECTION("wave_fact_chunk")
  {
    using ctn::hint::wave_fact_chunk;
    using value = wave_fact_chunk::value;
    test_hint<wave_fact_chunk>([] {
      CHECK(ctn::set_hint<wave_fact_chunk>(value::truncate));
      CHECK(ctn::get_hint<wave_fact_chunk>() == value::truncate);

      CHECK(ctn::set_hint<wave_fact_chunk>(value::ignore));
      CHECK(ctn::get_hint<wave_fact_chunk>() == value::ignore);

      CHECK(ctn::set_hint<wave_fact_chunk>(value::ignore_zero));
      CHECK(ctn::get_hint<wave_fact_chunk>() == value::ignore_zero);

      CHECK(ctn::set_hint<wave_fact_chunk>(value::strict));
      CHECK(ctn::get_hint<wave_fact_chunk>() == value::strict);
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

  SECTION("render_driver")
  {
    using ctn::hint::render_driver;
    test_hint<render_driver>([] {
      CHECK(ctn::set_hint<render_driver>(render_driver::value::opengl));
      CHECK(ctn::get_hint<render_driver>().value() ==
            render_driver::value::opengl);

      CHECK(ctn::set_hint<render_driver>(render_driver::value::opengles));
      CHECK(ctn::get_hint<render_driver>().value() ==
            render_driver::value::opengles);

      CHECK(ctn::set_hint<render_driver>(render_driver::value::opengles2));
      CHECK(ctn::get_hint<render_driver>().value() ==
            render_driver::value::opengles2);

      CHECK(ctn::set_hint<render_driver>(render_driver::value::metal));
      CHECK(ctn::get_hint<render_driver>().value() ==
            render_driver::value::metal);

      CHECK(ctn::set_hint<render_driver>(render_driver::value::direct3d));
      CHECK(ctn::get_hint<render_driver>().value() ==
            render_driver::value::direct3d);

      CHECK(ctn::set_hint<render_driver>(render_driver::value::software));
      CHECK(ctn::get_hint<render_driver>().value() ==
            render_driver::value::software);
    });

    ctn::set_hint<render_driver>(render_driver::value::opengl);
  }

  SECTION("raspberrypi::")
  {
    SECTION("video_layer")
    {
      using ctn::hint::raspberrypi::video_layer;
      test_hint<video_layer>([] {
        CHECK(ctn::set_hint<video_layer>(8'000));
        CHECK(ctn::get_hint<video_layer>().value() == 8'000);
      });
    }
  }

  SECTION("emscripten::")
  {
    SECTION("keyboard_element")
    {
      using ctn::hint::emscripten::keyboard_element;
      test_hint<keyboard_element>([] {
        CHECK(ctn::set_hint<keyboard_element>("#window"));
        CHECK_THAT(ctn::get_hint<keyboard_element>().value(),
                   Catch::Equals("#window"));

        CHECK(ctn::set_hint<keyboard_element>("#document"));
        CHECK_THAT(ctn::get_hint<keyboard_element>().value(),
                   Catch::Equals("#document"));

        CHECK(ctn::set_hint<keyboard_element>("#screen"));
        CHECK_THAT(ctn::get_hint<keyboard_element>().value(),
                   Catch::Equals("#screen"));

        CHECK(ctn::set_hint<keyboard_element>("#canvas"));
        CHECK_THAT(ctn::get_hint<keyboard_element>().value(),
                   Catch::Equals("#canvas"));
      });
    }
  }

  SECTION("qtwayland::")
  {
    SECTION("content_orientation")
    {
      using hint = ctn::hint::qtwayland::content_orientation;
      using value = hint::value;
      test_hint<hint>([] {
        CHECK(ctn::set_hint<hint>(value::primary));
        CHECK(ctn::get_hint<hint>() == value::primary);

        CHECK(ctn::set_hint<hint>(value::portrait));
        CHECK(ctn::get_hint<hint>() == value::portrait);

        CHECK(ctn::set_hint<hint>(value::landscape));
        CHECK(ctn::get_hint<hint>() == value::landscape);

        CHECK(ctn::set_hint<hint>(value::inverted_portrait));
        CHECK(ctn::get_hint<hint>() == value::inverted_portrait);

        CHECK(ctn::set_hint<hint>(value::inverted_landscape));
        CHECK(ctn::get_hint<hint>() == value::inverted_landscape);
      });
    }

    SECTION("window_flags")
    {
      using hint = ctn::hint::qtwayland::window_flags;
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

  SECTION("gamecontroller::")
  {
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
  }

  SECTION("windows::")
  {
    SECTION("d3d_compiler")
    {
      using ctn::hint::windows::d3d_compiler;
      using value = d3d_compiler::value;
      test_hint<d3d_compiler>([] {
        CHECK(ctn::set_hint<d3d_compiler>(value::none));
        CHECK(ctn::get_hint<d3d_compiler>() == value::none);

        CHECK(ctn::set_hint<d3d_compiler>(value::v46));
        CHECK(ctn::get_hint<d3d_compiler>() == value::v46);

        CHECK(ctn::set_hint<d3d_compiler>(value::v43));
        CHECK(ctn::get_hint<d3d_compiler>() == value::v43);
      });
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
  }

  SECTION("android::")
  {
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

  SECTION("x11::")
  {
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
  ctn::set_hint<render_driver>(render_driver::value::software);

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
      render_driver::value::software);

  handle.disconnect();

  ctn::set_hint<render_driver, ctn::hint_priority::override>(
      render_driver::value::opengl);
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