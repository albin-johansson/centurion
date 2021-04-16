#ifndef CENTURION_MOUSE_WHEEL_EVENT_HEADER
#define CENTURION_MOUSE_WHEEL_EVENT_HEADER

#include <SDL.h>

#include "../misc/integers.hpp"
#include "common_event.hpp"

namespace cen {

/// \addtogroup event
/// \{

/**
 * \enum mouse_wheel_direction
 *
 * \brief Mirrors the the `SDL_MouseWheelDirection` enum.
 *
 * \see `SDL_MouseWheelDirection`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
enum class mouse_wheel_direction
{
  normal = SDL_MOUSEWHEEL_NORMAL,   ///< The scroll direction is normal
  flipped = SDL_MOUSEWHEEL_FLIPPED  ///< The scroll direction is flipped natural
};

/**
 * \class mouse_wheel_event
 *
 * \brief Represents events triggered when a user moves the mouse wheel.
 *
 * \see `SDL_MouseWheelEvent`
 *
 * \since 4.0.0
 *
 * \headerfile event.hpp
 */
class mouse_wheel_event final : public common_event<SDL_MouseWheelEvent>
{
 public:
  /**
   * \brief Creates a mouse wheel event.
   *
   * \since 4.0.0
   */
  mouse_wheel_event() noexcept : common_event{event_type::mouse_wheel}
  {}

  /**
   * \brief Creates a `MouseMotionEvent` that is based on the supplied SDL
   * event.
   *
   * \param event the SDL event that will be copied.
   *
   * \since 4.0.0
   */
  explicit mouse_wheel_event(const SDL_MouseWheelEvent& event) noexcept
      : common_event{event}
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
   * \brief Sets the horizontally scrolled distance.
   *
   * \details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * \param xScroll the horizontally scrolled distance.
   *
   * \since 4.0.0
   */
  void set_x_scroll(const i32 xScroll) noexcept
  {
    m_event.x = xScroll;
  }

  /**
   * \brief Sets the vertically scrolled distance.
   *
   * \details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * \param yScroll the vertically scrolled distance.
   *
   * \since 4.0.0
   */
  void set_y_scroll(const i32 yScroll) noexcept
  {
    m_event.y = yScroll;
  }

  /**
   * \brief Sets the mouse wheel direction mode associated with the event.
   *
   * \param direction the mouse wheel direction mode associated with the event.
   *
   * \since 4.0.0
   */
  void set_direction(const mouse_wheel_direction direction) noexcept
  {
    m_event.direction = static_cast<u32>(direction);
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
   * \brief Returns the mouse instance ID, or `SDL_TOUCH_MOUSEID` if the event
   * was triggered by a touch input device.
   *
   * \return the mouse instance ID, or `SDL_TOUCH_MOUSEID`.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto which() const noexcept -> u32
  {
    return m_event.which;
  }

  /**
   * \brief Returns the horizontally scrolled distance
   *
   * \details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * \return the horizontally scrolled distance.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto x_scroll() const noexcept -> i32
  {
    return m_event.x;
  }

  /**
   * \brief Returns the vertically scrolled distance.
   *
   * \details A positive value indicates that the user scrolled to the right
   * and a negative value indicates that the user scrolled to the left.
   *
   * \return the vertically scrolled distance.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto y_scroll() const noexcept -> i32
  {
    return m_event.y;
  }

  /**
   * \brief Returns the mouse wheel direction mode associated with the event.
   *
   * \return the mouse wheel direction mode associated with the event.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto direction() const noexcept -> mouse_wheel_direction
  {
    return static_cast<mouse_wheel_direction>(m_event.direction);
  }
};

template <>
inline auto as_sdl_event(const common_event<SDL_MouseWheelEvent>& event)
    -> SDL_Event
{
  SDL_Event e;
  e.wheel = event.get();
  return e;
}

/**
 * \brief Indicates whether or not two mouse wheel direction values are equal.
 *
 * \param lhs the left-hand side mouse wheel direction value.
 * \param rhs the right-hand side mouse wheel direction value.
 *
 * \return `true` if the two values are equal; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator==(
    const mouse_wheel_direction lhs,
    const SDL_MouseWheelDirection rhs) noexcept -> bool
{
  return lhs == static_cast<mouse_wheel_direction>(rhs);
}

/// \copydoc operator==(mouse_wheel_direction, SDL_MouseWheelDirection)
[[nodiscard]] constexpr auto operator==(
    const SDL_MouseWheelDirection lhs,
    const mouse_wheel_direction rhs) noexcept -> bool
{
  return rhs == lhs;
}

/**
 * \brief Indicates whether or not two mouse wheel direction values aren't
 * equal.
 *
 * \param lhs the left-hand side mouse wheel direction value.
 * \param rhs the right-hand side mouse wheel direction value.
 *
 * \return `true` if the two values aren't equal; `false` otherwise.
 *
 * \since 4.0.0
 */
[[nodiscard]] constexpr auto operator!=(
    const mouse_wheel_direction lhs,
    const SDL_MouseWheelDirection rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \copydoc operator!=(mouse_wheel_direction, SDL_MouseWheelDirection)
[[nodiscard]] constexpr auto operator!=(
    const SDL_MouseWheelDirection lhs,
    const mouse_wheel_direction rhs) noexcept -> bool
{
  return !(lhs == rhs);
}

/// \} End of group event

}  // namespace cen

#endif  // CENTURION_MOUSE_WHEEL_EVENT_HEADER
