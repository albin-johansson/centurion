#ifndef CENTURION_VIDEO_CURSOR_HPP_
#define CENTURION_VIDEO_CURSOR_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string_view>  // string_view

#include "../core/exception.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../math.hpp"
#include "surface.hpp"

namespace cen {

/// \addtogroup video
/// \{

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

template <typename T>
class BasicCursor;

using Cursor = BasicCursor<detail::owning_type>;
using CursorHandle = BasicCursor<detail::handle_type>;

template <typename T>
class BasicCursor final {
 public:
  template <typename TT = T, detail::is_owner<TT> = 0>
  explicit BasicCursor(const SystemCursor cursor)
      : mCursor{SDL_CreateSystemCursor(static_cast<SDL_SystemCursor>(cursor))}
  {
    if (!mCursor) {
      throw SDLError{};
    }
  }

  template <typename TT = T, detail::is_owner<TT> = 0>
  BasicCursor(const Surface& surface, const Point& hotspot)
      : mCursor{SDL_CreateColorCursor(surface.get(), hotspot.GetX(), hotspot.GetY())}
  {
    if (!mCursor) {
      throw SDLError{};
    }
  }

  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit BasicCursor(SDL_Cursor* cursor) noexcept : mCursor{cursor}
  {}

  template <typename TT = T, detail::is_handle<TT> = 0>
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

  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mCursor != nullptr;
  }

 private:
  detail::Pointer<T, SDL_Cursor> mCursor;
};

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

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_VIDEO_CURSOR_HPP_