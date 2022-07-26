/*
 * MIT License
 *
 * Copyright (c) 2019-2022 Albin Johansson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

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

enum class mouse_button : uint8
{
  left = SDL_BUTTON_LEFT,
  middle = SDL_BUTTON_MIDDLE,
  right = SDL_BUTTON_RIGHT,
  x1 = SDL_BUTTON_X1,
  x2 = SDL_BUTTON_X2
};

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

/// Provides a view into the mouse state.
class mouse final
{
 public:
  mouse() noexcept = default;

  static auto warp(const ipoint& pos) noexcept -> result
  {
    return SDL_WarpMouseGlobal(pos.x(), pos.y()) == 0;
  }

  static void warp_in_window(const ipoint& pos) noexcept
  {
    SDL_WarpMouseInWindow(nullptr, pos.x(), pos.y());
  }

  template <typename T>
  static void warp_in_window(const basic_window<T>& window, const ipoint& pos) noexcept
  {
    SDL_WarpMouseInWindow(window.get(), pos.x(), pos.y());
  }

  static auto set_relative_mode(const bool enabled) noexcept -> result
  {
    return SDL_SetRelativeMouseMode(enabled ? SDL_TRUE : SDL_FALSE) == 0;
  }

  [[nodiscard]] static auto is_relative_mode_enabled() noexcept -> bool
  {
    return SDL_GetRelativeMouseMode() == SDL_TRUE;
  }

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

  [[nodiscard]] auto position() const noexcept -> ipoint { return mCurrentPosition; }

  [[nodiscard]] auto x() const noexcept -> int { return mCurrentPosition.x(); }
  [[nodiscard]] auto y() const noexcept -> int { return mCurrentPosition.y(); }

  [[nodiscard]] auto is_left_pressed() const noexcept -> bool
  {
    return is_pressed(SDL_BUTTON_LMASK);
  }

  [[nodiscard]] auto is_middle_pressed() const noexcept -> bool
  {
    return is_pressed(SDL_BUTTON_MMASK);
  }

  [[nodiscard]] auto is_right_pressed() const noexcept -> bool
  {
    return is_pressed(SDL_BUTTON_RMASK);
  }

  [[nodiscard]] auto was_left_released() const noexcept -> bool
  {
    return was_released(SDL_BUTTON_LMASK);
  }

  [[nodiscard]] auto was_middle_released() const noexcept -> bool
  {
    return was_released(SDL_BUTTON_MMASK);
  }

  [[nodiscard]] auto was_right_released() const noexcept -> bool
  {
    return was_released(SDL_BUTTON_RMASK);
  }

  [[nodiscard]] auto was_moved() const noexcept -> bool
  {
    return (mCurrentPosition.x() != mPreviousPosition.x()) ||
           (mCurrentPosition.y() != mPreviousPosition.y());
  }

  [[nodiscard]] static auto position_relative_window() noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetMouseState(&x, &y);
    return {x, y};
  }

  [[nodiscard]] static auto position_relative_desktop() noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetGlobalMouseState(&x, &y);
    return {x, y};
  }

  [[nodiscard]] static auto delta() noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetRelativeMouseState(&x, &y);
    return {x, y};
  }

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

template <typename T>
class basic_cursor;

using cursor = basic_cursor<detail::owner_tag>;
using cursor_handle = basic_cursor<detail::handle_tag>;

/**
 * Represents a mouse cursor.
 *
 * \see cursor
 * \see cursor_handle
 */
template <typename T>
class basic_cursor final
{
 public:
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_cursor(const system_cursor cursor)
      : mCursor{SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor))}
  {
    if (!mCursor) {
      throw sdl_error{};
    }
  }

  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  basic_cursor(const surface& surface, const ipoint& hotspot)
      : mCursor{SDL_CreateColorCursor(surface.get(), hotspot.x(), hotspot.y())}
  {
    if (!mCursor) {
      throw sdl_error{};
    }
  }

  /**
   * Creates a cursor handle.
   *
   * This constructor is only available for handles since it would otherwise be all too easy to
   * introduce subtle bugs by creating owning cursors from pointers obtained from
   * SDL_GetCursor() or SDL_GetDefaultCursor(), which should not be freed.
   *
   * \param cursor the associated cursor.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_cursor(SDL_Cursor* cursor) noexcept : mCursor{cursor}
  {}

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_cursor(const cursor& owner) noexcept : mCursor{owner.get()}
  {}

  void enable() noexcept { SDL_SetCursor(mCursor); }

  /**
   * \brief Indicates whether this cursor is currently active.
   *
   * Note, this function checks whether or not the associated cursor is active by comparing the
   * pointer obtained from SDL_GetCursor() with the internal pointer, so different cursors of
   * the same type will not be deemed equal by this function.
   *
   * \return true if the cursor is enabled; false otherwise.
   */
  [[nodiscard]] auto is_enabled() const noexcept -> bool { return SDL_GetCursor() == get(); }

  static void reset() noexcept { SDL_SetCursor(SDL_GetDefaultCursor()); }

  static void force_redraw() noexcept { SDL_SetCursor(nullptr); }

  static void set_visible(const bool visible) noexcept
  {
    SDL_ShowCursor(visible ? SDL_ENABLE : SDL_DISABLE);
  }

  [[nodiscard]] static auto visible() noexcept -> bool
  {
    return SDL_ShowCursor(SDL_QUERY) == SDL_ENABLE;
  }

  [[nodiscard]] static auto get_default() noexcept -> cursor_handle
  {
    return cursor_handle{SDL_GetDefaultCursor()};
  }

  [[nodiscard]] static auto get_current() noexcept -> cursor_handle
  {
    return cursor_handle{SDL_GetCursor()};
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Cursor* { return mCursor.get(); }

  /// Indicates whether a handle holds a non-null pointer.
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mCursor != nullptr;
  }

 private:
  detail::pointer<T, SDL_Cursor> mCursor;
};

}  // namespace cen

#endif  // CENTURION_MOUSE_HPP_