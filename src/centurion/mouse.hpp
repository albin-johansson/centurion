#ifndef CENTURION_MOUSE_HPP_
#define CENTURION_MOUSE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "core/common.hpp"
#include "core/exception.hpp"
#include "core/features.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "math.hpp"
#include "video/surface.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

enum class SystemCursor {
  Arrow = SDL_SYSTEM_CURSOR_ARROW,
  IBeam = SDL_SYSTEM_CURSOR_IBEAM,
  Wait = SDL_SYSTEM_CURSOR_WAIT,
  Crosshair = SDL_SYSTEM_CURSOR_CROSSHAIR,
  WaitArrow = SDL_SYSTEM_CURSOR_WAITARROW,
  Size_NW_SE = SDL_SYSTEM_CURSOR_SIZENWSE,
  Size_NE_SW = SDL_SYSTEM_CURSOR_SIZENESW,
  Size_W_E = SDL_SYSTEM_CURSOR_SIZEWE,
  Size_N_S = SDL_SYSTEM_CURSOR_SIZENS,
  SizeAll = SDL_SYSTEM_CURSOR_SIZEALL,
  No = SDL_SYSTEM_CURSOR_NO,
  Hand = SDL_SYSTEM_CURSOR_HAND
};

enum class mouse_button : Uint8 {
  left = SDL_BUTTON_LEFT,
  middle = SDL_BUTTON_MIDDLE,
  right = SDL_BUTTON_RIGHT,
  x1 = SDL_BUTTON_X1,
  x2 = SDL_BUTTON_X2
};

/* Provides information about the mouse state. */
class mouse final {
 public:
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
      const Uint32 mask = SDL_GetMouseState(&m_mouseX, &m_mouseY);
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
  void update(const Area size) noexcept { update(size.width, size.height); }

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
  void set_logical_size(const Area size) noexcept
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
  [[nodiscard]] auto x() const noexcept -> int { return m_mouseX; }

  /**
   * \brief Returns the y-coordinate of the mouse.
   *
   * \return the y-coordinate of the mouse.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto y() const noexcept -> int { return m_mouseY; }

  /**
   * \brief Returns the position of the mouse.
   *
   * \return the current position of the mouse cursor.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto position() const noexcept -> Point { return {m_mouseX, m_mouseY}; }

  /**
   * \brief Returns the logical width used by the mouse state instance.
   *
   * \return the logical width used by the mouse state instance, 1 is used by default.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto logical_width() const noexcept -> int { return m_logicalWidth; }

  /**
   * \brief Returns the logical height used by the mouse state instance.
   *
   * \return the logical height used by the mouse state instance, 1 is used by default.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto logical_height() const noexcept -> int { return m_logicalHeight; }

  /**
   * \brief Returns the logical size used by the mouse state instance.
   *
   * \return the logical size used.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto logical_size() const noexcept -> Area
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
  [[nodiscard]] auto is_left_button_pressed() const noexcept -> bool { return m_leftPressed; }

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

template <typename T>
class BasicCursor;

using Cursor = BasicCursor<detail::OwnerTag>;
using CursorHandle = BasicCursor<detail::HandleTag>;

template <typename T>
class BasicCursor final {
 public:
  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicCursor(const SystemCursor cursor)
      : mCursor{SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor))}
  {
    if (!mCursor) {
      throw SDLError{};
    }
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  BasicCursor(const Surface& surface, const Point& hotspot)
      : mCursor{SDL_CreateColorCursor(surface.get(), hotspot.GetX(), hotspot.GetY())}
  {
    if (!mCursor) {
      throw SDLError{};
    }
  }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit BasicCursor(SDL_Cursor* cursor) noexcept : mCursor{cursor}
  {}

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit BasicCursor(const Cursor& owner) noexcept : mCursor{owner.get()}
  {}

  void Enable() noexcept { SDL_SetCursor(mCursor); }

  /* Resets the active cursor to the system default. */
  static void Reset() noexcept { SDL_SetCursor(SDL_GetDefaultCursor()); }

  static void ForceRedraw() noexcept { SDL_SetCursor(nullptr); }

  static void SetVisible(const bool visible) noexcept
  {
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
  }

  [[nodiscard]] static auto GetDefault() noexcept -> CursorHandle
  {
    return CursorHandle{SDL_GetDefaultCursor()};
  }

  [[nodiscard]] static auto GetCurrent() noexcept -> CursorHandle
  {
    return CursorHandle{SDL_GetCursor()};
  }

  [[nodiscard]] static auto IsVisible() noexcept -> bool
  {
    return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
  }

  [[nodiscard]] constexpr static auto GetSystemCursors() noexcept -> int
  {
    return SDL_NUM_SYSTEM_CURSORS;
  }

  /* Indicates whether this cursor is currently active. */
  [[nodiscard]] auto IsEnabled() const noexcept -> bool { return SDL_GetCursor() == get(); }

  [[nodiscard]] auto get() const noexcept -> SDL_Cursor* { return mCursor.get(); }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mCursor != nullptr;
  }

 private:
  detail::Pointer<T, SDL_Cursor> mCursor;
};

[[nodiscard]] inline auto to_string(const mouse& mouse) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("mouse{{x: {}, y: {}}}", mouse.x(), mouse.y());
#else
  return "mouse{x: " + std::to_string(mouse.x()) + ", y: " + std::to_string(mouse.y()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const mouse& mouse) -> std::ostream&
{
  return stream << to_string(mouse);
}

[[nodiscard]] constexpr auto to_string(const mouse_button button) -> std::string_view
{
  switch (button) {
    case mouse_button::left:
      return "left";

    case mouse_button::middle:
      return "middle";

    case mouse_button::right:
      return "right";

    case mouse_button::x1:
      return "x1";

    case mouse_button::x2:
      return "x2";

    default:
      throw Error{"Did not recognize mouse button!"};
  }
}

inline auto operator<<(std::ostream& stream, const mouse_button button) -> std::ostream&
{
  return stream << to_string(button);
}

[[nodiscard]] constexpr auto to_string(const SystemCursor cursor) -> std::string_view
{
  switch (cursor) {
    case SystemCursor::Arrow:
      return "Arrow";

    case SystemCursor::IBeam:
      return "IBeam";

    case SystemCursor::Wait:
      return "Wait";

    case SystemCursor::Crosshair:
      return "Crosshair";

    case SystemCursor::WaitArrow:
      return "WaitArrow";

    case SystemCursor::Size_NW_SE:
      return "Size_NW_SE";

    case SystemCursor::Size_NE_SW:
      return "Size_NE_SW";

    case SystemCursor::Size_W_E:
      return "Size_W_E";

    case SystemCursor::Size_N_S:
      return "Size_N_S";

    case SystemCursor::SizeAll:
      return "SizeAll";

    case SystemCursor::No:
      return "No";

    case SystemCursor::Hand:
      return "Hand";

    default:
      throw Error{"Did not recognize system cursor!"};
  }
}

inline auto operator<<(std::ostream& stream, const SystemCursor cursor) -> std::ostream&
{
  return stream << to_string(cursor);
}

}  // namespace cen

#endif  // CENTURION_MOUSE_HPP_