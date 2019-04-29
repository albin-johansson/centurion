#include "ctn_fullscreen_window.h"
#include "ctn_screen.h"

using namespace centurion::tools;

namespace centurion {
namespace visuals {

FullscreenWindow::FullscreenWindow() : AbstractWindow(CreateWindow()) {}

FullscreenWindow::~FullscreenWindow() = default;

SDL_Window* FullscreenWindow::CreateWindow() {
  int w = Screen::GetWidth();
  int h = Screen::GetHeight();
  Uint32 flags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIDDEN;
  SDL_Window* result = SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, w, h, flags);
  return result;
}

FullscreenWindow_sptr FullscreenWindow::CreateShared() {
  return std::make_shared<FullscreenWindow>();
}

FullscreenWindow_uptr FullscreenWindow::CreateUnique() {
  return std::make_unique<FullscreenWindow>();
}

FullscreenWindow_wptr FullscreenWindow::CreateWeak() { return CreateShared(); }

}  // namespace visuals
}  // namespace centurion