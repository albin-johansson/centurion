#include "joystick.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_exception.hpp"

// Note, it's hard to actually test the joystick API, so coverage is the best
// we can do really.

TEST_CASE("joystick constructors", "[joystick]")
{
  SECTION("Index ctor")
  {
    CHECK_THROWS_AS(ctn::joystick{0}, ctn::centurion_exception);
  }
}

TEST_CASE("joystick smart pointer factory methods", "[joystick]")
{
  SECTION("Unique") { CHECK_THROWS(ctn::joystick::unique(0)); }

  SECTION("Shared") { CHECK_THROWS(ctn::joystick::shared(0)); }
}

TEST_CASE("joystick::update", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::update());
}

TEST_CASE("joystick locking/unlocking", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::lock());
  CHECK_NOTHROW(ctn::joystick::unlock());
}

TEST_CASE("joystick polling", "[joystick]")
{
  ctn::joystick::set_polling(false);
  CHECK(!ctn::joystick::polling());

  ctn::joystick::set_polling(true);
  CHECK(ctn::joystick::polling());
}

TEST_CASE("joystick::from_instance_id", "[joystick]")
{
  const auto* ptr = ctn::joystick::from_instance_id(0);
  CHECK(!ptr);
}

TEST_CASE("joystick::from_player_index", "[joystick]")
{
  const auto* ptr = ctn::joystick::from_player_index(0);
  CHECK(!ptr);
}

TEST_CASE("joystick::amount", "[joystick]")
{
  const auto amount = ctn::joystick::amount();
  REQUIRE(amount.has_value());
  CHECK(*amount == 0);
}

TEST_CASE("joystick::guid(int)", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::guid(0));
}

TEST_CASE("joystick::player_index(int)", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::player_index(0));
}

TEST_CASE("joystick::vendor(int)", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::vendor(0));
}

TEST_CASE("joystick::product(int)", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::product(0));
}

TEST_CASE("joystick::product_version(int)", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::product_version(0));
}

TEST_CASE("joystick::get_type(int)", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::get_type(0));
}

TEST_CASE("joystick::instance_id(int)", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::instance_id(0));
}

TEST_CASE("joystick::name(int)", "[joystick]")
{
  CHECK_NOTHROW(ctn::joystick::name(0));
}

TEST_CASE("joystick::guid_from_string(int)", "[joystick]")
{
  const ctn::czstring str = "";
  CHECK_NOTHROW(ctn::joystick::guid_from_string(str));
}

TEST_CASE("joystick::axis_max", "[joystick]")
{
  CHECK(ctn::joystick::axis_max() == SDL_JOYSTICK_AXIS_MAX);
}

TEST_CASE("joystick::axis_min", "[joystick]")
{
  CHECK(ctn::joystick::axis_min() == SDL_JOYSTICK_AXIS_MIN);
}

TEST_CASE("joystick::Power values", "[joystick]")
{
  using j_power = ctn::joystick::power;

  SECTION("Operator ==")
  {
    CHECK(j_power::unknown == SDL_JOYSTICK_POWER_UNKNOWN);
    CHECK(j_power::empty == SDL_JOYSTICK_POWER_EMPTY);
    CHECK(j_power::low == SDL_JOYSTICK_POWER_LOW);
    CHECK(j_power::medium == SDL_JOYSTICK_POWER_MEDIUM);
    CHECK(j_power::full == SDL_JOYSTICK_POWER_FULL);
    CHECK(j_power::wired == SDL_JOYSTICK_POWER_WIRED);
    CHECK(j_power::max == SDL_JOYSTICK_POWER_MAX);

    CHECK(SDL_JOYSTICK_POWER_UNKNOWN == j_power::unknown);
    CHECK(SDL_JOYSTICK_POWER_EMPTY == j_power::empty);
    CHECK(SDL_JOYSTICK_POWER_LOW == j_power::low);
    CHECK(SDL_JOYSTICK_POWER_MEDIUM == j_power::medium);
    CHECK(SDL_JOYSTICK_POWER_FULL == j_power::full);
    CHECK(SDL_JOYSTICK_POWER_WIRED == j_power::wired);
    CHECK(SDL_JOYSTICK_POWER_MAX == j_power::max);
  }

  SECTION("Operator !=")
  {
    CHECK(j_power::max != SDL_JOYSTICK_POWER_WIRED);
    CHECK(SDL_JOYSTICK_POWER_MEDIUM != j_power::low);
  }
}

TEST_CASE("joystick::HatState values", "[joystick]")
{
  using hs = ctn::joystick::hat_state;

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

TEST_CASE("joystick::Type values", "[joystick]")
{
  using joystick_t = ctn::joystick::type;

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