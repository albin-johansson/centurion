#ifndef CENTURION_CONTROLLER_SENSOR_EVENT_HEADER
#define CENTURION_CONTROLLER_SENSOR_EVENT_HEADER

#include <SDL.h>

#include <array>  // array

#include "../core/to_underlying.hpp"
#include "../detail/array_utils.hpp"
#include "../input/sensor_type.hpp"
#include "common_event.hpp"

namespace cen {

#if SDL_VERSION_ATLEAST(2, 0, 14)

/// \addtogroup event
/// \{

/**
 * \class controller_sensor_event
 *
 * \brief Represents events associated with controller sensor updates.
 *
 * \since 6.3.0
 */
class controller_sensor_event final : public common_event<SDL_ControllerSensorEvent>
{
 public:
  using data_type = std::array<float, 3>;

  /**
   * \brief Creates a controller sensor event.
   *
   * \since 6.3.0
   */
  controller_sensor_event() noexcept : common_event{event_type::controller_sensor_update}
  {}

  /**
   * \brief Creates a controller sensor event based on an SDL event.
   *
   * \param event the event that will be copied.
   *
   * \since 6.3.0
   */
  explicit controller_sensor_event(const SDL_ControllerSensorEvent& event) noexcept
      : common_event{event}
  {}

  /**
   * \brief Sets the joystick instance ID associated with the event.
   *
   * \param id the associated joystick instance ID.
   *
   * \since 6.3.0
   */
  void set_which(const SDL_JoystickID id) noexcept
  {
    m_event.which = id;
  }

  /**
   * \brief Sets the associated sensor type.
   *
   * \param sensor the type of the associated sensor.
   *
   * \since 6.3.0
   */
  void set_sensor(const sensor_type sensor) noexcept
  {
    m_event.sensor = to_underlying(sensor);
  }

  /**
   * \brief Sets the sensor values associated with the event.
   *
   * \param values the sensor values.
   *
   * \since 6.3.0
   */
  void set_data(const data_type& values)
  {
    detail::assign(values, m_event.data);
  }

  /**
   * \brief Returns the joystick instance ID associated with the event.
   *
   * \return the associated joystick instance ID.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto which() const noexcept -> SDL_JoystickID
  {
    return m_event.which;
  }

  /**
   * \brief Returns the type of the associated sensor.
   *
   * \return the associated sensor type.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto sensor() const noexcept -> sensor_type
  {
    return static_cast<sensor_type>(m_event.sensor);
  }

  /**
   * \brief Returns up to 3 values from the sensor.
   *
   * \return values from the sensor.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto data() const -> data_type
  {
    return detail::to_array(m_event.data);
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_ControllerSensorEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.csensor = event.get();
  return e;
}

/// \} End of group event

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen

#endif  // CENTURION_CONTROLLER_SENSOR_EVENT_HEADER
