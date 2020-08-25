#include "game_controller.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"

TEST_CASE("load_game_controller_mappings", "[game_controller]")
{
  const auto nAdded =
      ctn::gamecontroller::load_mappings("resources/gamecontrollerdb.txt");
  CHECK(nAdded > 0);
}