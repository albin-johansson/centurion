#ifndef CENTURION_SENSOR_EVENT_HEADER
#define CENTURION_SENSOR_EVENT_HEADER

#include <SDL.h>

#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

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

  // TODO float data[6];
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
