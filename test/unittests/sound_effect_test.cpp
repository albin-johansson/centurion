#ifndef CENTURION_NOAUDIO

#include "sound_effect.hpp"

#include <catch.hpp>

#include "centurion_exception.hpp"
#include "log.hpp"
#include "timer.hpp"

using namespace centurion;

static constexpr auto path = "resources/click.wav";

TEST_CASE("SoundEffect(CZString)", "[SoundEffect]")
{
  CHECK_THROWS_AS(SoundEffect("somebadpath"), centurion_exception);
  CHECK_THROWS_AS(SoundEffect(nullptr), centurion_exception);
}

TEST_CASE("SoundEffect(SoundEffect&&)", "[SoundEffect]")
{
  SoundEffect sound{path};
  SoundEffect other{std::move(sound)};

  CHECK(!sound.get());
  CHECK(other.get());
}

TEST_CASE("SoundEffect::operator=(SoundEffect&&)", "[SoundEffect]")
{
  SECTION("Self-assignment")
  {
    SoundEffect sound{path};

    sound = std::move(sound);
    CHECK(sound.get());
  }

  SECTION("Normal usage")
  {
    SoundEffect sound{path};
    SoundEffect other{path};

    other = std::move(sound);

    CHECK(!sound.get());
    CHECK(other.get());
  }
}

TEST_CASE("SoundEffect smart pointer factory methods", "[SoundEffect]")
{
  CHECK(SoundEffect::unique(path));
  CHECK(SoundEffect::shared(path));
  CHECK_THROWS_AS(SoundEffect::unique(""), centurion_exception);
  CHECK_THROWS_AS(SoundEffect::unique(nullptr), centurion_exception);
  CHECK_THROWS_AS(SoundEffect::shared(""), centurion_exception);
  CHECK_THROWS_AS(SoundEffect::shared(nullptr), centurion_exception);
}

TEST_CASE("SoundEffect::play", "[SoundEffect]")
{
  SoundEffect sound{path};

  CHECK(!sound.playing());

  sound.play();
  CHECK(sound.playing());

  sound.stop();
  CHECK(!sound.playing());

  sound.play(5);
  CHECK(sound.playing());
}

TEST_CASE("SoundEffect looping", "[SoundEffect]")
{
  SoundEffect sound{path};
  sound.set_volume(1);

  sound.play(10);
  CHECK(sound.playing());
  sound.stop();

  CHECK(SoundEffect::loopForever < 0);

  CHECK_NOTHROW(sound.play(SoundEffect::loopForever));
  CHECK(sound.playing());

  sound.stop();
  CHECK(!sound.playing());
}

TEST_CASE("SoundEffect::stop", "[SoundEffect]")
{
  SoundEffect sound{path};

  sound.play();
  sound.stop();
  CHECK(!sound.playing());
}

TEST_CASE("SoundEffect::fade_in", "[SoundEffect]")
{
  SoundEffect sound{path};

  using ms = milliseconds<int>;

  CHECK_NOTHROW(sound.fade_in(ms{-1}));
  sound.stop();

  CHECK_NOTHROW(sound.fade_in(ms{0}));
  CHECK(!sound.playing());

  sound.fade_in(ms{100});
  CHECK(sound.playing());
}

TEST_CASE("SoundEffect::fade_out", "[SoundEffect]")
{
  SoundEffect sound{path};

  using ms = milliseconds<int>;

  CHECK_NOTHROW(sound.fade_out(ms{0}));
  CHECK(!sound.playing());

  sound.play();
  sound.fade_out(ms{50});
  CHECK(sound.playing());

  Timer::delay(seconds<u32>(1));
  CHECK(!sound.playing());
}

TEST_CASE("SoundEffect:set_volume", "[SoundEffect]")
{
  SoundEffect sound{path};

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
    const auto volume = SoundEffect::maxVolume + 1;
    sound.set_volume(volume);
    CHECK(sound.volume() == SoundEffect::maxVolume);
  }
}

TEST_CASE("SoundEffect::volume", "[SoundEffect]")
{
  SoundEffect sound{path};
  CHECK(sound.volume() == SoundEffect::maxVolume);
  CHECK(sound.volume() == 128);  // because of the documentation guarantee
  CHECK(SoundEffect::maxVolume == MIX_MAX_VOLUME);
}

TEST_CASE("SoundEffect::playing", "[SoundEffect]")
{
  SoundEffect sound{path};

  CHECK(!sound.playing());
  sound.play(2);
  CHECK(sound.playing());
}

TEST_CASE("SoundEffect::to_string", "[SoundEffect]")
{
  SoundEffect sound{path};
  log::info(log::category::test, "%s", sound.to_string().c_str());
}

TEST_CASE("SoundEffect::max_volume", "[SoundEffect]")
{
  CHECK(SoundEffect::max_volume() == MIX_MAX_VOLUME);
}

#endif