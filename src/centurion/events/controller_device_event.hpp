#ifndef CENTURION_CONTROLLER_DEVICE_EVENT_HEADER
#define CENTURION_CONTROLLER_DEVICE_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class controller_device_event
 *
 * \brief Represents events related to game controller devices such as adding
 * or removing game controller devices.
 *
 * \see `SDL_ControllerDeviceEvent`
 *
 * \since 4.0.0
 */
class controller_device_event final : public common_event<SDL_ControllerDeviceEvent>
{
 public:
  /**
   * \brief Creates a controller device event of type `controller_device_added`.
   *
   * \since 4.0.0
   */
  controller_device_event() noexcept : common_event{event_type::controller_device_added}
  {}

  /**
   * \brief Creates a controller device event that is based on the supplied SDL
   * controller device event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit controller_device_event(const SDL_ControllerDeviceEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the joystick device index or instance ID.
   *
   * \details If the event type is `Added`, then this value is the joystick
   * device index. If the type of the event is either `Removed` or
   * `Remapped`, then this value is the instance ID.
   *
   * \param which the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const i32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Returns the joystick device index or instance ID.
   *
   * \details Returns the joystick device index if the type of the event is
   * `Added`. Returns the instance ID if the type of the event is either
   * `Removed` or `Remapped`.
   *
   * \return the joystick device index or instance ID.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> i32
  {
    return m_event.which;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_ControllerDeviceEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.cdevice = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_CONTROLLER_DEVICE_EVENT_HEADER
