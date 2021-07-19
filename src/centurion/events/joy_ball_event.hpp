#ifndef CENTURION_JOY_BALL_EVENT_HEADER
#define CENTURION_JOY_BALL_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "common_event.hpp"

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
class joy_ball_event final : public common_event<SDL_JoyBallEvent>
{
 public:
  /**
   * \brief Creates a joy ball event.
   *
   * \since 4.0.0
   */
  joy_ball_event() noexcept : common_event{event_type::joystick_ball_motion}
  {}

  /**
   * \brief Creates a joy ball event based on the supplied SDL joy ball event.
   *
   * \param event the SDL joy ball event that will be copied.
   *
   * \since 4.0.0
   */
  explicit joy_ball_event(const SDL_JoyBallEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param which the joystick instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const SDL_JoystickID which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the joystick trackball index associated with the event.
   *
   * \param ball the joystick trackball index.
   *
   * \since 4.0.0
   */
  void set_ball(const u8 ball) noexcept
  {
    m_event.ball = ball;
  }

  /**
   * \brief Sets the relative motion along the x-axis associated with the event.
   *
   * \param dx the relative motion along the x-axis.
   *
   * \since 4.0.0
   */
  void set_dx(const i16 dx) noexcept
  {
    m_event.xrel = dx;
  }

  /**
   * \brief Sets the relative motion along the y-axis associated with the event.
   *
   * \param dy the relative motion along the y-axis.
   *
   * \since 4.0.0
   */
  void set_dy(const i16 dy) noexcept
  {
    m_event.yrel = dy;
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the joystick instance ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID
  {
    return m_event.which;
  }

  /**
   * \brief Returns the joystick trackball index associated with the event.
   *
   * \return the joystick trackball index associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto ball() const noexcept -> u8
  {
    return m_event.ball;
  }

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
  [[nodiscard]] auto dx() const noexcept -> i16
  {
    return m_event.xrel;
  }

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
  [[nodiscard]] auto dy() const noexcept -> i16
  {
    return m_event.yrel;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_JoyBallEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.jball = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_JOY_BALL_EVENT_HEADER
