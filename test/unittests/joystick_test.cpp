#include "joystick.hpp"

#include <catch.hpp>

#include "exception.hpp"

// Note, it's hard to actually test the joystick API, so coverage is the best
// we can do really.

TEST_CASE("joystick constructors", "[joystick]")
{
  SECTION("Index ctor")
  {
    CHECK_THROWS_AS(cen::joystick{0}, cen::exception);
  }
}

TEST_CASE("joystick::update", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::update());
}

TEST_CASE("joystick locking/unlocking", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::lock());
  CHECK_NOTHROW(cen::joystick::unlock());
}

TEST_CASE("joystick polling", "[joystick]")
{
  cen::joystick::set_polling(false);
  CHECK(!cen::joystick::is_polling());

  cen::joystick::set_polling(true);
  CHECK(cen::joystick::is_polling());
}

TEST_CASE("joystick_from_instance_id", "[joystick]")
{
  const auto handle = cen::joystick_handle::from_instance_id(0);
  CHECK(!handle);
}

TEST_CASE("joystick_from_player_index", "[joystick]")
{
  const auto handle = cen::joystick_handle::from_player_index(0);
  CHECK(!handle);
}

TEST_CASE("joystick::amount", "[joystick]")
{
  const auto amount = cen::joystick::amount();
  REQUIRE(amount.has_value());
  CHECK(*amount == 0);
}

TEST_CASE("joystick::guid(int)", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::guid(0));
}

TEST_CASE("joystick::player_index(int)", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::player_index(0));
}

TEST_CASE("joystick::vendor(int)", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::vendor(0));
}

TEST_CASE("joystick::product(int)", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::product(0));
}

TEST_CASE("joystick::product_version(int)", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::product_version(0));
}

TEST_CASE("joystick::get_type(int)", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::get_type(0));
}

TEST_CASE("joystick::instance_id(int)", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::instance_id(0));
}

TEST_CASE("joystick::name(int)", "[joystick]")
{
  CHECK_NOTHROW(cen::joystick::name(0));
}

TEST_CASE("joystick::guid_from_string(int)", "[joystick]")
{
  const cen::czstring str = "";
  CHECK_NOTHROW(cen::joystick::guid_from_string(str));
}

TEST_CASE("joystick::axis_max", "[joystick]")
{
  CHECK(cen::joystick::axis_max() == SDL_JOYSTICK_AXIS_MAX);
}

TEST_CASE("joystick::axis_min", "[joystick]")
{
  CHECK(cen::joystick::axis_min() == SDL_JOYSTICK_AXIS_MIN);
}

TEST_CASE("joystick::power values", "[joystick]")
{
  using jpower = cen::joystick::power;

  SECTION("Operator ==")
  {
    CHECK(jpower::unknown == SDL_JOYSTICK_POWER_UNKNOWN);
    CHECK(jpower::empty == SDL_JOYSTICK_POWER_EMPTY);
    CHECK(jpower::low == SDL_JOYSTICK_POWER_LOW);
    CHECK(jpower::medium == SDL_JOYSTICK_POWER_MEDIUM);
    CHECK(jpower::full == SDL_JOYSTICK_POWER_FULL);
    CHECK(jpower::wired == SDL_JOYSTICK_POWER_WIRED);
    CHECK(jpower::max == SDL_JOYSTICK_POWER_MAX);

    CHECK(SDL_JOYSTICK_POWER_UNKNOWN == jpower::unknown);
    CHECK(SDL_JOYSTICK_POWER_EMPTY == jpower::empty);
    CHECK(SDL_JOYSTICK_POWER_LOW == jpower::low);
    CHECK(SDL_JOYSTICK_POWER_MEDIUM == jpower::medium);
    CHECK(SDL_JOYSTICK_POWER_FULL == jpower::full);
    CHECK(SDL_JOYSTICK_POWER_WIRED == jpower::wired);
    CHECK(SDL_JOYSTICK_POWER_MAX == jpower::max);
  }

  SECTION("Operator !=")
  {
    CHECK(jpower::max != SDL_JOYSTICK_POWER_WIRED);
    CHECK(SDL_JOYSTICK_POWER_MEDIUM != jpower::low);
  }
}

TEST_CASE("joystick::hat_state values", "[joystick]")
{
  using hs = cen::joystick::hat_state;

  CHECK(hs::centered == static_cast<hs>(SDL_HAT_CENTERED));
  CHECK(hs::up == static_cast<hs>(SDL_HAT_UP));
  CHECK(hs::right == static_cast<hs>(SDL_HAT_RIGHT));
  CHECK(hs::down == static_cast<hs>(SDL_HAT_DOWN));
  CHECK(hs::left == static_cast<hs>(SDL_HAT_LEFT));
  CHECK(hs::right_up == static_cast<hs>(SDL_HAT_RIGHTUP));
  CHECK(hs::right_down == static_cast<hs>(SDL_HAT_RIGHTDOWN));
  CHECK(hs::left_up == static_cast<hs>(SDL_HAT_LEFTUP));
  CHECK(hs::left_down == static_cast<hs>(SDL_HAT_LEFTDOWN));
}

TEST_CASE("joystick::type values", "[joystick]")
{
  using joystick_t = cen::joystick::type;

  SECTION("Operator ==")
  {
    CHECK(joystick_t::unknown == SDL_JOYSTICK_TYPE_UNKNOWN);
    CHECK(joystick_t::game_controller == SDL_JOYSTICK_TYPE_GAMECONTROLLER);
    CHECK(joystick_t::wheel == SDL_JOYSTICK_TYPE_WHEEL);
    CHECK(joystick_t::arcade_stick == SDL_JOYSTICK_TYPE_ARCADE_STICK);
    CHECK(joystick_t::flight_stick == SDL_JOYSTICK_TYPE_FLIGHT_STICK);
    CHECK(joystick_t::dance_pad == SDL_JOYSTICK_TYPE_DANCE_PAD);
    CHECK(joystick_t::guitar == SDL_JOYSTICK_TYPE_GUITAR);
    CHECK(joystick_t::drum_kit == SDL_JOYSTICK_TYPE_DRUM_KIT);
    CHECK(joystick_t::arcade_pad == SDL_JOYSTICK_TYPE_ARCADE_PAD);
    CHECK(joystick_t::throttle == SDL_JOYSTICK_TYPE_THROTTLE);

    CHECK(SDL_JOYSTICK_TYPE_UNKNOWN == joystick_t::unknown);
    CHECK(SDL_JOYSTICK_TYPE_GAMECONTROLLER == joystick_t::game_controller);
    CHECK(SDL_JOYSTICK_TYPE_WHEEL == joystick_t::wheel);
    CHECK(SDL_JOYSTICK_TYPE_ARCADE_STICK == joystick_t::arcade_stick);
    CHECK(SDL_JOYSTICK_TYPE_FLIGHT_STICK == joystick_t::flight_stick);
    CHECK(SDL_JOYSTICK_TYPE_DANCE_PAD == joystick_t::dance_pad);
    CHECK(SDL_JOYSTICK_TYPE_GUITAR == joystick_t::guitar);
    CHECK(SDL_JOYSTICK_TYPE_DRUM_KIT == joystick_t::drum_kit);
    CHECK(SDL_JOYSTICK_TYPE_ARCADE_PAD == joystick_t::arcade_pad);
    CHECK(SDL_JOYSTICK_TYPE_THROTTLE == joystick_t::throttle);
  }

  SECTION("Operator !=")
  {
    CHECK(joystick_t::guitar != SDL_JOYSTICK_TYPE_DANCE_PAD);
    CHECK(SDL_JOYSTICK_TYPE_ARCADE_PAD != joystick_t::flight_stick);
  }
}

TEST_CASE("joystick_handle", "[joystick]")
{


  CHECK(!cen::joystick_handle::from_player_index(0));
}