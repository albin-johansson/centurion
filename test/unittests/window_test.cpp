#include "window.h"

#include "catch.hpp"
#include "centurion_exception.h"
#include "log.h"
#include "renderer.h"
#include "surface.h"
#include "window_listener.h"

using namespace centurion;
using namespace centurion::video;

namespace {

class Incrementer final : public IWindowListener {
 public:
  int counter = 0;

  void window_updated(const Window& window) noexcept override
  {
    ++counter;
  }
};

}  // namespace

TEST_CASE("Window(string, int, int)", "[Window]")
{
  CHECK_THROWS_AS(Window("", 0, 10), CenturionException);
  CHECK_THROWS_AS(Window("", 10, 0), CenturionException);

  const auto width = 123;
  const auto height = 321;
  const auto title = "Foo";
  const Window window{title, width, height};

  CHECK(window.get_width() == width);
  CHECK(window.get_height() == height);
  CHECK(window.get_title() == title);
  CHECK(!window.is_visible());

  SECTION("Null title")
  {
    const Window window{nullptr, 10, 10};
    CHECK_THAT(window.get_title(), Catch::Equals(""));
  }
}

TEST_CASE("Window(int, int)", "[Window]")
{
  const auto width = 832;
  const auto height = 715;
  const Window window{width, height};

  CHECK(window.get_width() == width);
  CHECK(window.get_height() == height);
  CHECK(window.get_title() == "Centurion window");
  CHECK(!window.is_visible());
}

TEST_CASE("Window()", "[Window]")
{
  const Window window;

  CHECK(window.get_width() == 800);
  CHECK(window.get_height() == 600);
  CHECK(window.get_title() == "Centurion window");
  CHECK(!window.is_visible());
}

TEST_CASE("Window(Window&&)", "[Window]")
{
  Window window;
  Window other{std::move(window)};

  CHECK(!window.get_internal());
}

TEST_CASE("Window::operator=(Window&&)", "[Window]")
{
  Window window;
  Window other;

  window = std::move(other);

  CHECK(!other.get_internal());
}

TEST_CASE("Window smart pointer factory methods", "[Window]")
{
  SECTION("Unique")
  {
    CHECK_THROWS_AS(Window::unique("", 0, 10), CenturionException);
    CHECK_THROWS_AS(Window::unique("", 10, 0), CenturionException);
    CHECK_NOTHROW(Window::unique(nullptr, 10, 10));

    CHECK_THROWS_AS(Window::unique(10, 0), CenturionException);
    CHECK_THROWS_AS(Window::unique(0, 10), CenturionException);
    CHECK_NOTHROW(Window::unique(10, 10));

    CHECK_NOTHROW(Window::unique(nullptr));
    CHECK_NOTHROW(Window::unique(""));
    CHECK_NOTHROW(Window::unique());
  }

  SECTION("Shared")
  {
    CHECK_THROWS_AS(Window::shared("", 0, 10), CenturionException);
    CHECK_THROWS_AS(Window::shared("", 10, 0), CenturionException);
    CHECK_NOTHROW(Window::shared(nullptr, 10, 10));

    CHECK_THROWS_AS(Window::shared(10, 0), CenturionException);
    CHECK_THROWS_AS(Window::shared(0, 10), CenturionException);
    CHECK_NOTHROW(Window::shared(10, 10));

    CHECK_NOTHROW(Window::shared(nullptr));
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
  CHECK(window.is_visible());
  CHECK(listener->counter > 0);
}

TEST_CASE("Window::hide", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.hide();
  CHECK(!window.is_visible());
  CHECK(listener->counter > 0);
}

TEST_CASE("Window::center", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  SDL_DisplayMode dm;
  SDL_GetDesktopDisplayMode(0, &dm);

  const auto x = (dm.w - window.get_width()) / 2;
  const auto y = (dm.h - window.get_height()) / 2;

  window.center();

  CHECK(x == window.get_x());
  CHECK(y == window.get_y());
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
  CHECK(window.is_fullscreen());

  window.set_fullscreen(false);
  CHECK(!window.is_fullscreen());

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::set_resizable", "[Window]")
{
  Window window;
  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.set_resizable(true);
  CHECK(window.is_resizable());

  window.set_resizable(false);
  CHECK(!window.is_resizable());

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
  CHECK(window.get_width() == width);

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
  CHECK(window.get_height() == height);

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::set_grab_mouse && Window::is_grabbing_mouse", "[Window]")
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

TEST_CASE("Window::get_title && Window::set_title", "[Window]")
{
  const auto title = "HelloWorld";
  Window window{title};

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  CHECK(window.get_title() == title);

  const auto* other = "foo";
  window.set_title(other);

  CHECK(window.get_title() == other);
  CHECK(listener->counter > 0);
}

TEST_CASE("Window::set_opacity && Window::get_opacity", "[Window]")
{
  Window window;
  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  CHECK(window.get_opacity() == 1);

  SECTION("Windowed mode")
  {
    const auto opacity = 0.4f;
    window.set_opacity(opacity);

    CHECK(window.get_opacity() == opacity);
  }

  SECTION("Fullscreen mode")
  {
    window.set_opacity(1);
    window.set_fullscreen(true);

    const auto opacity = 0.75f;
    window.set_opacity(opacity);

    CHECK(window.get_opacity() == opacity);
  }

  CHECK(listener->counter > 0);
}

TEST_CASE("Window::get_position && Window::set_position", "[Window]")
{
  const auto x = 467;
  const auto y = 246;

  Window window;
  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  window.set_position(x, y);

  CHECK(listener->counter > 0);

  const auto [actualX, actualY] = window.get_position();
  CHECK(x == actualX);
  CHECK(y == actualY);
}

TEST_CASE("Window::set_decorated && Window::is_decorated", "[Window]")
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

TEST_CASE("Window::set_min_size && Window::get_min_size", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  const auto width = 123;
  const auto height = 496;

  window.set_min_size(width, height);
  CHECK(listener->counter > 0);

  const auto [actualWidth, actualHeight] = window.get_min_size();
  CHECK(width == actualWidth);
  CHECK(height == actualHeight);
}

TEST_CASE("Window::set_max_size && Window::get_max_size", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  const auto width = 723;
  const auto height = 813;

  window.set_max_size(width, height);
  CHECK(listener->counter > 0);

  const auto [actualWidth, actualHeight] = window.get_max_size();
  CHECK(width == actualWidth);
  CHECK(height == actualHeight);
}

TEST_CASE("Window::set_icon", "[Window]")
{
  Window window;

  auto listener = std::make_shared<Incrementer>();
  window.add_window_listener(listener);

  Surface icon{"resources/ctn_icon_1.png"};
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
  CHECK(window.get_brightness() == brightness);

  SECTION("Test clamping of bad arguments")
  {
    const auto tooHigh = 1.7f;
    window.set_brightness(tooHigh);
    CHECK(window.get_brightness() == 1);

    const auto tooLow = -1.4f;
    window.set_brightness(tooLow);
    CHECK(window.get_brightness() == 0);
  }
}

TEST_CASE("Window::get_brightness", "[Window]")
{
  const Window window;
  CHECK(window.get_brightness() == 1);
}

TEST_CASE("Window::get_display_index", "[Window]")
{
  const Window window;
  const auto index = window.get_display_index();
  CHECK(index);
  CHECK(*index == 0);
}

TEST_CASE("Window::get_renderer", "[Window]")
{
  const Window window;

  CHECK(!window.get_renderer());

  const Renderer renderer{window};
  SDL_Renderer* sdlRenderer = renderer;

  CHECK(window.get_renderer() == sdlRenderer);
}

TEST_CASE("Window to SDL_Window*", "[Window]")
{
  const Window window;
  CHECK(window.operator SDL_Window*());
}

TEST_CASE("Window::to_string", "[Window]")
{
  const Window window;
  Log::msgf(Category::Test, "%s", window.to_string().c_str());
}
