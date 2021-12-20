#ifndef CENTURION_EVENTS_MOUSE_BUTTON_EVENT_HPP_
#define CENTURION_EVENTS_MOUSE_BUTTON_EVENT_HPP_

#include <SDL.h>

#include "../common.hpp"
#include "../input/button_state.hpp"
#include "../mouse.hpp"
#include "event_base.hpp"

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
class mouse_button_event final : public EventBase<SDL_MouseButtonEvent> {
 public:
  /**
   * \brief Creates a mouse button event of type `mouse_button_down`.
   *
   * \since 4.0.0
   */
  mouse_button_event() noexcept : EventBase{EventType::MouseButtonDown} {}

  /**
   * \brief Creates a mouse_button_event that is based on the supplied SDL
   * event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit mouse_button_event(const SDL_MouseButtonEvent& event) noexcept : EventBase{event}
  {}

  /**
   * \brief Sets the window ID associated with the event.
   *
   * \param id the window ID associated with the event.
   *
   * \since 4.0.0
   */
  void set_window_id(const Uint32 id) noexcept { mEvent.windowID = id; }

  /**
   * \brief Sets the mouse instance ID.
   *
   * \param which the mouse instance ID.
   *
   * \since 4.0.0
   */
  void set_which(const Uint32 which) noexcept { mEvent.which = which; }

  /**
   * \brief Sets the mouse button associated with the event.
   *
   * \param button the mouse button associated with the event.
   *
   * \since 4.0.0
   */
  void set_button(const MouseButton button) noexcept { mEvent.button = ToUnderlying(button); }

  /**
   * \brief Sets the button state associated with the event.
   *
   * \param state the button state associated with the event.
   *
   * \since 4.0.0
   */
  void set_state(const ButtonState state) noexcept { mEvent.state = ToUnderlying(state); }

  /**
   * \brief Sets the amount of clicks associated with the event.
   *
   * \param clicks the amount of clicks associated with the event.
   *
   * \since 4.0.0
   */
  void set_clicks(const Uint8 clicks) noexcept { mEvent.clicks = clicks; }

  /**
   * \brief Sets the x-coordinate of the mouse relative to the window.
   *
   * \param x the x-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  void set_x(const Sint32 x) noexcept { mEvent.x = x; }

  /**
   * \brief Sets the y-coordinate of the mouse relative to the window.
   *
   * \param y the y-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  void set_y(const Sint32 y) noexcept { mEvent.y = y; }

  /**
   * \brief Returns the ID of the window associated with the event.
   *
   * \return the ID of the window associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto window_id() const noexcept -> Uint32 { return mEvent.windowID; }

  /**
   * \brief Returns the mouse instance ID, or SDL_TOUCH_MOUSEID if the event was
   * triggered by a touch input device.
   *
   * \return the mouse instance ID, or SDL_TOUCH_MOUSEID.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> Uint32 { return mEvent.which; }

  /**
   * \brief Returns the mouse button associated with the event.
   *
   * \return the mouse button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto button() const noexcept -> MouseButton
  {
    return static_cast<MouseButton>(mEvent.button);
  }

  /**
   * \brief Returns the state of the mouse button associated with the event.
   *
   * \return the state of the mouse button associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto state() const noexcept -> ButtonState
  {
    return static_cast<ButtonState>(mEvent.state);
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
    return state() == ButtonState::Pressed;
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
    return state() == ButtonState::Released;
  }

  /**
   * \brief Returns the number of mouse clicks associated with the event.
   *
   * \return the number of mouse clicks associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto clicks() const noexcept -> Uint8 { return mEvent.clicks; }

  /**
   * \brief Returns the x-coordinate of the mouse relative to the window.
   *
   * \return the x-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x() const noexcept -> Sint32 { return mEvent.x; }

  /**
   * \brief Returns the y-coordinate of the mouse relative to the window.
   *
   * \return the y-coordinate of the mouse relative to the window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y() const noexcept -> Sint32 { return mEvent.y; }
};

/// \name SDL event conversions
/// \{

template <>
inline auto AsSDLEvent(const EventBase<SDL_MouseButtonEvent>& event) -> SDL_Event
{
  SDL_Event e;
  e.button = event.get();
  return e;
}

/// \} End of SDL event conversions

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_EVENTS_MOUSE_BUTTON_EVENT_HPP_
