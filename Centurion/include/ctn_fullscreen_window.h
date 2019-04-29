#pragma once
#include <memory>
#include "ctn_abstract_window.h"

namespace centurion {
namespace visuals {

class FullscreenWindow;
using FullscreenWindow_sptr = std::shared_ptr<FullscreenWindow>;
using FullscreenWindow_uptr = std::unique_ptr<FullscreenWindow>;
using FullscreenWindow_wptr = std::weak_ptr<FullscreenWindow>;

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