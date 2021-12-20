#ifndef CENTURION_EVENTS_CONTROLLER_TOUCHPAD_EVENT_HPP_
#define CENTURION_EVENTS_CONTROLLER_TOUCHPAD_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "../detail/stdlib.hpp"
#include "event_base.hpp"

namespace cen {

#if SDL_VERSION_ATLEAST(2, 0, 14)

/// \addtogroup event
/// \{

/**
 * \class controller_touchpad_event
 *
 * \brief Represents events associated with controller touchpads.
 *
 * \since 6.3.0
 */
class controller_touchpad_event final : public EventBase<SDL_ControllerTouchpadEvent> {
 public:
  /**
   * \brief Creates a controller touchpad event with `controller_touchpad_down` as the specific
   * type.
   *
   * \see `EventType::ControllerTouchpadDown`
   * \see `EventType::ControllerTouchpadUp`
   * \see `EventType::ControllerTouchpadMotion`
   *
   * \since 6.3.0
   */
  controller_touchpad_event() noexcept : EventBase{EventType::ControllerTouchpadDown} {}

  /**
   * \brief Creates a controller touchpad event based an SDL event.
   *
   * \param event the event that will be copied.
   *
   * \since 6.3.0
   */
  explicit controller_touchpad_event(const SDL_ControllerTouchpadEvent& event) noexcept
      : EventBase{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param id the associated joystick instance ID.
   *
   * \since 6.3.0
   */
  void set_which(const SDL_JoystickID id) noexcept { mEvent.which = id; }

  /**
   * \brief Sets the touchpad index associated with the event.
   *
   * \param index the associated touchpad index.
   *
   * \since 6.3.0
   */
  void set_touchpad_index(const Sint32 index) noexcept { mEvent.touchpad = index; }

  /**
   * \brief Sets the finger index on the touchpad associated with the event.
   *
   * \param index the associated finger index.
   *
   * \since 6.3.0
   */
  void set_finger_index(const Sint32 index) noexcept { mEvent.finger = index; }

  /**
   * \brief Sets the associated x-coordinate.
   *
   * \details The supplied value is clamped within the range [0, 1].
   *
   * \param x the normalized x-coordinate.
   *
   * \since 6.3.0
   */
  void set_x(const float x) noexcept { mEvent.x = detail::clamp(x, 0.0f, 1.0f); }

  /**
   * \brief Sets the associated y-coordinate.
   *
   * \details The supplied value is clamped within the range [0, 1].
   *
   * \param y the normalized y-coordinate.
   *
   * \since 6.3.0
   */
  void set_y(const float y) noexcept { mEvent.y = detail::clamp(y, 0.0f, 1.0f); }

  /**
   * \brief Sets the associated pressure.
   *
   * \details The supplied value is clamped within the range [0, 1].
   *
   * \param pressure the normalized y-coordinate.
   *
   * \since 6.3.0
   */
  void set_pressure(const float pressure) noexcept
  {
    mEvent.pressure = detail::clamp(pressure, 0.0f, 1.0f);
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the associated joystick instance ID.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  /**
   * \brief Returns the touchpad index associated with the event.
   *
   * \return the associated touchpad index.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto touchpad_index() const noexcept -> Sint32 { return mEvent.touchpad; }

  /**
   * \brief Returns the finger index associated with the event.
   *
   * \return the associated finger index.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto finger_index() const noexcept -> Sint32 { return mEvent.finger; }

  /**
   * \brief Returns the associated x-coordinate.
   *
   * \return the normalized x-coordinate.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto x() const noexcept -> float { return mEvent.x; }

  /**
   * \brief Returns the associated y-coordinate.
   *
   * \return the normalized y-coordinate.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto y() const noexcept -> float { return mEvent.y; }

  /**
   * \brief Returns the associated pressure.
   *
   * \return the normalized pressure.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto pressure() const noexcept -> float { return mEvent.pressure; }
};

template <>
inline auto AsSDLEvent(const EventBase<SDL_ControllerTouchpadEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.ctouchpad = event.get();
  return e;
}

/// \} End of group event

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen

#endif  // CENTURION_EVENTS_CONTROLLER_TOUCHPAD_EVENT_HPP_
