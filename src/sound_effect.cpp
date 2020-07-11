#ifndef CENTURION_SOUND_EFFECT_SOURCE
#define CENTURION_SOUND_EFFECT_SOURCE

#include "sound_effect.hpp"

#include "error.hpp"

namespace centurion {

CENTURION_DEF
sound_effect::sound_effect(czstring file)
{
  if (!file) {
    throw centurion_exception{"Cannot create sound effect from null file!"};
  }
  m_chunk = Mix_LoadWAV(file);
  if (!m_chunk) {
    throw detail::Error::from_mixer("Failed to create SoundEffect instance!");
  }
}

CENTURION_DEF
sound_effect::sound_effect(sound_effect&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
sound_effect::~sound_effect()
{
  destroy();
}

CENTURION_DEF
auto sound_effect::operator=(sound_effect&& other) noexcept -> sound_effect&
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void sound_effect::destroy() noexcept
{
  if (m_chunk) {
    stop();
    Mix_FreeChunk(m_chunk);
  }
}

CENTURION_DEF
void sound_effect::move(sound_effect&& other) noexcept
{
  destroy();

  m_chunk = other.m_chunk;
  m_channel = other.m_channel;

  other.m_chunk = nullptr;
}

CENTURION_DEF
auto sound_effect::unique(czstring file) -> std::unique_ptr<sound_effect>
{
  return std::make_unique<sound_effect>(file);
}

CENTURION_DEF
auto sound_effect::shared(czstring file) -> std::shared_ptr<sound_effect>
{
  return std::make_shared<sound_effect>(file);
}

CENTURION_DEF
void sound_effect::activate(int nLoops) noexcept
{
  if (m_channel != undefinedChannel) {
    Mix_PlayChannel(m_channel, m_chunk, nLoops);
  } else {
    m_channel = Mix_PlayChannel(undefinedChannel, m_chunk, nLoops);
  }
}

CENTURION_DEF
void sound_effect::play(int nLoops) noexcept
{
  if (nLoops < 0) {
    nLoops = -1;
  }
  activate(nLoops);
}

CENTURION_DEF
void sound_effect::stop() noexcept
{
  if (is_playing()) {
    Mix_Pause(m_channel);
    m_channel = undefinedChannel;
  }
}

CENTURION_DEF
void sound_effect::fade_in(milliseconds<int> ms) noexcept
{
  if (ms.count() > 0 && !is_playing()) {
    if (m_channel != undefinedChannel) {
      Mix_FadeInChannelTimed(m_channel, m_chunk, 0, ms.count(), -1);
    } else {
      m_channel =
          Mix_FadeInChannelTimed(undefinedChannel, m_chunk, 0, ms.count(), -1);
    }
  }
}

CENTURION_DEF
void sound_effect::fade_out(milliseconds<int> ms) noexcept
{
  if ((ms.count() > 0) && is_playing()) {
    Mix_FadeOutChannel(m_channel, ms.count());
  }
}

CENTURION_DEF
void sound_effect::set_volume(int volume) noexcept
{
  Mix_VolumeChunk(m_chunk, detail::clamp_inclusive({0, max_volume()}, volume));
}

CENTURION_DEF
auto sound_effect::is_playing() const noexcept -> bool
{
  return (m_channel != undefinedChannel) && Mix_Playing(m_channel);
}

CENTURION_DEF
auto sound_effect::is_fading() const noexcept -> bool
{
  return is_playing() && Mix_FadingChannel(m_channel);
}

CENTURION_DEF
auto sound_effect::to_string() const -> std::string
{
  const auto address = detail::address_of(this);
  const auto vol = std::to_string(volume());
  return "[SoundEffect@" + address + " | Volume: " + vol + "]";
}

}  // namespace centurion

#endif  // CENTURION_SOUND_EFFECT_SOURCE