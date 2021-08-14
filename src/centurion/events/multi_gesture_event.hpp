#ifndef CENTURION_MULTI_GESTURE_EVENT_HEADER
#define CENTURION_MULTI_GESTURE_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class multi_gesture_event
 *
 * \brief Provides information about events related to touch events triggered
 * by multiple fingers.
 *
 * \see `SDL_MultiGestureEvent`
 *
 * \since 4.0.0
 */
class multi_gesture_event final : public common_event<SDL_MultiGestureEvent>
{
 public:
  /**
   * \brief Creates a multi-gesture event.
   *
   * \since 4.0.0
   */
  multi_gesture_event() noexcept : common_event{event_type::multi_gesture}
  {}

  /**
   * \brief Creates an event that is based on the supplied SDL event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit multi_gesture_event(const SDL_MultiGestureEvent& event) noexcept
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
   * \brief Sets the amount that the fingers rotated during the gesture
   * associated with the event.
   *
   * \param dTheta the amount that the fingers rotated.
   *
   * \since 4.0.0
   */
  void set_delta_theta(const float dTheta) noexcept
  {
    m_event.dTheta = dTheta;
  }

  /**
   * \brief Sets the amount that the fingers pinched during the gesture
   * associated with the event.
   *
   * \param dDistance the amount that the fingers pinched.
   *
   * \since 4.0.0
   */
  void set_delta_distance(const float dDistance) noexcept
  {
    m_event.dDist = dDistance;
  }

  /**
   * \brief Sets the x-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * \param centerX the x-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * \since 4.0.0
   */
  void set_center_x(const float centerX) noexcept
  {
    m_event.x = centerX;
  }

  /**
   * \brief Sets the y-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * \param centerY the y-coordinate of the normalized center of the gesture
   * associated with the event.
   *
   * \since 4.0.0
   */
  void set_center_y(const float centerY) noexcept
  {
    m_event.y = centerY;
  }

  /**
   * \brief Sets the number of fingers that was used in the gesture associated
   * with the event.
   *
   * \param count the number of fingers that were use.
   *
   * \since 6.1.0
   */
  void set_finger_count(const u16 count) noexcept
  {
    m_event.numFingers = count;
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
   * \brief Returns the amount that the fingers rotated during the gesture
   * associated with the event.
   *
   * \return the amount that the fingers rotated.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto delta_theta() const noexcept -> float
  {
    return m_event.dTheta;
  }

  /**
   * \brief Returns the amount that the fingers pinched during the gesture
   * associated with the event.
   *
   * \return the amount that the fingers pinched.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto delta_distance() const noexcept -> float
  {
    return m_event.dDist;
  }

  /**
   * \brief Returns the x-coordinate of the normalized center of gesture
   * associated with the event.
   *
   * \return the x-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto center_x() const noexcept -> float
  {
    return m_event.x;
  }

  /**
   * \brief Returns the y-coordinate of the normalized center of gesture
   * associated with the event.
   *
   * \return the y-coordinate of the normalized center of gesture associated
   * with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto center_y() const noexcept -> float
  {
    return m_event.y;
  }

  /**
   * \brief Returns the amount of fingers used in the gesture associated with the event.
   *
   * \return the amount of fingers used in the gesture.
   *
   * \since 6.1.0
   */
  [[nodiscard]] auto finger_count() const noexcept -> u16
  {
    return m_event.numFingers;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_MultiGestureEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.mgesture = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_MULTI_GESTURE_EVENT_HEADER
