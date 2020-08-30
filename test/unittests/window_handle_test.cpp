#include "window_handle.hpp"

#include <catch.hpp>
#include <iostream>

#include "cen.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include "window_utils.hpp"

TEST_CASE("window_handle::window_handle(SDL_Window*)", "[window_handle]")
{
  SECTION("Null pointer")
  {
    cen::window_handle handle{nullptr};
    CHECK(!handle);
    CHECK(!handle.get());
  }

  SECTION("From valid pointer")
  {
    cen::window window;
    cen::window_handle handle{window.get()};
    CHECK(handle);
    CHECK(handle.get());
  }
}

TEST_CASE("window_handle::window_handle(const window&)", "[window_handle]")
{
  cen::window window;
  cen::window_handle handle{window};
  CHECK(handle);
  CHECK(handle.get());
}

TEST_CASE("window_handle get renderer", "[window_handle]")
{
  cen::window window;
  cen::window_handle handle{window};

  CHECK(!cen::get_renderer(handle));

  cen::renderer renderer{window};
  CHECK(cen::get_renderer(handle));
}

TEST_CASE("window_handle to_string", "[window_handle]")
{
  cen::window window;
  cen::window_handle handle{window};

  cen::log::put(cen::to_string(handle));
}

TEST_CASE("window_handle stream operator", "[window_handle]")
{
  cen::window window;
  cen::window_handle handle{window};

  std::cout << "COUT: " << handle << '\n';
}