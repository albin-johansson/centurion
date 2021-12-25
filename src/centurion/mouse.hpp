#ifndef CENTURION_MOUSE_HPP_
#define CENTURION_MOUSE_HPP_

#include <SDL.h>

#include <ostream>      // ostream
#include <string>       // string, to_string
#include <string_view>  // string_view

#include "common.hpp"
#include "features.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "math.hpp"
#include "surface.hpp"

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

enum class MouseButton : Uint8 {
  Left = SDL_BUTTON_LEFT,
  Middle = SDL_BUTTON_MIDDLE,
  Right = SDL_BUTTON_RIGHT,
  X1 = SDL_BUTTON_X1,
  X2 = SDL_BUTTON_X2
};

/* Provides information about the mouse state. */
class Mouse final {
 public:
  Mouse() noexcept = default;

  void Update(const Area& windowSize) noexcept
  {
    mPreviousPosition = mCurrentPosition;
    mPreviousMask = mCurrentMask;

    int x{};
    int y{};
    mCurrentMask = SDL_GetMouseState(&x, &y);

    {
      const auto xRatio =
          static_cast<float>(x) / static_cast<float>(detail::max(windowSize.width, 1));
      const auto yRatio =
          static_cast<float>(y) / static_cast<float>(detail::max(windowSize.height, 1));

      mCurrentPosition.SetX(static_cast<int>(xRatio * mLogicalSize.width));
      mCurrentPosition.SetY(static_cast<int>(yRatio * mLogicalSize.height));
    }
  }

  void ResetLogicalSize() noexcept
  {
    mLogicalSize.width = 1;
    mLogicalSize.height = 1;
  }

  void SetLogicalSize(const FArea& size) noexcept
  {
    mLogicalSize.width = detail::max(size.width, 1.0f);
    mLogicalSize.height = detail::max(size.height, 1.0f);
  }

  [[nodiscard]] auto GetPosition() const noexcept -> Point { return mCurrentPosition; }

  [[nodiscard]] auto GetX() const noexcept -> int { return mCurrentPosition.GetX(); }

  [[nodiscard]] auto GetY() const noexcept -> int { return mCurrentPosition.GetY(); }

  [[nodiscard]] auto GetLogicalSize() const noexcept -> FArea { return mLogicalSize; }

  [[nodiscard]] auto GetLogicalWidth() const noexcept -> float { return mLogicalSize.width; }

  [[nodiscard]] auto GetLogicalHeight() const noexcept -> float { return mLogicalSize.height; }

  [[nodiscard]] auto IsLeftButtonPressed() const noexcept -> bool
  {
    return IsButtonPressed(SDL_BUTTON_LMASK);
  }

  [[nodiscard]] auto IsMiddleButtonPressed() const noexcept -> bool
  {
    return IsButtonPressed(SDL_BUTTON_MMASK);
  }

  [[nodiscard]] auto IsRightButtonPressed() const noexcept -> bool
  {
    return IsButtonPressed(SDL_BUTTON_RMASK);
  }

  [[nodiscard]] auto WasLeftButtonReleased() const noexcept -> bool
  {
    return WasButtonReleased(SDL_BUTTON_LMASK);
  }

  [[nodiscard]] auto WasMiddleButtonReleased() const noexcept -> bool
  {
    return WasButtonReleased(SDL_BUTTON_MMASK);
  }

  [[nodiscard]] auto WasRightButtonReleased() const noexcept -> bool
  {
    return WasButtonReleased(SDL_BUTTON_RMASK);
  }

  [[nodiscard]] auto WasMoved() const noexcept -> bool
  {
    return (mCurrentPosition.GetX() != mPreviousPosition.GetX()) ||
           (mCurrentPosition.GetY() != mPreviousPosition.GetY());
  }

 private:
  Point mCurrentPosition{};
  Point mPreviousPosition{};
  FArea mLogicalSize{1, 1};
  Uint32 mCurrentMask{};
  Uint32 mPreviousMask{};

  [[nodiscard]] auto IsButtonPressed(const Uint32 mask) const noexcept -> bool
  {
    return mCurrentMask & mask;
  }

  [[nodiscard]] auto WasButtonReleased(const Uint32 mask) const noexcept -> bool
  {
    return !(mCurrentMask & mask) && mPreviousMask & mask;
  }
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

[[nodiscard]] inline auto to_string(const Mouse& mouse) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Mouse(x: {}, y: {})", mouse.GetX(), mouse.GetY());
#else
  return "Mouse(x: " + std::to_string(mouse.GetX()) + ", y: " + std::to_string(mouse.GetY()) +
         ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

inline auto operator<<(std::ostream& stream, const Mouse& mouse) -> std::ostream&
{
  return stream << to_string(mouse);
}

[[nodiscard]] constexpr auto to_string(const MouseButton button) -> std::string_view
{
  switch (button) {
    case MouseButton::Left:
      return "left";

    case MouseButton::Middle:
      return "middle";

    case MouseButton::Right:
      return "right";

    case MouseButton::X1:
      return "x1";

    case MouseButton::X2:
      return "x2";

    default:
      throw Error{"Did not recognize mouse button!"};
  }
}

inline auto operator<<(std::ostream& stream, const MouseButton button) -> std::ostream&
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