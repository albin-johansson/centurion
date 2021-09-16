#ifndef CENTURION_MOUSE_HEADER
#define CENTURION_MOUSE_HEADER

#include <ostream>  // ostream
#include <string>   // string, to_string

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/integers.hpp"
#include "../detail/max.hpp"
#include "../math/area.hpp"
#include "../math/point.hpp"

namespace cen {

/// \addtogroup input
/// \{

/**
 * \class mouse
 *
 * \brief Provides information about the mouse state, which is an alternative to dealing
 * with mouse events.
 *
 * \since 3.0.0
 *
 * \see `keyboard`
 */
class mouse final
{
 public:
  /**
   * \brief Creates a `mouse` instance.
   *
   * \since 3.0.0
   */
  mouse() noexcept = default;

  /**
   * \brief Updates the mouse state. The window width and height will be adjusted to be at
   * least 1.
   *
   * \param windowWidth the current window width, set to 1 by default.
   * \param windowHeight the current window height, set to 1 by default.
   *
   * \since 3.0.0
   */
  void update(const int windowWidth = 1, const int windowHeight = 1) noexcept
  {
    m_oldX = m_mouseX;
    m_oldY = m_mouseY;
    m_prevLeftPressed = m_leftPressed;
    m_prevRightPressed = m_rightPressed;

    {
      const u32 mask = SDL_GetMouseState(&m_mouseX, &m_mouseY);
      m_leftPressed = mask & SDL_BUTTON(SDL_BUTTON_LEFT);
      m_rightPressed = mask & SDL_BUTTON(SDL_BUTTON_RIGHT);
    }

    {
      const auto xRatio =
          static_cast<float>(m_mouseX) / static_cast<float>(detail::max(windowWidth, 1));
      const auto adjustedX = xRatio * static_cast<float>(m_logicalWidth);

      const auto yRatio =
          static_cast<float>(m_mouseY) / static_cast<float>(detail::max(windowHeight, 1));
      const auto adjustedY = yRatio * static_cast<float>(m_logicalHeight);

      m_mouseX = static_cast<int>(adjustedX);
      m_mouseY = static_cast<int>(adjustedY);
    }
  }

  /**
   * \brief Updates the mouse state.
   *
   * \param size the size of the window.
   *
   * \since 5.3.0
   */
  void update(const iarea size) noexcept
  {
    update(size.width, size.height);
  }

  /**
   * \brief Resets the screen and logical dimensions of the mouse state instance.
   *
   * \since 3.0.0
   */
  void reset() noexcept
  {
    m_logicalWidth = 1;
    m_logicalHeight = 1;
  }

  /**
   * \brief Sets the logical width that will be used to determine the mouse position.
   *
   * \details The supplied value will be adjusted to be at least 1.
   *
   * \param logicalWidth the logical width that will be used to determine the mouse
   * position.
   *
   * \since 3.0.0
   */
  void set_logical_width(const int logicalWidth) noexcept
  {
    m_logicalWidth = detail::max(logicalWidth, 1);
  }

  /**
   * \brief Sets the logical height that will be used to determine the mouse position.
   *
   * \details The supplied value will be adjusted to be at least 1.
   *
   * \param logicalHeight the logical height that will be used to determine the mouse
   * position.
   *
   * \since 3.0.0
   */
  void set_logical_height(const int logicalHeight) noexcept
  {
    m_logicalHeight = detail::max(logicalHeight, 1);
  }

  /**
   * \brief Sets the current logical window size.
   *
   * \param size the logical size that will be used to determine the mouse position.
   *
   * \since 5.3.0
   */
  void set_logical_size(const iarea size) noexcept
  {
    set_logical_width(size.width);
    set_logical_height(size.height);
  }

  /**
   * \brief Indicates whether or not the left mouse button was released.
   *
   * \return `true` if the left mouse button was released; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto was_left_button_released() const noexcept -> bool
  {
    return !m_leftPressed && m_prevLeftPressed;
  }

  /**
   * \brief Indicates whether or not the right mouse button was released.
   *
   * \return `true` if the right mouse button was released; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto was_right_button_released() const noexcept -> bool
  {
    return !m_rightPressed && m_prevRightPressed;
  }

  /**
   * \brief Indicates whether or not the mouse was moved.
   *
   * \return `true` if the mouse was moved; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto was_moved() const noexcept -> bool
  {
    return (m_mouseX != m_oldX) || (m_mouseY != m_oldY);
  }

  /**
   * \brief Returns the x-coordinate of the mouse.
   *
   * \return the x-coordinate of the mouse.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto x() const noexcept -> int
  {
    return m_mouseX;
  }

  /**
   * \brief Returns the y-coordinate of the mouse.
   *
   * \return the y-coordinate of the mouse.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto y() const noexcept -> int
  {
    return m_mouseY;
  }

  /**
   * \brief Returns the position of the mouse.
   *
   * \return the current position of the mouse cursor.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto position() const noexcept -> ipoint
  {
    return {m_mouseX, m_mouseY};
  }

  /**
   * \brief Returns the logical width used by the mouse state instance.
   *
   * \return the logical width used by the mouse state instance, 1 is used by default.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto logical_width() const noexcept -> int
  {
    return m_logicalWidth;
  }

  /**
   * \brief Returns the logical height used by the mouse state instance.
   *
   * \return the logical height used by the mouse state instance, 1 is used by default.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto logical_height() const noexcept -> int
  {
    return m_logicalHeight;
  }

  /**
   * \brief Returns the logical size used by the mouse state instance.
   *
   * \return the logical size used.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto logical_size() const noexcept -> iarea
  {
    return {m_logicalWidth, m_logicalHeight};
  }

  /**
   * \brief Indicates whether or not the left mouse button is currently pressed.
   *
   * \return `true` if the left mouse button is pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_left_button_pressed() const noexcept -> bool
  {
    return m_leftPressed;
  }

  /**
   * \brief Indicates whether or not the right mouse button is currently pressed.
   *
   * \return `true` if the right mouse button is pressed; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_right_button_pressed() const noexcept -> bool
  {
    return m_rightPressed;
  }

 private:
  int m_mouseX{};
  int m_mouseY{};
  int m_oldX{};
  int m_oldY{};
  int m_logicalWidth{1};
  int m_logicalHeight{1};
  bool m_leftPressed{};
  bool m_rightPressed{};
  bool m_prevLeftPressed{};
  bool m_prevRightPressed{};
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a mouse.
 *
 * \param mouse the mouse instance that will be converted.
 *
 * \return a string that represents the mouse.
 *
 * \since 6.2.0
 */
[[nodiscard]] inline auto to_string(const mouse& mouse) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("mouse{{x: {}, y: {}}}", mouse.x(), mouse.y());
#else
  return "mouse{x: " + std::to_string(mouse.x()) + ", y: " + std::to_string(mouse.y()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a mouse.
 *
 * \param stream the output stream that will be used.
 * \param mouse the mouse that will be printed.
 *
 * \return the used stream.
 *
 * \since 6.2.0
 */
inline auto operator<<(std::ostream& stream, const mouse& mouse) -> std::ostream&
{
  return stream << to_string(mouse);
}

/// \} End of streaming

/// \} End of group input

}  // namespace cen

#endif  // CENTURION_MOUSE_HEADER