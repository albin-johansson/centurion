#ifndef CENTURION_TOUCH_FINGER_EVENT_HEADER
#define CENTURION_TOUCH_FINGER_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "../detail/clamp.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class touch_finger_event
 *
 * \brief Represents an event related to touch screen actions.
 *
 * \see `SDL_TouchFingerEvent`
 *
 * \since 4.0.0
 */
class touch_finger_event final : public common_event<SDL_TouchFingerEvent>
{
 public:
  /**
   * \brief Creates a touch finger event of type `touch_down`.
   *
   * \since 4.0.0
   */
  touch_finger_event() noexcept : common_event{event_type::touch_down}
  {}

  /**
   * \brief Creates a touch finger event that is based on the supplied SDL
   * ouch finger event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit touch_finger_event(const SDL_TouchFingerEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Sets the ID of the associated touch device.
   *
   * \param id the ID of the associated touch device.
   *
   * \since 4.0.0
   */
  void set_touch_id(const SDL_TouchID id) noexcept
  {
    m_event.touchId = id;
  }

  /**
   * \brief Sets the finger ID associated with the event.
   *
   * \param id the finger ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_finger_id(const SDL_FingerID id) noexcept
  {
    m_event.fingerId = id;
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Sets the window ID of the window under the finger.
   *
   * \param id the window ID of the window under the finger.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Sets the normalized x-coordinate of the location of the event.
   *
   * \details The supplied value will be clamped to the range [0, 1].
   *
   * \param x the normalized x-coordinate of the location of the event,
   * clamped to the range [0, 1].
   *
   * \since 4.0.0
   */
  void set_x(const float x) noexcept
  {
    m_event.x = detail::clamp(x, 0.0f, 1.0f);
  }

  /**
   * \brief Sets the normalized y-coordinate of the location of the event.
   *
   * \details The supplied value will be clamped to the range [0, 1].
   *
   * \param y the normalized y-coordinate of the location of the event,
   * clamped to the range [0, 1].
   *
   * \since 4.0.0
   */
  void set_y(const float y) noexcept
  {
    m_event.y = detail::clamp(y, 0.0f, 1.0f);
  }

  /**
   * \brief Sets the normalized distance moved along the x-axis.
   *
   * \details The supplied value will be clamped to the range [-1, 1].
   *
   * \param dx the normalized distance moved along the x-axis, clamped to the
   * range [-1, 1].
   *
   * \since 4.0.0
   */
  void set_dx(const float dx) noexcept
  {
    m_event.dx = detail::clamp(dx, -1.0f, 1.0f);
  }

  /**
   * \brief Sets the normalized distance moved along the y-axis.
   *
   * \details The supplied value will be clamped to the range [-1, 1].
   *
   * \param dy the normalized distance moved along the y-axis, clamped to the
   * range [-1, 1].
   *
   * \since 4.0.0
   */
  void set_dy(const float dy) noexcept
  {
    m_event.dy = detail::clamp(dy, -1.0f, 1.0f);
  }

  /**
   * \brief Sets the normalized pressure associated with the event.
   *
   * \details The supplied value will be clamped to the range [0, 1].
   *
   * \param pressure the normalized pressure associated with the event, clamped
   * in the range [0, 1].
   *
   * \since 4.0.0
   */
  void set_pressure(const float pressure) noexcept
  {
    m_event.pressure = detail::clamp(pressure, 0.0f, 1.0f);
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
   * \brief Returns the finger ID associated with the event.
   *
   * \return the finger ID associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto finger_id() const noexcept -> SDL_FingerID
  {
    return m_event.fingerId;
  }

#if SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Returns the window ID of the window under the finger.
   *
   * \return the window ID of the window under the finger.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 12)

  /**
   * \brief Returns the normalized x-coordinate of the location of the event.
   *
   * \details The returned value will be in the range [0, 1].
   *
   * \return the normalized x-coordinate of the location of the event, in the
   * range [0, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x() const noexcept -> float
  {
    return m_event.x;
  }

  /**
   * \brief Returns the normalized y-coordinate of the location of the event.
   *
   * \details The returned value will be in the range [0, 1].
   *
   * \return the normalized y-coordinate of the location of the event, in the
   * range [0, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y() const noexcept -> float
  {
    return m_event.y;
  }

  /**
   * \brief Returns the normalized distance moved along the x-axis.
   *
   * \details The returned value will be in the range [-1, 1].
   *
   * \return the normalized distance moved along the x-axis, in the range
   * [-1, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dx() const noexcept -> float
  {
    return m_event.dx;
  }

  /**
   * \brief Returns the normalized distance moved along the y-axis.
   *
   * \details The returned value will be in the range [-1, 1].
   *
   * \return the normalized distance moved along the y-axis, in the range
   * [-1, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto dy() const noexcept -> float
  {
    return m_event.dy;
  }

  /**
   * \brief Returns the normalized pressure associated with the event.
   *
   * \details The returned value will be in the range [0, 1].
   *
   * \return the normalized pressure associated with the event, in the range
   * [0, 1].
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto pressure() const noexcept -> float
  {
    return m_event.pressure;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_TouchFingerEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.tfinger = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_TOUCH_FINGER_EVENT_HEADER
