/*
 * MIT License
 *
 * Copyright (c) 2019-2020 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef CENTURION_AUDIO_DEVICE_EVENT_HEADER
#define CENTURION_AUDIO_DEVICE_EVENT_HEADER

#include <SDL_events.h>

#include "centurion_api.h"
#include "common_event.h"

namespace centurion {
namespace event {

/**
 * The AudioDeviceEvent class represents an event that is associated with
 * some sort of audio device, either capture of output.
 *
 * @see SDL_AudioDeviceEvent
 * @since 4.0.0
 */
class AudioDeviceEvent : public CommonEvent<SDL_AudioDeviceEvent> {
 public:
  /**
   * Creates a default-initialized audio device event.
   *
   * @since 4.0.0
   */
  CENTURION_API AudioDeviceEvent() noexcept;

  /**
   * Creates a audio device event based on the supplied SDL event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API AudioDeviceEvent(const SDL_AudioDeviceEvent& event) noexcept;

  /**
   * Creates a audio device event based on the supplied SDL event.
   *
   * @param event the SDL event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API AudioDeviceEvent(SDL_AudioDeviceEvent&& event) noexcept;

  /**
   * Sets the audio device ID that is associated with the event.
   *
   * @param which the audio device ID that is associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_which(Uint32 which) noexcept;

  /**
   * Sets whether or not the audio device event is associated with a capture
   * device.
   *
   * @param capture true if the event is associated with a capture device;
   * false indicates that the event is associated with an output device.
   * @since 4.0.0
   */
  CENTURION_API void set_capture(bool capture) noexcept;

  /**
   * Returns the audio device ID associated with the event.
   *
   * @return the audio device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API Uint32 which() const noexcept;

  /**
   * Indicates whether or not the audio device event is associated with an audio
   * output device.
   *
   * @return true if the event is associated with an output device; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool output() const noexcept;

  /**
   * Indicates whether or not the audio device event is associated with an audio
   * capture device.
   *
   * @return true if the event is associated with a capture device; false
   * otherwise.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API bool capture() const noexcept;
};

static_assert(validate_event<AudioDeviceEvent, SDL_AudioDeviceEvent>(),
              "AudioDeviceEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "audio_device_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_AUDIO_DEVICE_EVENT_HEADER
