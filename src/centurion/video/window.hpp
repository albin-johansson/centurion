#ifndef CENTURION_WINDOW_HEADER
#define CENTURION_WINDOW_HEADER

#include <SDL.h>

#include <cassert>   // assert
#include <optional>  // optional
#include <ostream>   // ostream
#include <string>    // string, to_string

#include "../compiler/features.hpp"

#if CENTURION_HAS_FEATURE_FORMAT

#include <format>  // format

#endif  // CENTURION_HAS_FEATURE_FORMAT

#include "../core/exception.hpp"
#include "../core/integers.hpp"
#include "../core/not_null.hpp"
#include "../core/owner.hpp"
#include "../core/result.hpp"
#include "../core/str.hpp"
#include "../detail/address_of.hpp"
#include "../detail/clamp.hpp"
#include "../detail/convert_bool.hpp"
#include "../detail/max.hpp"
#include "../detail/owner_handle_api.hpp"
#include "../math/area.hpp"
#include "../math/rect.hpp"
#include "flash_op.hpp"
#include "pixel_format.hpp"
#include "surface.hpp"

namespace cen {

/// \addtogroup video
/// \{

template <typename T>
class basic_window;

/**
 * \typedef window
 *
 * \brief Represents an owning window.
 *
 * \since 5.0.0
 */
using window = basic_window<detail::owning_type>;

/**
 * \typedef window_handle
 *
 * \brief Represents a non-owning window.
 *
 * \since 5.0.0
 */
using window_handle = basic_window<detail::handle_type>;

/**
 * \class basic_window
 *
 * \brief Represents an operating system window.
 *
 * \ownerhandle `window`/`window_handle`
 *
 * \since 5.0.0
 *
 * \see `window`
 * \see `window_handle`
 * \see `get_window()`
 * \see `get_grabbed_window()`
 * \see `mouse_focus_window()`
 * \see `keyboard_focus_window()`
 * \see `get_renderer()`
 * \see `make_window_and_renderer()`
 */
template <typename T>
class basic_window final
{
 public:
  /**
   * \enum window_flags
   *
   * \brief Represents different window features and options.
   *
   * \details Values of this enum are intended to be used to create flag bitmasks, that
   * can be used when creating windows and to obtain information from created windows.
   *
   * \see `SDL_WindowFlags`
   *
   * \since 6.0.0
   */
  enum window_flags : u32
  {
    fullscreen = SDL_WINDOW_FULLSCREEN,
    opengl = SDL_WINDOW_OPENGL,
    shown = SDL_WINDOW_SHOWN,
    hidden = SDL_WINDOW_HIDDEN,
    borderless = SDL_WINDOW_BORDERLESS,
    resizable = SDL_WINDOW_RESIZABLE,
    minimized = SDL_WINDOW_MINIMIZED,
    maximized = SDL_WINDOW_MAXIMIZED,
    input_grabbed = SDL_WINDOW_INPUT_GRABBED,
    input_focus = SDL_WINDOW_INPUT_FOCUS,
    mouse_focus = SDL_WINDOW_MOUSE_FOCUS,
    fullscreen_desktop = SDL_WINDOW_FULLSCREEN_DESKTOP,
    foreign = SDL_WINDOW_FOREIGN,
    high_dpi = SDL_WINDOW_ALLOW_HIGHDPI,
    mouse_capture = SDL_WINDOW_MOUSE_CAPTURE,
    always_on_top = SDL_WINDOW_ALWAYS_ON_TOP,
    skip_taskbar = SDL_WINDOW_SKIP_TASKBAR,
    utility = SDL_WINDOW_UTILITY,
    tooltip = SDL_WINDOW_TOOLTIP,
    popup_menu = SDL_WINDOW_POPUP_MENU,
    vulkan = SDL_WINDOW_VULKAN,

#if SDL_VERSION_ATLEAST(2, 0, 14)
    metal = SDL_WINDOW_METAL
#endif  // SDL_VERSION_ATLEAST(2, 0, 14)
  };

  /// \name Construction
  /// \{

  /**
   * \brief Creates a window from a pointer to an SDL window.
   *
   * \note If you're creating a `window` instance, then ownership of the pointer is
   * claimed. Furthermore, if you're creating a `window_handle`, ownership is *not*
   * claimed.
   *
   * \param window a pointer to the associated SDL window. Ownership of this pointer is
   * claimed if the window is owning.
   *
   * \since 5.0.0
   */
  explicit basic_window(maybe_owner<SDL_Window*> window) noexcept(!detail::is_owning<T>())
      : m_window{window}
  {
    if constexpr (detail::is_owning<T>()) {
      if (!m_window) {
        throw cen_error{"Cannot create window from null pointer!"};
      }
    }
  }

  /**
   * \brief Creates an owning window with the specified title and size.
   *
   * \details The window will be hidden by default.
   *
   * \param title the title of the window, can't be null.
   * \param size the size of the window, components must be greater than zero.
   * \param flags the window flags.
   *
   * \throws cen_error if the supplied width or height aren't greater than zero.
   * \throws sdl_error if the window cannot be created.
   *
   * \see `default_size()`
   * \see `default_flags()`
   *
   * \since 3.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  explicit basic_window(const not_null<str> title,
                        const iarea size = default_size(),
                        const u32 flags = default_flags())
  {
    assert(title);

    if (size.width < 1) {
      throw cen_error{"Bad window width!"};
    }
    else if (size.height < 1) {
      throw cen_error{"Bad window height!"};
    }

    m_window.reset(SDL_CreateWindow(title,
                                    SDL_WINDOWPOS_CENTERED,
                                    SDL_WINDOWPOS_CENTERED,
                                    size.width,
                                    size.height,
                                    flags));
    if (!m_window) {
      throw sdl_error{};
    }
  }

  /**
   * \brief Creates an owning window with the specified title and size.
   *
   * \details The window will be hidden by default.
   *
   * \param title the title of the window.
   * \param size the size of the window, components must be greater than zero.
   * \param flags the window flags, see `window_flags`.
   *
   * \throws cen_error if the supplied width or height aren't greater than zero.
   * \throws sdl_error if the window cannot be created.
   *
   * \see `default_size()`
   * \see `default_flags()`
   *
   * \since 5.3.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  explicit basic_window(const std::string& title,
                        const iarea size = default_size(),
                        const u32 flags = default_flags())
      : basic_window{title.c_str(), size, flags}
  {}

  /**
   * \brief Creates a window.
   *
   * \details The window will use the size obtained from `default_size()` as its initial
   * size.
   *
   * \throws sdl_error if the window cannot be created.
   *
   * \since 3.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  basic_window() : basic_window{"Centurion window"}
  {}

  /**
   * \brief Creates a window handle based on an owning window.
   *
   * \param owner the owning window to base the handle on.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit basic_window(const window& owner) noexcept : m_window{owner.get()}
  {}

  /// \} End of construction

  /// \name Mutators
  /// \{

  /**
   * \brief Makes the window visible.
   *
   * \since 3.0.0
   */
  void show() noexcept
  {
    SDL_ShowWindow(m_window);
  }

  /**
   * \brief Makes the window invisible.
   *
   * \since 3.0.0
   */
  void hide() noexcept
  {
    SDL_HideWindow(m_window);
  }

  /**
   * \brief Raises this window above other windows and requests focus.
   *
   * \since 3.0.0
   */
  void raise() noexcept
  {
    SDL_RaiseWindow(m_window);
  }

  /**
   * \brief Maximizes the window.
   *
   * \since 3.1.0
   */
  void maximize() noexcept
  {
    SDL_MaximizeWindow(m_window);
  }

  /**
   * \brief Minimizes the window.
   *
   * \since 3.1.0
   */
  void minimize() noexcept
  {
    SDL_MinimizeWindow(m_window);
  }

  /**
   * \brief Restores the position and size of the window if it's minimized or maximized.
   *
   * \since 5.3.0
   */
  void restore() noexcept
  {
    SDL_RestoreWindow(m_window);
  }

  /**
   * \brief Updates the window surface.
   *
   * \return `success` if the surface was successfully updated; `failure` otherwise.
   *
   * \since 5.0.0
   */
  auto update_surface() noexcept -> result
  {
    return SDL_UpdateWindowSurface(m_window) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  /**
   * \brief Modifies the flash state of the window to acquire attention from the user.
   *
   * \param op the flash operation that will be performed.
   *
   * \return `success` if the operation was successful; `failure` otherwise.
   *
   * \since 6.2.0
   */
  auto flash(const flash_op op = flash_op::briefly) noexcept -> result
  {
    return SDL_FlashWindow(m_window, static_cast<SDL_FlashOperation>(op)) == 0;
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  /// \} End of mutators

  /// \name Setters
  /// \{

  /**
   * \brief Sets whether or not the window is in fullscreen mode.
   *
   * \param enabled `true` if the window should be fullscreen; `false` for windowed mode.
   *
   * \return `success` if the display mode was changed; `failure` otherwise.
   *
   * \since 3.0.0
   */
  auto set_fullscreen(const bool enabled) noexcept -> result
  {
    return SDL_SetWindowFullscreen(m_window, enabled ? fullscreen : 0) == 0;
  }

  /**
   * \brief Sets whether or not the window is in fullscreen desktop mode.
   *
   * \details This mode is useful when you want to "fake" fullscreen mode.
   *
   * \param enabled `true` if the window should be fullscreen desktop; `false` for
   * windowed mode.
   *
   * \return `success` if the display mode was changed; `failure` otherwise.
   *
   * \since 4.0.0
   */
  auto set_fullscreen_desktop(const bool enabled) noexcept -> result
  {
    return SDL_SetWindowFullscreen(m_window, enabled ? fullscreen_desktop : 0) == 0;
  }

  /**
   * \brief Sets whether or not the window is decorated.
   *
   * \details This is enabled by default.
   *
   * \param decorated `true` if the window should be decorated; `false` otherwise.
   *
   * \since 3.0.0
   */
  void set_decorated(const bool decorated) noexcept
  {
    SDL_SetWindowBordered(m_window, detail::convert_bool(decorated));
  }

  /**
   * \brief Sets whether or not the window should be resizable.
   *
   * \param resizable `true` if the window should be resizable; `false` otherwise.
   *
   * \since 3.0.0
   */
  void set_resizable(const bool resizable) noexcept
  {
    SDL_SetWindowResizable(m_window, detail::convert_bool(resizable));
  }

  /**
   * \brief Sets the icon that will be used by the window.
   *
   * \param icon the surface that will serve as the icon of the window.
   *
   * \since 3.0.0
   */
  void set_icon(const surface& icon) noexcept
  {
    SDL_SetWindowIcon(m_window, icon.get());
  }

  /**
   * \brief Sets the title of the window.
   *
   * \param title the title of the window, can't be null.
   *
   * \since 3.0.0
   */
  void set_title(const not_null<str> title) noexcept
  {
    assert(title);
    SDL_SetWindowTitle(m_window, title);
  }

  /**
   * \brief Sets the title of the window.
   *
   * \param title the title of the window.
   *
   * \since 5.3.0
   */
  void set_title(const std::string& title) noexcept
  {
    set_title(title.c_str());
  }

  /**
   * \brief Sets the opacity of the window.
   *
   * \details The supplied opacity will be clamped to a value in the legal range.
   *
   * \param opacity the opacity, in the range [0, 1].
   *
   * \return `success` if the opacity was successfully set; `failure` otherwise.
   *
   * \since 3.0.0
   */
  auto set_opacity(const float opacity) noexcept -> result
  {
    return SDL_SetWindowOpacity(m_window, opacity) == 0;
  }

  /**
   * \brief Sets whether or not the mouse should be confined within the window.
   *
   * \brief This property is disabled by default.
   *
   * \param grab `true` if the mouse should be confined within the window; `false`
   * otherwise.
   *
   * \see `set_grab_keyboard()`
   *
   * \since 3.0.0
   */
  void set_grab_mouse(const bool grab) noexcept
  {
    SDL_SetWindowGrab(m_window, detail::convert_bool(grab));
  }

  /**
   * \brief Sets the overall brightness of the window.
   *
   * \note A brightness value outside the legal range will be clamped to the closest valid
   * value.
   *
   * \param brightness the brightness value, in the range [0, 1].
   *
   * \return `success` if the brightness was successfully set; `failure` otherwise.
   *
   * \since 3.0.0
   */
  auto set_brightness(const float brightness) noexcept -> result
  {
    return SDL_SetWindowBrightness(m_window, detail::clamp(brightness, 0.0f, 1.0f)) == 0;
  }

  /**
   * \brief Sets whether or not the mouse should be captured.
   *
   * \note A window might have to be visible in order for the mouse to be captured.
   *
   * \param capture `true` if the mouse should be captured; `false` otherwise.
   *
   * \return `success` on the mouse capture was successfully changed; `failure` otherwise.
   *
   * \since 5.0.0
   */
  static auto set_capturing_mouse(const bool capture) noexcept -> result
  {
    return SDL_CaptureMouse(detail::convert_bool(capture)) == 0;
  }

#if SDL_VERSION_ATLEAST(2, 0, 16)

  /**
   * \brief Sets whether or not the keyboard input should be grabbed by the window.
   *
   * \param grab `true` if the keyboard should be grabbed; `false` otherwise.
   *
   * \see `set_grab_mouse()`
   *
   * \since 6.2.0
   */
  void set_grab_keyboard(const bool grab) noexcept
  {
    SDL_SetWindowKeyboardGrab(m_window, detail::convert_bool(grab));
  }

  /**
   * \brief Sets whether or not a window is always on top of other windows.
   *
   * \param enabled `true` if the window should be on top of all other windows; `false`
   * otherwise.
   *
   * \since 6.2.0
   */
  void set_always_on_top(const bool enabled) noexcept
  {
    SDL_SetWindowAlwaysOnTop(m_window, detail::convert_bool(enabled));
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 16)

  /// \} End of setters

  /// \name Position functions
  /// \{

  /**
   * \brief Centers the window position relative to the screen.
   *
   * \note Windows are centered by default.
   *
   * \since 3.0.0
   */
  void center() noexcept
  {
    set_position({SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED});
  }

  /**
   * \brief Sets the x-coordinate of the window.
   *
   * \param x the new x-coordinate of the window.
   *
   * \since 6.0.0
   */
  void set_x(const int x) noexcept
  {
    set_position({x, y()});
  }

  /**
   * \brief Sets the y-coordinate of the window.
   *
   * \param y the new y-coordinate of the window.
   *
   * \since 6.0.0
   */
  void set_y(const int y) noexcept
  {
    set_position({x(), y});
  }

  /**
   * \brief Sets the position of the window.
   *
   * \note It's possible to use `SDL_WINDOWPOS_CENTERED` or `SDL_WINDOWPOS_UNDEFINED` as
   * any of the components of the point.
   *
   * \param position the new position of the window.
   *
   * \since 5.0.0
   */
  void set_position(const ipoint position) noexcept
  {
    SDL_SetWindowPosition(m_window, position.x(), position.y());
  }

  /**
   * \brief Returns the x-coordinate of the window position.
   *
   * \return the x-coordinate of the window position.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto x() const noexcept -> int
  {
    return position().x();
  }

  /**
   * \brief Returns the y-coordinate of the window position.
   *
   * \return the y-coordinate of the window position.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto y() const noexcept -> int
  {
    return position().y();
  }

  /**
   * \brief Returns the current position of the window.
   *
   * \note Windows are centered by default.
   *
   * \return the current position of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto position() const noexcept -> ipoint
  {
    int x{};
    int y{};
    SDL_GetWindowPosition(m_window, &x, &y);
    return {x, y};
  }

  /// \} End of position functions

  /// \name Size functions
  /// \{

  /**
   * \brief Sets the width of the window.
   *
   * \details The supplied width is capped to always be at least 1.
   *
   * \param width the new width of the window, must be greater than zero.
   *
   * \since 3.0.0
   */
  void set_width(const int width) noexcept
  {
    SDL_SetWindowSize(m_window, detail::max(width, 1), height());
  }

  /**
   * \brief Sets the height of the window.
   *
   * \details The supplied height is capped to always be at least 1.
   *
   * \param height the new height of the window, must be greater than zero.
   *
   * \since 3.0.0
   */
  void set_height(const int height) noexcept
  {
    SDL_SetWindowSize(m_window, width(), detail::max(height, 1));
  }

  /**
   * \brief Sets the size of the window.
   *
   * \pre The supplied width and height must be greater than zero.
   *
   * \param size the new size of the window.
   *
   * \since 5.0.0
   */
  void set_size(const iarea size) noexcept
  {
    assert(size.width > 0);
    assert(size.height > 0);
    SDL_SetWindowSize(m_window, size.width, size.height);
  }

  /**
   * \brief Sets the minimum size of the window.
   *
   * \pre The supplied width and height must be greater than zero.
   *
   * \param size the minimum size of the window.
   *
   * \since 3.0.0
   */
  void set_min_size(const iarea size) noexcept
  {
    assert(size.width > 0);
    assert(size.height > 0);
    SDL_SetWindowMinimumSize(m_window, size.width, size.height);
  }

  /**
   * \brief Sets the maximum size of the window.
   *
   * \pre The supplied width and height must be greater than zero.
   *
   * \param size the maximum size of the window.
   *
   * \since 3.0.0
   */
  void set_max_size(const iarea size) noexcept
  {
    assert(size.width > 0);
    assert(size.height > 0);
    SDL_SetWindowMaximumSize(m_window, size.width, size.height);
  }

  /**
   * \brief Returns the current width of the window.
   *
   * \return the current width of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto width() const noexcept -> int
  {
    return size().width;
  }

  /**
   * \brief Returns the current height of the window.
   *
   * \return the current height of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto height() const noexcept -> int
  {
    return size().height;
  }

  /**
   * \brief Returns the current size of the window.
   *
   * \note Calling this function is slightly faster than calling both `width` and `height`
   * to obtain the window size.
   *
   * \return the size of the window.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowSize(m_window, &size.width, &size.height);
    return size;
  }

  /**
   * \brief Returns the minimum size of the window.
   *
   * \return the minimum size of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto min_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowMinimumSize(m_window, &size.width, &size.height);
    return size;
  }

  /**
   * \brief Returns the maximum size of the window.
   *
   * \return the maximum size of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto max_size() const noexcept -> iarea
  {
    iarea size{};
    SDL_GetWindowMaximumSize(m_window, &size.width, &size.height);
    return size;
  }

  /**
   * \brief Returns the default size of a window.
   *
   * \note This function is only available for owning windows.
   *
   * \return the default size of a window.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] constexpr static auto default_size() noexcept -> iarea
  {
    return {800, 600};
  }

  /// \} End of size functions

  /// \name Flag queries
  /// \{

  /**
   * \brief Returns a mask that represents the flags associated with the window.
   *
   * \details You can check the returned mask using the `SDL_WindowFlags` enum.
   *
   * \return a mask that represents the flags associated with the window.
   *
   * \see `SDL_WindowFlags`
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto flags() const noexcept -> u32
  {
    return SDL_GetWindowFlags(m_window);
  }

  /**
   * \brief Indicates whether or not a flag is set.
   *
   * \details Some of the use cases of this function can be replaced by more explicit
   * functions, e.g. `is_fullscreen()` instead of `check_flag(SDL_WINDOW_FULLSCREEN)`.
   *
   * \param flag the flag that will be tested.
   *
   * \return `true` if the flag is set; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto check_flag(const SDL_WindowFlags flag) const noexcept -> bool
  {
    return static_cast<bool>(flags() & flag);
  }

  /**
   * \brief Indicates whether or not a flag is set.
   *
   * \details Some of the use cases of this function can be replaced by more explicit
   * functions, e.g. `is_fullscreen()` instead of `check_flag(cen::window::fullscreen)`.
   *
   * \param flag the flag that will be tested.
   *
   * \return `true` if the flag is set; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto check_flag(const window_flags flag) const noexcept -> bool
  {
    return static_cast<bool>(flags() & flag);
  }

  /**
   * \brief Indicates whether or not the window has grabbed the input focus.
   *
   * \return `true` if the window has grabbed input focus; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto has_grabbed_input() const noexcept -> bool
  {
    return check_flag(input_grabbed);
  }

  /**
   * \brief Indicates whether or not the window has input focus.
   *
   * \note The window might have to be visible for this to be true.
   *
   * \return `true` if the window has input focus; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto has_input_focus() const noexcept -> bool
  {
    return check_flag(input_focus);
  }

  /**
   * \brief Indicates whether or not the window has mouse focus.
   *
   * \return `true` if the window has mouse focus; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto has_mouse_focus() const noexcept -> bool
  {
    return check_flag(mouse_focus);
  }

  /**
   * \brief Indicates whether or not the window is borderless.
   *
   * \note This check is the opposite of `is_decorated()`.
   *
   * \details Windows are not borderless by default.
   *
   * \return `true` if the window is borderless; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_borderless() const noexcept -> bool
  {
    return check_flag(borderless);
  }

  /**
   * \brief Indicates whether or not the window is decorated.
   *
   * \note This check is the opposite of `is_borderless()`.
   *
   * \details Windows are decorated by default.
   *
   * \return `true` if the window is decorated; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_decorated() const noexcept -> bool
  {
    return !is_borderless();
  }

  /**
   * \brief Indicates whether or not the window is resizable.
   *
   * \details By default, this property is set to false.
   *
   * \return `true` if the window is resizable; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_resizable() const noexcept -> bool
  {
    return check_flag(resizable);
  }

  /**
   * \brief Indicates whether or the window supports high-DPI mode.
   *
   * \return `true` if the window supports high-DPI mode; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_high_dpi() const noexcept -> bool
  {
    return check_flag(high_dpi);
  }

  /**
   * \brief Indicates whether or not the window is in fullscreen mode.
   *
   * \return `true` if the window is in fullscreen mode; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_fullscreen() const noexcept -> bool
  {
    return check_flag(fullscreen);
  }

  /**
   * \brief Indicates whether or not the window is in fullscreen desktop mode.
   *
   * \return `true` if the window is in fullscreen desktop mode; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_fullscreen_desktop() const noexcept -> bool
  {
    return check_flag(fullscreen_desktop);
  }

  /**
   * \brief Indicates whether or not the window is visible.
   *
   * \return `true` if the window is visible; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto is_visible() const noexcept -> bool
  {
    return check_flag(shown);
  }

  /**
   * \brief Indicates whether or not the window is hidden.
   *
   * \return `true` if the window isn't visible; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_hidden() const noexcept -> bool
  {
    return check_flag(hidden);
  }

  /**
   * \brief Indicates whether or not the window is usable with an OpenGL-context.
   *
   * \return `true` if the window is compatible with an OpenGL-context; false otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_opengl() const noexcept -> bool
  {
    return check_flag(opengl);
  }

  /**
   * \brief Indicates whether or not the window is usable as a Vulkan surface.
   *
   * \return `true` if the window is is usable as a Vulkan surface; false otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_vulkan() const noexcept -> bool
  {
    return check_flag(vulkan);
  }

#if SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Indicates whether or not the window can be used as a Metal view.
   *
   * \return `true` if the window can be used as a Metal view; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_metal() const noexcept -> bool
  {
    return check_flag(metal);
  }

#endif  // SDL_VERSION_ATLEAST(2, 0, 14)

  /**
   * \brief Indicates whether or not the window wasn't created by SDL.
   *
   * \return `true` if the window wasn't created by SDL; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_foreign() const noexcept -> bool
  {
    return check_flag(foreign);
  }

  /**
   * \brief Indicates whether or not the window is capturing the mouse.
   *
   * \return `true` if the window is capturing the mouse; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_capturing_mouse() const noexcept -> bool
  {
    return check_flag(mouse_capture);
  }

  /**
   * \brief Indicates whether or not the window is minimized.
   *
   * \return `true` if the window is minimized; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_minimized() const noexcept -> bool
  {
    return check_flag(minimized);
  }

  /**
   * \brief Indicates whether or not the window is maximized.
   *
   * \return `true` if the window is maximized; `false` otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_maximized() const noexcept -> bool
  {
    return check_flag(maximized);
  }

  /**
   * \brief Indicates whether or not the window is set to be always on top of other
   * windows.
   *
   * \return `true` if the window is always on top of other windows; false otherwise.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto is_always_on_top() const noexcept -> bool
  {
    return check_flag(always_on_top);
  }

  /**
   * \brief Indicates whether or not the window is a "utility" window.
   *
   * \return `true` if window is a "utility" window; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_utility() const noexcept -> bool
  {
    return check_flag(utility);
  }

  /**
   * \brief Indicates whether or not the window is a tooltip.
   *
   * \return `true` if the window is a tooltip; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_tooltip() const noexcept -> bool
  {
    return check_flag(tooltip);
  }

  /**
   * \brief Indicates whether or not the window is a popup menu.
   *
   * \return `true` if the window is a popup menu; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_popup_menu() const noexcept -> bool
  {
    return check_flag(popup_menu);
  }

  /**
   * \brief Indicates whether or not the window is excluded from the taskbar.
   *
   * \return `true` if the window is excluded from the taskbar; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_excluded_from_taskbar() const noexcept -> bool
  {
    return check_flag(skip_taskbar);
  }

  template <typename TT = T, detail::is_owner<TT> = 0>
  [[nodiscard]] constexpr static auto default_flags() noexcept -> u32
  {
    return hidden;
  }

  /// \} End of flag queries

  /// \name Getters
  /// \{

  /**
   * \brief Returns a numerical ID of the window.
   *
   * \return a numerical ID of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto id() const noexcept -> u32
  {
    return SDL_GetWindowID(m_window);
  }

  /**
   * \brief Returns the display index associated with the window.
   *
   * \return the display index associated with the window; `std::nullopt` if the display
   * index cannot be obtained.
   *
   * \since 3.1.0
   */
  [[nodiscard]] auto display_index() const noexcept -> std::optional<int>
  {
    const auto index = SDL_GetWindowDisplayIndex(m_window);
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
   * \return the title of the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto title() const -> std::string
  {
    return SDL_GetWindowTitle(m_window);
  }

  /**
   * \brief Returns the current brightness value of the window.
   *
   * \details The default value of this property is 1.
   *
   * \return the current brightness of the window, in the range [0, 1].
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto brightness() const noexcept -> float
  {
    return SDL_GetWindowBrightness(m_window);
  }

  /**
   * \brief Returns the opacity of the window.
   *
   * \return the opacity of the window, in the range [0, 1].
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto opacity() const noexcept -> float
  {
    float opacity{1};
    SDL_GetWindowOpacity(m_window, &opacity);
    return opacity;
  }

  /**
   * \brief Returns the pixel format of the window.
   *
   * \return the pixel format used by the window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto get_pixel_format() const noexcept -> pixel_format
  {
    return static_cast<pixel_format>(SDL_GetWindowPixelFormat(m_window));
  }

  /**
   * \brief Returns a handle to the window framebuffer surface.
   *
   * \warning It is not possible use the framebuffer surface with the 3D or 2D rendering
   * APIs.
   *
   * \return a handle to the window surface, might not contain a valid surface pointer.
   *
   * \since 5.0.0
   */
  [[nodiscard]] auto get_surface() noexcept -> surface_handle
  {
    return surface_handle{SDL_GetWindowSurface(m_window)};
  }

  /**
   * \brief Indicates whether or not the window is currently grabbing the mouse input.
   *
   * \return `true` if the window is grabbing the mouse; `false` otherwise.
   *
   * \since 3.0.0
   */
  [[nodiscard]] auto grabbing_mouse() const noexcept -> bool
  {
    return SDL_GetWindowGrab(m_window);
  }

  /**
   * \brief Indicates whether or not the screen keyboard is shown for the window.
   *
   * \return `true` if the screen keyboard is shown for the window; `false` otherwise.
   *
   * \since 6.0.0
   */
  [[nodiscard]] auto is_screen_keyboard_shown() const noexcept -> bool
  {
    return SDL_IsScreenKeyboardShown(get()) == SDL_TRUE;
  }

  /**
   * \brief Returns a pointer to the associated SDL window.
   *
   * \warning Don't take ownership of the returned pointer!
   *
   * \return a pointer to the associated SDL window.
   *
   * \since 4.0.0
   */
  [[nodiscard]] auto get() const noexcept -> SDL_Window*
  {
    return m_window.get();
  }

  /// \} End of getters

  /// \name Conversions
  /// \{

  /**
   * \brief Converts to `SDL_Window*`.
   *
   * \return a pointer to the associated SDL window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator SDL_Window*() noexcept
  {
    return m_window.get();
  }

  /**
   * \brief Converts to `const SDL_Window*`.
   *
   * \return a pointer to the associated SDL window.
   *
   * \since 3.0.0
   */
  [[nodiscard]] explicit operator const SDL_Window*() const noexcept
  {
    return m_window.get();
  }

  /**
   * \brief Indicates whether or not the handle holds a non-null pointer.
   *
   * \note This function is only available for window handles.
   *
   * \warning It's undefined behaviour to invoke other member functions that use the
   * internal pointer if this function returns `false`.
   *
   * \return `true` if the handle holds a non-null pointer; `false` otherwise.
   *
   * \since 5.0.0
   */
  template <typename TT = T, detail::is_handle<TT> = 0>
  explicit operator bool() const noexcept
  {
    return m_window != nullptr;
  }

  /// \} End of conversions

 private:
  struct deleter final
  {
    void operator()(SDL_Window* window) noexcept
    {
      SDL_DestroyWindow(window);
    }
  };
  detail::pointer_manager<T, SDL_Window, deleter> m_window;
};

/// \name String conversions
/// \{

/**
 * \brief Returns a textual representation of a window.
 *
 * \param window the window that will be converted.
 *
 * \return a textual representation of the window.
 *
 * \since 5.0.0
 */
template <typename T>
[[nodiscard]] auto to_string(const basic_window<T>& window) -> std::string
{
#if CENTURION_HAS_FEATURE_FORMAT
  return std::format("window{{data: {}, width: {}, height: {}}}",
                     detail::address_of(window.get()),
                     window.width(),
                     window.height());
#else
  return "window{data: " + detail::address_of(window.get()) +
         ", width: " + std::to_string(window.width()) +
         ", height: " + std::to_string(window.height()) + "}";
#endif  // CENTURION_HAS_FEATURE_FORMAT
}

/// \} End of string conversions

/// \name Streaming
/// \{

/**
 * \brief Prints a textual representation of a window.
 *
 * \param stream the stream that will be used.
 * \param window the window that will be printed.
 *
 * \return the used stream.
 *
 * \since 5.0.0
 */
template <typename T>
auto operator<<(std::ostream& stream, const basic_window<T>& window) -> std::ostream&
{
  return stream << to_string(window);
}

/// \} End of streaming

/// \} End of group video

}  // namespace cen

#endif  // CENTURION_WINDOW_HEADER
