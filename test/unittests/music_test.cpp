#include "catch.hpp"
#include "music.h"
#include "centurion_exception.h"
#include "timer.h"

using namespace centurion;

static constexpr auto path = "resources/hiddenPond.mp3";

TEST_CASE("Music::Music(string)", "[Music]") {
  CHECK_THROWS_AS(Music{""}, CenturionException);
  CHECK_NOTHROW(Music{path});
}

TEST_CASE("Music smart pointer factory methods", "[Music]") {
  CHECK_THROWS_AS(Music::unique(""), CenturionException);
  CHECK_THROWS_AS(Music::unique(""), CenturionException);
  CHECK_NOTHROW(Music::unique(path));
  CHECK_NOTHROW(Music::shared(path));
}

TEST_CASE("Music::play", "[Music]") {
  Music music{path};
  music.play();
  CHECK(Music::is_playing());
  CHECK(!Music::is_fading());
  CHECK(!Music::is_paused());
  CHECK(Music::get_fade_status() == FadeStatus::None);
}

TEST_CASE("Music::resume", "[Music]") {
  CHECK_NOTHROW(Music::resume());

  Music music{path};

  music.play();
  Music::pause();
  CHECK(Music::is_paused());

  Music::resume();
  CHECK(Music::is_playing());
}

TEST_CASE("Music::pause", "[Music]") {
  CHECK_NOTHROW(Music::pause());

  Music music{path};

  music.play();
  Music::pause();
  CHECK(Music::is_paused());

  music.fade_in(100);
  Music::pause();
  CHECK(Music::is_paused());
}

TEST_CASE("Music::halt", "[Music]") {
  CHECK_NOTHROW(Music::halt());

  Music music{path};

  music.play();
  Music::halt();

  CHECK(!Music::is_playing());
  CHECK(!Music::is_fading());

  music.fade_in(100);
  Music::halt();

  CHECK(!Music::is_playing());
  CHECK(!Music::is_fading());
}

TEST_CASE("Music::fade_in", "[Music]") {
  CHECK(!Music::is_fading());

  Music music{path};
  CHECK_NOTHROW(music.fade_in(-1));

  Music::halt();

  music.fade_in(100);
  CHECK(Music::is_fading());
}

TEST_CASE("Music::fade_out", "[Music]") {
  CHECK(!Music::is_fading());
  CHECK_NOTHROW(Music::fade_out(100));
  CHECK_NOTHROW(Music::fade_out(-1));

  Music music{path};
  music.fade_in(100);

  CHECK(Music::is_fading());
}

TEST_CASE("Music::set_volume", "[Music]") {
  const auto originalVolume = Music::get_volume();

  SECTION("Valid volume") {
    const auto volume = 102;
    Music::set_volume(volume);
    CHECK(volume == Music::get_volume());
  }

  SECTION("Negative volume") {
    const auto volume = -1;
    Music::set_volume(volume);
    CHECK(Music::get_volume() == 0);
  }

  SECTION("Volume overflow") {
    const auto volume = Music::maxVolume + 1;
    Music::set_volume(volume);
    CHECK(Music::maxVolume == Music::get_volume());
  }

  Music::set_volume(originalVolume);
}

TEST_CASE("Music::is_playing", "[Music]") {
  CHECK(!Music::is_playing());

  Music music{path};

  music.play();
  CHECK(Music::is_playing());

  Music::halt();

  music.fade_in(100);
  CHECK(Music::is_playing());
}

TEST_CASE("Music::is_paused", "[Music]") {
  CHECK(!Music::is_paused());

  Music music{path};
  music.play();

  Music::pause();
  CHECK(Music::is_paused());
}

TEST_CASE("Music::is_fading", "[Music]") {
  CHECK(!Music::is_fading());

  Music music{path};

  music.play();
  CHECK(!Music::is_fading());
  Music::halt();

  music.fade_in(200);
  CHECK(Music::is_fading());

  Music::fade_out(50); // This should have no effect, since the music is fading in
  CHECK(Music::get_fade_status() == FadeStatus::In);
}

TEST_CASE("Music::get_volume", "[Music]") {
  CHECK(Music::get_volume() == Music::maxVolume);

  const auto volume = 47;
  Music::set_volume(volume);

  CHECK(Music::get_volume() == volume);
}

TEST_CASE("Music::get_fade_status", "[Music]") {
  CHECK(Music::get_fade_status() == FadeStatus::None);
  CHECK(!Music::is_fading());

  Music music{path};

  music.fade_in(100);
  CHECK(Music::get_fade_status() == FadeStatus::In);
  CHECK(Music::is_fading());
  CHECK(Music::is_playing());
  CHECK(!Music::is_paused());

  Music::halt();

  music.play();
  Music::fade_out(100);
  CHECK(Music::get_fade_status() == FadeStatus::Out);
  CHECK(Music::is_fading());
  CHECK(Music::is_playing());
  CHECK(!Music::is_paused());

  Music::halt();
  CHECK(Music::get_fade_status() == FadeStatus::None);
}

TEST_CASE("Music::get_music_type", "[Music]") {
  Music music{path};
  CHECK(music.get_music_type() == MusicType::MP3);
}

TEST_CASE("Music to Mix_Music*", "[Music]") {
  Music music{path};
  Mix_Music* sdlMusic = music;
  CHECK(sdlMusic);
}

TEST_CASE("FadeStatus enum values", "[Music]") {
  CHECK(FadeStatus::None == MIX_NO_FADING);
  CHECK(FadeStatus::In == MIX_FADING_IN);
  CHECK(FadeStatus::Out == MIX_FADING_OUT);

  CHECK(MIX_NO_FADING == FadeStatus::None);
  CHECK(MIX_FADING_IN == FadeStatus::In);
  CHECK(MIX_FADING_OUT == FadeStatus::Out);
}

TEST_CASE("MusicType enum values", "[Music]") {
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