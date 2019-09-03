#include "ctn_screen.h"
#include <SDL.h>
#include <stdexcept>

namespace centurion {
namespace tools {

// TODO platform independent version of this class (GetWidth() and GetHeight())

void Screen::SetScreenSaverEnabled(bool enabled) noexcept {
  if (enabled) {
    SDL_EnableScreenSaver();
  } else {
    SDL_DisableScreenSaver();
  }
}

int Screen::GetWidth() {
  SDL_DisplayMode dm;

  if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
    SDL_Log("Failed to obtain screen width! Error: %s", SDL_GetError());
    throw std::exception();
  }

  return dm.w;

//  DPI_AWARENESS_CONTEXT context = GetThreadDpiAwarenessContext();
//  if (context != DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) {
//    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
//  }
//  return GetSystemMetrics(SM_CXSCREEN);
}

int Screen::GetHeight() {
  SDL_DisplayMode dm;

  if (SDL_GetDesktopDisplayMode(0, &dm) != 0) {
    SDL_Log("Failed to obtain screen height! Error: %s", SDL_GetError());
    throw std::exception();
  }

  return dm.h;

//  DPI_AWARENESS_CONTEXT context = GetThreadDpiAwarenessContext();
//  if (context != DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) {
//    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
//  }
//  return GetSystemMetrics(SM_CYSCREEN);
}

}  // namespace tools
}  // namespace centurion