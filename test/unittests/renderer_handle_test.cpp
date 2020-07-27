#include "renderer_handle.hpp"

#include <catch.hpp>
#include <iostream>

#include "centurion_as_ctn.hpp"
#include "renderer.hpp"
#include "window.hpp"

TEST_CASE("renderer_handle::renderer_handle(SDL_Renderer*)",
          "[renderer_handle]")
{
  SECTION("Null pointer")
  {
    ctn::renderer_handle handle{nullptr};
    CHECK(!handle);
    CHECK(!handle.get());
  }

  SECTION("From valid pointer")
  {
    ctn::window window;
    ctn::renderer renderer{window};
    ctn::renderer_handle handle{renderer.get()};

    CHECK(handle);
    CHECK(handle.get());
  }
}

TEST_CASE("renderer_handle::renderer_handle(const renderer&)",
          "[renderer_handle]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  ctn::renderer_handle handle{renderer};

  CHECK(handle);
  CHECK(handle.get());
}

TEST_CASE("renderer_handle to_string", "[renderer_handle]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  ctn::renderer_handle handle{renderer};

  ctn::log::put(ctn::log::category::test, ctn::to_string(handle));
}

TEST_CASE("renderer_handle stream operator", "[renderer_handle]")
{
  ctn::window window;
  ctn::renderer renderer{window};
  ctn::renderer_handle handle{renderer};

  std::cout << "COUT: " << handle << '\n';
}