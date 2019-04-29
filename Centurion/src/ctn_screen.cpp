#include "ctn_screen.h"
#include <SDL.h>
#include <windows.h>
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
  DPI_AWARENESS_CONTEXT context = GetThreadDpiAwarenessContext();
  if (context != DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
  }
  return GetSystemMetrics(SM_CXSCREEN);
}

int Screen::GetHeight() {
  DPI_AWARENESS_CONTEXT context = GetThreadDpiAwarenessContext();
  if (context != DPI_AWARENESS_CONTEXT_SYSTEM_AWARE) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
  }
  return GetSystemMetrics(SM_CYSCREEN);
}

}  // namespace tools
}  // namespace centurion