#ifndef CENTURION_DOLLAR_GESTURE_HEADER
#define CENTURION_DOLLAR_GESTURE_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "common_event.hpp"

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
class dollar_gesture_event final : public common_event<SDL_DollarGestureEvent>
{
 public:
  /**
   * \brief Creates a dollar gesture event of type `dollar_gesture`.
   *
   * \since 4.0.0
   */
  dollar_gesture_event() noexcept : common_event{event_type::dollar_gesture}
  {
    set_type(event_type::dollar_gesture);
  }

  /**
   * \brief Creates a dollar gesture event that is based on the supplied SDL
   * dollar gesture event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit dollar_gesture_event(const SDL_DollarGestureEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the touch device ID associated with the event.
   *
   * \param id the touch device ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_touch_id(const SDL_TouchID id) noexcept
  {
    m_event.touchId = id;
  }

  /**
   * \brief Sets the gesture ID associated with the event.
   *
   * \param id the gesture ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_gesture_id(const SDL_GestureID id) noexcept
  {
    m_event.gestureId = id;
  }

  /**
   * \brief Sets the amount of fingers used to draw the stroke.
   *
   * \param fingers the amount of fingers used to draw the stroke.
   *
   * \todo Centurion 7.0.0: Rename to set_finger_count.
   *
   * \since 4.0.0
   */
  void set_fingers(const u32 fingers) noexcept
  {
    m_event.numFingers = fingers;
  }

  /**
   * \brief Sets the error value for the performed stroke compared with the
   * gesture template associated with the event.
   *
   * \since 4.0.0
   */
  void set_error(const float error) noexcept
  {
    m_event.error = error;
  }

  /**
   * \brief Sets the normalized x-coordinate of the center of the gesture.
   *
   * \param x the normalized x-coordinate of the center of the gesture.
   *
   * \since 4.0.0
   */
  void set_x(const float x) noexcept
  {
    m_event.x = x;
  }

  /**
   * \brief Sets the normalized y-coordinate of the center of the gesture.
   *
   * \param y the normalized y-coordinate of the center of the gesture.
   *
   * \since 4.0.0
   */
  void set_y(const float y) noexcept
  {
    m_event.y = y;
  }

  /**
   * \brief Returns the touch device ID associated with the event.
   *
   * \return the touch device ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto touch_id() const noexcept -> SDL_TouchID
  {
    return m_event.touchId;
  }

  /**
   * \brief Returns the unique ID of the closest gesture to the performed
   * stroke.
   *
   * \return the unique ID of the closest gesture to the performed stroke.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto gesture_id() const noexcept -> SDL_GestureID
  {
    return m_event.gestureId;
  }

  /**
   * \brief Returns the amount of fingers used to draw the stroke.
   *
   * \return the amount of fingers used to draw the stroke.
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto finger_count() const noexcept -> u32
  {
    return m_event.numFingers;
  }

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
  [[nodiscard]] auto error() const noexcept -> float
  {
    return m_event.error;
  }

  /**
   * \brief Returns the x-coordinate of the normalized center of the gesture.
   *
   * \return the x-coordinate of the normalized center of the gesture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x() const noexcept -> float
  {
    return m_event.x;
  }

  /**
   * \brief Returns the y-coordinate of the normalized center of the gesture.
   *
   * \return the y-coordinate of the normalized center of the gesture.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y() const noexcept -> float
  {
    return m_event.y;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_DollarGestureEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.dgesture = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_DOLLAR_GESTURE_HEADER
