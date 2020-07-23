#include "window.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_exception.hpp"
#include "centurion_types.hpp"
#include "log.hpp"
#include "screen.hpp"
#include "surface.hpp"

namespace {

inline auto create(SDL_WindowFlags flag) -> ctn::window
{
  return ctn::window{SDL_CreateWindow("", 0, 0, 10, 10, flag)};
}

}  // namespace

TEST_CASE("window()", "[window]")
{
  const ctn::window window;

  CHECK(window.width() == 800);
  CHECK(window.height() == 600);
  CHECK_THAT(window.title(), Catch::Equals("Centurion window"));
  CHECK(!window.visible());
}

TEST_CASE("window(nn_owner<SDL_Window*>)", "[window]")
{
  auto* w = SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN);
  CHECK_NOTHROW(ctn::window{w});
}

TEST_CASE("window(czstring, area_i)", "[window]")
{
  CHECK_THROWS_AS(ctn::window("", {0, 10}), ctn::centurion_exception);
  CHECK_THROWS_AS(ctn::window("", {10, 0}), ctn::centurion_exception);

  SECTION("Normal")
  {
    const auto width = 123;
    const auto height = 321;
    const auto title = "Foo";
    const ctn::window window{title, {width, height}};

    CHECK(window.width() == width);
    CHECK(window.height() == height);
    CHECK_THAT(window.title(), Catch::Equals(title));
    CHECK(!window.visible());
  }

  SECTION("Null title")
  {
    const ctn::window window{nullptr, {10, 10}};
    CHECK_THAT(window.title(), Catch::Equals(""));
  }
}

TEST_CASE("window(window&&)", "[window]")
{
  ctn::window window;
  ctn::window other{std::move(window)};

  CHECK(!window.get());
  CHECK(other.get());
}

TEST_CASE("window::operator=(window&&)", "[window]")
{
  SECTION("Self-assignment")
  {
    ctn::window window;
    window = std::move(window);
    CHECK(window.get());
  }

  SECTION("Normal usage")
  {
    ctn::window window;
    ctn::window other;

    other = std::move(window);

    CHECK(!window.get());
    CHECK(other.get());
  }
}

TEST_CASE("window::unique", "[window]")
{
  SECTION("window::unique()") { CHECK(ctn::window::unique()); }

  SECTION("window::unique(nn_owner<SDL_Window*>)")
  {
    auto* good = SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN);
    CHECK(ctn::window::unique(good));
  }

  SECTION("window::unique(czstring, area_i)")
  {
    CHECK_THROWS_AS(ctn::window::unique("", {0, 10}), ctn::centurion_exception);
    CHECK_THROWS_AS(ctn::window::unique("", {10, 0}), ctn::centurion_exception);
    CHECK_NOTHROW(ctn::window::unique(nullptr, {10, 10}));
    CHECK(ctn::window::unique("Foo", {10, 10}));
  }
}

TEST_CASE("window::shared", "[window]")
{
  SECTION("window::shared()") { CHECK(ctn::window::shared()); }

  SECTION("window::shared(nn_owner<SDL_Window*>)")
  {
    auto* good = SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN);
    CHECK(ctn::window::shared(good));
  }

  SECTION("window::shared(czstring, area_i)")
  {
    CHECK_THROWS_AS(ctn::window::shared("", {0, 10}), ctn::centurion_exception);
    CHECK_THROWS_AS(ctn::window::shared("", {10, 0}), ctn::centurion_exception);
    CHECK_NOTHROW(ctn::window::shared(nullptr, {10, 10}));
    CHECK(ctn::window::shared("Foo", {10, 10}));
  }
}

TEST_CASE("window::show", "[window]")
{
  ctn::window window;

  window.show();

  CHECK(window.visible());
}

TEST_CASE("window::hide", "[window]")
{
  ctn::window window;

  window.hide();

  CHECK(!window.visible());
}

TEST_CASE("window::center", "[window]")
{
  ctn::window window;

  const auto x = (ctn::screen::width() - window.width()) / 2;
  const auto y = (ctn::screen::height() - window.height()) / 2;

  window.center();

  CHECK(x == window.x());
  CHECK(y == window.y());
}

TEST_CASE("window::raise", "[!mayfail][window]")
{
  ctn::window window;

  window.show();
  window.raise();

  CHECK(window.has_input_focus());
}

TEST_CASE("window:maximize", "[window]")
{
  ctn::window window;

  window.show();
  window.maximize();

  CHECK(window.maximized());
}

TEST_CASE("window::minimize", "[!mayfail][window]")
{
  ctn::window window;

  window.show();
  window.minimize();

  CHECK(window.minimized());
}

TEST_CASE("window::set_fullscreen", "[window]")
{
  ctn::window window;
  CHECK(!window.fullscreen());

  window.set_fullscreen(true);
  CHECK(window.fullscreen());

  window.set_fullscreen(false);
  CHECK(!window.fullscreen());
}

TEST_CASE("window::set_fullscreen_desktop", "[window]")
{
  ctn::window window;
  CHECK(!window.fullscreen_desktop());

  window.set_fullscreen_desktop(true);
  CHECK(window.fullscreen_desktop());

  window.set_fullscreen_desktop(false);
  CHECK(!window.fullscreen_desktop());
}

TEST_CASE("window::set_decorated", "[window]")
{
  ctn::window window;
  CHECK(window.decorated());

  window.set_decorated(false);
  CHECK(!window.decorated());

  window.set_decorated(true);
  CHECK(window.decorated());
}

TEST_CASE("window::set_resizable", "[window]")
{
  ctn::window window;
  CHECK(!window.resizable());

  window.set_resizable(true);
  CHECK(window.resizable());

  window.set_resizable(false);
  CHECK(!window.resizable());
}

TEST_CASE("window::set_width", "[window]")
{
  SECTION("Invalid width")
  {
    ctn::window window;

    const auto widthBefore = window.width();

    CHECK_NOTHROW(window.set_width(-1));
    CHECK_NOTHROW(window.set_width(0));

    CHECK(window.width() == widthBefore);
  }

  ctn::window window;

  const auto width = 812;
  window.set_width(width);

  CHECK(window.width() == width);
}

TEST_CASE("window::set_height", "[window]")
{
  SECTION("Invalid height")
  {
    ctn::window window;

    const auto heightBefore = window.height();

    CHECK_NOTHROW(window.set_height(-1));
    CHECK_NOTHROW(window.set_height(0));

    CHECK(window.height() == heightBefore);
  }

  ctn::window window;

  const auto height = 327;
  window.set_height(height);

  CHECK(window.height() == height);
}

TEST_CASE("window::set_icon", "[window]")
{
  ctn::window window;
  ctn::surface icon{"resources/panda.png"};
  CHECK_NOTHROW(window.set_icon(icon));
}

TEST_CASE("window::set_title", "[window]")
{
  ctn::window window;

  ctn::czstring title = "foo";
  window.set_title(title);

  CHECK_THAT(window.title(), Catch::Equals(title));
}

TEST_CASE("window::set_opacity", "[window]")
{
  ctn::window window;
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
  ctn::window window;

  const auto width = 123;
  const auto height = 496;

  window.set_min_size({width, height});

  const auto minSize = window.min_size();
  CHECK(width == minSize.width);
  CHECK(height == minSize.height);
}

TEST_CASE("window::set_max_size", "[window]")
{
  ctn::window window;

  const auto width = 834;
  const auto height = 123;
  window.set_max_size({width, height});

  const auto maxSize = window.max_size();
  CHECK(width == maxSize.width);
  CHECK(height == maxSize.height);
}

TEST_CASE("window::set_position", "[window]")
{
  const auto x = 467;
  const auto y = 246;

  ctn::window window;
  window.set_position(x, y);

  const auto pos = window.position();
  CHECK(x == pos.x());
  CHECK(y == pos.y());
}

TEST_CASE("window::set_grab_mouse", "[!mayfail][window]")
{
  ctn::window window;
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
    ctn::window window;
    const auto brightness = 0.8f;
    window.set_brightness(brightness);
    CHECK(window.brightness() == 1);

    window.set_fullscreen(true);
    window.set_brightness(brightness);
    CHECK(window.brightness() == brightness);
  }

  SECTION("Test clamping of bad arguments")
  {
    ctn::window window;
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
  ctn::window window;

  window.set_capturing_mouse(true);
  CHECK(!window.capturing_mouse());

  window.show();

  window.set_capturing_mouse(false);
  CHECK(!window.capturing_mouse());

  window.set_capturing_mouse(true);
  CHECK(window.capturing_mouse());
}

TEST_CASE("window::decorated", "[window]")
{
  SECTION("Normal")
  {
    const ctn::window window;
    CHECK(window.decorated());
  }
  SECTION("Not decorated")
  {
    const ctn::window window = create(SDL_WINDOW_BORDERLESS);
    CHECK(!window.decorated());
  }
}

TEST_CASE("window::grabbing_mouse", "[!mayfail][window]")
{
  SECTION("Normal")
  {
    const ctn::window window;
    CHECK(!window.grabbing_mouse());
  }
  SECTION("Grabbing mouse")
  {
    const ctn::window window = create(SDL_WINDOW_INPUT_GRABBED);
    CHECK(window.grabbing_mouse());
  }
}

TEST_CASE("window::resizable", "[window]")
{
  SECTION("Normal")
  {
    const ctn::window window;
    CHECK(!window.resizable());
  }
  SECTION("Resizable")
  {
    const ctn::window window = create(SDL_WINDOW_RESIZABLE);
    CHECK(window.resizable());
  }
}

TEST_CASE("window::fullscreen", "[window]")
{
  SECTION("Normal")
  {
    const ctn::window window;
    CHECK(!window.fullscreen());
  }
  SECTION("Fullscreen")
  {
    const ctn::window window = create(SDL_WINDOW_FULLSCREEN);
    CHECK(window.fullscreen());
  }
}

TEST_CASE("window::fullscreen_desktop", "[window]")
{
  SECTION("Normal")
  {
    const ctn::window window;
    CHECK(!window.fullscreen_desktop());
  }
  SECTION("Fullscreen desktop")
  {
    const ctn::window window = create(SDL_WINDOW_FULLSCREEN_DESKTOP);
    CHECK(window.fullscreen_desktop());
  }
}

TEST_CASE("window::visible", "[window]")
{
  SECTION("Normal")
  {
    const ctn::window window;
    CHECK(!window.visible());
  }
  SECTION("Visible")
  {
    const ctn::window window = create(SDL_WINDOW_SHOWN);
    CHECK(window.visible());
  }
}

TEST_CASE("window::brightness", "[window]")
{
  const ctn::window window;
  CHECK(window.brightness() == 1);
}

TEST_CASE("window::opacity", "[window]")
{
  const ctn::window window;
  CHECK(window.opacity() == 1);
}

TEST_CASE("window::x", "[window]")
{
  const ctn::window window;
  const auto x = (ctn::screen::width() - window.width()) / 2;
  CHECK(window.x() == x);
}

TEST_CASE("window::y", "[window]")
{
  const ctn::window window;
  const auto y = (ctn::screen::height() - window.height()) / 2;
  CHECK(window.y() == y);
}

TEST_CASE("window::id", "[window]")
{
  ctn::window window;
  CHECK(window.id() == SDL_GetWindowID(window.get()));
}

TEST_CASE("window::display_index", "[window]")
{
  ctn::window window;
  const auto index = window.display_index();
  CHECK(index);
  CHECK(*index == SDL_GetWindowDisplayIndex(window.get()));
}

TEST_CASE("window::position", "[window]")
{
  const ctn::window window;
  const auto position = window.position();

  const auto x = (ctn::screen::width() - window.width()) / 2;
  const auto y = (ctn::screen::height() - window.height()) / 2;

  CHECK(position.x() == x);
  CHECK(position.y() == y);
}

TEST_CASE("window::width", "[window]")
{
  const auto width = 921;
  ctn::window window{"", {width, 10}};
  CHECK(window.width() == width);
}

TEST_CASE("window::height", "[window]")
{
  const auto height = 435;
  ctn::window window{"", {10, height}};
  CHECK(window.height() == height);
}

TEST_CASE("window::opengl", "[window]")
{
  SECTION("Normal")
  {
    const ctn::window window;
    CHECK(!window.opengl());
  }

  SECTION("With OpenGL support")
  {
    const ctn::window window = create(SDL_WINDOW_OPENGL);
    CHECK(window.opengl());
  }
}

TEST_CASE("window::vulkan", "[!mayfail][window]")
{
  SECTION("Normal")
  {
    const ctn::window window;
    CHECK(!window.vulkan());
  }

  SECTION("With Vulkan support")
  {
    const ctn::window window = create(SDL_WINDOW_VULKAN);
    CHECK(window.vulkan());
  }
}

TEST_CASE("window::has_input_focus", "[!mayfail][window]")
{
  ctn::window window;
  CHECK(!window.has_input_focus());

  window.show();
  window.raise();

  CHECK(window.has_input_focus());
}

TEST_CASE("window::has_mouse_focus", "[window]")
{
  const ctn::window window;
  CHECK(!window.has_mouse_focus());
}

TEST_CASE("window::is_foreign", "[window]")
{
  const ctn::window window;
  CHECK(!window.is_foreign());
}

TEST_CASE("window::capturing_mouse", "[!mayfail][window]")
{
  const ctn::window window;
  CHECK(!window.capturing_mouse());
}

TEST_CASE("window::always_on_top", "[window]")
{
  SECTION("Normal")
  {
    const ctn::window window;
    CHECK(!window.always_on_top());
  }

  SECTION("Always on top")
  {
    const ctn::window window = create(SDL_WINDOW_ALWAYS_ON_TOP);
    CHECK(window.always_on_top());
  }
}

TEST_CASE("window::minimized", "[window]")
{
  ctn::window window;
  CHECK(!window.minimized());
}

TEST_CASE("window::maximized", "[window]")
{
  ctn::window window;
  CHECK(!window.maximized());
}

TEST_CASE("window::check_flag", "[window]")
{
  const ctn::window window;
  auto* sdlWindow = window.get();

  // returns true if the CTN and SDL queries match
  const auto validate = [&window, sdlWindow](SDL_WindowFlags flag) noexcept {
    const bool ctnValue = window.check_flag(flag);
    const bool sdlValue =
        SDL_GetWindowFlags(sdlWindow) & static_cast<ctn::u32>(flag);
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
  const ctn::window window{win};

  CHECK(window.flags() == SDL_GetWindowFlags(win));
}

TEST_CASE("window::renderer", "[window]")
{
  ctn::window window;
  CHECK(!window.renderer());

  ctn::renderer renderer{window};
  auto view = window.renderer();

  REQUIRE(view.has_value());
  CHECK(view->get() == renderer.get());
}

TEST_CASE("window::pixel_format", "[window]")
{
  ctn::window window;
  const auto format = SDL_GetWindowPixelFormat(window.get());
  CHECK(window.get_pixel_format() == static_cast<ctn::pixel_format>(format));
}

TEST_CASE("window::title", "[window]")
{
  ctn::czstring title = "HelloWorld";
  const ctn::window window{title};
  CHECK_THAT(window.title(), Catch::Equals(title));
}

TEST_CASE("window::to_string", "[window]")
{
  const ctn::window window;
  ctn::log::info(ctn::log::category::test, "%s", window.to_string().c_str());
}

TEST_CASE("window::get", "[window]")
{
  const ctn::window window;
  CHECK(window.get());
}

TEST_CASE("window to SDL_Window*", "[window]")
{
  SECTION("Const")
  {
    const ctn::window window;
    CHECK(window.operator const SDL_Window*());
  }

  SECTION("Non-const")
  {
    ctn::window window;
    CHECK(window.operator SDL_Window*());
  }
}
