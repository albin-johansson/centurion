#pragma once
#include <memory>
#include "ctn_abstract_window.h"

namespace centurion {
namespace visuals {

class FullscreenWindow;
typedef std::shared_ptr<FullscreenWindow> FullscreenWindow_sptr;
typedef std::unique_ptr<FullscreenWindow> FullscreenWindow_uptr;
typedef std::weak_ptr<FullscreenWindow> FullscreenWindow_wptr;

class FullscreenWindow final : public AbstractWindow {
 private:
  SDL_Window* CreateWindow();

 public:
  FullscreenWindow();

  ~FullscreenWindow();

  static FullscreenWindow_sptr CreateShared();

  static FullscreenWindow_uptr CreateUnique();

  static FullscreenWindow_wptr CreateWeak();
};

}  // namespace visuals
}  // namespace centurion