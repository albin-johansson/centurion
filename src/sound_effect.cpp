#ifndef CENTURION_NOAUDIO

#include "sound_effect.h"
#include <type_traits>
#include "centurion_exception.h"
#include "centurion_utils.h"
#include "error.h"

namespace centurion {

// TODO check Mix documentation if there are any redundancies

static_assert(std::is_final_v<SoundEffect>);

static_assert(std::is_nothrow_move_constructible_v<SoundEffect>);
static_assert(std::is_nothrow_move_assignable_v<SoundEffect>);

static_assert(!std::is_copy_constructible_v<SoundEffect>);
static_assert(!std::is_copy_assignable_v<SoundEffect>);

static_assert(std::is_convertible_v<SoundEffect, Mix_Chunk*>);

const int SoundEffect::loopForever = -10;
const int SoundEffect::maxVolume = get_max_volume();

SoundEffect::SoundEffect(const std::string& file) {
  chunk = Mix_LoadWAV(file.c_str());
  if (!chunk) {
    throw CenturionException(Error::descriptionf());
  }
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

std::unique_ptr<SoundEffect> SoundEffect::unique(const std::string& file) {
  return std::make_unique<SoundEffect>(file);
}

std::shared_ptr<SoundEffect> SoundEffect::shared(const std::string& file) {
  return std::make_shared<SoundEffect>(file);
}

void SoundEffect::activate(int nLoops) noexcept {
  if (channel != undefinedChannel) {
    Mix_PlayChannel(channel, chunk, nLoops);
  } else {
    channel = Mix_PlayChannel(undefinedChannel, chunk, nLoops);
  }
}

void SoundEffect::play(int nLoops) noexcept {
  if (nLoops < 0) { nLoops = loopForever; }
  activate(nLoops);
}

void SoundEffect::stop() noexcept {
  if (is_playing()) {
    Mix_Pause(channel);
    channel = undefinedChannel;
  }
}

void SoundEffect::fade_in(int ms) noexcept {
  if (ms > 0 && !is_playing()) {
    if (channel != undefinedChannel) {
      Mix_FadeInChannelTimed(channel, chunk, 0, ms, -1);
    } else {
      channel = Mix_FadeInChannelTimed(undefinedChannel, chunk, 0, ms, -1);
    }
  }
}

void SoundEffect::fade_out(int ms) noexcept {
  if ((ms > 0) && is_playing()) {
    Mix_FadeOutChannel(channel, ms);
  }
}

void SoundEffect::set_volume(int volume) noexcept {
  if (volume < 0) { volume = 0; }
  if (volume > get_max_volume()) { volume = get_max_volume(); }
  Mix_VolumeChunk(chunk, volume);
}

int SoundEffect::get_volume() const noexcept {
  return chunk->volume;
}

bool SoundEffect::is_playing() const noexcept {
  return (channel != undefinedChannel) && Mix_Playing(channel);
}

std::string SoundEffect::to_string() const {
  const auto address = CenturionUtils::address(this);
  const auto volume = std::to_string(get_volume());
  return "[SoundEffect@" + address + " | Volume: " + volume + "]";
}

SoundEffect::operator Mix_Chunk*() const noexcept {
  return chunk;
}

}

#endif