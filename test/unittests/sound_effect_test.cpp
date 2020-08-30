#include "sound_effect.hpp"

#include <catch.hpp>
#include <iostream>

#include "cen.hpp"
#include "exception.hpp"
#include "log.hpp"
#include "thread.hpp"

static constexpr auto path = "resources/click.wav";

TEST_CASE("sound_effect(nn_czstring)", "[sound_effect]")
{
  CHECK_THROWS_AS(cen::sound_effect("somebadpath"), cen::mix_error);
}

TEST_CASE("sound_effect(sound_effect&&)", "[sound_effect]")
{
  cen::sound_effect sound{path};
  cen::sound_effect other{std::move(sound)};

  CHECK(!sound.get());
  CHECK(other.get());
}

TEST_CASE("sound_effect::operator=(sound_effect&&)", "[sound_effect]")
{
  SECTION("Self-assignment")
  {
    cen::sound_effect sound{path};

    sound = std::move(sound);
    CHECK(sound.get());
  }

  SECTION("Normal usage")
  {
    cen::sound_effect sound{path};
    cen::sound_effect other{path};

    other = std::move(sound);

    CHECK(!sound.get());
    CHECK(other.get());
  }
}

TEST_CASE("sound_effect smart pointer factory methods", "[sound_effect]")
{
  CHECK(cen::sound_effect::unique(path));
  CHECK(cen::sound_effect::shared(path));
  CHECK_THROWS_AS(cen::sound_effect::unique(""), cen::mix_error);
  CHECK_THROWS_AS(cen::sound_effect::shared(""), cen::mix_error);
}

TEST_CASE("sound_effect::play", "[sound_effect]")
{
  cen::sound_effect sound{path};

  CHECK(!sound.is_playing());

  sound.play();
  CHECK(sound.is_playing());

  sound.stop();
  CHECK(!sound.is_playing());

  sound.play(5);
  CHECK(sound.is_playing());
}

TEST_CASE("sound_effect looping", "[sound_effect]")
{
  cen::sound_effect sound{path};
  sound.set_volume(1);

  sound.play(10);
  CHECK(sound.is_playing());
  sound.stop();

  CHECK(cen::sound_effect::loopForever < 0);

  CHECK_NOTHROW(sound.play(cen::sound_effect::loopForever));
  CHECK(sound.is_playing());

  sound.stop();
  CHECK(!sound.is_playing());
}

TEST_CASE("sound_effect::stop", "[sound_effect]")
{
  cen::sound_effect sound{path};

  sound.play();
  sound.stop();
  CHECK(!sound.is_playing());
}

TEST_CASE("sound_effect::fade_in", "[sound_effect]")
{
  cen::sound_effect sound{path};

  using ms = cen::milliseconds<int>;

  CHECK_NOTHROW(sound.fade_in(ms{-1}));
  sound.stop();

  CHECK_NOTHROW(sound.fade_in(ms{0}));
  CHECK(!sound.is_playing());

  sound.fade_in(ms{100});
  CHECK(sound.is_playing());
}

TEST_CASE("sound_effect::fade_out", "[sound_effect]")
{
  cen::sound_effect sound{path};

  using ms = cen::milliseconds<int>;

  CHECK_NOTHROW(sound.fade_out(ms{0}));
  CHECK(!sound.is_playing());

  sound.play();
  sound.fade_out(ms{50});
  CHECK(sound.is_playing());

  cen::thread::sleep(cen::seconds<cen::u32>(1));
  CHECK(!sound.is_playing());
}

TEST_CASE("sound_effect:set_volume", "[sound_effect]")
{
  cen::sound_effect sound{path};

  SECTION("Valid volume")
  {
    const auto volume = 27;
    sound.set_volume(volume);
    CHECK(volume == sound.volume());
  }

  SECTION("Volume underflow")
  {
    const auto volume = -1;
    sound.set_volume(volume);
    CHECK(sound.volume() == 0);
  }

  SECTION("Volume overflow")
  {
    const auto volume = cen::sound_effect::max_volume() + 1;
    sound.set_volume(volume);
    CHECK(sound.volume() == cen::sound_effect::max_volume());
  }
}

TEST_CASE("sound_effect::volume", "[sound_effect]")
{
  cen::sound_effect sound{path};
  CHECK(sound.volume() == cen::sound_effect::max_volume());
  CHECK(sound.volume() == 128);  // because of the documentation guarantee
  CHECK(cen::sound_effect::max_volume() == MIX_MAX_VOLUME);
}

TEST_CASE("sound_effect::is_playing", "[sound_effect]")
{
  cen::sound_effect sound{path};

  CHECK(!sound.is_playing());
  sound.play(2);
  CHECK(sound.is_playing());
}

TEST_CASE("sound_effect::is_fading", "[sound_effect]")
{
  cen::sound_effect sound{path};

  CHECK(!sound.is_fading());

  sound.play(2);
  CHECK(!sound.is_fading());

  sound.stop();
  sound.fade_in(cen::milliseconds<int>{100});
  CHECK(sound.is_fading());
  CHECK(sound.is_playing());
}

TEST_CASE("sound_effect to_string", "[sound_effect]")
{
  const cen::sound_effect sound{path};
  cen::log::put(cen::to_string(sound));
}

TEST_CASE("sound_effect stream operator", "[sound_effect]")
{
  const cen::sound_effect sound{path};
  std::cout << "COUT: " << sound << '\n';
}

TEST_CASE("sound_effect::max_volume", "[sound_effect]")
{
  CHECK(cen::sound_effect::max_volume() == MIX_MAX_VOLUME);
}
