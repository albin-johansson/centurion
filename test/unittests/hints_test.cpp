#include "hints.h"

#include <catch.hpp>

using namespace centurion;
using namespace hint;

namespace {

template <typename Hint, typename Lambda>
void test_hint(Lambda&& lambda)
{
  const auto optPrev = get_hint<Hint>();

  lambda();

  if (optPrev) {
    set_hint<Hint, HintPrio::Default>(*optPrev);
  }
}

}  // namespace

TEST_CASE("HintPrio", "[Hints]")
{
  CHECK(HintPrio::Default == static_cast<HintPrio>(SDL_HINT_DEFAULT));
  CHECK(HintPrio::Normal == static_cast<HintPrio>(SDL_HINT_NORMAL));
  CHECK(HintPrio::Override == static_cast<HintPrio>(SDL_HINT_OVERRIDE));

  CHECK(static_cast<HintPrio>(SDL_HINT_DEFAULT) == HintPrio::Default);
  CHECK(static_cast<HintPrio>(SDL_HINT_NORMAL) == HintPrio::Normal);
  CHECK(static_cast<HintPrio>(SDL_HINT_OVERRIDE) == HintPrio::Override);
}

TEST_CASE("set_hint", "[Hints]")
{
  SECTION("AccelerometerAsJoystick")
  {
    test_hint<AccelerometerAsJoystick>([] {
      CHECK(set_hint<AccelerometerAsJoystick>(true));
      CHECK(get_hint<AccelerometerAsJoystick>().value());

      CHECK(set_hint<AccelerometerAsJoystick>(false));
      CHECK(!get_hint<AccelerometerAsJoystick>().value());
    });
  }

  SECTION("RenderDriver")
  {
    test_hint<RenderDriver>([] {
      const auto value = OpenGL;
      CHECK(set_hint<RenderDriver>(value));
      CHECK(get_hint<RenderDriver>().value() == value);
    });
  }

  SECTION("NoSignalHandlers")
  {
    test_hint<NoSignalHandlers>([] {
      CHECK(set_hint<NoSignalHandlers>(true));
      CHECK(get_hint<NoSignalHandlers>().value());

      CHECK(set_hint<NoSignalHandlers>(false));
      CHECK(!get_hint<NoSignalHandlers>().value());
    });
  }

  SECTION("AndroidAPKExpansionMainFileVersion") {
    test_hint<AndroidAPKExpansionMainFileVersion>([]{
      CHECK(set_hint<AndroidAPKExpansionMainFileVersion>(1));
      CHECK(get_hint<AndroidAPKExpansionMainFileVersion>() == 1);
    });
  }
}