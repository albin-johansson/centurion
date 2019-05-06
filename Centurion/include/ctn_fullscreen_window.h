#pragma once
#include <memory>
#include "ctn_abstract_window.h"

namespace centurion {
namespace visuals {

class FullscreenWindow;
using FullscreenWindow_sptr = std::shared_ptr<FullscreenWindow>;
using FullscreenWindow_uptr = std::unique_ptr<FullscreenWindow>;
using FullscreenWindow_wptr = std::weak_ptr<FullscreenWindow>;

/**
\brief The FullscreenWindow class represents a fullscreen top-level frame.
\since 2.0.0
*/
class FullscreenWindow final : public AbstractWindow {  // FIXME document
 private:
  SDL_Window* CreateWindow();

 public:
  FullscreenWindow();

  ~FullscreenWindow();

  /**
  \brief Creates and returns a shared pointer to a FullscreenWindow instance.
  \since 2.0.0
  */
  static FullscreenWindow_sptr CreateShared();

  /**
  \brief Creates and returns a unique pointer to a FullscreenWindow instance.
  \since 2.0.0
  */
  static FullscreenWindow_uptr CreateUnique();

  /**
  \brief Creates and returns a weak pointer to a FullscreenWindow instance.
  \since 2.0.0
  */
  static FullscreenWindow_wptr CreateWeak();
};

}  // namespace visuals
}  // namespace centurion