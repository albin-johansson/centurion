#ifndef CENTURION_USER_EVENT_HEADER
#define CENTURION_USER_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class user_event
 *
 * \brief Represents a custom user event.
 *
 * \since 6.3.0
 */
class user_event final : public common_event<SDL_UserEvent>
{
 public:
  /**
   * \brief Creates a user event.
   *
   * \details Note that the event will be created using `event_type::user`, but you can use any
   * event type value in the range [`event_type::user`, SDL_LASTEVENT - 1].
   *
   * \since 6.3.0
   */
  user_event() noexcept : common_event{event_type::user}
  {}

  /**
   * \brief Creates a user event based on an SDL event.
   *
   * \param event the event that will be copied.
   *
   * \since 6.3.0
   */
  explicit user_event(const SDL_UserEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Sets the window ID associated with the event.
   *
   * \param id the ID of the associated window.
   *
   * \since 6.3.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Sets the user-defined event code associated with the event.
   *
   * \param code the custom event code.
   *
   * \since 6.3.0
   */
  void set_code(const i32 code) noexcept
  {
    m_event.code = code;
  }

  /**
   * \brief Sets an opaque data pointer to some user data.
   *
   * \param data the user data, can safely be null.
   *
   * \since 6.3.0
   */
  void set_data_1(void* data) noexcept
  {
    m_event.data1 = data;
  }

  /// \copydoc set_data_1()
  void set_data_2(void* data) noexcept
  {
    m_event.data2 = data;
  }

  /**
   * \brief Returns the ID of the window associated with the event.
   *
   * \return the associated window ID.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

  /**
   * \brief Returns the user-defined event code associated with the event.
   *
   * \return the associated event code.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto code() const noexcept -> i32
  {
    return m_event.code;
  }

  /**
   * \brief Returns a pointer to the first user data slot.
   *
   * \return a pointer to the user data, might be null.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto data_1() noexcept -> void*
  {
    return m_event.data1;
  }

  /// \copydoc data_1()
  [[nodiscard]] auto data_1() const noexcept -> const void*
  {
    return m_event.data1;
  }

  /**
   * \brief Returns a pointer to the second user data slot.
   *
   * \return a pointer to the user data, might be null.
   *
   * \since 6.3.0
   */
  [[nodiscard]] auto data_2() noexcept -> void*
  {
    return m_event.data2;
  }

  /// \copydoc data_2()
  [[nodiscard]] auto data_2() const noexcept -> const void*
  {
    return m_event.data2;
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_UserEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.user = event.get();
  return e;
}

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_USER_EVENT_HEADER
