#include "ctn_window.h"
#include <stdexcept>
#include "ctn_bool_converter.h"
#include "ctn_renderer.h"
#include "ctn_screen.h"
#include "ctn_texture.h"

using namespace centurion::geo;
using namespace centurion::tools;

namespace centurion {
namespace visuals {

SDL_Window* Window::CreateWindow(int w, int h, Uint32 flags) {
  std::string title = "Centurion window";
  SDL_Window* result = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED, w, h, flags);
  return result;
}

Window::Window(int w, int h)
    : AbstractWindow(CreateWindow(w, h, SDL_WINDOW_HIDDEN)) {}

Window::Window(int w, int h, Uint32 flags)
    : AbstractWindow(CreateWindow(w, h, flags)) {
  if (flags | SDL_WINDOW_FULLSCREEN) {
    throw std::invalid_argument("Invalid window flag: SDL_WINDOW_FULLSCREEN! ");
  }
}

Window::~Window() = default;

void Window::SetResizable(bool resizable) {
  SDL_bool b = BoolConverter::Convert(resizable);
  SDL_SetWindowResizable(sdlWindow, b);
}

void Window::SetBordered(bool bordered) {
  SDL_bool b = BoolConverter::Convert(bordered);
  SDL_SetWindowBordered(sdlWindow, b);
}

void Window::SetWindowIcon(Surface_sptr icon) {
  SDL_SetWindowIcon(sdlWindow, icon->GetSDLVersion());
}

void Window::SetLocation(int x, int y) {
  SDL_SetWindowPosition(sdlWindow, x, y);
}

void Window::SetMaxSize(int width, int height) {
  SDL_SetWindowMaximumSize(sdlWindow, width, height);
}

void Window::SetMinSize(int width, int height) {
  SDL_SetWindowMinimumSize(sdlWindow, width, height);
}

void Window::SetSize(int width, int height) {
  SDL_SetWindowSize(sdlWindow, width, height);
}

void Window::SetTitle(std::string title) {
  SDL_SetWindowTitle(sdlWindow, title.c_str());
}

ITexture_sptr Window::CreateTexture(const std::string& path) const {
  return Texture::CreateShared(path, renderer->GetSDLVersion());
}

Window_sptr Window::CreateShared(int width, int height) {
  return std::make_shared<Window>(width, height);
}

Window_uptr Window::CreateUnique(int width, int height) {
  return std::make_unique<Window>(width, height);
}

Window_wptr Window::CreateWeak(int width, int height) {
  return CreateShared(width, height);
}

}  // namespace visuals
}  // namespace centurion