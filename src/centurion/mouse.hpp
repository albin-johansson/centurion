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
#include "render.hpp"
#include "surface.hpp"
#include "window.hpp"

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
   * \brief Moves the mouse cursor to the specified position.
   *
   * \param pos the global mouse position destination.
   *
   * \return `success` if the mouse cursor was successfully moved; `failure` otherwise.
   */
  static auto warp(const ipoint& pos) noexcept -> result
  {
    return SDL_WarpMouseGlobal(pos.x(), pos.y()) == 0;
  }

  /**
   * \brief Moves the mouse cursor to the specified position in the focused window.
   *
   * \param pos a coordinate in the focused window.
   */
  static void warp_in_window(const ipoint& pos) noexcept
  {
    SDL_WarpMouseInWindow(nullptr, pos.x(), pos.y());
  }

  /**
   * \brief Moves the mouse cursor to the specified position in a window.
   *
   * \param window the source window.
   * \param pos a coordinate in the window.
   */
  template <typename T>
  static void warp_in_window(const basic_window<T>& window, const ipoint& pos) noexcept
  {
    SDL_WarpMouseInWindow(window.get(), pos.x(), pos.y());
  }

  /**
   * \brief Sets whether relative mouse mode is enabled.
   *
   * \param enabled `true` to enable relative mouse mode; `false` otherwise.
   *
   * \return `success` if the mouse mode was updated; `failure` otherwise.
   *
   * \see `SDL_SetRelativeMouseMode`
   */
  static auto set_relative_mode(const bool enabled) noexcept -> result
  {
    return SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE) == 0;
  }

  /**
   * \brief Indicates whether relative mouse mode is enabled.
   *
   * \return `true` if relative mode is enabled; `false` otherwise.
   */
  [[nodiscard]] static auto is_relative_mode_enabled() noexcept -> bool
  {
    return SDL_GetRelativeMouseMode() == SDL_TRUE;
  }

  /**
   * \brief Updates the mouse state.
   *
   * \note This function just reads the state reported by `SDL_GetMouseState()`, it does not
   * account for any scaling, etc.
   */
  void update() noexcept
  {
    mPreviousMask = mCurrentMask;
    mPreviousPosition = mCurrentPosition;

    int mx{};
    int my{};
    mCurrentMask = SDL_GetMouseState(&mx, &my);

    mCurrentPosition.set_x(mx);
    mCurrentPosition.set_y(my);
  }

#if SDL_VERSION_ATLEAST(2, 0, 18)

  /**
   * \brief Updates the mouse state according to the logical size of a renderer.
   *
   * \details Use this function if you are making use of logical renderer coordinates.
   *
   * \param renderer the current renderer.
   *
   * \atleastsdl 2.0.18
   */
  template <typename T>
  void update(const basic_renderer<T>& renderer) noexcept
  {
    mPreviousMask = mCurrentMask;
    mPreviousPosition = mCurrentPosition;

    int mx{};
    int my{};
    mCurrentMask = SDL_GetMouseState(&mx, &my);

    const auto logicalSize = renderer.logical_size();
    if (logicalSize.width != 0 && logicalSize.height != 0) {
      mCurrentPosition = renderer.to_logical(mx, my);
    }
    else {
      /* No logical size has been set for the renderer */
      mCurrentPosition.set_x(mx);
      mCurrentPosition.set_y(my);
    }
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 18)

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

  /**
   * \brief Returns the position of the mouse relative to the currently focused window.
   *
   * \return the mouse position.
   */
  [[nodiscard]] static auto position_relative_window() noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetMouseState(&x, &y);
    return {x, y};
  }

  /**
   * \brief Returns the position of the mouse relative to the desktop environment.
   *
   * \return the mouse position.
   */
  [[nodiscard]] static auto position_relative_desktop() noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetGlobalMouseState(&x, &y);
    return {x, y};
  }

  /**
   * \brief Returns the position delta.
   *
   * \return the difference in position.
   */
  [[nodiscard]] static auto delta() noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetRelativeMouseState(&x, &y);
    return {x, y};
  }

  /**
   * \brief Indicates whether the mouse is haptic.
   *
   * \return `true` if the mouse has haptic features; `false` otherwise.
   */
  [[nodiscard]] static auto is_haptic() noexcept -> bool
  {
    return SDL_MouseIsHaptic() == SDL_TRUE;
  }

 private:
  ipoint mCurrentPosition;
  ipoint mPreviousPosition;
  uint32 mCurrentMask{};
  uint32 mPreviousMask{};

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