#ifndef CENTURION_SOUND_EFFECT_SOURCE
#define CENTURION_SOUND_EFFECT_SOURCE

#ifndef CENTURION_NOAUDIO

#include "sound_effect.h"

#include "centurion_exception.h"
#include "centurion_utils.h"
#include "error.h"

namespace centurion {
namespace audio {

// TODO check Mix documentation if there are any redundancies

CENTURION_DEF SoundEffect::SoundEffect(const std::string& file)
{
  chunk = Mix_LoadWAV(file.c_str());
  if (!chunk) {
    throw CenturionException{Error::descriptionf()};
  }
}

CENTURION_DEF SoundEffect::SoundEffect(SoundEffect&& other) noexcept
{
  Mix_FreeChunk(chunk);

  chunk = other.chunk;
  other.chunk = nullptr;

  channel = other.channel;
}

CENTURION_DEF SoundEffect::~SoundEffect()
{
  if (chunk) {
    stop();
    Mix_FreeChunk(chunk);
  }
}

CENTURION_DEF SoundEffect& SoundEffect::operator=(SoundEffect&& other) noexcept
{
  Mix_FreeChunk(chunk);

  chunk = other.chunk;
  other.chunk = nullptr;

  channel = other.channel;

  return *this;
}

CENTURION_DEF std::unique_ptr<SoundEffect> SoundEffect::unique(
    const std::string& file)
{
#ifdef CENTURION_HAS_MAKE_UNIQUE
  return std::make_unique<SoundEffect>(file);
#else
  return centurion::make_unique<SoundEffect>(file);
#endif
}

CENTURION_DEF std::shared_ptr<SoundEffect> SoundEffect::shared(
    const std::string& file)
{
  return std::make_shared<SoundEffect>(file);
}

CENTURION_DEF void SoundEffect::activate(int nLoops) noexcept
{
  if (channel != undefinedChannel) {
    Mix_PlayChannel(channel, chunk, nLoops);
  } else {
    channel = Mix_PlayChannel(undefinedChannel, chunk, nLoops);
  }
}

CENTURION_DEF void SoundEffect::play(int nLoops) noexcept
{
  if (nLoops < 0) {
    nLoops = -1;
  }
  activate(nLoops);
}

CENTURION_DEF void SoundEffect::stop() noexcept
{
  if (is_playing()) {
    Mix_Pause(channel);
    channel = undefinedChannel;
  }
}

CENTURION_DEF void SoundEffect::fade_in(int ms) noexcept
{
  if (ms > 0 && !is_playing()) {
    if (channel != undefinedChannel) {
      Mix_FadeInChannelTimed(channel, chunk, 0, ms, -1);
    } else {
      channel = Mix_FadeInChannelTimed(undefinedChannel, chunk, 0, ms, -1);
    }
  }
}

CENTURION_DEF void SoundEffect::fade_out(int ms) noexcept
{
  if ((ms > 0) && is_playing()) {
    Mix_FadeOutChannel(channel, ms);
  }
}

CENTURION_DEF void SoundEffect::set_volume(int volume) noexcept
{
  if (volume < 0) {
    volume = 0;
  }
  if (volume > get_max_volume()) {
    volume = get_max_volume();
  }
  Mix_VolumeChunk(chunk, volume);
}

CENTURION_DEF int SoundEffect::get_volume() const noexcept
{
  return chunk->volume;
}

CENTURION_DEF bool SoundEffect::is_playing() const noexcept
{
  return (channel != undefinedChannel) && Mix_Playing(channel);
}

CENTURION_DEF std::string SoundEffect::to_string() const
{
  const auto address = address_of(this);
  const auto volume = std::to_string(get_volume());
  return "[SoundEffect@" + address + " | Volume: " + volume + "]";
}

CENTURION_DEF SoundEffect::operator Mix_Chunk*() const noexcept
{
  return chunk;
}

}  // namespace audio
}  // namespace centurion

#endif  // CENTURION_NOAUDIO
#endif  // CENTURION_SOUND_EFFECT_SOURCE