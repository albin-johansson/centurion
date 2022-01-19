#ifndef CENTURION_WINDOW_HPP_
#define CENTURION_WINDOW_HPP_

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string, to_string
#include <utility>   // pair, make_pair, move

#include "common.hpp"
#include "detail/owner_handle_api.hpp"
#include "detail/stdlib.hpp"
#include "features.hpp"
#include "math.hpp"
#include "render.hpp"
#include "surface.hpp"
#include "video.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

namespace cen {

/// \addtogroup video
/// \{

template <typename T>
class basic_window;

using window = basic_window<detail::owner_tag>;          ///< An owning window.
using window_handle = basic_window<detail::handle_tag>;  ///< A non-owning window.

/**
 * \brief Represents an operating-system window.
 *
 * \ownerhandle `window`/`handle`
 *
 * \see `window`
 * \see `window_handle`
 *
 * \see `get_grabbed_window()`
 * \see `get_mouse_focus_window()`
 * \see `get_keyboard_focus_window()`
 * \see `get_window()`
 * \see `get_renderer()`
 */
template <typename T>
class basic_window final {
 public:
  /**
   * \brief Represents different window features and options.
   *
   * \details Values of this enum are intended to be used to create flag bitmasks, that
   * can be used when creating windows and to obtain information from created windows.
   */
  enum window_flags : uint32 {
    fullscreen = SDL_WINDOW_FULLSCREEN,
    fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,

    shown = SDL_WINDOW_SHOWN,
    hidden = SDL_WINDOW_HIDDEN,
    minimized = SDL_WINDOW_MINIMIZED,
    maximized = SDL_WINDOW_MAXIMIZED,

    borderless = SDL_WINDOW_BORDERLESS,
    resizable = SDL_WINDOW_RESIZABLE,
    skip_taskbar = SDL_WINDOW_SKIP_TASKBAR,

    input_grabbed = SDL_WINDOW_INPUT_GRABBED,
    input_focus = SDL_WINDOW_INPUT_FOCUS,
    mouse_focus = SDL_WINDOW_MOUSE_FOCUS,
    mouse_capture = SDL_WINDOW_MOUSE_CAPTURE,

    allow_high_dpi = SDL_WINDOW_ALLOW_HIGHDPI,
    always_on_top = SDL_WINDOW_ALWAYS_ON_TOP,

    foreign = SDL_WINDOW_FOREIGN,
    utility = SDL_WINDOW_UTILITY,
    tooltip = SDL_WINDOW_TOOLTIP,
    popup_menu = SDL_WINDOW_POPUP_MENU,

    opengl = SDL_WINDOW_OPENGL,
    vulkan = SDL_WINDOW_VULKAN,

#if SDL_VERSION_ATLEAST(2, 0, 14)
    metal = SDL_WINDOW_METAL
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
  };

  /// \name Construction
  /// \{

  /**
   * \brief Creates a window from an existing SDL window.
   *
   * \details Ownership of the supplied pointer is claimed if the window has owning semantics.
   *
   * \param window a pointer to the associated SDL window.
   *
   * \throws exception if the pointer is null and the window has owning semantics.
   */
  explicit basic_window(maybe_owner<SDL_Window*> window) noexcept(detail::is_handle<T>)
      : mWindow{window}
  {
    if constexpr (detail::is_owner<T>) {
      if (!mWindow) {
        throw exception{"Cannot create window from null pointer!"};
      }
    }
  }

  /**
   * \brief Creates an window with the specified title, size, and flags.
   *
   * \param title the window title.
   * \param size the initial window size.
   * \param flags the window flags.
   *
   * \throws exception if the window size is invalid.
   * \throws sdl_error if the window cannot be created.
   *
   * \see `default_size()`
   * \see `default_flags()`
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_window(not_null<const char*> title,
                        const iarea size = default_size(),
                        const uint32 flags = default_flags())
  {
    assert(title);

    if (size.width < 1) {
      throw exception{"Bad window width!"};
    }
    else if (size.height < 1) {
      throw exception{"Bad window height!"};
    }

    mWindow.reset(SDL_CreateWindow(title,
                                   SDL_WINDOWPOS_CENTERED,
                                   SDL_WINDOWPOS_CENTERED,
                                   size.width,
                                   size.height,
                                   flags));
    if (!mWindow) {
      throw sdl_error{};
    }
  }

  /// \copydoc basic_window(not_null<const char*>, iarea, uint32)
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  explicit basic_window(const std::string& title,
                        const iarea size = default_size(),
                        const uint32 flags = default_flags())
      : basic_window{title.c_str(), size, flags}
  {}

  /**
   * \brief Creates a window with `"Centurion"` as title along with default size and flags.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  basic_window() : basic_window{"Centurion"}
  {}

  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit basic_window(const window& owner) noexcept : mWindow{owner.get()}
  {}

  /// \} End of construction

  /// \name Renderer functions
  /// \{

  /**
   * \brief Creates a renderer associated with the window.
   *
   * \param index the index of the render driver.
   * \param flags the renderer flags that will be used.
   *
   * \return the created renderer.
   *
   * \throws sdl_error if the renderer cannot be created.
   *
   * \see `basic_renderer::default_flags()`
   */
  [[nodiscard]] auto create_renderer(const int index,
                                     const uint32 flags = renderer::default_flags())
      -> renderer
  {
    if (auto* ptr = SDL_CreateRenderer(get(), index, flags)) {
      return renderer{ptr};
    }
    else {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates a renderer associated with the window.
   *
   * \param flags the renderer flags that will be used.
   *
   * \return the created renderer.
   *
   * \throws sdl_error if the renderer cannot be created.
   *
   * \see `basic_renderer::default_flags()`
   */
  [[nodiscard]] auto create_renderer(const uint32 flags = renderer::default_flags())
      -> renderer
  {
    return create_renderer(-1, flags);
  }

  /**
   * \brief Returns a handle to the associated renderer.
   *
   * \details The returned handle will be empty if the window doesn't have an associated
   * renderer.
   *
   * \return a potentially empty renderer handle.
   *
   * \see `create_renderer()`
   */
  [[nodiscard]] auto get_renderer() noexcept -> renderer_handle
  {
    return renderer_handle{SDL_GetRenderer(mWindow)};
  }

  /// \} End of renderer functions

  /// \name Mutators
  /// \{

  /**
   * \brief Makes the window visible.
   */
  void show() noexcept { SDL_ShowWindow(mWindow); }

  /**
   * \brief Makes the window invisible.
   */
  void hide() noexcept { SDL_HideWindow(mWindow); }

  /**
   * \brief Raises this window above other windows and requests focus.
   */
  void raise() noexcept { SDL_RaiseWindow(mWindow); }

  /**
   * \brief Maximizes the window.
   */
  void maximize() noexcept { SDL_MaximizeWindow(mWindow); }

  /**
   * \brief Minimizes the window.
   */
  void minimize() noexcept { SDL_MinimizeWindow(mWindow); }

  /**
   * \brief Restores the position and size of the window (if it is minimized or maximized).
   */
  void restore() noexcept { SDL_RestoreWindow(mWindow); }

  /**
   * \brief Updates the window surface.
   *
   * \return `success` if the surface was successfully updated; `failure` otherwise.
   */
  auto update_surface() noexcept -> result { return SDL_UpdateWindowSurface(mWindow) == 0; }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  /**
   * \brief Modifies the flash state of the window to acquire attention from the user.
   *
   * \param op the flash operation that will be performed.
   *
   * \return `success` if the operation was successful; `failure` otherwise.
   */
  auto flash(const flash_op op = flash_op::briefly) noexcept -> result
  {
    return SDL_FlashWindow(mWindow, static_cast<SDL_FlashOperation>(op)) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  /// \} End of mutators

  /// \name Setters
  /// \{

  /**
   * \brief Sets whether the window is in fullscreen mode.
   *
   * \param enabled `true` if the window should be fullscreen; `false` for windowed mode.
   *
   * \return `success` if the display mode was changed; `failure` otherwise.
   */
  auto set_fullscreen(const bool enabled) noexcept -> result
  {
    return SDL_SetWindowFullscreen(mWindow, enabled ? fullscreen : 0) == 0;
  }

  /**
   * \brief Sets whether the window is in fullscreen desktop mode.
   *
   * \details This mode is useful when you want to "fake" fullscreen mode.
   *
   * \param enabled `true` if the window should be fullscreen desktop; `false` for windowed
   * mode.
   *
   * \return `success` if the display mode was changed; `failure` otherwise.
   */
  auto set_fullscreen_desktop(const bool enabled) noexcept -> result
  {
    return SDL_SetWindowFullscreen(mWindow, enabled ? fullscreen_desktop : 0) == 0;
  }

  /**
   * \brief Sets whether the window is decorated.
   *
   * \details This is enabled by default.
   *
   * \param decorated `true` if the window should be decorated; `false` otherwise.
   */
  void set_decorated(const bool decorated) noexcept
  {
    SDL_SetWindowBordered(mWindow, decorated ? SDL_TRUE : SDL_FALSE);
  }

  /**
   * \brief Sets whether the window should be resizable.
   *
   * \param resizable `true` if the window should be resizable; `false` otherwise.
   */
  void set_resizable(const bool resizable) noexcept
  {
    SDL_SetWindowResizable(mWindow, resizable ? SDL_TRUE : SDL_FALSE);
  }

  /**
   * \brief Sets the icon that will be used by the window.
   *
   * \param icon the new window icon.
   */
  void set_icon(const surface& icon) noexcept { SDL_SetWindowIcon(mWindow, icon.get()); }

  /**
   * \brief Sets the title of the window.
   *
   * \param title the new window title.
   */
  void set_title(not_null<const char*> title) noexcept
  {
    assert(title);
    SDL_SetWindowTitle(mWindow, title);
  }

  /// \copydoc set_title()
  void set_title(const std::string& title) noexcept { set_title(title.c_str()); }

  /**
   * \brief Sets the opacity of the window.
   *
   * \details The supplied opacity will be clamped to a value in the legal range.
   *
   * \param opacity the opacity, in the range [0, 1].
   *
   * \return `success` if the opacity was successfully set; `failure` otherwise.
   */
  auto set_opacity(const float opacity) noexcept -> result
  {
    return SDL_SetWindowOpacity(mWindow, opacity) == 0;
  }

  /**
   * \brief Sets the overall brightness of the window.
   *
   * \details The brightness will be clamped to the closest valid value.
   *
   * \param brightness the brightness value, in the range [0, 1].
   *
   * \return `success` if the brightness was successfully set; `failure` otherwise.
   */
  auto set_brightness(const float brightness) noexcept -> result
  {
    return SDL_SetWindowBrightness(mWindow, detail::clamp(brightness, 0.0f, 1.0f)) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  /**
   * \brief Sets whether the keyboard input should be grabbed by the window.
   *
   * \param grab `true` if the keyboard should be grabbed; `false` otherwise.
   */
  void set_grab_keyboard(const bool grab) noexcept
  {
    SDL_SetWindowKeyboardGrab(mWindow, grab ? SDL_TRUE : SDL_FALSE);
  }

  /**
   * \brief Sets whether a window is always on top of other windows.
   *
   * \param enabled `true` if the window should be on top; `false` otherwise.
   */
  void set_always_on_top(const bool enabled) noexcept
  {
    SDL_SetWindowAlwaysOnTop(mWindow, enabled ? SDL_TRUE : SDL_FALSE);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  /// \} End of setters

  /// \name Position functions
  /// \{

  /**
   * \brief Centers the window position relative to the screen.
   *
   * \details Windows are centered by default.
   */
  void center() noexcept { set_position({SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED}); }

  /**
   * \brief Sets the position of the window.
   *
   * \note It's possible to use `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED` as
   * any of the components of the point (see `center()`).
   *
   * \param position the new window position.
   */
  void set_position(const ipoint position) noexcept
  {
    SDL_SetWindowPosition(mWindow, position.x(), position.y());
  }

  /**
   * \brief Sets the x-coordinate of the window.
   *
   * \param x the new window x-coordinate.
   */
  void set_x(const int x) noexcept { set_position({x, y()}); }

  /**
   * \brief Sets the y-coordinate of the window.
   *
   * \param y the new window y-coordinate.
   */
  void set_y(const int y) noexcept { set_position({x(), y}); }

  /**
   * \brief Returns the current position of the window.
   *
   * \return the window position.
   */
  [[nodiscard]] auto position() const noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetWindowPosition(mWindow, &x, &y);
    return {x, y};
  }

  /**
   * \brief Returns the x-coordinate of the window.
   *
   * \return the window x-coordinate.
   */
  [[nodiscard]] auto x() const noexcept -> int { return position().x(); }

  /**
   * \brief Returns the y-coordinate of the window.
   *
   * \return the window y-coordinate.
   */
  [[nodiscard]] auto y() const noexcept -> int { return position().y(); }

  /// \} End of position functions

  /// \name Size functions
  /// \{

  /**
   * \brief Sets the size of the window.
   *
   * \details The width and height are adjusted to be at least 1.
   *
   * \param size the new window size.
   */
  void set_size(const iarea size) noexcept
  {
    SDL_SetWindowSize(mWindow, detail::max(size.width, 1), detail::max(size.height, 1));
  }

  /**
   * \brief Sets the width of the window.
   *
   * \details The width is adjusted to be at least 1.
   *
   * \param width the new window width.
   */
  void set_width(const int width) noexcept
  {
    SDL_SetWindowSize(mWindow, detail::max(width, 1), height());
  }

  /**
   * \brief Sets the height of the window.
   *
   * \details The height is adjusted to be at least 1.
   *
   * \param height the new window height.
   */
  void set_height(const int height) noexcept
  {
    SDL_SetWindowSize(mWindow, width(), detail::max(height, 1));
  }

  /**
   * \brief Sets the minimum size of the window.
   *
   * \details The width and height are adjusted to be at least 1.
   *
   * \param size the new minimum window size.
   */
  void set_min_size(const iarea size) noexcept
  {
    SDL_SetWindowMinimumSize(mWindow, detail::max(size.width, 1), detail::max(size.height, 1));
  }

  /**
   * \brief Sets the maximum size of the window.
   *
   * \details The width and height are adjusted to be at least 1.
   *
   * \param size the new maximum window size.
   */
  void set_max_size(const iarea size) noexcept
  {
    SDL_SetWindowMaximumSize(mWindow, detail::max(size.width, 1), detail::max(size.height, 1));
  }

  /**
   * \brief Returns the current size of the window.
   *
   * \return the window size.
   */
  [[nodiscard]] auto size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowSize(mWindow, &size.width, &size.height);
    return size;
  }

  /**
   * \brief Returns the current width of the window.
   *
   * \return the window width.
   */
  [[nodiscard]] auto width() const noexcept -> int { return size().width; }

  /**
   * \brief Returns the current height of the window.
   *
   * \return the window height.
   */
  [[nodiscard]] auto height() const noexcept -> int { return size().height; }

  /**
   * \brief Returns the current minimum size of the window.
   *
   * \return the minimum window size.
   */
  [[nodiscard]] auto min_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowMinimumSize(mWindow, &size.width, &size.height);
    return size;
  }

  /**
   * \brief Returns the current maximum size of the window.
   *
   * \return the maximum window size.
   */
  [[nodiscard]] auto max_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowMaximumSize(mWindow, &size.width, &size.height);
    return size;
  }

  /// \} End of size functions

  /// \name Mouse functions
  /// \{

  /**
   * \brief Sets whether or not the mouse should be captured.
   *
   * \note A window might have to be visible in order for the mouse to be captured.
   *
   * \param capture `true` if the mouse should be captured; `false` otherwise.
   *
   * \return `success` if the mouse capture was successfully changed; `failure` otherwise.
   */
  static auto set_capturing_mouse(const bool capture) noexcept -> result
  {
    return SDL_CaptureMouse(capture ? SDL_TRUE : SDL_FALSE) == 0;
  }

  /**
   * \brief Sets whether the mouse should be confined within the window.
   *
   * \brief This is disabled by default.
   *
   * \param grab `true` if the mouse should be confined within the window; `false` otherwise.
   */
  void set_grab_mouse(const bool grab) noexcept
  {
    SDL_SetWindowGrab(mWindow, grab ? SDL_TRUE : SDL_FALSE);
  }

  /**
   * \brief Indicates whether the window is currently grabbing the mouse input.
   *
   * \return `true` if the window is grabbing the mouse; `false` otherwise.
   */
  [[nodiscard]] auto is_grabbing_mouse() const noexcept -> bool
  {
    return SDL_GetWindowGrab(mWindow);
  }

  /// \} End of mouse functions

  /// \name Getters
  /// \{

  /**
   * \brief Returns the identifier associated with the window.
   *
   * \return the window identifier.
   */
  [[nodiscard]] auto id() const noexcept -> uint32 { return SDL_GetWindowID(mWindow); }

  /**
   * \brief Returns the display index associated with the window.
   *
   * \return the display index associated with the window; an empty optional is returned if the
   * display index cannot be obtained.
   */
  [[nodiscard]] auto display_index() const noexcept -> std::optional<int>
  {
    const auto index = SDL_GetWindowDisplayIndex(mWindow);
    if (index != -1) {
      return index;
    }
    else {
      return std::nullopt;
    }
  }

  /**
   * \brief Returns the title of the window.
   *
   * \return the window title.
   */
  [[nodiscard]] auto title() const -> std::string { return SDL_GetWindowTitle(mWindow); }

  /**
   * \brief Returns the current brightness of the window.
   *
   * \return the window brightness, in the range [0, 1].
   */
  [[nodiscard]] auto brightness() const noexcept -> float
  {
    return SDL_GetWindowBrightness(mWindow);
  }

  /**
   * \brief Returns the current opacity of the window.
   *
   * \return the window opacity, in the range [0, 1].
   */
  [[nodiscard]] auto opacity() const noexcept -> float
  {
    float opacity{1};
    SDL_GetWindowOpacity(mWindow, &opacity);
    return opacity;
  }

  /**
   * \brief Returns the pixel format used by the window.
   *
   * \return the window pixel format.
   */
  [[nodiscard]] auto format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(SDL_GetWindowPixelFormat(mWindow));
  }

  /**
   * \brief Indicates whether the screen keyboard is shown for the window.
   *
   * \return `true` if the screen keyboard is shown; `false` otherwise.
   */
  [[nodiscard]] auto is_screen_keyboard_shown() const noexcept -> bool
  {
    return SDL_IsScreenKeyboardShown(get()) == SDL_TRUE;
  }

  /// \} End of getters

  /// \name Flag queries
  /// \{

  /**
   * \brief Returns a mask that represents the flags associated with the window.
   *
   * \return a mask that represents the flags associated with the window.
   *
   * \see `window_flags`
   */
  [[nodiscard]] auto flags() const noexcept -> uint32 { return SDL_GetWindowFlags(mWindow); }

  /**
   * \brief Indicates whether or not a flag is set.
   *
   * \details Some of the use cases of this function can be replaced by more explicit
   * functions, e.g. `is_fullscreen()` instead of `check_flag(window::fullscreen)`.
   *
   * \param flag the flag that will be tested.
   *
   * \return `true` if the flag is set; `false` otherwise.
   */
  [[nodiscard]] auto check_flag(const uint32 flag) const noexcept -> bool
  {
    return flags() & flag;
  }

  /**
   * \brief Indicates whether the window has grabbed the input focus.
   *
   * \return `true` if the window has grabbed input focus; `false` otherwise.
   */
  [[nodiscard]] auto has_grabbed_input() const noexcept -> bool
  {
    return check_flag(input_grabbed);
  }

  /**
   * \brief Indicates whether the window has input focus.
   *
   * \note The window might have to be visible for this to be true.
   *
   * \return `true` if the window has input focus; `false` otherwise.
   */
  [[nodiscard]] auto has_input_focus() const noexcept -> bool
  {
    return check_flag(input_focus);
  }

  /**
   * \brief Indicates whether the window has mouse focus.
   *
   * \return `true` if the window has mouse focus; `false` otherwise.
   */
  [[nodiscard]] auto has_mouse_focus() const noexcept -> bool
  {
    return check_flag(mouse_focus);
  }

  /**
   * \brief Indicates whether the window is borderless.
   *
   * \note This check is the opposite of `is_decorated()`.
   *
   * \return `true` if the window is borderless; `false` otherwise.
   */
  [[nodiscard]] auto is_borderless() const noexcept -> bool { return check_flag(borderless); }

  /**
   * \brief Indicates whether the window is decorated.
   *
   * \note This check is the opposite of `is_borderless()`.
   *
   * \return `true` if the window is decorated; `false` otherwise.
   */
  [[nodiscard]] auto is_decorated() const noexcept -> bool { return !is_borderless(); }

  /**
   * \brief Indicates whether the window is resizable.
   *
   * \return `true` if the window is resizable; `false` otherwise.
   */
  [[nodiscard]] auto is_resizable() const noexcept -> bool { return check_flag(resizable); }

  /**
   * \brief Indicates whether the window supports high-DPI mode.
   *
   * \return `true` if the window supports high-DPI mode; `false` otherwise.
   */
  [[nodiscard]] auto is_high_dpi() const noexcept -> bool
  {
    return check_flag(allow_high_dpi);
  }

  /**
   * \brief Indicates whether the window is in fullscreen mode.
   *
   * \return `true` if the window is fullscreen; `false` otherwise.
   */
  [[nodiscard]] auto is_fullscreen() const noexcept -> bool { return check_flag(fullscreen); }

  /**
   * \brief Indicates whether the window is in fullscreen desktop mode.
   *
   * \return `true` if the window is fullscreen desktop; `false` otherwise.
   */
  [[nodiscard]] auto is_fullscreen_desktop() const noexcept -> bool
  {
    return check_flag(fullscreen_desktop);
  }

  /**
   * \brief Indicates whether the window is visible.
   *
   * \return `true` if the window is visible; `false` otherwise.
   */
  [[nodiscard]] auto is_visible() const noexcept -> bool { return check_flag(shown); }

  /**
   * \brief Indicates whether the window is hidden (not visible).
   *
   * \return `true` if the window is hidden; `false` otherwise.
   */
  [[nodiscard]] auto is_hidden() const noexcept -> bool { return check_flag(hidden); }

  /**
   * \brief Indicates whether the window is usable with an OpenGL-context.
   *
   * \return `true` if the window is OpenGL-compatible; `false` otherwise.
   */
  [[nodiscard]] auto is_opengl() const noexcept -> bool { return check_flag(opengl); }

  /**
   * \brief Indicates whether the window is usable as a Vulkan surface.
   *
   * \return `true` if the window is is usable as a Vulkan surface; `false` otherwise.
   */
  [[nodiscard]] auto is_vulkan() const noexcept -> bool { return check_flag(vulkan); }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Indicates whether the window can be used as a Metal view.
   *
   * \return `true` if the window can be used as a Metal view; `false` otherwise.
   */
  [[nodiscard]] auto is_metal() const noexcept -> bool { return check_flag(metal); }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Indicates whether the window wasn't created by SDL.
   *
   * \return `true` if the window wasn't created by SDL; `false` otherwise.
   */
  [[nodiscard]] auto is_foreign() const noexcept -> bool { return check_flag(foreign); }

  /**
   * \brief Indicates whether the window is capturing the mouse.
   *
   * \return `true` if the window is capturing the mouse; `false` otherwise.
   */
  [[nodiscard]] auto is_capturing_mouse() const noexcept -> bool
  {
    return check_flag(mouse_capture);
  }

  /**
   * \brief Indicates whether the window is minimized.
   *
   * \return `true` if the window is minimized; `false` otherwise.
   */
  [[nodiscard]] auto is_minimized() const noexcept -> bool { return check_flag(minimized); }

  /**
   * \brief Indicates whether the window is maximized.
   *
   * \return `true` if the window is maximized; `false` otherwise.
   */
  [[nodiscard]] auto is_maximized() const noexcept -> bool { return check_flag(maximized); }

  /**
   * \brief Indicates whether the window is set to be always on top of other windows.
   *
   * \return `true` if the window is always on top; `false` otherwise.
   */
  [[nodiscard]] auto is_always_on_top() const noexcept -> bool
  {
    return check_flag(always_on_top);
  }

  /**
   * \brief Indicates whether the window is a "utility" window.
   *
   * \return `true` if window is a utility window; `false` otherwise.
   */
  [[nodiscard]] auto is_utility() const noexcept -> bool { return check_flag(utility); }

  /**
   * \brief Indicates whether the window is a tooltip window.
   *
   * \return `true` if the window is a tooltip; `false` otherwise.
   */
  [[nodiscard]] auto is_tooltip() const noexcept -> bool { return check_flag(tooltip); }

  /**
   * \brief Indicates whether the window is a popup menu.
   *
   * \return `true` if the window is a popup menu; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_popup_menu() const noexcept -> bool { return check_flag(popup_menu); }

  /**
   * \brief Indicates whether the window is excluded from the taskbar.
   *
   * \return `true` if the window is excluded from the taskbar; `false` otherwise.
   */
  [[nodiscard]] auto is_excluded_from_taskbar() const noexcept -> bool
  {
    return check_flag(skip_taskbar);
  }

  /// \} End of flag queries

  /// \name Misc functions
  /// \{

  /**
   * \brief Returns a handle to the window framebuffer surface.
   *
   * \warning It is not possible use the framebuffer surface with the 2D rendering APIs.
   *
   * \return a potentially empty handle to the window surface.
   */
  [[nodiscard]] auto get_surface() noexcept -> surface_handle
  {
    return surface_handle{SDL_GetWindowSurface(mWindow)};
  }

  [[nodiscard]] auto get() const noexcept -> SDL_Window* { return mWindow.get(); }

  /**
   * \brief Indicates whether a handle holds a non-null pointer.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   */
  template <typename TT = T, detail::enable_for_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return mWindow != nullptr;
  }

  /// \} End of misc functions

  /**
   * \brief Returns the window size used by default.
   *
   * \return the default window size.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] constexpr static auto default_size() noexcept -> iarea
  {
    return {800, 600};
  }

  /**
   * \brief Returns the window flags used by default.
   *
   * \return the default window flags.
   */
  template <typename TT = T, detail::enable_for_owner<TT> = 0>
  [[nodiscard]] constexpr static auto default_flags() noexcept -> uint32
  {
    return hidden;
  }

 private:
  detail::pointer<T, SDL_Window> mWindow;
};

/// \name Window functions
/// \{

template <typename T>
[[nodiscard]] auto to_string(const basic_window<T>& window) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("window(data: {}, width: {}, height: {})",
                     detail::address_of(window.get()),
                     window.width(),
                     window.height());
#else
  return "window(data: " + detail::address_of(window.get()) +
         ", width: " + std::to_string(window.width()) +
         ", height: " + std::to_string(window.height()) + ")";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

template <typename T>
auto operator<<(std::ostream& stream, const basic_window<T>& window) -> std::ostream&
{
  return stream << to_string(window);
}

/**
 * \brief Returns a handle to the currently grabbed window.
 *
 * \return a potentially empty window handle.
 */
[[nodiscard]] inline auto get_grabbed_window() noexcept -> window_handle
{
  return window_handle{SDL_GetGrabbedWindow()};
}

/**
 * \brief Returns a handle to the window that currently has mouse focus.
 *
 * \return a potentially empty window handle.
 */
[[nodiscard]] inline auto get_mouse_focus_window() noexcept -> window_handle
{
  return window_handle{SDL_GetMouseFocus()};
}

/**
 * \brief Returns a handle to the window that currently has keyboard focus.
 *
 * \return a potentially empty window handle.
 */
[[nodiscard]] inline auto get_keyboard_focus_window() noexcept -> window_handle
{
  return window_handle{SDL_GetKeyboardFocus()};
}

/**
 * \brief Returns a handle to the window associated with an identifier.
 *
 * \param id the identifier associated with the desired window.
 *
 * \return a potentially empty window handle.
 */
[[nodiscard]] inline auto get_window(const uint32 id) noexcept -> window_handle
{
  return window_handle{SDL_GetWindowFromID(id)};
}

/// \} End of window functions

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_WINDOW_HPP_
