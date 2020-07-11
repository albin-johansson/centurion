#ifndef CENTURION_MUSIC_SOURCE
#define CENTURION_MUSIC_SOURCE

#include "music.hpp"

#include "centurion_exception.hpp"
#include "error.hpp"

namespace centurion {

CENTURION_DEF
music::music(czstring file)
{
  m_music = Mix_LoadMUS(file);
  if (!m_music) {
    throw detail::Error::from_mixer("Failed to create Music instance!");
  }
}

CENTURION_DEF
music::music(music&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
music::~music() noexcept
{
  destroy();
}

CENTURION_DEF
auto music::operator=(music&& other) noexcept -> music&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void music::destroy() noexcept
{
  if (m_music) {
    Mix_FreeMusic(m_music);
  }
}

CENTURION_DEF
void music::move(music&& other) noexcept
{
  destroy();
  m_music = other.m_music;
  other.m_music = nullptr;
}

CENTURION_DEF
auto music::unique(czstring file) -> std::unique_ptr<music>
{
  return std::make_unique<music>(file);
}

CENTURION_DEF
auto music::shared(czstring file) -> std::shared_ptr<music>
{
  return std::make_shared<music>(file);
}

CENTURION_DEF
void music::play(int nLoops) noexcept
{
  if (nLoops < -1) {
    nLoops = -1;
  }
  Mix_PlayMusic(m_music, nLoops);
}

CENTURION_DEF
void music::resume() noexcept
{
  Mix_ResumeMusic();
}

CENTURION_DEF
void music::pause() noexcept
{
  Mix_PauseMusic();
}

CENTURION_DEF
void music::halt() noexcept
{
  Mix_HaltMusic();
}

CENTURION_DEF
void music::fade_in(milliseconds<int> ms, int nLoops) noexcept
{
  if (ms.count() < 0) {
    ms = milliseconds<int>{0};
  }

  if (nLoops < -1) {
    nLoops = -1;
  }

  Mix_FadeInMusic(m_music, nLoops, ms.count());
}

CENTURION_DEF
void music::fade_out(milliseconds<int> ms) noexcept
{
  if (is_fading()) {
    return;
  }
  if (ms.count() < 0) {
    ms = milliseconds<int>{0};
  }
  Mix_FadeOutMusic(ms.count());
}

CENTURION_DEF
void music::set_volume(int volume) noexcept
{
  Mix_VolumeMusic(detail::clamp_inclusive({0, MIX_MAX_VOLUME}, volume));
}

CENTURION_DEF
auto music::is_playing() noexcept -> bool
{
  return Mix_PlayingMusic();
}

CENTURION_DEF
auto music::is_paused() noexcept -> bool
{
  return Mix_PausedMusic();
}

CENTURION_DEF
auto music::is_fading() noexcept -> bool
{
  const auto status = get_fade_status();
  return status == fade_status::in || status == fade_status::out;
}

CENTURION_DEF
auto music::volume() noexcept -> int
{
  return Mix_VolumeMusic(-1);
}

CENTURION_DEF
auto music::get_fade_status() noexcept -> fade_status
{
  return static_cast<fade_status>(Mix_FadingMusic());
}

CENTURION_DEF
auto music::type() const noexcept -> music_type
{
  return static_cast<music_type>(Mix_GetMusicType(m_music));
}

CENTURION_DEF
auto music::to_string() const -> std::string
{
  return "[Music@" + detail::address_of(this) + "]";
}

}  // namespace centurion

#endif  // CENTURION_MUSIC_SOURCE