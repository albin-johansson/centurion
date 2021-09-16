#ifndef CENTURION_AUDIO_DEVICE_EVENT_HEADER
#define CENTURION_AUDIO_DEVICE_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class audio_device_event
 *
 * \brief Represents an event that is associated with some sort of audio device, either
 * capture of output.
 *
 * \see `SDL_AudioDeviceEvent`
 *
 * \since 4.0.0
 */
class audio_device_event final : public common_event<SDL_AudioDeviceEvent>
{
 public:
  /**
   * \brief Creates an audio device event of type `audio_device_added`.
   *
   * \since 4.0.0
   */
  audio_device_event() noexcept : common_event{event_type::audio_device_added}
  {}

  /**
   * \brief Creates a audio device event based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit audio_device_event(const SDL_AudioDeviceEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Sets the audio device ID that is associated with the event.
   *
   * \param which the audio device ID that is associated with the event.
   *
   * \since 4.0.0
   */
  void set_which(const u32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets whether or not the audio device event is associated with a
   * capture device.
   *
   * \param capture `true` if the event is associated with a capture device;
   * `false` indicates that the event is associated with an output device.
   *
   * \since 4.0.0
   */
  void set_capture(const bool capture) noexcept
  {
    m_event.iscapture = capture;
  }

  /**
   * \brief Returns the audio device ID associated with the event.
   *
   * \return the audio device ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> u32
  {
    return m_event.which;
  }

  /**
   * \brief Indicates whether or not the audio device event is associated with
   * an audio output device.
   *
   * \return `true` if the event is associated with an output device; false
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto output() const noexcept -> bool
  {
    return !capture();
  }

  /**
   * \brief Indicates whether or not the audio device event is associated with
   * an audio capture device.
   *
   * \return `true` if the event is associated with a capture device; false
   * otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto capture() const noexcept -> bool
  {
    return m_event.iscapture;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_AudioDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.adevice = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_AUDIO_DEVICE_EVENT_HEADER
