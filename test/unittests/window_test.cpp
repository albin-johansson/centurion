#include "window.h"

#include <catch.hpp>

#include "centurion_exception.h"
#include "log.h"
#include "renderer.h"
#include "screen.h"
#include "surface.h"
#include "window_listener.h"

using namespace centurion;

namespace {

class Incrementer final : public IWindowListener {
 public:
  int counter = 0;

  void window_updated(const Window& window) noexcept override { ++counter; }
};

inline Window create(SDL_WindowFlags flag)
{
  return Window{SDL_CreateWindow("", 0, 0, 10, 10, flag)};
}

}  // namespace

TEST_CASE("Window(string, int, int)", "[Window]")
{
  CHECK_THROWS_AS(Window("", 0, 10), CenturionException);
  CHECK_THROWS_AS(Window("", 10, 0), CenturionException);

  const auto width = 123;
  const auto height = 321;
  const auto title = "Foo";
  const Window window{title, width, height};

  CHECK(window.width() == width);
  CHECK(window.height() == height);
  CHECK(window.title() == title);
  CHECK(!window.visible());

  SECTION("Null title")
  {
    const Window window{nullptr, 10, 10};
    CHECK_THAT(window.title(), Catch::Equals(""));
  }
}

TEST_CASE("Window(int, int)", "[Window]")
{
  const auto width = 832;
  const auto height = 715;
  const Window window{width, height};

  CHECK(window.width() == width);
  CHECK(window.height() == height);
  CHECK(window.title() == "Centurion window");
  CHECK(!window.visible());
}

TEST_CASE("Window()", "[Window]")
{
  const Window window;

  CHECK(window.width() == 800);
  CHECK(window.height() == 600);
  CHECK(window.title() == "Centurion window");
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
    SDL_Window* w = SDL_CreateWindow("foo", 0, 0, 100, 100, SDL_WINDOW_HIDDEN);
    Window window{w};
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

TEST_CASE("Window smart pointer factory methods", "[Window]")
{
  SECTION("Unique")
  {
    CHECK_THROWS_AS(Window::unique("", 0, 10), CenturionException);
    CHECK_THROWS_AS(Window::unique("", 10, 0), CenturionException);
    CHECK_THROWS_AS(Window::unique(static_cast<Owner<SDL_Window*>>(nullptr)),
                    CenturionException);
    CHECK_NOTHROW(Window::unique(nullptr, 10, 10));

    CHECK_THROWS_AS(Window::unique(10, 0), CenturionException);
    CHECK_THROWS_AS(Window::unique(0, 10), CenturionException);
    CHECK_NOTHROW(Window::unique(10, 10));

    CHECK_NOTHROW(Window::unique(static_cast<const char*>(nullptr)));
    CHECK_NOTHROW(Window::unique(""));
    CHECK_NOTHROW(Window::unique());
  }

  SECTION("Shared")
  {
    CHECK_THROWS_AS(Window::shared("", 0, 10), CenturionException);
    CHECK_THROWS_AS(Window::shared("", 10, 0), CenturionException);
    CHECK_THROWS_AS(Window::shared(static_cast<Owner<SDL_Window*>>(nullptr)),
                    CenturionException);
    CHECK_NOTHROW(Window::shared(nullptr, 10, 10));

    CHECK_THROWS_AS(Window::shared(10, 0), CenturionException);
    CHECK_THROWS_AS(Window::shared(0, 10), CenturionException);
    CHECK_NOTHROW(Window::shared(10, 10));

    CHECK_NOTHROW(Window::shared(static_cast<const char*>(nullptr)));
    CHECK_NOTHROW(Window::shared(""));
    CHECK_NOTHROW(Window::shared());
  }
}

TEST_CASE("Window::show", "[Window]")
{
  Window window{"Foo", 100, 100};

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.show();
  CHECK(window.visible());
  CHECK(listener->counter > 0);
}

TEST_CASE("Window::hide", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.hide();
  CHECK(!window.visible());
  CHECK(listener->counter > 0);
}

TEST_CASE("Window::center", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  SDL_DisplayMode dm;
  SDL_GetDesktopDisplayMode(0, &dm);

  const auto x = (dm.w - window.width()) / 2;
  const auto y = (dm.h - window.height()) / 2;

  window.center();

  CHECK(x == window.x());
  CHECK(y == window.y());
  CHECK(listener->counter > 0);
}

TEST_CASE("Window::raise", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.show();
  window.raise();

  CHECK(listener->counter > 0);
}

TEST_CASE("Window:maximise", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.show();
  window.maximise();

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::minimise", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.show();
  window.minimise();

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::add_window_listener", "[Window]")
{
  SECTION("Null argument")
  {
    Window window;
    std::shared_ptr<Incrementer> listener = nullptr;
    CHECK_NOTHROW(window.add_window_listener(listener));
  }
  SECTION("Listener becomes invalid")
  {
    // TODO investigate further

    Window window;
    auto listener = std::make_shared<Incrementer>();

    window.add_window_listener(listener);

    listener.reset();

    CHECK_NOTHROW(window.center());
  }
}

TEST_CASE("Window::set_fullscreen", "[Window]")
{
  Window window;
  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.set_fullscreen(true);
  CHECK(window.fullscreen());

  window.set_fullscreen(false);
  CHECK(!window.fullscreen());

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::set_resizable", "[Window]")
{
  Window window;
  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.set_resizable(true);
  CHECK(window.resizable());

  window.set_resizable(false);
  CHECK(!window.resizable());

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::set_width", "[Window]")
{
  SECTION("Invalid width")
  {
    Window window;
    CHECK_THROWS_AS(window.set_width(0), CenturionException);
    CHECK_THROWS_AS(window.set_width(-1), CenturionException);
  }

  Window window;
  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  const auto width = 812;
  window.set_width(width);
  CHECK(window.width() == width);

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::set_height", "[Window]")
{
  SECTION("Invalid height")
  {
    Window window;
    CHECK_THROWS_AS(window.set_height(0), CenturionException);
    CHECK_THROWS_AS(window.set_height(-1), CenturionException);
  }

  Window window;
  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  const auto height = 327;
  window.set_height(height);
  CHECK(window.height() == height);

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::set_grab_mouse && Window::grabbing_mouse", "[Window]")
{
  //  Window window;
  //  window.show();
  //
  //  CHECK(!window.is_grabbing_mouse());
  //
  //  window.set_grab_mouse(true);
  //  CHECK(window.is_grabbing_mouse());
  //
  //  window.set_grab_mouse(false);
  //  CHECK(!window.is_grabbing_mouse());
}

TEST_CASE("Window::set_title", "[Window]")
{
  Window window;

  const auto* title = "foo";
  window.set_title(title);

  CHECK(window.title() == title);
}

TEST_CASE("Window::set_opacity && Window::opacity", "[Window]")
{
  Window window;
  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

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

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::position && Window::set_position", "[Window]")
{
  const auto x = 467;
  const auto y = 246;

  Window window;
  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.set_position(x, y);

  CHECK(listener->counter > 0);

  const auto pos = window.position();
  CHECK(x == pos.x());
  CHECK(y == pos.y());
}

TEST_CASE("Window::set_min_size", "[Window]")
{
  Window window;

  const auto minWidth = 50;
  const auto minHeight = 88;
  window.set_min_size(minWidth, minHeight);

  const auto minSize = window.min_size();
  CHECK(minSize.width == minWidth);
  CHECK(minSize.height == minHeight);
}

TEST_CASE("Window::set_max_size", "[Window]")
{
  Window window;

  const auto maxWidth = 834;
  const auto maxHeight = 123;
  window.set_max_size(maxWidth, maxHeight);

  const auto maxSize = window.max_size();
  CHECK(maxSize.width == maxWidth);
  CHECK(maxSize.height == maxHeight);
}

TEST_CASE("Window::set_decorated && Window::decorated", "[Window]")
{
  //  Window window;
  //  CHECK(window.is_decorated());
  //
  //  window.set_decorated(false);
  //  CHECK(!window.is_decorated());
  //
  //  window.set_decorated(true);
  //  CHECK(window.is_decorated());
}

TEST_CASE("Window::set_min_size && Window::min_size", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  const auto width = 123;
  const auto height = 496;

  window.set_min_size(width, height);
  CHECK(listener->counter > 0);

  const auto [actualWidth, actualHeight] = window.min_size();
  CHECK(width == actualWidth);
  CHECK(height == actualHeight);
}

TEST_CASE("Window::set_icon", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  Surface icon{"resources/panda.png"};
  window.set_icon(icon);

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::set_brightness", "[Window]")
{
  Window window;
  window.set_fullscreen(true);

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  const auto brightness = 0.8f;
  window.set_brightness(brightness);

  CHECK(listener->counter > 0);
  CHECK(window.brightness() == brightness);

  SECTION("Test clamping of bad arguments")
  {
    const auto tooHigh = 1.7f;
    window.set_brightness(tooHigh);
    CHECK(window.brightness() == 1);

    const auto tooLow = -1.4f;
    window.set_brightness(tooLow);
    CHECK(window.brightness() == 0);
  }
}

// TODO * * * * overhaul all tests above this point * * * *

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
  Window window{width, 10};
  CHECK(window.width() == width);
}

TEST_CASE("Window::height", "[Window]")
{
  const auto height = 435;
  Window window{10, height};
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

TEST_CASE("Window::capturing_mouse", "[Window]")
{
  SECTION("Normal")
  {
    const Window window;
    CHECK(!window.capturing_mouse());
  }
  SECTION("Capturing mouse")
  {
    Window window;
    window.show();

    window.set_capturing_mouse(false);
    CHECK(!window.capturing_mouse());

    window.set_capturing_mouse(true);
    CHECK(window.capturing_mouse());
  }
}

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
  const auto* title = "HelloWorld";
  const Window window{title};
  CHECK(window.title() == title);
}

TEST_CASE("Window::to_string", "[Window]")
{
  const Window window;
  Log::msgf(Category::Test, "%s", window.to_string().c_str());
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
