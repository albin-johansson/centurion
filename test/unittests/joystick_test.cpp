#include "joystick.h"

#include <catch.hpp>

using namespace centurion;

// Note, it's hard to actually test the joystick API, so coverage is the best
// we can do really.

TEST_CASE("...", "[Joystick]")
{}

TEST_CASE("Joystick::Power values", "[Joystick]")
{
  using JPower = Joystick::Power;

  CHECK(JPower::Unknown == static_cast<JPower>(SDL_JOYSTICK_POWER_UNKNOWN));
  CHECK(JPower::Empty == static_cast<JPower>(SDL_JOYSTICK_POWER_EMPTY));
  CHECK(JPower::Low == static_cast<JPower>(SDL_JOYSTICK_POWER_LOW));
  CHECK(JPower::Medium == static_cast<JPower>(SDL_JOYSTICK_POWER_MEDIUM));
  CHECK(JPower::Full == static_cast<JPower>(SDL_JOYSTICK_POWER_FULL));
  CHECK(JPower::Wired == static_cast<JPower>(SDL_JOYSTICK_POWER_WIRED));
  CHECK(JPower::Max == static_cast<JPower>(SDL_JOYSTICK_POWER_MAX));
}

TEST_CASE("Joystick::HatState values", "[Joystick]")
{
  using HS = Joystick::HatState;

  CHECK(HS::Centered == static_cast<HS>(SDL_HAT_CENTERED));
  CHECK(HS::Up == static_cast<HS>(SDL_HAT_UP));
  CHECK(HS::Right == static_cast<HS>(SDL_HAT_RIGHT));
  CHECK(HS::Down == static_cast<HS>(SDL_HAT_DOWN));
  CHECK(HS::Left == static_cast<HS>(SDL_HAT_LEFT));
  CHECK(HS::RightUp == static_cast<HS>(SDL_HAT_RIGHTUP));
  CHECK(HS::RightDown == static_cast<HS>(SDL_HAT_RIGHTDOWN));
  CHECK(HS::LeftUp == static_cast<HS>(SDL_HAT_LEFTUP));
  CHECK(HS::LeftDown == static_cast<HS>(SDL_HAT_LEFTDOWN));
}

TEST_CASE("Joystick::Type values", "[Joystick]")
{
  using Type = Joystick::Type;

  CHECK(Type::Unknown == static_cast<Type>(SDL_JOYSTICK_TYPE_UNKNOWN));
  CHECK(Type::GameController ==
        static_cast<Type>(SDL_JOYSTICK_TYPE_GAMECONTROLLER));
  CHECK(Type::Wheel == static_cast<Type>(SDL_JOYSTICK_TYPE_WHEEL));
  CHECK(Type::ArcadeStick == static_cast<Type>(SDL_JOYSTICK_TYPE_ARCADE_STICK));
  CHECK(Type::FlightStick == static_cast<Type>(SDL_JOYSTICK_TYPE_FLIGHT_STICK));
  CHECK(Type::DancePad == static_cast<Type>(SDL_JOYSTICK_TYPE_DANCE_PAD));
  CHECK(Type::Guitar == static_cast<Type>(SDL_JOYSTICK_TYPE_GUITAR));
  CHECK(Type::DrumKit == static_cast<Type>(SDL_JOYSTICK_TYPE_DRUM_KIT));
  CHECK(Type::ArcadePad == static_cast<Type>(SDL_JOYSTICK_TYPE_ARCADE_PAD));
  CHECK(Type::Throttle == static_cast<Type>(SDL_JOYSTICK_TYPE_THROTTLE));
}