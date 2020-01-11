#pragma once
#include <string>
#include <vector>
#include <utility>
#include <gsl>
#include <SDL.h>

namespace centurion {

class IWindowListener;

/**
 * The Window class is a wrapper around an SDL_Window instance. Window instances can't be copied.
 * The class can safely be used as a base class, since it provides a virtual destructor.
 * Instances of the Window class can be implicitly converted to SDL_Window*.
 *
 * @see IWindowListener
 * @since 3.0.0
 */
class Window {
 private:
  SDL_Window* window = nullptr;
  std::vector<IWindowListener*> windowListeners;

  /**
   * Notifies all registered window listeners that the window has been updated.
   *
   * @since 3.0.0
   */
  void notify_window_listeners() noexcept;

 public:
  /**
   * Creates a window instance. The window will be hidden by default.
   *
   * @param title the title of thw window.
   * @param width the width of the window, must be greater than zero.
   * @param height the height of the window, must be greater than zero.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 3.0.0
   */
  explicit Window(const std::string& title, int width, int height);

  /**
   * Creates a window instance. The window will be hidden by default.
   *
   * @param width the width of the window, must be greater than zero.
   * @param height the height of the window, must be greater than zero.
   * @throws invalid_argument if the supplied width or height values aren't
   * greater than zero.
   * @since 3.0.0
   */
  explicit Window(int width, int height);

  /**
   * Creates a 800x600 window with the specified title.
   *
   * @param title the title of the window.
   * @since 3.0.0
   */
  explicit Window(const std::string& title);

  /**
   * Creates a 800x600 window. The window will be hidden by default.
   *
   * @since 3.0.0
   */
  Window();

  /**
   * Creates a window by moving the contents of the supplied window into the new window.
   *
   * @param other the window that will be moved.
   * @since 3.0.0
   */
  Window(Window&& other) noexcept;

  Window(const Window&) noexcept = delete;

  virtual ~Window();

  Window& operator=(const Window&) noexcept = delete;

  /**
   * Moves the contents of the supplied window into this window.
   *
   * @param other the window whose contents will be moved.
   * @return the changed window.
   * @since 3.0.0
   */
  [[nodiscard]]
  Window& operator=(Window&& other) noexcept;

  /**
   * Makes the window visible. Triggers a window listener update.
   *
   * @since 3.0.0
   */
  void show() noexcept;

  /**
   * Makes the window invisible. Triggers a window listener update.
   *
   * @since 3.0.0
   */
  void hide() noexcept;

  /**
   * Centers the window position relative to the screen.
   *
   * @since 3.0.0
   */
  void center() noexcept;

  /**
   * Raises this window above other windows and requests focus.
   *
   * @since 3.0.0
   */
  void raise() noexcept;

  /**
   * Adds a window listener to the window. Null listener are always silently ignored. The window
   * takes no ownership of supplied pointers.
   *
   * @param listener a window listener, may be null.
   * @since 3.0.0
   */
  void add_window_listener(IWindowListener* listener) noexcept;

  /**
   * Sets whether or not the window is in fullscreen mode. Triggers a window listener update.
   *
   * @param fullscreen true if the window should enable fullscreen mode; false
   * otherwise.
   * @since 3.0.0
   */
  void set_fullscreen(bool fullscreen) noexcept;

  /**
   * Sets whether or not the window is decorated. Triggers a window listener update. This property
   * is enabled by default.
   *
   * @param decorated true if the window should be decorated; false otherwise.
   * @since 3.0.0
   */
  void set_decorated(bool decorated) noexcept;

  /**
   * Sets whether or not the window should be resizable. Triggers a window listener update.
   *
   * @param isResizable true if the window should be resizable; false otherwise.
   * @since 3.0.0
   */
  void set_resizable(bool isResizable) noexcept;

  /**
   * Sets the width of the window. Triggers a window listener update.
   *
   * @param width the new width of the window.
   * @throws invalid_argument if the supplied width isn't greater than zero.
   * @since 3.0.0
   */
  void set_width(int width);

  /**
   * Sets the height of the window. Triggers a window listener update.
   *
   * @param height the new height of the window.
   * @throws invalid_argument if the supplied height isn't greater than
   * zero.
   * @since 3.0.0
   */
  void set_height(int height);

  /**
   * Sets the icon that will be used by the window. Triggers a window listener update.
   *
   * @param icon a pointer to the surface that will serve as the icon of the window.
   * @since 3.0.0
   */
  void set_icon(gsl::not_null<SDL_Surface*> icon) noexcept;

  /**
   * Sets the title of the window.
   *
   * @param title the title of the window.
   * @since 3.0.0
   */
  void set_title(const std::string& title) noexcept;

  /**
   * Sets the gamma brightness of the window. This operation is only supported if the window is
   * in fullscreen mode. This property will be reset every time the fullscreen mode is exited.
   *
   * @param gamma the brightness value, in the range [0, 1].
   * @since 3.0.0
   */
  void set_gamma(float gamma) noexcept;

  /**
   * Sets the opacity of the window.
   *
   * @param opacity the opacity, in the range [0, 1]. This value will be clamped to a value in
   * the legal range internally.
   * @since 3.0.0
   */
  void set_opacity(float opacity) noexcept;

  /**
   * Sets the minimum size of the window.
   *
   * @param width the minimum width of the window, must be greater than zero.
   * @param height the minimum height of the window, must be greater than zero.
   * @since 3.0.0
   */
  void set_min_size(int width, int height) noexcept;

  /**
   * Sets the maximum size of the window.
   *
   * @param width the maximum width of the window, must be greater than zero.
   * @param height the maximum height of the window, must be greater than zero.
   * @since 3.0.0
   */
  void set_max_size(int width, int height) noexcept;

  /**
   * Sets the position of the window. Note, it's possible to use SDL_WINDOWPOS_CENTERED or
   * SDL_WINDOWPOS_UNDEFINED as any of the arguments.
   *
   * @param x the screen x-coordinate that the window will adapt.
   * @param y the screen y-coordinate that the window will adapt.
   * @since 3.0.0
   */
  void set_position(int x, int y) noexcept;

  /**
   * Sets whether or not the mouse should be confined within the window. This property is disabled
   * by default.
   *
   * @param grabMouse true if the mouse should be confined within the window; false otherwise.
   * @since 3.0.0
   */
  void set_grab_mouse(bool grabMouse) noexcept;

  /**
   * Indicates whether or not the window is resizable.
   *
   * @return true if the window is resizable; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_resizable() const noexcept;

  /**
   * Indicates whether or not the window is in fullscreen mode.
   *
   * @return true if the window is in fullscreen mode; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_fullscreen() const noexcept;

  /**
   * Indicates whether or not the window is visible.
   *
   * @return true if the window is visible; false otherwise.
   * @since 3.0.0
   */
  [[nodiscard]]
  bool is_visible() const noexcept;

  [[nodiscard]]
  int get_x() const noexcept;

  [[nodiscard]]
  int get_y() const noexcept;

  [[nodiscard]]
  std::pair<int, int> get_position() const noexcept;

  /**
   * Returns the current width of the window.
   *
   * @return the current width of the window.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_width() const noexcept;

  /**
   * Returns the current height of the window.
   *
   * @return the current height of the window.
   * @since 3.0.0
   */
  [[nodiscard]]
  int get_height() const noexcept;

  /**
   * Returns the title of the window.
   *
   * @return the title of the window.
   * @since 3.0.0
   */
  [[nodiscard]]
  std::string get_title() const noexcept;

  /**
   * Implicit conversion to raw SDL_Window pointer.
   *
   * @return a pointer to the SDL_Window representation of the window.
   * @since 3.0.0
   */
  /*implicit*/ operator SDL_Window*() const noexcept;
};

}