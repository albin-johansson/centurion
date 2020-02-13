#ifndef CENTURION_MUSIC_SOURCE
#define CENTURION_MUSIC_SOURCE

#ifndef CENTURION_NOAUDIO

#include "music.h"

#include "centurion_exception.h"
#include "centurion_utils.h"
#include "error.h"

namespace centurion {

// FIXME there is some duplication between SoundEffect and Music
CENTURION_DEF const int Music::maxVolume = MIX_MAX_VOLUME;
CENTURION_DEF const int Music::loopForever = -1;

CENTURION_DEF Music::Music(const std::string& file) {
  music = Mix_LoadMUS(file.c_str());
  if (!music) {
    throw CenturionException{"Failed to create music! " + Error::msg()};
  }
}

CENTURION_DEF Music::Music(Music&& other) noexcept {
  Mix_FreeMusic(music);

  music = other.music;
  other.music = nullptr;
}

CENTURION_DEF Music::~Music() noexcept {
  if (music) {
    Mix_FreeMusic(music);
  }
}

CENTURION_DEF Music& Music::operator=(Music&& other) noexcept {
  Mix_FreeMusic(music);

  music = other.music;
  other.music = nullptr;

  return *this;
}

CENTURION_DEF std::unique_ptr<Music> Music::unique(const std::string& file) {
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<Music>(file);
#else
  return centurion::make_unique<Music>(file);
#endif
}

CENTURION_DEF std::shared_ptr<Music> Music::shared(const std::string& file) {
  return std::make_shared<Music>(file);
}

CENTURION_DEF void Music::play(int nLoops) noexcept {
  if (nLoops < -1) {
    nLoops = -1;
  }
  Mix_PlayMusic(music, nLoops);
}

CENTURION_DEF void Music::resume() noexcept { Mix_ResumeMusic(); }

CENTURION_DEF void Music::pause() noexcept { Mix_PauseMusic(); }

CENTURION_DEF void Music::halt() noexcept { Mix_HaltMusic(); }

CENTURION_DEF void Music::fade_in(int ms, int nLoops) noexcept {
  if (ms < 0) {
    ms = 0;
  }
  if (nLoops < -1) {
    nLoops = -1;
  }
  Mix_FadeInMusic(music, nLoops, ms);
}

CENTURION_DEF void Music::fade_out(int ms) {
  if (is_fading()) {
    return;
  }
  if (ms < 0) {
    ms = 0;
  }
  Mix_FadeOutMusic(ms);
}

CENTURION_DEF void Music::set_volume(int volume) noexcept {
  if (volume > maxVolume) {
    volume = maxVolume;
  } else if (volume < 0) {
    volume = 0;
  }
  Mix_VolumeMusic(volume);
}

CENTURION_DEF bool Music::is_playing() noexcept { return Mix_PlayingMusic(); }

CENTURION_DEF bool Music::is_paused() noexcept { return Mix_PausedMusic(); }

CENTURION_DEF bool Music::is_fading() noexcept {
  const auto status = get_fade_status();
  return status == FadeStatus::In || status == FadeStatus::Out;
}

CENTURION_DEF int Music::get_volume() noexcept { return Mix_VolumeMusic(-1); }

CENTURION_DEF FadeStatus Music::get_fade_status() noexcept {
  return static_cast<FadeStatus>(Mix_FadingMusic());
}

CENTURION_DEF MusicType Music::get_music_type() const noexcept {
  return static_cast<MusicType>(Mix_GetMusicType(music));
}

CENTURION_DEF std::string Music::to_string() const {
  return "[Music@" + CenturionUtils::address(this) + "]";
}

CENTURION_DEF Music::operator Mix_Music*() const noexcept { return music; }

CENTURION_DEF bool operator==(FadeStatus lhs, Mix_Fading rhs) noexcept {
  return static_cast<Mix_Fading>(lhs) == rhs;
}

CENTURION_DEF bool operator==(Mix_Fading lhs, FadeStatus rhs) noexcept {
  return lhs == static_cast<Mix_Fading>(rhs);
}

CENTURION_DEF bool operator==(MusicType lhs, Mix_MusicType rhs) noexcept {
  return static_cast<Mix_MusicType>(lhs) == rhs;
}

CENTURION_DEF bool operator==(Mix_MusicType lhs, MusicType rhs) noexcept {
  return lhs == static_cast<Mix_MusicType>(rhs);
}

}  // namespace centurion

#endif  // CENTURION_NOAUDIO
#endif  // CENTURION_MUSIC_SOURCE