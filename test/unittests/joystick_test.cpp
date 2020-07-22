#include "joystick.hpp"

#include <catch.hpp>

#include "centurion_as_ctn.hpp"
#include "centurion_exception.hpp"

// Note, it's hard to actually test the joystick API, so coverage is the best
// we can do really.

TEST_CASE("Constructors", "[joystick]")
{
  SECTION("Index ctor")
  {
    CHECK_THROWS_AS(ctn::joystick{0}, ctn::centurion_exception);
  }

  SECTION("SDL_Joystick* ctor")
  {
    SDL_Joystick* ptr = nullptr;
    CHECK_THROWS_AS(ctn::joystick{ptr}, ctn::centurion_exception);
  }
}

TEST_CASE("Smart pointer factory methods", "[joystick]")
{
  SECTION("Unique")
  {
    CHECK_THROWS_AS(ctn::joystick::unique(0), ctn::centurion_exception);
    CHECK_THROWS_AS(ctn::joystick::unique(nullptr), ctn::centurion_exception);
  }

  SECTION("Shared")
  {
    CHECK_THROWS_AS(ctn::joystick::shared(0), ctn::centurion_exception);
    CHECK_THROWS_AS(ctn::joystick::shared(nullptr), ctn::centurion_exception);
  }
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
    CHECK(j_power::Unknown == SDL_JOYSTICK_POWER_UNKNOWN);
    CHECK(j_power::Empty == SDL_JOYSTICK_POWER_EMPTY);
    CHECK(j_power::Low == SDL_JOYSTICK_POWER_LOW);
    CHECK(j_power::Medium == SDL_JOYSTICK_POWER_MEDIUM);
    CHECK(j_power::Full == SDL_JOYSTICK_POWER_FULL);
    CHECK(j_power::Wired == SDL_JOYSTICK_POWER_WIRED);
    CHECK(j_power::Max == SDL_JOYSTICK_POWER_MAX);

    CHECK(SDL_JOYSTICK_POWER_UNKNOWN == j_power::Unknown);
    CHECK(SDL_JOYSTICK_POWER_EMPTY == j_power::Empty);
    CHECK(SDL_JOYSTICK_POWER_LOW == j_power::Low);
    CHECK(SDL_JOYSTICK_POWER_MEDIUM == j_power::Medium);
    CHECK(SDL_JOYSTICK_POWER_FULL == j_power::Full);
    CHECK(SDL_JOYSTICK_POWER_WIRED == j_power::Wired);
    CHECK(SDL_JOYSTICK_POWER_MAX == j_power::Max);
  }

  SECTION("Operator !=")
  {
    CHECK(j_power::Max != SDL_JOYSTICK_POWER_WIRED);
    CHECK(SDL_JOYSTICK_POWER_MEDIUM != j_power::Low);
  }
}

TEST_CASE("joystick::HatState values", "[joystick]")
{
  using hs = ctn::joystick::hat_state;

  CHECK(hs::Centered == static_cast<hs>(SDL_HAT_CENTERED));
  CHECK(hs::Up == static_cast<hs>(SDL_HAT_UP));
  CHECK(hs::Right == static_cast<hs>(SDL_HAT_RIGHT));
  CHECK(hs::Down == static_cast<hs>(SDL_HAT_DOWN));
  CHECK(hs::Left == static_cast<hs>(SDL_HAT_LEFT));
  CHECK(hs::RightUp == static_cast<hs>(SDL_HAT_RIGHTUP));
  CHECK(hs::RightDown == static_cast<hs>(SDL_HAT_RIGHTDOWN));
  CHECK(hs::LeftUp == static_cast<hs>(SDL_HAT_LEFTUP));
  CHECK(hs::LeftDown == static_cast<hs>(SDL_HAT_LEFTDOWN));
}

TEST_CASE("joystick::Type values", "[joystick]")
{
  using joystick_t = ctn::joystick::type;

  SECTION("Operator ==")
  {
    CHECK(joystick_t::Unknown == SDL_JOYSTICK_TYPE_UNKNOWN);
    CHECK(joystick_t::GameController == SDL_JOYSTICK_TYPE_GAMECONTROLLER);
    CHECK(joystick_t::Wheel == SDL_JOYSTICK_TYPE_WHEEL);
    CHECK(joystick_t::ArcadeStick == SDL_JOYSTICK_TYPE_ARCADE_STICK);
    CHECK(joystick_t::FlightStick == SDL_JOYSTICK_TYPE_FLIGHT_STICK);
    CHECK(joystick_t::DancePad == SDL_JOYSTICK_TYPE_DANCE_PAD);
    CHECK(joystick_t::Guitar == SDL_JOYSTICK_TYPE_GUITAR);
    CHECK(joystick_t::DrumKit == SDL_JOYSTICK_TYPE_DRUM_KIT);
    CHECK(joystick_t::ArcadePad == SDL_JOYSTICK_TYPE_ARCADE_PAD);
    CHECK(joystick_t::Throttle == SDL_JOYSTICK_TYPE_THROTTLE);

    CHECK(SDL_JOYSTICK_TYPE_UNKNOWN == joystick_t::Unknown);
    CHECK(SDL_JOYSTICK_TYPE_GAMECONTROLLER == joystick_t::GameController);
    CHECK(SDL_JOYSTICK_TYPE_WHEEL == joystick_t::Wheel);
    CHECK(SDL_JOYSTICK_TYPE_ARCADE_STICK == joystick_t::ArcadeStick);
    CHECK(SDL_JOYSTICK_TYPE_FLIGHT_STICK == joystick_t::FlightStick);
    CHECK(SDL_JOYSTICK_TYPE_DANCE_PAD == joystick_t::DancePad);
    CHECK(SDL_JOYSTICK_TYPE_GUITAR == joystick_t::Guitar);
    CHECK(SDL_JOYSTICK_TYPE_DRUM_KIT == joystick_t::DrumKit);
    CHECK(SDL_JOYSTICK_TYPE_ARCADE_PAD == joystick_t::ArcadePad);
    CHECK(SDL_JOYSTICK_TYPE_THROTTLE == joystick_t::Throttle);
  }

  SECTION("Operator !=")
  {
    CHECK(joystick_t::Guitar != SDL_JOYSTICK_TYPE_DANCE_PAD);
    CHECK(SDL_JOYSTICK_TYPE_ARCADE_PAD != joystick_t::FlightStick);
  }
}