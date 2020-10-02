#include "window.hpp"

#include <catch.hpp>
#include <iostream>

#include "exception.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include "screen.hpp"
#include "surface.hpp"
#include "types.hpp"
#include "window_utils.hpp"

namespace {

inline auto create(SDL_WindowFlags flag) -> cen::window
{
  return cen::window{SDL_CreateWindow("", 0, 0, 10, 10, flag)};
}

}  // namespace

TEST_CASE("window()", "[window]")
{
  const cen::window window;

  CHECK(window.width() == 800);
  CHECK(window.height() == 600);
  CHECK_THAT(window.title(), Catch::Equals("Centurion window"));
  CHECK(!window.is_visible());
}

TEST_CASE("window(owner<SDL_Window*>)", "[window]")
{
  CHECK_NOTHROW(
      cen::window{SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN)});
  SDL_Window* bad{};
  CHECK_THROWS_AS(cen::window{bad}, cen::exception);
}

TEST_CASE("window(nn_czstring, iarea)", "[window]")
{
  CHECK_THROWS_AS(cen::window("", {0, 10}), cen::exception);
  CHECK_THROWS_AS(cen::window("", {10, 0}), cen::exception);

  SECTION("Normal")
  {
    const auto width = 123;
    const auto height = 321;
    const auto title = "Foo";
    const cen::window window{title, {width, height}};

    CHECK(window.width() == width);
    CHECK(window.height() == height);
    CHECK_THAT(window.title(), Catch::Equals(title));
    CHECK(!window.is_visible());
  }
}

TEST_CASE("window(window&&)", "[window]")
{
  cen::window window;
  cen::window other{std::move(window)};

  CHECK(!window.get());
  CHECK(other.get());
}

TEST_CASE("window::operator=(window&&)", "[window]")
{
  SECTION("Self-assignment")
  {
    cen::window window;
    window = std::move(window);
    CHECK(window.get());
  }

  SECTION("Normal usage")
  {
    cen::window window;
    cen::window other;

    other = std::move(window);

    CHECK(!window.get());
    CHECK(other.get());
  }
}

TEST_CASE("window::show", "[window]")
{
  cen::window window;

  window.show();

  CHECK(window.is_visible());
}

TEST_CASE("window::hide", "[window]")
{
  cen::window window;

  window.hide();

  CHECK(!window.is_visible());
}

TEST_CASE("window::center", "[window]")
{
  cen::window window;

  const auto x = (cen::screen::width() - window.width()) / 2;
  const auto y = (cen::screen::height() - window.height()) / 2;

  window.center();

  CHECK(x == window.x());
  CHECK(y == window.y());
}

TEST_CASE("window::raise", "[!mayfail][window]")
{
  cen::window window;

  window.show();
  window.raise();

  CHECK(window.has_input_focus());
}

TEST_CASE("window:maximize", "[window]")
{
  cen::window window;

  window.show();
  window.maximize();

  CHECK(window.is_maximized());
}

TEST_CASE("window::minimize", "[!mayfail][window]")
{
  cen::window window;

  window.show();
  window.minimize();

  CHECK(window.is_minimized());
}

TEST_CASE("window::set_fullscreen", "[window]")
{
  cen::window window;
  CHECK(!window.is_fullscreen());

  window.set_fullscreen(true);
  CHECK(window.is_fullscreen());

  window.set_fullscreen(false);
  CHECK(!window.is_fullscreen());
}

TEST_CASE("window::set_fullscreen_desktop", "[window]")
{
  cen::window window;
  CHECK(!window.is_fullscreen_desktop());

  window.set_fullscreen_desktop(true);
  CHECK(window.is_fullscreen_desktop());

  window.set_fullscreen_desktop(false);
  CHECK(!window.is_fullscreen_desktop());
}

TEST_CASE("window::set_decorated", "[window]")
{
  cen::window window;
  CHECK(window.is_decorated());

  window.set_decorated(false);
  CHECK(!window.is_decorated());

  window.set_decorated(true);
  CHECK(window.is_decorated());
}

TEST_CASE("window::set_resizable", "[window]")
{
  cen::window window;
  CHECK(!window.is_resizable());

  window.set_resizable(true);
  CHECK(window.is_resizable());

  window.set_resizable(false);
  CHECK(!window.is_resizable());
}

TEST_CASE("window::set_width", "[window]")
{
  SECTION("Invalid width")
  {
    cen::window window;

    CHECK_NOTHROW(window.set_width(-1));
    CHECK(window.width() == 1);

    CHECK_NOTHROW(window.set_width(0));
    CHECK(window.width() == 1);
  }

  SECTION("Valid width")
  {
    cen::window window;

    const auto width = 812;
    window.set_width(width);

    CHECK(window.width() == width);
  }
}

TEST_CASE("window::set_height", "[window]")
{
  SECTION("Invalid height")
  {
    cen::window window;

    CHECK_NOTHROW(window.set_height(-1));
    CHECK(window.height() == 1);

    CHECK_NOTHROW(window.set_height(0));
    CHECK(window.height() == 1);
  }

  SECTION("Valid height")
  {
    cen::window window;

    const auto height = 327;
    window.set_height(height);

    CHECK(window.height() == height);
  }
}

TEST_CASE("window::set_size", "[window]")
{
  SECTION("Invalid size")
  {
    cen::window window;

    CHECK_NOTHROW(window.set_size({-1, -1}));
    CHECK(window.width() == 1);
    CHECK(window.height() == 1);

    CHECK_NOTHROW(window.set_size({0, 0}));
    CHECK(window.width() == 1);
    CHECK(window.height() == 1);

    CHECK_NOTHROW(window.set_size({10, 0}));
    CHECK(window.width() == 10);
    CHECK(window.height() == 1);

    CHECK_NOTHROW(window.set_size({0, 10}));
    CHECK(window.width() == 1);
    CHECK(window.height() == 10);
  }

  SECTION("Valid size")
  {
    cen::window window;

    const cen::iarea size{424, 182};
    window.set_size(size);

    CHECK(window.size() == size);
  }
}

TEST_CASE("window::set_icon", "[window]")
{
  cen::window window;
  cen::surface icon{"resources/panda.png"};
  CHECK_NOTHROW(window.set_icon(icon));
}

TEST_CASE("window::set_title", "[window]")
{
  cen::window window;

  cen::czstring title = "foo";
  window.set_title(title);

  CHECK_THAT(window.title(), Catch::Equals(title));
}

TEST_CASE("window::set_opacity", "[window]")
{
  cen::window window;
  CHECK(window.opacity() == 1);

  SECTION("Windowed mode")
  {
    const auto opacity = 0.4f;
    window.set_opacity(opacity);

    CHECK(window.opacity() == opacity);
  }

  SECTION("Fullscreen mode")
  {
    window.set_opacity(1);
    window.set_fullscreen(true);

    const auto opacity = 0.75f;
    window.set_opacity(opacity);

    CHECK(window.opacity() == opacity);
  }
}

TEST_CASE("window::set_min_size", "[window]")
{
  cen::window window;

  const auto width = 123;
  const auto height = 496;

  window.set_min_size({width, height});

  const auto minSize = window.min_size();
  CHECK(width == minSize.width);
  CHECK(height == minSize.height);
}

TEST_CASE("window::set_max_size", "[window]")
{
  cen::window window;

  const auto width = 834;
  const auto height = 123;
  window.set_max_size({width, height});

  const auto maxSize = window.max_size();
  CHECK(width == maxSize.width);
  CHECK(height == maxSize.height);
}

TEST_CASE("window::set_position", "[window]")
{
  const cen::ipoint pos{467, 246};

  cen::window window;
  window.set_position(pos);

  CHECK(pos == window.position());
}

TEST_CASE("window::set_grab_mouse", "[!mayfail][window]")
{
  cen::window window;
  CHECK(!window.grabbing_mouse());

  window.show();
  window.set_grab_mouse(true);
  CHECK(window.grabbing_mouse());

  window.set_grab_mouse(false);
  CHECK(!window.grabbing_mouse());
}

TEST_CASE("window::set_brightness", "[window]")
{
  SECTION("Only in fullscreen mode")
  {
    cen::window window;
    const auto brightness = 0.8f;
    window.set_brightness(brightness);
    CHECK(window.brightness() == 1);

    window.set_fullscreen(true);
    window.set_brightness(brightness);
    CHECK(window.brightness() == brightness);
  }

  SECTION("Test clamping of bad arguments")
  {
    cen::window window;
    window.set_fullscreen(true);

    const auto tooHigh = 1.7f;
    window.set_brightness(tooHigh);
    CHECK(window.brightness() == 1);

    const auto tooLow = -1.4f;
    window.set_brightness(tooLow);
    CHECK(window.brightness() == 0);
  }
}

TEST_CASE("window::set_capturing_mouse", "[!mayfail][window]")
{
  cen::window window;

  cen::window::set_capturing_mouse(true);
  CHECK(!window.is_capturing_mouse());

  window.show();

  cen::window::set_capturing_mouse(false);
  CHECK(!window.is_capturing_mouse());

  cen::window::set_capturing_mouse(true);
  CHECK(window.is_capturing_mouse());
}

TEST_CASE("window::is_decorated", "[window]")
{
  SECTION("Normal")
  {
    const cen::window window;
    CHECK(window.is_decorated());
  }

  SECTION("Not decorated")
  {
    const cen::window window = create(SDL_WINDOW_BORDERLESS);
    CHECK(!window.is_decorated());
  }
}

TEST_CASE("window::grabbing_mouse", "[!mayfail][window]")
{
  SECTION("Normal")
  {
    const cen::window window;
    CHECK(!window.grabbing_mouse());
  }
  SECTION("Grabbing mouse")
  {
    const cen::window window = create(SDL_WINDOW_INPUT_GRABBED);
    CHECK(window.grabbing_mouse());
  }
}

TEST_CASE("window::is_resizable", "[window]")
{
  SECTION("Normal")
  {
    const cen::window window;
    CHECK(!window.is_resizable());
  }

  SECTION("Resizable")
  {
    const cen::window window = create(SDL_WINDOW_RESIZABLE);
    CHECK(window.is_resizable());
  }
}

TEST_CASE("window::is_fullscreen", "[window]")
{
  SECTION("Normal")
  {
    const cen::window window;
    CHECK(!window.is_fullscreen());
  }

  SECTION("Fullscreen")
  {
    const cen::window window = create(SDL_WINDOW_FULLSCREEN);
    CHECK(window.is_fullscreen());
  }
}

TEST_CASE("window::is_fullscreen_desktop", "[window]")
{
  SECTION("Normal")
  {
    const cen::window window;
    CHECK(!window.is_fullscreen_desktop());
  }

  SECTION("Fullscreen desktop")
  {
    const cen::window window = create(SDL_WINDOW_FULLSCREEN_DESKTOP);
    CHECK(window.is_fullscreen_desktop());
  }
}

TEST_CASE("window::is_visible", "[window]")
{
  SECTION("Normal")
  {
    const cen::window window;
    CHECK(!window.is_visible());
  }

  SECTION("Visible")
  {
    const cen::window window = create(SDL_WINDOW_SHOWN);
    CHECK(window.is_visible());
  }
}

TEST_CASE("window::brightness", "[window]")
{
  const cen::window window;
  CHECK(window.brightness() == 1);
}

TEST_CASE("window::opacity", "[window]")
{
  const cen::window window;
  CHECK(window.opacity() == 1);
}

TEST_CASE("window::x", "[window]")
{
  const cen::window window;
  const auto x = (cen::screen::width() - window.width()) / 2;
  CHECK(window.x() == x);
}

TEST_CASE("window::y", "[window]")
{
  const cen::window window;
  const auto y = (cen::screen::height() - window.height()) / 2;
  CHECK(window.y() == y);
}

TEST_CASE("window::id", "[window]")
{
  cen::window window;
  CHECK(window.id() == SDL_GetWindowID(window.get()));
}

TEST_CASE("window::display_index", "[window]")
{
  cen::window window;
  const auto index = window.display_index();
  CHECK(index);
  CHECK(*index == SDL_GetWindowDisplayIndex(window.get()));
}

TEST_CASE("window::position", "[window]")
{
  const cen::window window;
  const auto position = window.position();

  const auto x = (cen::screen::width() - window.width()) / 2;
  const auto y = (cen::screen::height() - window.height()) / 2;

  CHECK(position.x() == x);
  CHECK(position.y() == y);
}

TEST_CASE("window::width", "[window]")
{
  const auto width = 921;
  cen::window window{"", {width, 10}};
  CHECK(window.width() == width);
}

TEST_CASE("window::height", "[window]")
{
  const auto height = 435;
  cen::window window{"", {10, height}};
  CHECK(window.height() == height);
}

TEST_CASE("window::size", "[window]")
{
  const cen::iarea size{285, 435};
  cen::window window{"", size};

  CHECK(window.width() == size.width);
  CHECK(window.height() == size.height);
  CHECK(window.size() == size);
}

TEST_CASE("window::is_opengl", "[window]")
{
  SECTION("Normal")
  {
    const cen::window window;
    CHECK(!window.is_opengl());
  }

  SECTION("With OpenGL support")
  {
    const cen::window window = create(SDL_WINDOW_OPENGL);
    CHECK(window.is_opengl());
  }
}

TEST_CASE("window::is_vulkan", "[!mayfail][window]")
{
  SECTION("Normal")
  {
    const cen::window window;
    CHECK(!window.is_vulkan());
  }

  SECTION("With Vulkan support")
  {
    auto* ptr = SDL_CreateWindow(
        "foo", 0, 0, 100, 100, SDL_WINDOW_HIDDEN | SDL_WINDOW_VULKAN);
    if (ptr) {
      cen::window window{ptr};
      CHECK(window.is_vulkan());
    }
  }
}

TEST_CASE("window::has_input_focus", "[!mayfail][window]")
{
  cen::window window;
  CHECK(!window.has_input_focus());

  window.show();
  window.raise();

  CHECK(window.has_input_focus());
}

TEST_CASE("window::has_mouse_focus", "[window]")
{
  const cen::window window;
  CHECK(!window.has_mouse_focus());
}

TEST_CASE("window::is_foreign", "[window]")
{
  const cen::window window;
  CHECK(!window.is_foreign());
}

TEST_CASE("window::is_capturing_mouse", "[!mayfail][window]")
{
  const cen::window window;
  CHECK(!window.is_capturing_mouse());
}

TEST_CASE("window::always_on_top", "[window]")
{
  SECTION("Normal")
  {
    const cen::window window;
    CHECK(!window.always_on_top());
  }

  SECTION("Always on top")
  {
    const cen::window window = create(SDL_WINDOW_ALWAYS_ON_TOP);
    CHECK(window.always_on_top());
  }
}

TEST_CASE("window::is_minimized", "[window]")
{
  cen::window window;
  CHECK(!window.is_minimized());
}

TEST_CASE("window::is_maximized", "[window]")
{
  cen::window window;
  CHECK(!window.is_maximized());
}

TEST_CASE("window::check_flag", "[window]")
{
  const cen::window window;
  auto* sdlWindow = window.get();

  // returns true if the CEN and SDL queries match
  const auto validate = [&window, sdlWindow](SDL_WindowFlags flag) noexcept {
    const bool ctnValue = window.check_flag(flag);
    const bool sdlValue =
        SDL_GetWindowFlags(sdlWindow) & static_cast<cen::u32>(flag);
    return ctnValue == sdlValue;
  };

  SECTION("SDL_WINDOW_FULLSCREEN")
  {
    CHECK(!window.check_flag(SDL_WINDOW_FULLSCREEN));
    CHECK(validate(SDL_WINDOW_FULLSCREEN));
  }

  SECTION("SDL_WINDOW_OPENGL")
  {
    CHECK(!window.check_flag(SDL_WINDOW_OPENGL));
    CHECK(validate(SDL_WINDOW_OPENGL));
  }

  SECTION("SDL_WINDOW_SHOWN")
  {
    CHECK(!window.check_flag(SDL_WINDOW_SHOWN));
    CHECK(validate(SDL_WINDOW_SHOWN));
  }

  SECTION("SDL_WINDOW_HIDDEN")
  {
    CHECK(window.check_flag(SDL_WINDOW_HIDDEN));
    CHECK(validate(SDL_WINDOW_HIDDEN));
  }

  SECTION("SDL_WINDOW_BORDERLESS")
  {
    CHECK(!window.check_flag(SDL_WINDOW_BORDERLESS));
    CHECK(validate(SDL_WINDOW_BORDERLESS));
  }

  SECTION("SDL_WINDOW_RESIZABLE")
  {
    CHECK(!window.check_flag(SDL_WINDOW_RESIZABLE));
    CHECK(validate(SDL_WINDOW_RESIZABLE));
  }

  SECTION("SDL_WINDOW_MINIMIZED")
  {
    CHECK(!window.check_flag(SDL_WINDOW_MINIMIZED));
    CHECK(validate(SDL_WINDOW_MINIMIZED));
  }

  SECTION("SDL_WINDOW_MAXIMIZED")
  {
    CHECK(!window.check_flag(SDL_WINDOW_MAXIMIZED));
    CHECK(validate(SDL_WINDOW_MAXIMIZED));
  }

  SECTION("SDL_WINDOW_INPUT_GRABBED")
  {
    CHECK(!window.check_flag(SDL_WINDOW_INPUT_GRABBED));
    CHECK(validate(SDL_WINDOW_INPUT_GRABBED));
  }

  SECTION("SDL_WINDOW_INPUT_FOCUS")
  {
    CHECK(!window.check_flag(SDL_WINDOW_INPUT_FOCUS));
    CHECK(validate(SDL_WINDOW_INPUT_FOCUS));
  }

  SECTION("SDL_WINDOW_MOUSE_FOCUS")
  {
    CHECK(!window.check_flag(SDL_WINDOW_MOUSE_FOCUS));
    CHECK(validate(SDL_WINDOW_MOUSE_FOCUS));
  }

  SECTION("SDL_WINDOW_FULLSCREEN_DESKTOP")
  {
    CHECK(!window.check_flag(SDL_WINDOW_FULLSCREEN_DESKTOP));
    CHECK(validate(SDL_WINDOW_FULLSCREEN_DESKTOP));
  }

  SECTION("SDL_WINDOW_FOREIGN")
  {
    CHECK(!window.check_flag(SDL_WINDOW_FOREIGN));
    CHECK(validate(SDL_WINDOW_FOREIGN));
  }

  SECTION("SDL_WINDOW_ALLOW_HIGHDPI")
  {
    CHECK(!window.check_flag(SDL_WINDOW_ALLOW_HIGHDPI));
    CHECK(validate(SDL_WINDOW_ALLOW_HIGHDPI));
  }

  SECTION("SDL_WINDOW_MOUSE_CAPTURE")
  {
    CHECK(!window.check_flag(SDL_WINDOW_MOUSE_CAPTURE));
    CHECK(validate(SDL_WINDOW_MOUSE_CAPTURE));
  }

  SECTION("SDL_WINDOW_ALWAYS_ON_TOP")
  {
    CHECK(!window.check_flag(SDL_WINDOW_ALWAYS_ON_TOP));
    CHECK(validate(SDL_WINDOW_ALWAYS_ON_TOP));
  }

  SECTION("SDL_WINDOW_SKIP_TASKBAR")
  {
    CHECK(!window.check_flag(SDL_WINDOW_SKIP_TASKBAR));
    CHECK(validate(SDL_WINDOW_SKIP_TASKBAR));
  }

  SECTION("SDL_WINDOW_UTILITY")
  {
    CHECK(!window.check_flag(SDL_WINDOW_UTILITY));
    CHECK(validate(SDL_WINDOW_UTILITY));
  }

  SECTION("SDL_WINDOW_TOOLTIP")
  {
    CHECK(!window.check_flag(SDL_WINDOW_TOOLTIP));
    CHECK(validate(SDL_WINDOW_TOOLTIP));
  }

  SECTION("SDL_WINDOW_POPUP_MENU")
  {
    CHECK(!window.check_flag(SDL_WINDOW_POPUP_MENU));
    CHECK(validate(SDL_WINDOW_POPUP_MENU));
  }

  SECTION("SDL_WINDOW_VULKAN")
  {
    CHECK(!window.check_flag(SDL_WINDOW_VULKAN));
    CHECK(validate(SDL_WINDOW_VULKAN));
  }
}

TEST_CASE("window::flags", "[window]")
{
  auto* win = SDL_CreateWindow(
      "", 0, 0, 10, 10, SDL_WINDOW_HIDDEN | SDL_WINDOW_MAXIMIZED);
  const cen::window window{win};

  CHECK(window.flags() == SDL_GetWindowFlags(win));
}

TEST_CASE("window::pixel_format", "[window]")
{
  cen::window window;
  const auto format = SDL_GetWindowPixelFormat(window.get());
  CHECK(window.get_pixel_format() == static_cast<cen::pixel_format>(format));
}

TEST_CASE("window::title", "[window]")
{
  cen::czstring title = "HelloWorld";
  const cen::window window{title};
  CHECK_THAT(window.title(), Catch::Equals(title));
}

TEST_CASE("window::get", "[window]")
{
  const cen::window window;
  CHECK(window.get());
}

TEST_CASE("window to SDL_Window*", "[window]")
{
  SECTION("Const")
  {
    const cen::window window;
    CHECK(window.operator const SDL_Window*());
  }

  SECTION("Non-const")
  {
    cen::window window;
    CHECK(window.operator SDL_Window*());
  }
}

TEST_CASE("renderer_handle from window", "[window]")
{
  cen::window window;

  CHECK(!cen::get_renderer(window));

  cen::renderer renderer{window};
  auto handle = cen::get_renderer(window);

  REQUIRE(handle);
  CHECK(handle.get() == renderer.get());
}

TEST_CASE("get_grabbed_window", "[!mayfail][window]")
{
  SECTION("No grabbed window")
  {
    CHECK_FALSE(cen::get_grabbed_window());
  }

  SECTION("With grabbed window")
  {
    cen::window window;
    window.set_grab_mouse(true);
    window.show();

    auto grabbed = cen::get_grabbed_window();
    CHECK(window.get() == grabbed.get());
  }
}

TEST_CASE("get_window_from_id", "[window]")
{
  CHECK_FALSE(cen::get_window_from_id(0));

  cen::window window;
  const auto id = window.id();

  CHECK(window.get() == cen::get_window_from_id(id).get());
}

TEST_CASE("window to_string", "[window]")
{
  const cen::window window;
  cen::log::put(cen::to_string(window));
}

TEST_CASE("window stream operator", "[window]")
{
  const cen::window window;
  std::cout << "COUT: " << window << '\n';
}
