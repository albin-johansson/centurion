#ifndef CENTURION_MOUSE_HPP_
#define CENTURION_MOUSE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "math.hpp"
#include "surface.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/**
 * \ingroup input
 * \defgroup mouse Mouse
 *
 * \brief Provides utilities related to mouse input.
 */

/// \addtogroup mouse
/// \{

/**
 * \brief Represents different standard system cursors.
 */
enum class system_cursor
{
  arrow = SDL_SYSTEM_CURSOR_ARROW,
  ibeam = SDL_SYSTEM_CURSOR_IBEAM,
  wait = SDL_SYSTEM_CURSOR_WAIT,
  crosshair = SDL_SYSTEM_CURSOR_CROSSHAIR,
  wait_arrow = SDL_SYSTEM_CURSOR_WAITARROW,
  size_nw_se = SDL_SYSTEM_CURSOR_SIZENWSE,
  size_ne_sw = SDL_SYSTEM_CURSOR_SIZENESW,
  size_we = SDL_SYSTEM_CURSOR_SIZEWE,
  size_ns = SDL_SYSTEM_CURSOR_SIZENS,
  size_all = SDL_SYSTEM_CURSOR_SIZEALL,
  no = SDL_SYSTEM_CURSOR_NO,
  hand = SDL_SYSTEM_CURSOR_HAND
};

/// \name System cursor functions
/// \{

/**
 * \brief Returns the number of system cursors.
 *
 * \return the system cursor count.
 */
[[nodiscard]] constexpr auto system_cursor_count() noexcept -> int
{
  return SDL_NUM_SYSTEM_CURSORS;
}

[[nodiscard]] constexpr auto to_string(const system_cursor cursor) -> std::string_view
{
  switch (cursor) {
    case system_cursor::arrow:
      return "arrow";

    case system_cursor::ibeam:
      return "ibeam";

    case system_cursor::wait:
      return "wait";

    case system_cursor::crosshair:
      return "crosshair";

    case system_cursor::wait_arrow:
      return "wait_arrow";

    case system_cursor::size_nw_se:
      return "size_nw_se";

    case system_cursor::size_ne_sw:
      return "size_ne_sw";

    case system_cursor::size_we:
      return "size_we";

    case system_cursor::size_ns:
      return "size_ns";

    case system_cursor::size_all:
      return "size_all";

    case system_cursor::no:
      return "no";

    case system_cursor::hand:
      return "hand";

    default:
      throw exception{"Did not recognize system cursor!"};
  }
}

inline auto operator<<(std::ostream& stream, const system_cursor cursor) -> std::ostream&
{
  return stream << to_string(cursor);
}

/// \} End of system cursor functions

/**
 * \brief Represents different mouse buttons.
 */
enum class mouse_button : uint8
{
  left = SDL_BUTTON_LEFT,
  middle = SDL_BUTTON_MIDDLE,
  right = SDL_BUTTON_RIGHT,
  x1 = SDL_BUTTON_X1,
  x2 = SDL_BUTTON_X2
};

/// \name Mouse button functions
/// \{

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
      throw exception{"Did not recognize mouse button!"};
  }
}

inline auto operator<<(std::ostream& stream, const mouse_button button) -> std::ostream&
{
  return stream << to_string(button);
}

/// \} End of mouse button functions

/**
 * \brief Provides a view into the mouse state.
 */
class mouse final
{
 public:
  mouse() noexcept = default;

  /**
   * \brief Updates the mouse state.
   *
   * \details The width and height will be adjusted to be at least 1.
   *
   * \param width the window width.
   * \param height the window height.
   */
  void update(const int width = 1, const int height = 1) noexcept
  {
    mPreviousPosition = mCurrentPosition;
    mPreviousMask = mCurrentMask;

    int mx{};
    int my{};
    mCurrentMask = SDL_GetMouseState(&mx, &my);

    const auto clampedWidth = detail::max(static_cast<float>(width), 1.0f);
    const auto clampedHeight = detail::max(static_cast<float>(height), 1.0f);

    const auto xRatio = static_cast<float>(mx) / clampedWidth;
    const auto yRatio = static_cast<float>(my) / clampedHeight;

    mCurrentPosition.set_x(static_cast<int>(xRatio * mLogicalSize.width));
    mCurrentPosition.set_y(static_cast<int>(yRatio * mLogicalSize.height));
  }

  /**
   * \brief Updates the mouse state.
   *
   * \details The width and height will be adjusted to be at least 1.
   *
   * \param size the window size.
   */
  void update(const iarea& size) noexcept { update(size.width, size.height); }

  /**
   * \brief Resets the logical size.
   */
  void reset_logical_size() noexcept
  {
    mLogicalSize.width = 1;
    mLogicalSize.height = 1;
  }

  /**
   * \brief Updates the logical size, used to calculate the mouse position.
   *
   * \details The width and height will be adjusted to be at least 1.
   *
   * \param size the logical size.
   */
  void set_logical_size(const farea& size) noexcept
  {
    mLogicalSize.width = detail::max(size.width, 1.0f);
    mLogicalSize.height = detail::max(size.height, 1.0f);
  }

  /**
   * \brief Returns the position of the mouse.
   *
   * \return the mouse position.
   */
  [[nodiscard]] auto position() const noexcept -> ipoint { return mCurrentPosition; }

  /**
   * \brief Returns the x-coordinate of the mouse.
   *
   * \return the mouse x-coordinate.
   */
  [[nodiscard]] auto x() const noexcept -> int { return mCurrentPosition.x(); }

  /**
   * \brief Returns the y-coordinate of the mouse.
   *
   * \return the mouse y-coordinate.
   */
  [[nodiscard]] auto y() const noexcept -> int { return mCurrentPosition.y(); }

  /**
   * \brief Returns the used logical size.
   *
   * \note The logical size is by default set to (1, 1).
   *
   * \return the logical size.
   */
  [[nodiscard]] auto logical_size() const noexcept -> farea { return mLogicalSize; }

  /**
   * \brief Returns the logical width used.
   *
   * \return the logical width.
   */
  [[nodiscard]] auto logical_width() const noexcept -> float { return mLogicalSize.width; }

  /**
   * \brief Returns the logical height used.
   *
   * \return the logical height.
   */
  [[nodiscard]] auto logical_height() const noexcept -> float { return mLogicalSize.height; }

  /**
   * \brief Indicates whether the left mouse button is pressed.
   *
   * \return `true` if the LMB is pressed; `false` otherwise.
   */
  [[nodiscard]] auto is_left_pressed() const noexcept -> bool
  {
    return is_pressed(SDL_BUTTON_LMASK);
  }

  /**
   * \brief Indicates whether the middle mouse button is pressed.
   *
   * \return `true` if the MMB is pressed; `false` otherwise.
   */
  [[nodiscard]] auto is_middle_pressed() const noexcept -> bool
  {
    return is_pressed(SDL_BUTTON_MMASK);
  }

  /**
   * \brief Indicates whether the right mouse button is pressed.
   *
   * \return `true` if the RMB is pressed; `false` otherwise.
   */
  [[nodiscard]] auto is_right_pressed() const noexcept -> bool
  {
    return is_pressed(SDL_BUTTON_RMASK);
  }

  /**
   * \brief Indicates whether the left mouse button was released.
   *
   * \return `true` if the LMB was released; `false` otherwise.
   */
  [[nodiscard]] auto was_left_released() const noexcept -> bool
  {
    return was_released(SDL_BUTTON_LMASK);
  }

  /**
   * \brief Indicates whether the middle mouse button was released.
   *
   * \return `true` if the MMB was released; `false` otherwise.
   */
  [[nodiscard]] auto was_middle_released() const noexcept -> bool
  {
    return was_released(SDL_BUTTON_MMASK);
  }

  /**
   * \brief Indicates whether the right mouse button was released.
   *
   * \return `true` if the RMB was released; `false` otherwise.
   */
  [[nodiscard]] auto was_right_released() const noexcept -> bool
  {
    return was_released(SDL_BUTTON_RMASK);
  }

  /**
   * \brief Indicates whether the mouse was moved.
   *
   * \return `true` if the mouse was moved; `false` otherwise.
   */
  [[nodiscard]] auto was_moved() const noexcept -> bool
  {
    return (mCurrentPosition.x() != mPreviousPosition.x()) ||
           (mCurrentPosition.y() != mPreviousPosition.y());
  }

 private:
  ipoint mCurrentPosition;
  ipoint mPreviousPosition;
  uint32 mCurrentMask{};
  uint32 mPreviousMask{};
  farea mLogicalSize{1, 1}; /* Logical size of (1, 1) has no effect */

  [[nodiscard]] auto is_pressed(const uint32 mask) const noexcept -> bool
  {
    return mCurrentMask & mask;
  }

  [[nodiscard]] auto was_released(const uint32 mask) const noexcept -> bool
  {
    return !(mCurrentMask & mask) && mPreviousMask & mask;
  }
};

/// \name Mouse functions
/// \{

[[nodiscard]] inline auto to_string(const mouse& mouse) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("mouse(x: {}, y: {})", mouse.x(), mouse.y());
#else
  return "mouse(x: " + std::to_string(mouse.x()) + ", y: " + std::to_string(mouse.y()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const mouse& mouse) -> std::ostream&
{
  return stream << to_string(mouse);
}

/// \} End of mouse functions

template <typename T>
class basic_cursor;

using cursor = basic_cursor<detail::owner_tag>;          ///< An owning cursor.
using cursor_handle = basic_cursor<detail::handle_tag>;  ///< A non-owning cursor.

/**
 * \brief Represents a mouse cursor.
 *
 * \ownerhandle `cursor`/`cursor_handle`
 *
 * \see `cursor`
 * \see `cursor_handle`
 *
 * \see `SDL_Cursor`
 */
template <typename T>
class basic_cursor final
{
 public:
  /// \name Construction
  /// \{

  /**
   * \brief Creates a system cursor.
   *
   * \param cursor the type of the cursor.
   *
   * \throws sdl_error if the cursor cannot be created.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_cursor(const system_cursor cursor)
      : mCursor{SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor))}
  {
    if (!mCursor) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a cursor based on a surface.
   *
   * \param surface the icon associated with the cursor.
   * \param hotspot the activation point in the surface for mouse clicks.
   *
   * \throws sdl_error if the cursor cannot be created.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  basic_cursor(const surface& surface, const ipoint& hotspot)
      : mCursor{SDL_CreateColorCursor(surface.get(), hotspot.x(), hotspot.y())}
  {
    if (!mCursor) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a cursor handle.
   *
   * \note This constructor is only available for handles since it would otherwise be too easy
   * to introduce subtle bugs by creating owning cursors from pointers obtained from
   * `SDL_GetCursor()` or `SDL_GetDefaultCursor()`, which should not be freed.
   *
   * \param cursor the associated cursor.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_cursor(SDL_Cursor* cursor) noexcept : mCursor{cursor}
  {}

  /**
   * \brief Creates a handle to an owning cursor.
   *
   * \param owner the associated owner.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_cursor(const cursor& owner) noexcept : mCursor{owner.get()}
  {}

  /// \} End of construction

  /// \name Cursor instance control
  /// \{

  /**
   * \brief Makes the cursor the active cursor.
   */
  void enable() noexcept { SDL_SetCursor(mCursor); }

  /**
   * \brief Indicates whether this cursor is currently active.
   *
   * \note This function checks whether or not the associated cursor is active by comparing the
   * pointer obtained from `SDL_GetCursor()` with the internal pointer, so different cursors of
   * the same type will not be deemed equal by this function.
   *
   * \return `true` if the cursor is enabled; `false` otherwise.
   */
  [[nodiscard]] auto is_enabled() const noexcept -> bool { return SDL_GetCursor() == get(); }

  /// \} End of cursor instance control

  /// \name Global cursor management
  /// \{

  /**
   * \brief Resets the active cursor to the system default.
   */
  static void reset() noexcept { SDL_SetCursor(SDL_GetDefaultCursor()); }

  /**
   * \brief Forces a cursor redraw.
   */
  static void force_redraw() noexcept { SDL_SetCursor(nullptr); }

  /**
   * \brief Sets whether any mouse cursor is visible.
   *
   * \param visible `true` if cursors should be visible; `false` otherwise.
   */
  static void set_visible(const bool visible) noexcept
  {
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
  }

  /**
   * \brief Indicates whether cursors are visible.
   *
   * \return `true` if cursors are visible; `false` otherwise.
   */
  [[nodiscard]] static auto visible() noexcept -> bool
  {
    return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
  }

  /// \} End of global cursor management

  /// \name Cursor getters
  /// \{

  /**
   * \brief Returns a handle to the default cursor for the system.
   *
   * \return a potentially empty cursor handle.
   */
  [[nodiscard]] static auto get_default() noexcept -> cursor_handle
  {
    return cursor_handle{SDL_GetDefaultCursor()};
  }

  /**
   * \brief Returns a handle to the current cursor.
   *
   * \return a potentially empty cursor handle.
   */
  [[nodiscard]] static auto get_current() noexcept -> cursor_handle
  {
    return cursor_handle{SDL_GetCursor()};
  }

  /// \} End of cursor getters

  /// \name Misc functions
  /// \{

  [[nodiscard]] auto get() const noexcept -> SDL_Cursor* { return mCursor.get(); }

  /**
   * \brief Indicates whether a handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mCursor != nullptr;
  }

  /// \} End of misc functions

 private:
  detail::pointer<T, SDL_Cursor> mCursor;
};

/// \} End of group mouse

}  // namespace cen

#endif  // CENTURION_MOUSE_HPP_