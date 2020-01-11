#include "catch.hpp"
#include "window.h"
#include <memory>

using namespace centurion;

TEST_CASE("Window(string, int, int)", "[Window]") {
  CHECK_THROWS_AS(Window("", 0, 10), std::invalid_argument);
  CHECK_THROWS_AS(Window("", 10, 0), std::invalid_argument);

  const auto width = 123;
  const auto height = 321;
  const auto title = "Foo";
  Window window(title, width, height);

  CHECK(window.get_width() == width);
  CHECK(window.get_height() == height);
  CHECK(window.get_title() == title);
  CHECK(!window.is_visible());
}

TEST_CASE("Window(int, int)", "[Window]") {
  const auto width = 832;
  const auto height = 715;
  Window window(width, height);

  CHECK(window.get_width() == width);
  CHECK(window.get_height() == height);
  CHECK(window.get_title() == "Centurion window");
  CHECK(!window.is_visible());
}

TEST_CASE("Window()", "[Window]") {
  Window window;

  CHECK(window.get_width() == 800);
  CHECK(window.get_height() == 600);
  CHECK(window.get_title() == "Centurion window");
  CHECK(!window.is_visible());
}

TEST_CASE("Window::show", "[Window]") {
  Window window("Foo", 100, 100);

  window.show();
  CHECK(window.is_visible());
}

TEST_CASE("Window::hide", "[Window]") {
  Window window;

  window.hide();
  CHECK(!window.is_visible());
}

TEST_CASE("Window::center", "[Window]") {
  Window window;

  SDL_DisplayMode dm;
  SDL_GetDesktopDisplayMode(0, &dm);

  const auto x = (dm.w - window.get_width()) / 2;
  const auto y = (dm.h - window.get_height()) / 2;

  window.center();

  CHECK(x == window.get_x());
  CHECK(y == window.get_y());
}

TEST_CASE("Window::add_window_listener", "[Window]") {
  Window window;
  CHECK_NOTHROW(window.add_window_listener(nullptr));
}

TEST_CASE("Window::set_fullscreen", "[Window]") {
  Window window;

  window.set_fullscreen(true);
  CHECK(window.is_fullscreen());

  window.set_fullscreen(false);
  CHECK(!window.is_fullscreen());
}

TEST_CASE("Window::set_resizable", "[Window]") {
  Window window;

  window.set_resizable(true);
  CHECK(window.is_resizable());

  window.set_resizable(false);
  CHECK(!window.is_resizable());
}

TEST_CASE("Window::set_width", "[Window]") {
  Window window;

  const auto width = 812;
  window.set_width(width);
  CHECK(window.get_width() == width);
}

TEST_CASE("Window::set_height", "[Window]") {
  Window window;

  const auto height = 327;
  window.set_height(height);
  CHECK(window.get_height() == height);
}

TEST_CASE("Window::get_title", "[Window]") {
  const auto title = "HelloWorld";
  Window window(title);
  CHECK(window.get_title() == title);
}