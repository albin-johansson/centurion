#include "window.h"

#include <catch.hpp>

#include "centurion_exception.h"
#include "log.h"
#include "renderer.h"
#include "screen.h"
#include "surface.h"

using namespace centurion;

namespace {

inline Window create(SDL_WindowFlags flag)
{
  return Window{SDL_CreateWindow("", 0, 0, 10, 10, flag)};
}

}  // namespace

TEST_CASE("Window()", "[Window]")
{
  const Window window;

  CHECK(window.width() == 800);
  CHECK(window.height() == 600);
  CHECK_THAT(window.title(), Catch::Equals("Centurion window"));
  CHECK(!window.visible());
}

TEST_CASE("Window(Owner<SDL_Window*>)", "[Window]")
{
  SECTION("Null pointer")
  {
    SDL_Window* w = nullptr;
    CHECK_THROWS_AS(Window{w}, CenturionException);
  }

  SECTION("Good window")
  {
    SDL_Window* w = SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN);
    CHECK_NOTHROW(Window{w});
  }
}

TEST_CASE("Window(CZString, Area)", "[Window]")
{
  CHECK_THROWS_AS(Window("", {0, 10}), CenturionException);
  CHECK_THROWS_AS(Window("", {10, 0}), CenturionException);

  SECTION("Normal")
  {
    const auto width = 123;
    const auto height = 321;
    const auto title = "Foo";
    const Window window{title, {width, height}};

    CHECK(window.width() == width);
    CHECK(window.height() == height);
    CHECK_THAT(window.title(), Catch::Equals(title));
    CHECK(!window.visible());
  }

  SECTION("Null title")
  {
    const Window window{nullptr, {10, 10}};
    CHECK_THAT(window.title(), Catch::Equals(""));
  }
}

TEST_CASE("Window(Window&&)", "[Window]")
{
  Window window;
  Window other{std::move(window)};

  CHECK(!window.get());
  CHECK(other.get());
}

TEST_CASE("Window::operator=(Window&&)", "[Window]")
{
  SECTION("Self-assignment")
  {
    Window window;
    window = std::move(window);
    CHECK(window.get());
  }

  SECTION("Normal usage")
  {
    Window window;
    Window other;

    other = std::move(window);

    CHECK(!window.get());
    CHECK(other.get());
  }
}

TEST_CASE("Window::unique", "[Window]")
{
  SECTION("Window::unique()") { CHECK(Window::unique()); }

  SECTION("Window::unique(Owner<SDL_Window*>)")
  {
    auto* bad = static_cast<Owner<SDL_Window*>>(nullptr);
    CHECK_THROWS_AS(Window::unique(bad), CenturionException);

    auto* good = SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN);
    CHECK(Window::unique(good));
  }

  SECTION("Window::unique(CZString, Area)")
  {
    CHECK_THROWS_AS(Window::unique("", {0, 10}), CenturionException);
    CHECK_THROWS_AS(Window::unique("", {10, 0}), CenturionException);
    CHECK_NOTHROW(Window::unique(nullptr, {10, 10}));
    CHECK(Window::unique("Foo", {10, 10}));
  }
}

TEST_CASE("Window::shared", "[Window]")
{
  SECTION("Window::shared()") { CHECK(Window::shared()); }

  SECTION("Window::shared(Owner<SDL_Window*>)")
  {
    auto* bad = static_cast<Owner<SDL_Window*>>(nullptr);
    CHECK_THROWS_AS(Window::shared(bad), CenturionException);

    auto* good = SDL_CreateWindow("", 0, 0, 10, 10, SDL_WINDOW_HIDDEN);
    CHECK(Window::shared(good));
  }

  SECTION("Window::shared(CZString, Area)")
  {
    CHECK_THROWS_AS(Window::shared("", {0, 10}), CenturionException);
    CHECK_THROWS_AS(Window::shared("", {10, 0}), CenturionException);
    CHECK_NOTHROW(Window::shared(nullptr, {10, 10}));
    CHECK(Window::shared("Foo", {10, 10}));
  }
}

TEST_CASE("Window::show", "[Window]")
{
  Window window;

  window.show();

  CHECK(window.visible());
}

TEST_CASE("Window::hide", "[Window]")
{
  Window window;

  window.hide();

  CHECK(!window.visible());
}

TEST_CASE("Window::center", "[Window]")
{
  Window window;

  const auto x = (Screen::width() - window.width()) / 2;
  const auto y = (Screen::height() - window.height()) / 2;

  window.center();

  CHECK(x == window.x());
  CHECK(y == window.y());
}

#ifndef TRAVIS_TEST
TEST_CASE("Window::raise", "[Window]")
{
  Window window;

  window.show();
  window.raise();

  CHECK(window.has_input_focus());
}
#endif  // TRAVIS_TEST

TEST_CASE("Window:maximize", "[Window]")
{
  Window window;

  window.show();
  window.maximize();

  CHECK(window.maximized());
}

#ifndef TRAVIS_TEST
TEST_CASE("Window::minimize", "[Window]")
{
  Window window;

  window.show();
  window.minimize();

  CHECK(window.minimized());
}
#endif  // TRAVIS_TEST

TEST_CASE("Window::set_fullscreen", "[Window]")
{
  Window window;
  CHECK(!window.fullscreen());

  window.set_fullscreen(true);
  CHECK(window.fullscreen());

  window.set_fullscreen(false);
  CHECK(!window.fullscreen());
}

TEST_CASE("Window::set_fullscreen_desktop", "[Window]")
{
  Window window;
  CHECK(!window.fullscreen_desktop());

  window.set_fullscreen_desktop(true);
  CHECK(window.fullscreen_desktop());

  window.set_fullscreen_desktop(false);
  CHECK(!window.fullscreen_desktop());
}

TEST_CASE("Window::set_decorated", "[Window]")
{
  Window window;
  CHECK(window.decorated());

  window.set_decorated(false);
  CHECK(!window.decorated());

  window.set_decorated(true);
  CHECK(window.decorated());
}

TEST_CASE("Window::set_resizable", "[Window]")
{
  Window window;
  CHECK(!window.resizable());

  window.set_resizable(true);
  CHECK(window.resizable());

  window.set_resizable(false);
  CHECK(!window.resizable());
}

TEST_CASE("Window::set_width", "[Window]")
{
  SECTION("Invalid width")
  {
    Window window;

    const auto widthBefore = window.width();

    CHECK_NOTHROW(window.set_width(-1));
    CHECK_NOTHROW(window.set_width(0));

    CHECK(window.width() == widthBefore);
  }

  Window window;

  const auto width = 812;
  window.set_width(width);

  CHECK(window.width() == width);
}

TEST_CASE("Window::set_height", "[Window]")
{
  SECTION("Invalid height")
  {
    Window window;

    const auto heightBefore = window.height();

    CHECK_NOTHROW(window.set_height(-1));
    CHECK_NOTHROW(window.set_height(0));

    CHECK(window.height() == heightBefore);
  }

  Window window;

  const auto height = 327;
  window.set_height(height);

  CHECK(window.height() == height);
}

TEST_CASE("Window::set_icon", "[Window]")
{
  Window window;
  Surface icon{"resources/panda.png"};
  CHECK_NOTHROW(window.set_icon(icon));
}

TEST_CASE("Window::set_title", "[Window]")
{
  Window window;

  CZString title = "foo";
  window.set_title(title);

  CHECK_THAT(window.title(), Catch::Equals(title));
}

TEST_CASE("Window::set_opacity", "[Window]")
{
  Window window;
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

TEST_CASE("Window::set_min_size", "[Window]")
{
  Window window;

  const auto width = 123;
  const auto height = 496;

  window.set_min_size({width, height});

  const auto minSize = window.min_size();
  CHECK(width == minSize.width);
  CHECK(height == minSize.height);
}

TEST_CASE("Window::set_max_size", "[Window]")
{
  Window window;

  const auto width = 834;
  const auto height = 123;
  window.set_max_size({width, height});

  const auto maxSize = window.max_size();
  CHECK(width == maxSize.width);
  CHECK(height == maxSize.height);
}

TEST_CASE("Window::set_position", "[Window]")
{
  const auto x = 467;
  const auto y = 246;

  Window window;
  window.set_position(x, y);

  const auto pos = window.position();
  CHECK(x == pos.x());
  CHECK(y == pos.y());
}

#ifndef TRAVIS_TEST
TEST_CASE("Window::set_grab_mouse", "[Window]")
{
  Window window;
  CHECK(!window.grabbing_mouse());

  window.show();
  window.set_grab_mouse(true);
  CHECK(window.grabbing_mouse());

  window.set_grab_mouse(false);
  CHECK(!window.grabbing_mouse());
}
#endif  // TRAVIS_TEST

TEST_CASE("Window::set_brightness", "[Window]")
{
  SECTION("Only in fullscreen mode")
  {
    Window window;
    const auto brightness = 0.8f;
    window.set_brightness(brightness);
    CHECK(window.brightness() == 1);

    window.set_fullscreen(true);
    window.set_brightness(brightness);
    CHECK(window.brightness() == brightness);
  }

  SECTION("Test clamping of bad arguments")
  {
    Window window;
    window.set_fullscreen(true);

    const auto tooHigh = 1.7f;
    window.set_brightness(tooHigh);
    CHECK(window.brightness() == 1);

    const auto tooLow = -1.4f;
    window.set_brightness(tooLow);
    CHECK(window.brightness() == 0);
  }
}

#ifndef TRAVIS_TEST
TEST_CASE("Window::set_capturing_mouse", "[Window]")
{
  Window window;

  window.set_capturing_mouse(true);
  CHECK(!window.capturing_mouse());

  window.show();

  window.set_capturing_mouse(false);
  CHECK(!window.capturing_mouse());

  window.set_capturing_mouse(true);
  CHECK(window.capturing_mouse());
}
#endif  // TRAVIS_TEST

TEST_CASE("Window::decorated", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(window.decorated());
  }
  SECTION("Not decorated")
  {
    const Window window = create(SDL_WINDOW_BORDERLESS);
    CHECK(!window.decorated());
  }
}

#ifndef TRAVIS_TEST
TEST_CASE("Window::grabbing_mouse", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(!window.grabbing_mouse());
  }
  SECTION("Grabbing mouse")
  {
    const Window window = create(SDL_WINDOW_INPUT_GRABBED);
    CHECK(window.grabbing_mouse());
  }
}
#endif  // TRAVIS_TEST

TEST_CASE("Window::resizable", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(!window.resizable());
  }
  SECTION("Resizable")
  {
    const Window window = create(SDL_WINDOW_RESIZABLE);
    CHECK(window.resizable());
  }
}

TEST_CASE("Window::fullscreen", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(!window.fullscreen());
  }
  SECTION("Fullscreen")
  {
    const Window window = create(SDL_WINDOW_FULLSCREEN);
    CHECK(window.fullscreen());
  }
}

TEST_CASE("Window::fullscreen_desktop", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(!window.fullscreen_desktop());
  }
  SECTION("Fullscreen desktop")
  {
    const Window window = create(SDL_WINDOW_FULLSCREEN_DESKTOP);
    CHECK(window.fullscreen_desktop());
  }
}

TEST_CASE("Window::visible", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(!window.visible());
  }
  SECTION("Visible")
  {
    const Window window = create(SDL_WINDOW_SHOWN);
    CHECK(window.visible());
  }
}

TEST_CASE("Window::brightness", "[Window]")
{
  const Window window;
  CHECK(window.brightness() == 1);
}

TEST_CASE("Window::opacity", "[Window]")
{
  const Window window;
  CHECK(window.opacity() == 1);
}

TEST_CASE("Window::x", "[Window]")
{
  const Window window;
  const auto x = (Screen::width() - window.width()) / 2;
  CHECK(window.x() == x);
}

TEST_CASE("Window::y", "[Window]")
{
  const Window window;
  const auto y = (Screen::height() - window.height()) / 2;
  CHECK(window.y() == y);
}

TEST_CASE("Window::id", "[Window]")
{
  Window window;
  CHECK(window.id() == SDL_GetWindowID(window));
}

TEST_CASE("Window::display_index", "[Window]")
{
  Window window;
  const auto index = window.display_index();
  CHECK(index);
  CHECK(*index == SDL_GetWindowDisplayIndex(window));
}

TEST_CASE("Window::position", "[Window]")
{
  const Window window;
  const auto position = window.position();

  // Windows are centered by default TODO document this!
  const auto x = (Screen::width() - window.width()) / 2;
  const auto y = (Screen::height() - window.height()) / 2;

  CHECK(position.x() == x);
  CHECK(position.y() == y);
}

TEST_CASE("Window::width", "[Window]")
{
  const auto width = 921;
  Window window{"", {width, 10}};
  CHECK(window.width() == width);
}

TEST_CASE("Window::height", "[Window]")
{
  const auto height = 435;
  Window window{"",{10, height}};
  CHECK(window.height() == height);
}

TEST_CASE("Window::opengl", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(!window.opengl());
  }

  SECTION("With OpenGL support")
  {
    const Window window = create(SDL_WINDOW_OPENGL);
    CHECK(window.opengl());
  }
}

#ifndef TRAVIS_TEST
TEST_CASE("Window::vulkan", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(!window.vulkan());
  }

  SECTION("With Vulkan support")
  {
    const Window window = create(SDL_WINDOW_VULKAN);
    CHECK(window.vulkan());
  }
}

TEST_CASE("Window::has_input_focus", "[Window]")
{
  Window window;
  CHECK(!window.has_input_focus());

  window.show();
  window.raise();

  CHECK(window.has_input_focus());
}
#endif  // TRAVIS_TEST

TEST_CASE("Window::has_mouse_focus", "[Window]")
{
  const Window window;
  CHECK(!window.has_mouse_focus());
}

TEST_CASE("Window::is_foreign", "[Window]")
{
  const Window window;
  CHECK(!window.is_foreign());
}

#ifndef TRAVIS_TEST
TEST_CASE("Window::capturing_mouse", "[Window]")
{
  const Window window;
  CHECK(!window.capturing_mouse());
}
#endif  // TRAVIS_TEST

TEST_CASE("Window::always_on_top", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(!window.always_on_top());
  }

  SECTION("Always on top")
  {
    const Window window = create(SDL_WINDOW_ALWAYS_ON_TOP);
    CHECK(window.always_on_top());
  }
}

TEST_CASE("Window::minimized", "[Window]")
{
  Window window;
  CHECK(!window.minimized());
}

TEST_CASE("Window::maximized", "[Window]")
{
  Window window;
  CHECK(!window.maximized());
}

TEST_CASE("Window::check_flag", "[Window]")
{
  const Window window;
  auto* sdlWindow = window.get();

  // returns true if the CTN and SDL queries match
  const auto validate = [&window, sdlWindow](SDL_WindowFlags flag) noexcept {
    const bool ctnValue = window.check_flag(flag);
    const bool sdlValue =
        SDL_GetWindowFlags(sdlWindow) & static_cast<Uint32>(flag);
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
TEST_CASE("Window::flags", "[Window]")
{
  auto* win = SDL_CreateWindow(
      "", 0, 0, 10, 10, SDL_WINDOW_HIDDEN | SDL_WINDOW_MAXIMIZED);
  const Window window{win};

  CHECK(window.flags() == SDL_GetWindowFlags(win));
}

TEST_CASE("Window::renderer", "[Window]")
{
  const Window window;
  CHECK(!window.renderer());

  const Renderer renderer{window};
  CHECK(window.renderer() == renderer.get());
}

TEST_CASE("Window::pixel_format", "[Window]")
{
  Window window;
  const auto format = SDL_GetWindowPixelFormat(window);
  CHECK(window.pixel_format() == static_cast<PixelFormat>(format));
}

TEST_CASE("Window::title", "[Window]")
{
  CZString title = "HelloWorld";
  const Window window{title};
  CHECK_THAT(window.title(), Catch::Equals(title));
}

TEST_CASE("Window::to_string", "[Window]")
{
  const Window window;
  Log::info(Log::Category::Test, "%s", window.to_string().c_str());
}

TEST_CASE("Window::get", "[Window]")
{
  const Window window;
  CHECK(window.get());
}

TEST_CASE("Window to SDL_Window*", "[Window]")
{
  SECTION("Const")
  {
    const Window window;
    CHECK(window.operator const SDL_Window*());
  }

  SECTION("Non-const")
  {
    Window window;
    CHECK(window.operator SDL_Window*());
  }
}
