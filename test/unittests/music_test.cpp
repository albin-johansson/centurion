#ifndef CENTURION_NOAUDIO
#include "music.h"

#include <catch.hpp>

#include "centurion_exception.h"
#include "log.h"

using namespace centurion;

static constexpr auto path = "resources/hiddenPond.mp3";

TEST_CASE("Music::Music(CZString)", "[Music]")
{
  CHECK_THROWS_AS(Music{""}, CenturionException);
  CHECK_THROWS_AS(Music{nullptr}, CenturionException);
  CHECK_NOTHROW(Music{path});
}

TEST_CASE("Music(Music&&)", "[Music]")
{
  Music music{path};
  Music other{std::move(music)};

  CHECK(!music.get());
  CHECK(other.get());
}

TEST_CASE("Music::operator=(Music&&)", "[Music]")
{
  SECTION("Self-assignment")
  {
    Music music{path};
    music = std::move(music);
    CHECK(music.get());
  }

  SECTION("Normal usage")
  {
    Music music{path};
    Music other{path};

    other = std::move(music);

    CHECK(!music.get());
    CHECK(other.get());
  }
}

TEST_CASE("Music smart pointer factory methods", "[Music]")
{
  CHECK_THROWS_AS(Music::unique(""), CenturionException);
  CHECK_THROWS_AS(Music::unique(""), CenturionException);
  CHECK_NOTHROW(Music::unique(path));
  CHECK_NOTHROW(Music::shared(path));
}

TEST_CASE("Music::play", "[Music]")
{
  Music music{path};
  music.play();
  CHECK(Music::playing());
  CHECK(!Music::fading());
  CHECK(!Music::paused());
  CHECK(Music::fade_status() == FadeStatus::None);

  Music::halt();

  music.play(Music::loopForever);
  CHECK(Music::playing());

  Music::halt();
}

TEST_CASE("Music::resume", "[Music]")
{
  CHECK_NOTHROW(Music::resume());

  Music music{path};

  music.play();
  CHECK_NOTHROW(Music::resume());

  Music::pause();
  CHECK(Music::paused());

  Music::resume();
  CHECK(Music::playing());

  Music::halt();
  CHECK_NOTHROW(Music::resume());
}

TEST_CASE("Music::pause", "[Music]")
{
  CHECK_NOTHROW(Music::pause());

  Music music{path};

  music.play();
  Music::pause();
  CHECK(Music::paused());

  music.fade_in(100);
  Music::pause();
  CHECK(Music::paused());
}

TEST_CASE("Music::halt", "[Music]")
{
  CHECK_NOTHROW(Music::halt());

  Music music{path};

  music.play();
  Music::halt();

  CHECK(!Music::playing());
  CHECK(!Music::fading());

  music.fade_in(100);
  Music::halt();

  CHECK(!Music::playing());
  CHECK(!Music::fading());
}

TEST_CASE("Music::fade_in", "[Music]")
{
  CHECK(!Music::fading());

  Music music{path};
  CHECK_NOTHROW(music.fade_in(-1));

  Music::halt();

  music.fade_in(100);
  CHECK(Music::fading());
}

TEST_CASE("Music::fade_out", "[Music]")
{
  CHECK(!Music::fading());
  CHECK_NOTHROW(Music::fade_out(100));
  CHECK_NOTHROW(Music::fade_out(-1));

  Music music{path};
  music.fade_in(100);

  CHECK(Music::fading());
}

TEST_CASE("Music::set_volume", "[Music]")
{
  const auto originalVolume = Music::volume();

  SECTION("Valid volume")
  {
    const auto volume = 102;
    Music::set_volume(volume);
    CHECK(volume == Music::volume());
  }

  SECTION("Negative volume")
  {
    const auto volume = -1;
    Music::set_volume(volume);
    CHECK(Music::volume() == 0);
  }

  SECTION("Volume overflow")
  {
    const auto volume = Music::maxVolume + 1;
    Music::set_volume(volume);
    CHECK(Music::maxVolume == Music::volume());
  }

  Music::set_volume(originalVolume);
}

TEST_CASE("Music::playing", "[Music]")
{
  CHECK(!Music::playing());

  Music music{path};

  music.play();
  CHECK(Music::playing());

  Music::halt();

  music.fade_in(100);
  CHECK(Music::playing());
}

TEST_CASE("Music::paused", "[Music]")
{
  Music music{path};
  music.play();

  Music::pause();
  CHECK(Music::paused());
}

TEST_CASE("Music::fading", "[Music]")
{
  CHECK(!Music::fading());

  Music music{path};

  music.play();
  CHECK(!Music::fading());
  Music::halt();

  music.fade_in(200);
  CHECK(Music::fading());

  Music::fade_out(
      50);  // This should have no effect, since the music is fading in
  CHECK(Music::fade_status() == FadeStatus::In);
}

TEST_CASE("Music::volume", "[Music]")
{
  CHECK(Music::volume() == Music::maxVolume);

  const auto volume = 47;
  Music::set_volume(volume);

  CHECK(Music::volume() == volume);
}

TEST_CASE("Music::fade_status", "[Music]")
{
  CHECK(Music::fade_status() == FadeStatus::None);
  CHECK(!Music::fading());

  Music music{path};

  music.fade_in(100);
  CHECK(Music::fade_status() == FadeStatus::In);
  CHECK(Music::fading());
  CHECK(Music::playing());
  CHECK(!Music::paused());

  Music::halt();

  music.play();
  Music::fade_out(100);
  CHECK(Music::fade_status() == FadeStatus::Out);
  CHECK(Music::fading());
  CHECK(Music::playing());
  CHECK(!Music::paused());

  Music::halt();
  CHECK(Music::fade_status() == FadeStatus::None);
}

TEST_CASE("Music::music_type", "[Music]")
{
  Music music{path};
  CHECK(music.music_type() == MusicType::MP3);
}

TEST_CASE("Music::to_string", "[Music]")
{
  Music music{path};
  Log::info(Log::Category::Test, "%s", music.to_string().c_str());
}

TEST_CASE("Music to Mix_Music*", "[Music]")
{
  Music music{path};
  Mix_Music* sdlMusic = music;
  CHECK(sdlMusic);
}

TEST_CASE("FadeStatus enum values", "[Music]")
{
  CHECK(FadeStatus::None == MIX_NO_FADING);
  CHECK(FadeStatus::In == MIX_FADING_IN);
  CHECK(FadeStatus::Out == MIX_FADING_OUT);

  CHECK(MIX_NO_FADING == FadeStatus::None);
  CHECK(MIX_FADING_IN == FadeStatus::In);
  CHECK(MIX_FADING_OUT == FadeStatus::Out);
}

TEST_CASE("MusicType enum values", "[Music]")
{
  CHECK(MusicType::Unknown == MUS_NONE);
  CHECK(MusicType::MP3 == MUS_MP3);
  CHECK(MusicType::WAV == MUS_WAV);
  CHECK(MusicType::CMD == MUS_CMD);
  CHECK(MusicType::MOD == MUS_MOD);
  CHECK(MusicType::OGG == MUS_OGG);
  CHECK(MusicType::FLAC == MUS_FLAC);
  CHECK(MusicType::MIDI == MUS_MID);
  CHECK(MusicType::OPUS == MUS_OPUS);

  CHECK(MUS_NONE == MusicType::Unknown);
  CHECK(MUS_MP3 == MusicType::MP3);
  CHECK(MUS_WAV == MusicType::WAV);
  CHECK(MUS_CMD == MusicType::CMD);
  CHECK(MUS_MOD == MusicType::MOD);
  CHECK(MUS_OGG == MusicType::OGG);
  CHECK(MUS_FLAC == MusicType::FLAC);
  CHECK(MUS_MID == MusicType::MIDI);
  CHECK(MUS_OPUS == MusicType::OPUS);
}

#endif