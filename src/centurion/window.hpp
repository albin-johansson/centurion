#ifndef CENTURION_WINDOW_HPP_
#define CENTURION_WINDOW_HPP_

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string, to_string
#include <utility>   // pair, make_pair, move

#include "common.hpp"
#include "features.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "math.hpp"
#include "render.hpp"
#include "surface.hpp"
#include "video.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

template <typename T>
class BasicWindow;

using Window = BasicWindow<detail::OwnerTag>;
using WindowHandle = BasicWindow<detail::HandleTag>;

template <typename T>
class BasicWindow final {
 public:
  enum WindowFlags : Uint32 {
    Fullscreen = SDL_WINDOW_FULLSCREEN,
    OpenGL = SDL_WINDOW_OPENGL,
    Shown = SDL_WINDOW_SHOWN,
    Hidden = SDL_WINDOW_HIDDEN,
    Borderless = SDL_WINDOW_BORDERLESS,
    Resizable = SDL_WINDOW_RESIZABLE,
    Minimized = SDL_WINDOW_MINIMIZED,
    Maximized = SDL_WINDOW_MAXIMIZED,
    InputGrabbed = SDL_WINDOW_INPUT_GRABBED,
    InputFocus = SDL_WINDOW_INPUT_FOCUS,
    MouseFocus = SDL_WINDOW_MOUSE_FOCUS,
    FullscreenDesktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
    Foreign = SDL_WINDOW_FOREIGN,
    AllowHighDPI = SDL_WINDOW_ALLOW_HIGHDPI,
    MouseCapture = SDL_WINDOW_MOUSE_CAPTURE,
    AlwaysOnTop = SDL_WINDOW_ALWAYS_ON_TOP,
    SkipTaskbar = SDL_WINDOW_SKIP_TASKBAR,
    Utility = SDL_WINDOW_UTILITY,
    Tooltip = SDL_WINDOW_TOOLTIP,
    PopupMenu = SDL_WINDOW_POPUP_MENU,
    Vulkan = SDL_WINDOW_VULKAN,

#if SDL_VERSION_ATLEAST(2, 0, 14)
    Metal = SDL_WINDOW_METAL
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
  };

  explicit BasicWindow(MaybeOwner<SDL_Window*> window) noexcept(detail::is_handle<T>)
      : mWindow{window}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mWindow) {
        throw Error{"Cannot create window from null pointer!"};
      }
    }
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicWindow(const char* title,
                       const Area size = GetDefaultSize(),
                       const Uint32 flags = GetDefaultFlags())
  {
    assert(title);

    if (size.width < 1) {
      throw Error{"Bad window width!"};
    }
    else if (size.height < 1) {
      throw Error{"Bad window height!"};
    }

    mWindow.reset(SDL_CreateWindow(title,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   size.width,
                                   size.height,
                                   flags));
    if (!mWindow) {
      throw SDLError{};
    }
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  explicit BasicWindow(const std::string& title,
                       const Area size = GetDefaultSize(),
                       const Uint32 flags = GetDefaultFlags())
      : BasicWindow{title.c_str(), size, flags}
  {}

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  BasicWindow() : BasicWindow{"Centurion"}
  {}

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit BasicWindow(const Window& owner) noexcept : mWindow{owner.get()}
  {}

  void Show() noexcept { SDL_ShowWindow(mWindow); }

  void Hide() noexcept { SDL_HideWindow(mWindow); }

  void Raise() noexcept { SDL_RaiseWindow(mWindow); }

  void Maximize() noexcept { SDL_MaximizeWindow(mWindow); }

  void Minimize() noexcept { SDL_MinimizeWindow(mWindow); }

  void Restore() noexcept { SDL_RestoreWindow(mWindow); }

  void Center() noexcept { SetPosition({SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED}); }

  auto UpdateSurface() noexcept -> Result { return SDL_UpdateWindowSurface(mWindow) == 0; }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  auto Flash(const FlashOp op = FlashOp::Briefly) noexcept -> Result
  {
    return SDL_FlashWindow(mWindow, static_cast<SDL_FlashOperation>(op)) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  auto SetFullscreen(const bool enabled) noexcept -> Result
  {
    return SDL_SetWindowFullscreen(mWindow, enabled ? Fullscreen : 0) == 0;
  }

  auto SetFullscreenDesktop(const bool enabled) noexcept -> Result
  {
    return SDL_SetWindowFullscreen(mWindow, enabled ? FullscreenDesktop : 0) == 0;
  }

  void SetDecorated(const bool decorated) noexcept
  {
    SDL_SetWindowBordered(mWindow, decorated ? SDL_TRUE : SDL_FALSE);
  }

  void SetResizable(const bool resizable) noexcept
  {
    SDL_SetWindowResizable(mWindow, resizable ? SDL_TRUE : SDL_FALSE);
  }

  void SetIcon(const Surface& icon) noexcept { SDL_SetWindowIcon(mWindow, icon.get()); }

  void SetTitle(const char* title) noexcept
  {
    assert(title);
    SDL_SetWindowTitle(mWindow, title);
  }

  void SetTitle(const std::string& title) noexcept { SetTitle(title.c_str()); }

  auto SetOpacity(const float opacity) noexcept -> Result
  {
    return SDL_SetWindowOpacity(mWindow, opacity) == 0;
  }

  void SetGrabMouse(const bool grab) noexcept
  {
    SDL_SetWindowGrab(mWindow, grab ? SDL_TRUE : SDL_FALSE);
  }

  auto SetBrightness(const float brightness) noexcept -> Result
  {
    return SDL_SetWindowBrightness(mWindow, detail::clamp(brightness, 0.0f, 1.0f)) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  void SetGrabKeyboard(const bool grab) noexcept
  {
    SDL_SetWindowKeyboardGrab(mWindow, grab ? SDL_TRUE : SDL_FALSE);
  }

  void SetAlwaysOnTop(const bool enabled) noexcept
  {
    SDL_SetWindowAlwaysOnTop(mWindow, enabled ? SDL_TRUE : SDL_FALSE);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  void SetX(const int x) noexcept { SetPosition({x, GetY()}); }

  void SetY(const int y) noexcept { SetPosition({GetX(), y}); }

  void SetPosition(const Point position) noexcept
  {
    SDL_SetWindowPosition(mWindow, position.GetX(), position.GetY());
  }

  void SetWidth(const int width) noexcept
  {
    SDL_SetWindowSize(mWindow, detail::max(width, 1), GetHeight());
  }

  void SetHeight(const int height) noexcept
  {
    SDL_SetWindowSize(mWindow, GetWidth(), detail::max(height, 1));
  }

  void SetSize(const Area size) noexcept
  {
    assert(size.width > 0);
    assert(size.height > 0);
    SDL_SetWindowSize(mWindow, size.width, size.height);
  }

  void SetMinSize(const Area size) noexcept
  {
    assert(size.width > 0);
    assert(size.height > 0);
    SDL_SetWindowMinimumSize(mWindow, size.width, size.height);
  }

  void SetMaxSize(const Area size) noexcept
  {
    assert(size.width > 0);
    assert(size.height > 0);
    SDL_SetWindowMaximumSize(mWindow, size.width, size.height);
  }

  static auto SetCapturingMouse(const bool capture) noexcept -> Result
  {
    return SDL_CaptureMouse(capture ? SDL_TRUE : SDL_FALSE) == 0;
  }

  [[nodiscard]] auto GetID() const noexcept -> Uint32 { return SDL_GetWindowID(mWindow); }

  [[nodiscard]] auto GetPosition() const noexcept -> Point
  {
    int x{};
    int y{};
    SDL_GetWindowPosition(mWindow, &x, &y);
    return {x, y};
  }

  [[nodiscard]] auto GetX() const noexcept -> int { return GetPosition().GetX(); }

  [[nodiscard]] auto GetY() const noexcept -> int { return GetPosition().GetY(); }

  [[nodiscard]] auto GetSize() const noexcept -> Area
  {
    Area size{};
    SDL_GetWindowSize(mWindow, &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto GetWidth() const noexcept -> int { return GetSize().width; }

  [[nodiscard]] auto GetHeight() const noexcept -> int { return GetSize().height; }

  [[nodiscard]] auto GetMinSize() const noexcept -> Area
  {
    Area size{};
    SDL_GetWindowMinimumSize(mWindow, &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto GetMaxSize() const noexcept -> Area
  {
    Area size{};
    SDL_GetWindowMaximumSize(mWindow, &size.width, &size.height);
    return size;
  }

  [[nodiscard]] auto GetDisplayIndex() const noexcept -> std::optional<int>
  {
    const auto index = SDL_GetWindowDisplayIndex(mWindow);
    if (index != -1) {
      return index;
    }
    else {
      return std::nullopt;
    }
  }

  [[nodiscard]] auto GetTitle() const -> std::string { return SDL_GetWindowTitle(mWindow); }

  [[nodiscard]] auto GetBrightness() const noexcept -> float
  {
    return SDL_GetWindowBrightness(mWindow);
  }

  [[nodiscard]] auto GetOpacity() const noexcept -> float
  {
    float opacity{1};
    SDL_GetWindowOpacity(mWindow, &opacity);
    return opacity;
  }

  [[nodiscard]] auto GetPixelFormat() const noexcept -> PixelFormat
  {
    return static_cast<PixelFormat>(SDL_GetWindowPixelFormat(mWindow));
  }

  [[nodiscard]] auto GetSurface() noexcept -> SurfaceHandle
  {
    return SurfaceHandle{SDL_GetWindowSurface(mWindow)};
  }

  [[nodiscard]] auto GetFlags() const noexcept -> Uint32
  {
    return SDL_GetWindowFlags(mWindow);
  }

  [[nodiscard]] auto CheckFlag(const Uint32 flag) const noexcept -> bool
  {
    return GetFlags() & flag;
  }

  [[nodiscard]] auto HasGrabbedInput() const noexcept -> bool
  {
    return CheckFlag(InputGrabbed);
  }

  [[nodiscard]] auto HasInputFocus() const noexcept -> bool { return CheckFlag(InputFocus); }

  [[nodiscard]] auto HasMouseFocus() const noexcept -> bool { return CheckFlag(MouseFocus); }

  [[nodiscard]] auto IsBorderless() const noexcept -> bool { return CheckFlag(Borderless); }

  [[nodiscard]] auto IsDecorated() const noexcept -> bool { return !IsBorderless(); }

  [[nodiscard]] auto IsResizable() const noexcept -> bool { return CheckFlag(Resizable); }

  [[nodiscard]] auto IsHighDPI() const noexcept -> bool { return CheckFlag(AllowHighDPI); }

  [[nodiscard]] auto IsFullscreen() const noexcept -> bool { return CheckFlag(Fullscreen); }

  [[nodiscard]] auto IsFullscreenDesktop() const noexcept -> bool
  {
    return CheckFlag(FullscreenDesktop);
  }

  [[nodiscard]] auto IsVisible() const noexcept -> bool { return CheckFlag(Shown); }

  [[nodiscard]] auto IsHidden() const noexcept -> bool { return CheckFlag(Hidden); }

  [[nodiscard]] auto IsOpenGL() const noexcept -> bool { return CheckFlag(OpenGL); }

  [[nodiscard]] auto IsVulkan() const noexcept -> bool { return CheckFlag(Vulkan); }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto IsMetal() const noexcept -> bool { return CheckFlag(Metal); }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  [[nodiscard]] auto IsForeign() const noexcept -> bool { return CheckFlag(Foreign); }

  [[nodiscard]] auto IsCapturingMouse() const noexcept -> bool
  {
    return CheckFlag(MouseCapture);
  }

  [[nodiscard]] auto IsMinimized() const noexcept -> bool { return CheckFlag(Minimized); }

  [[nodiscard]] auto IsMaximized() const noexcept -> bool { return CheckFlag(Maximized); }

  [[nodiscard]] auto IsAlwaysOnTop() const noexcept -> bool { return CheckFlag(AlwaysOnTop); }

  [[nodiscard]] auto IsUtility() const noexcept -> bool { return CheckFlag(Utility); }

  [[nodiscard]] auto IsTooltip() const noexcept -> bool { return CheckFlag(Tooltip); }

  [[nodiscard]] auto IsPopupMenu() const noexcept -> bool { return CheckFlag(PopupMenu); }

  [[nodiscard]] auto IsExcludedFromTaskbar() const noexcept -> bool
  {
    return CheckFlag(SkipTaskbar);
  }

  [[nodiscard]] auto IsGrabbingMouse() const noexcept -> bool
  {
    return SDL_GetWindowGrab(mWindow);
  }

  [[nodiscard]] auto IsScreenKeyboardShown() const noexcept -> bool
  {
    return SDL_IsScreenKeyboardShown(get()) == SDL_TRUE;
  }

  [[nodiscard]] auto data() const noexcept -> SDL_Window* { return mWindow.get(); }

  [[nodiscard]] auto get() const noexcept -> SDL_Window* { return mWindow.get(); }

  template <typename TT = T, detail::EnableHandle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mWindow != nullptr;
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] constexpr static auto GetDefaultSize() noexcept -> Area
  {
    return {800, 600};
  }

  template <typename TT = T, detail::EnableOwner<TT> = 0>
  [[nodiscard]] constexpr static auto GetDefaultFlags() noexcept -> Uint32
  {
    return Hidden;
  }

 private:
  detail::Pointer<T, SDL_Window> mWindow;
};

template <typename T>
[[nodiscard]] auto to_string(const BasicWindow<T>& window) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("Window(data: {}, width: {}, height: {})",
                     detail::address_of(window.data()),
                     window.GetWidth(),
                     window.GetHeight());
#else
  return "Window(data: " + detail::address_of(window.data()) +
         ", width: " + std::to_string(window.GetWidth()) +
         ", height: " + std::to_string(window.GetHeight()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const BasicWindow<T>& window) -> std::ostream&
{
  return stream << to_string(window);
}

[[nodiscard]] inline auto GetGrabbedWindow() noexcept -> WindowHandle
{
  return WindowHandle{SDL_GetGrabbedWindow()};
}

[[nodiscard]] inline auto GetMouseFocusWindow() noexcept -> WindowHandle
{
  return WindowHandle{SDL_GetMouseFocus()};
}

[[nodiscard]] inline auto GetKeyboardFocusWindow() noexcept -> WindowHandle
{
  return WindowHandle{SDL_GetKeyboardFocus()};
}

[[nodiscard]] inline auto GetWindow(const Uint32 id) noexcept -> WindowHandle
{
  return WindowHandle{SDL_GetWindowFromID(id)};
}

template <typename T>
[[nodiscard]] auto GetRenderer(const BasicWindow<T>& window) noexcept -> RendererHandle
{
  return RendererHandle{SDL_GetRenderer(window.get())};
}

[[nodiscard]] inline auto MakeWindowAndRenderer(const Area size = Window::GetDefaultSize(),
                                                const Uint32 flags = Window::GetDefaultFlags())
    -> std::pair<Window, Renderer>
{
  cen::Window window{"Centurion window", size, flags};
  cen::Renderer renderer{window};
  return std::make_pair(std::move(window), std::move(renderer));
}

}  // namespace cen

#endif  // CENTURION_WINDOW_HPP_
