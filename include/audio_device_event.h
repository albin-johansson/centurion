#ifndef CENTURION_AUDIO_DEVICE_EVENT_HEADER
#define CENTURION_AUDIO_DEVICE_EVENT_HEADER

#include <SDL_events.h>

#include "base_event.h"
#include "centurion_api.h"

namespace centurion {
namespace event {

/**
 * The AudioDeviceEventID enum class is a wrapper for SDL_AUDIODEVICEADDED
 * and SDL_AUDIODEVICEREMOVED.
 *
 * @since 4.0.0
 */
enum class AudioDeviceEventID {
  Added = SDL_AUDIODEVICEADDED,
  Removed = SDL_AUDIODEVICEREMOVED
};

/**
 * The AudioDeviceEvent class represents an event that is associated with
 * some sort of audio device, either capture of output.
 *
 * @see SDL_AudioDeviceEvent
 * @since 4.0.0
 */
class AudioDeviceEvent : public BaseEvent<SDL_AudioDeviceEvent> {
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
   * Sets the type of the audio device event.
   *
   * @param id the type of the audio device event.
   * @since 4.0.0
   */
  CENTURION_API void set_type(AudioDeviceEventID id) noexcept;

  /**
   * Sets the audio device ID that is associated with the event.
   *
   * @param which the audio device ID that is associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_which(uint32_t which) noexcept;

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
   * Returns the type of the audio device event.
   *
   * @return the type of the audio device event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API AudioDeviceEventID type() const noexcept;

  /**
   * Returns the audio device ID associated with the event.
   *
   * @return the audio device ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API uint32_t which() const noexcept;

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

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "audio_device_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_AUDIO_DEVICE_EVENT_HEADER
