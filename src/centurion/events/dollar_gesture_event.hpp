#ifndef CENTURION_EVENTS_DOLLAR_GESTURE_HPP_
#define CENTURION_EVENTS_DOLLAR_GESTURE_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "event_base.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class dollar_gesture_event
 *
 * \brief Provides information about dollar gestures from touch events.
 *
 * \see `SDL_DollarGestureEvent`
 *
 * \since 4.0.0
 */
class dollar_gesture_event final : public EventBase<SDL_DollarGestureEvent> {
 public:
  /**
   * \brief Creates a dollar gesture event of type `dollar_gesture`.
   *
   * \since 4.0.0
   */
  dollar_gesture_event() noexcept : EventBase{EventType::DollarGesture} {}

  /**
   * \brief Creates a dollar gesture event that is based on the supplied SDL
   * dollar gesture event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit dollar_gesture_event(const SDL_DollarGestureEvent& event) noexcept
      : EventBase{event}
  {}

  /**
   * \brief Sets the touch device ID associated with the event.
   *
   * \param id the touch device ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_touch_id(const SDL_TouchID id) noexcept { mEvent.touchId = id; }

  /**
   * \brief Sets the gesture ID associated with the event.
   *
   * \param id the gesture ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_gesture_id(const SDL_GestureID id) noexcept { mEvent.gestureId = id; }

  /**
   * \brief Sets the amount of fingers used to draw the stroke.
   *
   * \param fingers the amount of fingers used to draw the stroke.
   *
   * \todo Centurion 7.0.0: Rename to set_finger_count.
   *
   * \since 4.0.0
   */
  void set_fingers(const Uint32 fingers) noexcept { mEvent.numFingers = fingers; }

  /**
   * \brief Sets the error value for the performed stroke compared with the
   * gesture template associated with the event.
   *
   * \since 4.0.0
   */
  void set_error(const float error) noexcept { mEvent.error = error; }

  /**
   * \brief Sets the normalized x-coordinate of the center of the gesture.
   *
   * \param x the normalized x-coordinate of the center of the gesture.
   *
   * \since 4.0.0
   */
  void set_x(const float x) noexcept { mEvent.x = x; }

  /**
   * \brief Sets the normalized y-coordinate of the center of the gesture.
   *
   * \param y the normalized y-coordinate of the center of the gesture.
   *
   * \since 4.0.0
   */
  void set_y(const float y) noexcept { mEvent.y = y; }

  /**
   * \brief Returns the touch device ID associated with the event.
   *
   * \return the touch device ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID { return mEvent.touchId; }

  /**
   * \brief Returns the unique ID of the closest gesture to the performed
   * stroke.
   *
   * \return the unique ID of the closest gesture to the performed stroke.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto gesture_id() const noexcept -> SDL_GestureID { return mEvent.gestureId; }

  /**
   * \brief Returns the amount of fingers used to draw the stroke.
   *
   * \return the amount of fingers used to draw the stroke.
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto finger_count() const noexcept -> Uint32 { return mEvent.numFingers; }

  /**
   * \brief Returns the difference between the gesture template and the
   * performed gesture.
   *
   * \details The lower the error, the better the match.
   *
   * \return the difference between the gesture template and the performed
   * gesture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto error() const noexcept -> float { return mEvent.error; }

  /**
   * \brief Returns the x-coordinate of the normalized center of the gesture.
   *
   * \return the x-coordinate of the normalized center of the gesture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x() const noexcept -> float { return mEvent.x; }

  /**
   * \brief Returns the y-coordinate of the normalized center of the gesture.
   *
   * \return the y-coordinate of the normalized center of the gesture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y() const noexcept -> float { return mEvent.y; }
};

/// \name SDL event conversions
/// \{

template <>
inline auto AsSDLEvent(const EventBase<SDL_DollarGestureEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.dgesture = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_DOLLAR_GESTURE_HPP_
