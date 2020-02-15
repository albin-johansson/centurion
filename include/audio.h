#pragma once
#include <SDL_mixer.h>

#include "music.h"
#include "sound_effect.h"

namespace centurion {
namespace audio {

/**
 * The maximum possible volume value.
 *
 * @since 4.0.0
 */
static constexpr int maxVolume = MIX_MAX_VOLUME;

/**
 * A constant that indicates that an audio snippet should be looped
 * indefinitely.
 *
 * @since 4.0.0
 */
static constexpr int loopForever = -1;

}  // namespace audio
}  // namespace centurion