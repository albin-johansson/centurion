#ifndef CENTURION_EVENTS_JOY_BALL_EVENT_HPP_
#define CENTURION_EVENTS_JOY_BALL_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "event_base.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class joy_ball_event
 *
 * \brief Represents the event that is triggered when a user moves a
 * trackball on a joystick.
 *
 * \see `SDL_JoyBallEvent`
 *
 * \since 4.0.0
 */
class joy_ball_event final : public EventBase<SDL_JoyBallEvent> {
 public:
  /**
   * \brief Creates a joy ball event.
   *
   * \since 4.0.0
   */
  joy_ball_event() noexcept : EventBase{EventType::JoyBallMotion} {}

  /**
   * \brief Creates a joy ball event based on the supplied SDL joy ball event.
   *
   * \param event the SDL joy ball event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_ball_event(const SDL_JoyBallEvent& event) noexcept : EventBase{event} {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the joystick instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept { mEvent.which = which; }

  /**
   * \brief Sets the joystick trackball index associated with the event.
   *
   * \param ball the joystick trackball index.
   *
   * \since 4.0.0
   */
  void set_ball(const Uint8 ball) noexcept { mEvent.ball = ball; }

  /**
   * \brief Sets the relative motion along the x-axis associated with the event.
   *
   * \param dx the relative motion along the x-axis.
   *
   * \since 4.0.0
   */
  void set_dx(const Sint16 dx) noexcept { mEvent.xrel = dx; }

  /**
   * \brief Sets the relative motion along the y-axis associated with the event.
   *
   * \param dy the relative motion along the y-axis.
   *
   * \since 4.0.0
   */
  void set_dy(const Sint16 dy) noexcept { mEvent.yrel = dy; }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID { return mEvent.which; }

  /**
   * \brief Returns the joystick trackball index associated with the event.
   *
   * \return the joystick trackball index associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto ball() const noexcept -> Uint8 { return mEvent.ball; }

  /**
   * \brief Returns the relative motion along the x-axis.
   *
   * \note Trackballs only return relative motion, i.e this is the change in
   * position of the ball along the x-axis since it was last updated.
   *
   * \return the relative motion along the x-axis.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dx() const noexcept -> Sint16 { return mEvent.xrel; }

  /**
   * \brief Returns the relative motion along the y-axis.
   *
   * \note Trackballs only return relative motion, i.e this is the change in
   * position of the ball along the y-axis since it was last updated.
   *
   * \return the relative motion along the y-axis.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dy() const noexcept -> Sint16 { return mEvent.yrel; }
};

/// \name SDL event conversions
/// \{

template <>
inline auto AsSDLEvent(const EventBase<SDL_JoyBallEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jball = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_JOY_BALL_EVENT_HPP_
