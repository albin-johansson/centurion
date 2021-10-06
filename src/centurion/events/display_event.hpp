#ifndef CENTURION_DISPLAY_EVENT_HEADER
#define CENTURION_DISPLAY_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "../core/to_underlying.hpp"
#include "common_event.hpp"
#include "display_event_id.hpp"

namespace cen {

#if SDL_VERSION_ATLEAST(2, 0, 14)

/// \addtogroup event
/// \{

/**
 * \class display_event
 *
 * \brief Represents events related to displays.
 *
 * \see `SDL_DisplayEvent`
 *
 * \since 6.3.0
 */
class display_event final : public common_event<SDL_DisplayEvent>
{
 public:
  /**
   * \brief Creates a display event.
   *
   * \since 6.3.0
   */
  display_event() noexcept : common_event{event_type::display}
  {}

  /**
   * \brief Creates a display event based an SDL event.
   *
   * \param event the event that will be copied.
   *
   * \since 6.3.0
   */
  explicit display_event(const SDL_DisplayEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Sets the associated display event ID.
   *
   * \param id the associated display event subtype.
   *
   * \since 6.3.0
   */
  void set_event_id(const display_event_id id) noexcept
  {
    m_event.event = static_cast<u8>(to_underlying(id));
  }

  /**
   * \brief Sets the associated display index.
   *
   * \param index the associated display index.
   *
   * \since 6.3.0
   */
  void set_index(const u32 index) noexcept
  {
    m_event.display = index;
  }

  /**
   * \brief Sets event type specific data.
   *
   * \param data the associated data value.
   *
   * \see `display_event_id`
   *
   * \since 6.3.0
   */
  void set_data_1(const i32 data) noexcept
  {
    m_event.data1 = data;
  }

  /**
   * \brief Returns the associated display event ID.
   *
   * \return the associated display event subtype.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto event_id() const noexcept -> display_event_id
  {
    return static_cast<display_event_id>(m_event.event);
  }

  /**
   * \brief Returns the index of the associated display.
   *
   * \return the associated display index.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto index() const noexcept -> u32
  {
    return m_event.display;
  }

  /**
   * \brief Returns subtype specific data.
   *
   * \details The returned value is the display orientation if the type of the event is
   * equivalent to `display_event_id::orientation`.
   *
   * \return subtype specific data.
   *
   * \see `screen_orientation`
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto data_1() const noexcept -> i32
  {
    return m_event.data1;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_DisplayEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.display = event.get();
  return e;
}

/// \} End of group event

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

}  // namespace cen

#endif  // CENTURION_DISPLAY_EVENT_HEADER
