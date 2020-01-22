#include "music.h"
#include <type_traits>
#include "centurion_exception.h"

namespace centurion {

static_assert(std::is_final_v<Music>);

static_assert(!std::is_nothrow_copy_constructible_v<Music>);
static_assert(!std::is_nothrow_copy_assignable_v<Music>);

static_assert(std::is_nothrow_move_constructible_v<Music>);
static_assert(std::is_nothrow_move_assignable_v<Music>);

static_assert(std::is_convertible_v<Music, Mix_Music*>);

const int Music::maxVolume = MIX_MAX_VOLUME;
const int Music::loopForever = -1;

Music::Music(const std::string& file) {
  music = Mix_LoadMUS(file.c_str());
  if (!music) {
    throw CenturionException{"Failed to create music! Error: " + std::string{Mix_GetError()}};
  }
}

Music::Music(Music&& other) noexcept
    : music{other.music} {
  other.music = nullptr;
}

Music::~Music() noexcept {
  if (music) {
    Mix_FreeMusic(music);
  }
}

Music& Music::operator=(Music&& other) noexcept {
  music = other.music;
  other.music = nullptr;
  return *this;
}

std::unique_ptr<Music> Music::unique(const std::string& file) {
  return std::make_unique<Music>(file);
}

std::shared_ptr<Music> Music::shared(const std::string& file) {
  return std::make_shared<Music>(file);
}

void Music::play(int nLoops) noexcept {
  if (nLoops < -1) { nLoops = -1; }
  Mix_PlayMusic(music, nLoops);
}

void Music::resume() noexcept {
  Mix_ResumeMusic();
}

void Music::pause() noexcept {
  Mix_PauseMusic();
}

void Music::halt() noexcept {
  Mix_HaltMusic();
}

void Music::fade_in(int ms, int nLoops) noexcept {
  if (ms < 0) { ms = 0; }
  if (nLoops < -1) { nLoops = -1; }
  Mix_FadeInMusic(music, nLoops, ms);
}

void Music::fade_out(int ms) {
  if (is_fading()) { return; }
  if (ms < 0) { ms = 0; }
  Mix_FadeOutMusic(ms);
}

void Music::set_volume(int volume) noexcept {
  if (volume > maxVolume) {
    volume = maxVolume;
  } else if (volume < 0) {
    volume = 0;
  }
  Mix_VolumeMusic(volume);
}

bool Music::is_playing() noexcept {
  return Mix_PlayingMusic();
}

bool Music::is_paused() noexcept {
  return Mix_PausedMusic();
}

bool Music::is_fading() noexcept {
  const auto status = get_fade_status();
  return status == FadeStatus::In || status == FadeStatus::Out;
}

int Music::get_volume() noexcept {
  return Mix_VolumeMusic(-1);
}

FadeStatus Music::get_fade_status() noexcept {
  return static_cast<FadeStatus>(Mix_FadingMusic());
}

MusicType Music::get_music_type() const noexcept {
  return static_cast<MusicType>(Mix_GetMusicType(music));
}

Music::operator Mix_Music*() const noexcept {
  return music;
}

bool operator==(FadeStatus lhs, Mix_Fading rhs) noexcept {
  return static_cast<Mix_Fading>(lhs) == rhs;
}

bool operator==(Mix_Fading lhs, FadeStatus rhs) noexcept {
  return lhs == static_cast<Mix_Fading>(rhs);
}

bool operator==(MusicType lhs, Mix_MusicType rhs) noexcept {
  return static_cast<Mix_MusicType>(lhs) == rhs;
}

bool operator==(Mix_MusicType lhs, MusicType rhs) noexcept {
  return lhs == static_cast<Mix_MusicType>(rhs);
}

}
