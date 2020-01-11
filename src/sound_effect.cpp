#include "sound_effect.h"
#include "centurion_exception.h"

namespace centurion {

SoundEffect::SoundEffect(const std::string& file) {
  chunk = Mix_LoadWAV(file.c_str());
  if (!chunk) {
    throw CenturionException(SDL_GetError());
  }
  set_volume(MIX_MAX_VOLUME / 2);
}

SoundEffect::~SoundEffect() {
  stop();
  Mix_FreeChunk(chunk);
}

void SoundEffect::activate(int nLoops) noexcept {
  if (channel != undefinedChannel) {
    Mix_PlayChannel(channel, chunk, nLoops);
  } else {
    channel = Mix_PlayChannel(undefinedChannel, chunk, nLoops);
  }
}

void SoundEffect::play() noexcept {
  activate(0);
}

void SoundEffect::loop(int nLoops) noexcept {
  if (nLoops < 0) { nLoops = -1; }
  activate(nLoops);
}

void SoundEffect::stop() noexcept {
  if (is_playing()) {
    Mix_Pause(channel);
    channel = undefinedChannel;
  }
}

void SoundEffect::fade_in(uint32_t ms) noexcept {
  if (ms > 0 && !is_playing()) {
    if (channel != undefinedChannel) {
      Mix_FadeInChannelTimed(channel, chunk, 0, ms, -1);
    } else {
      channel = Mix_FadeInChannelTimed(undefinedChannel, chunk, 0, ms, -1);
    }
  }
}

void SoundEffect::fade_out(uint32_t ms) noexcept {
  if ((ms > 0) && is_playing()) {
    Mix_FadeOutChannel(channel, ms);
  }
}

void SoundEffect::set_volume(int volume) noexcept {
  if (volume < 0) { volume = 0; }
  if (volume > MIX_MAX_VOLUME) { volume = MIX_MAX_VOLUME; }
  Mix_VolumeChunk(chunk, volume);
}

int SoundEffect::get_volume() const noexcept {
  return chunk->volume;
}

bool SoundEffect::is_playing() const noexcept {
  return (channel != undefinedChannel) && Mix_Playing(channel);
}

}
