#include "renderer_handle.hpp"

#include <catch.hpp>
#include <iostream>

#include "cen.hpp"
#include "log.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("renderer_handle::renderer_handle(SDL_Renderer*)",
          "[renderer_handle]")
{
  SECTION("Null pointer")
  {
    cen::renderer_handle handle{nullptr};
    CHECK(!handle);
    CHECK(!handle.get());
  }

  SECTION("From valid pointer")
  {
    cen::window window;
    cen::renderer renderer{window};
    cen::renderer_handle handle{renderer.get()};

    CHECK(handle);
    CHECK(handle.get());
  }
}

TEST_CASE("renderer_handle::renderer_handle(const renderer&)",
          "[renderer_handle]")
{
  cen::window window;
  cen::renderer renderer{window};
  cen::renderer_handle handle{renderer};

  CHECK(handle);
  CHECK(handle.get());
}

TEST_CASE("renderer_handle to_string", "[renderer_handle]")
{
  cen::window window;
  cen::renderer renderer{window};
  cen::renderer_handle handle{renderer};

  cen::log::put(cen::to_string(handle));
}

TEST_CASE("renderer_handle stream operator", "[renderer_handle]")
{
  cen::window window;
  cen::renderer renderer{window};
  cen::renderer_handle handle{renderer};

  std::cout << "COUT: " << handle << '\n';
}