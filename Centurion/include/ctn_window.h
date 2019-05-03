#pragma once
#include <SDL_stdinc.h>
#include <SDL_video.h>
#include <memory>
#include <string>
#include "ctn_abstract_window.h"
#include "ctn_color.h"
#include "ctn_font.h"
#include "ctn_point.h"
#include "ctn_rectangle.h"
#include "ctn_renderer_interface.h"
#include "ctn_surface.h"
#include "ctn_texture_interface.h"

namespace centurion {
namespace visuals {

class Window;
using Window_sptr = std::shared_ptr<Window>;
using Window_uptr = std::unique_ptr<Window>;
using Window_wptr = std::weak_ptr<Window>;

/**
\brief The Window class represents a windowed frame.
\since 1.0.0
*/
class Window final : public AbstractWindow {
 private:
  SDL_Window* CreateWindow(int width, int height, Uint32 flags);

 public:
  /**
  \param width - the width of the window.
  \param height - the height of the window.
  \since 2.0.0
  */
  Window(int width, int height);

  /**
  \param width - the width of the window.
  \param height - the height of the window.
  \param flags - the flags used to create the window, see SDL_WINDOW_x for
  possible values.
  \throws invalid_argument if the SDL_WINDOW_FULLSCREEN flag is used.
  \since 2.0.0
  */
  Window(int width, int height, Uint32 flags);

  ~Window();

  /**
  \brief Sets the title text of this window.
  \param title - the new title of the window.
  \since 2.0.0
  */
  void SetTitle(std::string title);

  /**
  \brief Sets whether or not this window is resizable.
  \param resizable - true if the window is resizable, false otherwise.
  \since 1.0.0
  */
  void SetResizable(bool resizable);

  /**
  \brief Assigns whether or not this window is bordered.
  \param bordered - true if the window should be bordered, false otherwise.
  \since 2.0.0
  */
  void SetBordered(bool bordered);

  /**
  \brief Sets the window icon.
  \param icon - the surface that will be used as the window icon.
  \since 2.0.0
  */
  void SetWindowIcon(Surface_sptr icon);

  /**
  \brief Sets the location of this window.
  \param x - the x-coordinate of the window.
  \param y - the y-coordinate of the window.
  \since 2.0.0
  */
  void SetLocation(int x, int y);

  /**
  \brief Sets the maximum size of this window.
  \param width - the maximum width of this window.
  \param height - the maximum height of this window.
  \since 2.0.0
  */
  void SetMaxSize(int width, int height);

  /**
  \brief Sets the minimum size of this window.
  \param width - the minimum width of this window.
  \param height - the minimum height of this window.
  \since 2.0.0
  */
  void SetMinSize(int width, int height);

  /**
  \brief Sets the size of this window.
  \param width - the new width of this window.
  \param height - the new height of this window.
  \since 2.0.0
  */
  void SetSize(int width, int height);

  /**
  \brief Creates and returns a Texture found at the supplied path.
  \param path - the path of the image in the file system.
  \since 1.0.0
  */
  ITexture_sptr CreateTexture(const std::string& path) const;

  /**
  \brief Returns a shared pointer that points to a Window instance.
  \param width - the width of the window.
  \param height - the height of the window.
  \since 1.1.0
  */
  static Window_sptr CreateShared(int width, int height);

  /**
  \brief Returns a unique pointer that points to a Window instance.
  \param width - the width of the window.
  \param height - the height of the window.
  \since 1.1.0
  */
  static Window_uptr CreateUnique(int width, int height);

  /**
  \brief Returns a weak pointer that points to a Window instance.
  \param width - the width of the window.
  \param height - the height of the window.
  \since 1.1.0
  */
  static Window_wptr CreateWeak(int width, int height);
};

}  // namespace visuals
}  // namespace centurion