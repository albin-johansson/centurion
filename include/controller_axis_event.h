#ifndef CENTURION_CONTROLLER_AXIS_EVENT_HEADER
#define CENTURION_CONTROLLER_AXIS_EVENT_HEADER

#include <SDL_events.h>

#include <type_traits>

#include "base_event.h"
#include "centurion_api.h"

namespace centurion {
namespace event {

/**
 * The GameControllerAxis enum class mirrors the values of the
 * SDL_GameControllerAxis enum.
 *
 * @see SDL_GameControllerAxis
 * @since 4.0.0
 */
enum class GameControllerAxis {
  Invalid = SDL_CONTROLLER_AXIS_INVALID,
  LeftX = SDL_CONTROLLER_AXIS_LEFTX,
  LeftY = SDL_CONTROLLER_AXIS_LEFTY,
  RightX = SDL_CONTROLLER_AXIS_RIGHTX,
  RightY = SDL_CONTROLLER_AXIS_RIGHTY,
  TriggerLeft = SDL_CONTROLLER_AXIS_TRIGGERLEFT,
  TriggerRight = SDL_CONTROLLER_AXIS_TRIGGERRIGHT,
  Max = SDL_CONTROLLER_AXIS_MAX
};

/**
 * Indicates whether or not the two game controller axis values are the same.
 *
 * @param axis the lhs Centurion game controller axis value.
 * @param sdlAxis the rhs SDL game controller axis value.
 * @return true if the game controller axis values are the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(GameControllerAxis axis,
                              SDL_GameControllerAxis sdlAxis) noexcept;

/**
 * Indicates whether or not the two game controller axis values are the same.
 *
 * @param sdlAxis the lhs SDL game controller axis value.
 * @param axis the rhs Centurion game controller axis value.
 * @return true if the game controller axis values are the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator==(SDL_GameControllerAxis sdlAxis,
                              GameControllerAxis axis) noexcept;

/**
 * Indicates whether or not the two game controller axis values aren't the same.
 *
 * @param axis the lhs Centurion game controller axis value.
 * @param sdlAxis the rhs SDL game controller axis value.
 * @return true if the game controller axis values aren't the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(GameControllerAxis axis,
                              SDL_GameControllerAxis sdlAxis) noexcept;

/**
 * Indicates whether or not the two game controller axis values aren't the same.
 *
 * @param sdlAxis the lhs SDL game controller axis value.
 * @param axis the rhs Centurion game controller axis value.
 * @return true if the game controller axis values aren't the same; false
 * otherwise.
 * @since 4.0.0
 */
CENTURION_NODISCARD
CENTURION_API bool operator!=(SDL_GameControllerAxis sdlAxis,
                              GameControllerAxis axis) noexcept;

/**
 * A type alias for SDL_JoystickID.
 *
 * @since 4.0.0
 */
using JoystickID = SDL_JoystickID;

/**
 * The ControllerAxisEvent represents an event triggered by game controller
 * axis motion.
 *
 * @since 4.0.0
 */
class ControllerAxisEvent : public BaseEvent<SDL_ControllerAxisEvent> {
 public:
  /**
   * Creates a default-initialized controller axis event.
   *
   * @since 4.0.0
   */
  CENTURION_API ControllerAxisEvent() noexcept;

  /**
   * Creates a controller axis event that is based on the supplied SDL
   * controller axis event.
   *
   * @param event the SDL event that will be copied.
   * @since 4.0.0
   */
  CENTURION_API ControllerAxisEvent(
      const SDL_ControllerAxisEvent& event) noexcept;

  /**
   * Creates a controller axis event by moving the supplied SDL controller
   * axis event.
   *
   * @param event the SDL controller axis event that will be moved.
   * @since 4.0.0
   */
  CENTURION_API ControllerAxisEvent(SDL_ControllerAxisEvent&& event) noexcept;

  /**
   * Sets the joystick instance ID associated with the event.
   *
   * @param which the instance ID of the joystick that the event is
   * associated with.
   * @since 4.0.0
   */
  CENTURION_API void set_which(JoystickID which) noexcept;

  /**
   * Sets the game controller axis value associated with the event.
   *
   * @param axis the game controller axis value associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_axis(GameControllerAxis axis) noexcept;

  /**
   * Sets the axis value associated with the event.
   *
   * @param value the new axis value associated with the event.
   * @since 4.0.0
   */
  CENTURION_API void set_value(int16_t value) noexcept;

  /**
   * Returns the joystick instance ID associated with the event.
   *
   * @return the joystick instance ID associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API JoystickID which() const noexcept;

  /**
   * Returns the game controller axis value associated with the event.
   *
   * @return the game controller axis value associated with the event.
   * @since 4.0.0
   * @see GameControllerAxis
   */
  CENTURION_NODISCARD
  CENTURION_API GameControllerAxis axis() const noexcept;

  /**
   * Returns the axis value associated with the event.
   *
   * @return the axis value associated with the event.
   * @since 4.0.0
   */
  CENTURION_NODISCARD
  CENTURION_API int16_t value() const noexcept;
};

static_assert(validate_event<ControllerAxisEvent>(),
              "ControllerAxisEvent failed event type specification!");

}  // namespace event
}  // namespace centurion

#ifdef CENTURION_HEADER_ONLY
#include "controller_axis_event.cpp"
#endif  // CENTURION_HEADER_ONLY

#endif  // CENTURION_CONTROLLER_AXIS_EVENT_HEADER
