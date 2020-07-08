#ifndef CENTURION_MUSIC_SOURCE
#define CENTURION_MUSIC_SOURCE

#include "music.hpp"

#include "centurion_exception.hpp"
#include "error.hpp"

namespace centurion {

CENTURION_DEF
Music::Music(czstring file)
{
  m_music = Mix_LoadMUS(file);
  if (!m_music) {
    throw detail::Error::from_mixer("Failed to create Music instance!");
  }
}

CENTURION_DEF
Music::Music(Music&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
Music::~Music() noexcept
{
  destroy();
}

CENTURION_DEF
Music& Music::operator=(Music&& other) noexcept
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void Music::destroy() noexcept
{
  if (m_music) {
    Mix_FreeMusic(m_music);
  }
}

CENTURION_DEF
void Music::move(Music&& other) noexcept
{
  destroy();
  m_music = other.m_music;
  other.m_music = nullptr;
}

CENTURION_DEF
UniquePtr<Music> Music::unique(czstring file)
{
  return std::make_unique<Music>(file);
}

CENTURION_DEF
SharedPtr<Music> Music::shared(czstring file)
{
  return std::make_shared<Music>(file);
}

CENTURION_DEF
void Music::play(int nLoops) noexcept
{
  if (nLoops < -1) {
    nLoops = -1;
  }
  Mix_PlayMusic(m_music, nLoops);
}

CENTURION_DEF
void Music::resume() noexcept
{
  Mix_ResumeMusic();
}

CENTURION_DEF
void Music::pause() noexcept
{
  Mix_PauseMusic();
}

CENTURION_DEF
void Music::halt() noexcept
{
  Mix_HaltMusic();
}

CENTURION_DEF
void Music::fade_in(int ms, int nLoops) noexcept
{
  if (ms < 0) {
    ms = 0;
  }
  if (nLoops < -1) {
    nLoops = -1;
  }
  Mix_FadeInMusic(m_music, nLoops, ms);
}

CENTURION_DEF
void Music::fade_out(int ms)
{
  if (fading()) {
    return;
  }
  if (ms < 0) {
    ms = 0;
  }
  Mix_FadeOutMusic(ms);
}

CENTURION_DEF
void Music::set_volume(int volume) noexcept
{
  Mix_VolumeMusic(detail::clamp_inclusive({0, MIX_MAX_VOLUME}, volume));
}

CENTURION_DEF
bool Music::playing() noexcept
{
  return Mix_PlayingMusic();
}

CENTURION_DEF
bool Music::paused() noexcept
{
  return Mix_PausedMusic();
}

CENTURION_DEF
bool Music::fading() noexcept
{
  const auto status = fade_status();
  return status == FadeStatus::In || status == FadeStatus::Out;
}

CENTURION_DEF
int Music::volume() noexcept
{
  return Mix_VolumeMusic(-1);
}

CENTURION_DEF
FadeStatus Music::fade_status() noexcept
{
  return static_cast<FadeStatus>(Mix_FadingMusic());
}

CENTURION_DEF
MusicType Music::music_type() const noexcept
{
  return static_cast<MusicType>(Mix_GetMusicType(m_music));
}

CENTURION_DEF
std::string Music::to_string() const
{
  return "[Music@" + detail::address_of(this) + "]";
}

CENTURION_DEF
bool operator==(FadeStatus lhs, Mix_Fading rhs) noexcept
{
  return static_cast<Mix_Fading>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(Mix_Fading lhs, FadeStatus rhs) noexcept
{
  return lhs == static_cast<Mix_Fading>(rhs);
}

CENTURION_DEF
bool operator==(MusicType lhs, Mix_MusicType rhs) noexcept
{
  return static_cast<Mix_MusicType>(lhs) == rhs;
}

CENTURION_DEF
bool operator==(Mix_MusicType lhs, MusicType rhs) noexcept
{
  return lhs == static_cast<Mix_MusicType>(rhs);
}

}  // namespace centurion

#endif  // CENTURION_MUSIC_SOURCE