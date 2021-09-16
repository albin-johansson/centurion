#ifndef CENTURION_SENSOR_EVENT_HEADER
#define CENTURION_SENSOR_EVENT_HEADER

#include <SDL.h>

#include <array>  // array, to_array

#include "../compiler/features.hpp"
#include "../core/integers.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class sensor_event
 *
 * \brief Represents events related to updates of sensors.
 *
 * \since 6.3.0
 */
class sensor_event final : public common_event<SDL_SensorEvent>
{
 public:
  /**
   * \brief Creates a sensor event.
   *
   * \since 6.3.0
   */
  sensor_event() noexcept : common_event{event_type::sensor_update}
  {}

  /**
   * \brief Creates a sensor event based an SDL event.
   *
   * \param event the event that will be copied.
   *
   * \since 6.3.0
   */
  explicit sensor_event(const SDL_SensorEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Returns the instance ID of the associated sensor.
   *
   * \return the associated sensor instance ID.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto which() const noexcept -> i32
  {
    return m_event.which;
  }

  /**
   * \brief Returns up to 6 values from the sensor.
   *
   * \return values from the sensor.
   *
   * \see `basic_sensor::data()`
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto data() const noexcept -> std::array<float, 6>
  {
#if CENTURION_HAS_FEATURE_TO_ARRAY
    return std::to_array(m_event.data);
#else
    std::array<float, 6> array{};

    for (usize i = 0; i < 6; ++i) {
      array[i] = m_event.data[i];
    }

    return array;
#endif  // CENTURION_HAS_FEATURE_TO_ARRAY
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_SensorEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.sensor = event.get();
  return e;
}

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_SENSOR_EVENT_HEADER
