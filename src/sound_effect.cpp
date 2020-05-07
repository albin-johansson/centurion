#ifndef CENTURION_SOUND_EFFECT_SOURCE
#define CENTURION_SOUND_EFFECT_SOURCE

#include "sound_effect.h"

#include "centurion_exception.h"
#include "centurion_utils.h"
#include "error.h"

namespace centurion {
namespace audio {

// TODO check Mix documentation if there are any redundancies

CENTURION_DEF
SoundEffect::SoundEffect(const std::string& file)
{
  m_chunk = Mix_LoadWAV(file.c_str());
  if (!m_chunk) {
    throw CenturionException{Error::descriptionf()};
  }
}

CENTURION_DEF
SoundEffect::SoundEffect(SoundEffect&& other) noexcept
{
  Mix_FreeChunk(m_chunk);

  m_chunk = other.m_chunk;
  other.m_chunk = nullptr;

  m_channel = other.m_channel;
}

CENTURION_DEF
SoundEffect::~SoundEffect()
{
  if (m_chunk) {
    stop();
    Mix_FreeChunk(m_chunk);
  }
}

CENTURION_DEF
SoundEffect& SoundEffect::operator=(SoundEffect&& other) noexcept
{
  Mix_FreeChunk(m_chunk);

  m_chunk = other.m_chunk;
  other.m_chunk = nullptr;

  m_channel = other.m_channel;

  return *this;
}

CENTURION_DEF
std::unique_ptr<SoundEffect> SoundEffect::unique(const std::string& file)
{
  return centurion::make_unique<SoundEffect>(file);
}

CENTURION_DEF
std::shared_ptr<SoundEffect> SoundEffect::shared(const std::string& file)
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
  if (volume < 0) {
    volume = 0;
  }
  if (volume > max_volume()) {
    volume = max_volume();
  }
  Mix_VolumeChunk(m_chunk, volume);
}

CENTURION_DEF
int SoundEffect::volume() const noexcept
{
  return m_chunk->volume;
}

CENTURION_DEF
bool SoundEffect::playing() const noexcept
{
  return (m_channel != undefinedChannel) && Mix_Playing(m_channel);
}

CENTURION_DEF
std::string SoundEffect::to_string() const
{
  const auto address = address_of(this);
  const auto vol = std::to_string(volume());
  return "[SoundEffect@" + address + " | Volume: " + vol + "]";
}

CENTURION_DEF
SoundEffect::operator Mix_Chunk*() const noexcept
{
  return m_chunk;
}

}  // namespace audio
}  // namespace centurion

#endif  // CENTURION_SOUND_EFFECT_SOURCE