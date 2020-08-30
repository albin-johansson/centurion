#include "sound_effect.hpp"

#include <algorithm>

#include "centurion_exception.hpp"
#include "detail/utils.hpp"

namespace centurion {

sound_effect::sound_effect(nn_czstring file) : m_chunk{Mix_LoadWAV(file)}
{
  if (!m_chunk) {
    throw mix_error{"Failed to load sound effect from file"};
  }
}

auto sound_effect::unique(nn_czstring file) -> uptr
{
  return std::make_unique<sound_effect>(file);
}

auto sound_effect::shared(nn_czstring file) -> sptr
{
  return std::make_shared<sound_effect>(file);
}

void sound_effect::activate(int nLoops) noexcept
{
  if (m_channel != undefined_channel()) {
    Mix_PlayChannel(m_channel, m_chunk.get(), nLoops);
  } else {
    m_channel = Mix_PlayChannel(undefined_channel(), m_chunk.get(), nLoops);
  }
}

void sound_effect::play(int nLoops) noexcept
{
  if (nLoops < 0) {
    nLoops = -1;
  }
  activate(nLoops);
}

void sound_effect::stop() noexcept
{
  if (is_playing()) {
    Mix_Pause(m_channel);
    m_channel = undefined_channel();
  }
}

void sound_effect::fade_in(milliseconds<int> ms) noexcept
{
  if (ms.count() > 0 && !is_playing()) {
    if (m_channel != undefined_channel()) {
      Mix_FadeInChannelTimed(m_channel, m_chunk.get(), 0, ms.count(), -1);
    } else {
      m_channel = Mix_FadeInChannelTimed(
          undefined_channel(), m_chunk.get(), 0, ms.count(), -1);
    }
  }
}

void sound_effect::fade_out(milliseconds<int> ms) noexcept  // NOLINT
{
  if ((ms.count() > 0) && is_playing()) {
    Mix_FadeOutChannel(m_channel, ms.count());
  }
}

void sound_effect::set_volume(int volume) noexcept
{
  Mix_VolumeChunk(m_chunk.get(), std::clamp(volume, 0, max_volume()));
}

auto sound_effect::is_playing() const noexcept -> bool
{
  return (m_channel != undefined_channel()) && Mix_Playing(m_channel);
}

auto sound_effect::is_fading() const noexcept -> bool
{
  return is_playing() && Mix_FadingChannel(m_channel);
}

auto to_string(const sound_effect& sound) -> std::string
{
  using namespace std::string_literals;

  const auto ptr = detail::address_of(sound.get());
  const auto vol = std::to_string(sound.volume());

  return "[sound_effect | ptr: "s + ptr + ", volume: "s + vol + "]"s;
}

auto operator<<(std::ostream& stream, const sound_effect& sound)
    -> std::ostream&
{
  stream << to_string(sound);
  return stream;
}

}  // namespace centurion
