#include "music.hpp"

#include <algorithm>
#include <type_traits>

#include "detail/to_string.hpp"
#include "exception.hpp"

namespace cen {

static_assert(std::is_final_v<music>);
static_assert(!std::is_nothrow_copy_constructible_v<music>);
static_assert(!std::is_nothrow_copy_assignable_v<music>);
static_assert(std::is_nothrow_move_constructible_v<music>);
static_assert(std::is_nothrow_move_assignable_v<music>);

music::music(nn_czstring file) : m_music{Mix_LoadMUS(file)}
{
  if (!m_music) {
    throw mix_error{"Failed to load music from file"};
  }
}

void music::play(int nLoops) noexcept
{
  if (nLoops < -1) {
    nLoops = -1;
  }
  Mix_PlayMusic(m_music.get(), nLoops);
}

void music::resume() noexcept
{
  Mix_ResumeMusic();
}

void music::pause() noexcept
{
  Mix_PauseMusic();
}

void music::halt() noexcept
{
  Mix_HaltMusic();
}

void music::fade_in(milliseconds<int> ms, int nLoops) noexcept
{
  if (ms.count() < 0) {
    ms = milliseconds<int>::zero();
  }

  if (nLoops < -1) {
    nLoops = -1;
  }

  Mix_FadeInMusic(m_music.get(), nLoops, ms.count());
}

void music::fade_out(milliseconds<int> ms) noexcept
{
  if (is_fading()) {
    return;
  }
  if (ms.count() < 0) {
    ms = milliseconds<int>::zero();
  }
  Mix_FadeOutMusic(ms.count());
}

void music::set_volume(int volume) noexcept
{
  Mix_VolumeMusic(std::clamp(volume, 0, MIX_MAX_VOLUME));
}

auto music::is_playing() noexcept -> bool
{
  return Mix_PlayingMusic();
}

auto music::is_paused() noexcept -> bool
{
  return Mix_PausedMusic();
}

auto music::is_fading() noexcept -> bool
{
  const auto status = get_fade_status();
  return status == fade_status::in || status == fade_status::out;
}

auto music::volume() noexcept -> int
{
  return Mix_VolumeMusic(-1);
}

auto music::get_fade_status() noexcept -> fade_status
{
  return static_cast<fade_status>(Mix_FadingMusic());
}

auto music::type() const noexcept -> music_type
{
  return static_cast<music_type>(Mix_GetMusicType(m_music.get()));
}

auto to_string(const music& music) -> std::string
{
  using namespace std::string_literals;
  using detail::to_string;
  return "[music | data: "s + detail::address_of(music.get()) + ", volume: "s +
         to_string(music.volume()).value() + "]"s;
}

auto operator<<(std::ostream& stream, const music& music) -> std::ostream&
{
  stream << to_string(music);
  return stream;
}

}  // namespace cen
