#ifndef CENTURION_NOAUDIO

#include "sound_effect.h"
#include <type_traits>
#include "centurion_exception.h"

namespace centurion {

static_assert(std::has_virtual_destructor_v<SoundEffect>);
static_assert(!std::is_final_v<SoundEffect>);

static_assert(std::is_nothrow_move_constructible_v<SoundEffect>);
static_assert(std::is_nothrow_move_assignable_v<SoundEffect>);

static_assert(!std::is_copy_constructible_v<SoundEffect>);
static_assert(!std::is_copy_assignable_v<SoundEffect>);

static_assert(std::is_convertible_v<SoundEffect, Mix_Chunk*>);

SoundEffect::SoundEffect(const std::string& file) {
  chunk = Mix_LoadWAV(file.c_str());
  if (!chunk) {
    throw CenturionException(SDL_GetError());
  }
  set_volume(MIX_MAX_VOLUME / 2);
}

SoundEffect::SoundEffect(SoundEffect&& other) noexcept
    : chunk{other.chunk},
      channel{other.channel} {
  other.chunk = nullptr;
}

SoundEffect::~SoundEffect() {
  if (chunk) {
    stop();
    Mix_FreeChunk(chunk);
  }
}

SoundEffect& SoundEffect::operator=(SoundEffect&& other) noexcept {
  chunk = other.chunk;
  channel = other.channel;

  other.chunk = nullptr;

  return *this;
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

SoundEffect::operator Mix_Chunk*() const noexcept {
  return chunk;
}

}

#endif