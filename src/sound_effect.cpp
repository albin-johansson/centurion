#ifndef CENTURION_SOUND_EFFECT_SOURCE
#define CENTURION_SOUND_EFFECT_SOURCE

#include "sound_effect.hpp"

#include "error.hpp"

namespace centurion {

CENTURION_DEF
SoundEffect::SoundEffect(czstring file)
{
  if (!file) {
    throw CenturionException{"Cannot create sound effect from null file!"};
  }
  m_chunk = Mix_LoadWAV(file);
  if (!m_chunk) {
    throw detail::Error::from_mixer("Failed to create SoundEffect instance!");
  }
}

CENTURION_DEF
SoundEffect::SoundEffect(SoundEffect&& other) noexcept
{
  move(std::move(other));
}

CENTURION_DEF
SoundEffect::~SoundEffect()
{
  destroy();
}

CENTURION_DEF
SoundEffect& SoundEffect::operator=(SoundEffect&& other) noexcept
{
  if (this != &other) {
    move(std::move(other));
  }
  return *this;
}

CENTURION_DEF
void SoundEffect::destroy() noexcept
{
  if (m_chunk) {
    stop();
    Mix_FreeChunk(m_chunk);
  }
}

CENTURION_DEF
void SoundEffect::move(SoundEffect&& other) noexcept
{
  destroy();

  m_chunk = other.m_chunk;
  m_channel = other.m_channel;

  other.m_chunk = nullptr;
}

CENTURION_DEF
std::unique_ptr<SoundEffect> SoundEffect::unique(czstring file)
{
  return std::make_unique<SoundEffect>(file);
}

CENTURION_DEF
std::shared_ptr<SoundEffect> SoundEffect::shared(czstring file)
{
  return std::make_shared<SoundEffect>(file);
}

CENTURION_DEF
void SoundEffect::activate(int nLoops) noexcept
{
  if (m_channel != undefinedChannel) {
    Mix_PlayChannel(m_channel, m_chunk, nLoops);
  } else {
    m_channel = Mix_PlayChannel(undefinedChannel, m_chunk, nLoops);
  }
}

CENTURION_DEF
void SoundEffect::play(int nLoops) noexcept
{
  if (nLoops < 0) {
    nLoops = -1;
  }
  activate(nLoops);
}

CENTURION_DEF
void SoundEffect::stop() noexcept
{
  if (playing()) {
    Mix_Pause(m_channel);
    m_channel = undefinedChannel;
  }
}

CENTURION_DEF
void SoundEffect::fade_in(int ms) noexcept
{
  if (ms > 0 && !playing()) {
    if (m_channel != undefinedChannel) {
      Mix_FadeInChannelTimed(m_channel, m_chunk, 0, ms, -1);
    } else {
      m_channel = Mix_FadeInChannelTimed(undefinedChannel, m_chunk, 0, ms, -1);
    }
  }
}

CENTURION_DEF
void SoundEffect::fade_out(int ms) noexcept
{
  if ((ms > 0) && playing()) {
    Mix_FadeOutChannel(m_channel, ms);
  }
}

CENTURION_DEF
void SoundEffect::set_volume(int volume) noexcept
{
  Mix_VolumeChunk(m_chunk, detail::clamp_inclusive({0, max_volume()}, volume));
}

CENTURION_DEF
bool SoundEffect::playing() const noexcept
{
  return (m_channel != undefinedChannel) && Mix_Playing(m_channel);
}

CENTURION_DEF
std::string SoundEffect::to_string() const
{
  const auto address = detail::address_of(this);
  const auto vol = std::to_string(volume());
  return "[SoundEffect@" + address + " | Volume: " + vol + "]";
}

}  // namespace centurion

#endif  // CENTURION_SOUND_EFFECT_SOURCE