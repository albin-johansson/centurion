#include "window_handle.hpp"

#include <catch.hpp>
#include <iostream>

#include "centurion_as_ctn.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include "window_utils.hpp"

TEST_CASE("window_handle::window_handle(SDL_Window*)", "[window_handle]")
{
  SECTION("Null pointer")
  {
    ctn::window_handle handle{nullptr};
    CHECK(!handle);
    CHECK(!handle.get());
  }

  SECTION("From valid pointer")
  {
    ctn::window window;
    ctn::window_handle handle{window.get()};
    CHECK(handle);
    CHECK(handle.get());
  }
}

TEST_CASE("window_handle::window_handle(const window&)", "[window_handle]")
{
  ctn::window window;
  ctn::window_handle handle{window};
  CHECK(handle);
  CHECK(handle.get());
}

TEST_CASE("window_handle get renderer", "[window_handle]")
{
  ctn::window window;
  ctn::window_handle handle{window};

  CHECK(!ctn::get_renderer(handle));

  ctn::renderer renderer{window};
  CHECK(ctn::get_renderer(handle));
}

TEST_CASE("window_handle to_string", "[window_handle]")
{
  ctn::window window;
  ctn::window_handle handle{window};

  ctn::log::put(ctn::log::category::test, ctn::to_string(handle));
}

TEST_CASE("window_handle stream operator", "[window_handle]")
{
  ctn::window window;
  ctn::window_handle handle{window};

  std::cout << "COUT: " << handle << '\n';
}