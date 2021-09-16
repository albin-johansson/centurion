#ifndef CENTURION_MOUSE_BUTTON_EVENT_HEADER
#define CENTURION_MOUSE_BUTTON_EVENT_HEADER

#include <SDL.h>

#include "../core/integers.hpp"
#include "../core/to_underlying.hpp"
#include "../input/button_state.hpp"
#include "../input/mouse_button.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \class mouse_button_event
 *
 * \brief Represents an event triggered by mouse button presses or releases.
 *
 * \see `SDL_MouseButtonEvent`
 *
 * \since 4.0.0
 */
class mouse_button_event final : public common_event<SDL_MouseButtonEvent>
{
 public:
  /**
   * \brief Creates a mouse button event of type `mouse_button_down`.
   *
   * \since 4.0.0
   */
  mouse_button_event() noexcept : common_event{event_type::mouse_button_down}
  {}

  /**
   * \brief Creates a mouse_button_event that is based on the supplied SDL
   * event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit mouse_button_event(const SDL_MouseButtonEvent& event) noexcept : common_event{event}
  {}

  /**
   * \brief Sets the window ID associated with the event.
   *
   * \param id the window ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_window_id(const u32 id) noexcept
  {
    m_event.windowID = id;
  }

  /**
   * \brief Sets the mouse instance ID.
   *
   * \param which the mouse instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const u32 which) noexcept
  {
    m_event.which = which;
  }

  /**
   * \brief Sets the mouse button associated with the event.
   *
   * \param button the mouse button associated with the event.
   *
   * \since 4.0.0
   */
  void set_button(const mouse_button button) noexcept
  {
    m_event.button = to_underlying(button);
  }

  /**
   * \brief Sets the button state associated with the event.
   *
   * \param state the button state associated with the event.
   *
   * \since 4.0.0
   */
  void set_state(const button_state state) noexcept
  {
    m_event.state = to_underlying(state);
  }

  /**
   * \brief Sets the amount of clicks associated with the event.
   *
   * \param clicks the amount of clicks associated with the event.
   *
   * \since 4.0.0
   */
  void set_clicks(const u8 clicks) noexcept
  {
    m_event.clicks = clicks;
  }

  /**
   * \brief Sets the x-coordinate of the mouse relative to the window.
   *
   * \param x the x-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  void set_x(const i32 x) noexcept
  {
    m_event.x = x;
  }

  /**
   * \brief Sets the y-coordinate of the mouse relative to the window.
   *
   * \param y the y-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  void set_y(const i32 y) noexcept
  {
    m_event.y = y;
  }

  /**
   * \brief Returns the ID of the window associated with the event.
   *
   * \return the ID of the window associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> u32
  {
    return m_event.windowID;
  }

  /**
   * \brief Returns the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * \return the mouse instance ID, or SDL_TOUCH_MOUSEID.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> u32
  {
    return m_event.which;
  }

  /**
   * \brief Returns the mouse button associated with the event.
   *
   * \return the mouse button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto button() const noexcept -> mouse_button
  {
    return static_cast<mouse_button>(m_event.button);
  }

  /**
   * \brief Returns the state of the mouse button associated with the event.
   *
   * \return the state of the mouse button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> button_state
  {
    return static_cast<button_state>(m_event.state);
  }

  /**
   * \brief Indicates whether or not the associated button is pressed.
   *
   * \return `true` if the associated button is pressed; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto pressed() const noexcept -> bool
  {
    return state() == button_state::pressed;
  }

  /**
   * \brief Indicates whether or not the associated button is released.
   *
   * \return `true` if the associated button is released; `false` otherwise.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto released() const noexcept -> bool
  {
    return state() == button_state::released;
  }

  /**
   * \brief Returns the number of mouse clicks associated with the event.
   *
   * \return the number of mouse clicks associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto clicks() const noexcept -> u8
  {
    return m_event.clicks;
  }

  /**
   * \brief Returns the x-coordinate of the mouse relative to the window.
   *
   * \return the x-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x() const noexcept -> i32
  {
    return m_event.x;
  }

  /**
   * \brief Returns the y-coordinate of the mouse relative to the window.
   *
   * \return the y-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y() const noexcept -> i32
  {
    return m_event.y;
  }
};

/// \name SDL event conversions
/// \{

template <>
inline auto as_sdl_event(const common_event<SDL_MouseButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.button = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_MOUSE_BUTTON_EVENT_HEADER
