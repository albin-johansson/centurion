#include "ctn_window.h"
#include <stdexcept>
#include "ctn_bool_converter.h"
#include "ctn_screen.h"
#include "ctn_texture.h"

using namespace centurion::geo;
using namespace centurion::tools;

namespace centurion {
namespace visuals {

Window::Window() {
  Uint32 flags = SDL_WINDOW_HIDDEN;
  windowedWidth = 800;
  windowedHeight = 600;
  sdlWindow = SDL_CreateWindow("Centurion window", SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, windowedWidth,
                               windowedHeight, flags);
  Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE;
  SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, rendererFlags);
  renderer = Renderer::CreateUnique(sdlRenderer);
  isFullscreen = false;
}

Window::~Window() {
  SDL_HideWindow(sdlWindow);
  SDL_DestroyWindow(sdlWindow);
}

void Window::CheckWindowDimensions(int width, int height) {
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid dimensions for window!");
  }
}

void Window::Show() { SDL_ShowWindow(sdlWindow); }

void Window::Hide() { SDL_HideWindow(sdlWindow); }

void Window::SetResizable(bool resizable) {
  SDL_bool b = BoolConverter::Convert(resizable);
  SDL_SetWindowResizable(sdlWindow, b);
}

// FIXME SetFullscreen is broken
void Window::SetFullscreen(bool fullscreen) {
  // SDL_SetRelativeMouseMode(SDL_TRUE);
  if (fullscreen) {
    SDL_SetWindowFullscreen(sdlWindow, SDL_WINDOW_FULLSCREEN);
  } else {
    SDL_SetWindowFullscreen(sdlWindow, 0);
    SDL_SetWindowSize(sdlWindow, windowedWidth, windowedHeight);
  }
  isFullscreen = !isFullscreen;
  // SDL_SetRelativeMouseMode(SDL_FALSE);
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

void Window::SetMaximumSize(int width, int height) {
  SDL_SetWindowMaximumSize(sdlWindow, width, height);
}

void Window::SetMinimumSize(int width, int height) {
  SDL_SetWindowMinimumSize(sdlWindow, width, height);
}

void Window::SetTitle(std::string title) {
  SDL_SetWindowTitle(sdlWindow, title.c_str());
}

void Window::SetWindowedSize(int width, int height) {
  SDL_SetWindowSize(sdlWindow, width, height);
  this->windowedWidth = width;
  this->windowedHeight = height;
}

void Window::ApplyRendering() {
  if (drawable != nullptr) {
    drawable->Draw(*renderer);
  }
  renderer->Update();
}

void Window::SetDrawable(const IDrawable_sptr drawable) {
  this->drawable = drawable;
}

void Window::Clear() { renderer->Clear(); }

void Window::Render(ITexture& texture, int x, int y, int w, int h) {
  renderer->Render(texture, x, y, w, h);
}

void Window::Render(ITexture& texture, const Rectangle rect) {
  renderer->Render(texture, rect);
}

void Window::Render(ITexture& texture, int x, int y) {
  renderer->Render(texture, x, y);
}

void Window::RenderFilledRect(int x, int y, int w, int h) {
  renderer->RenderFilledRect(x, y, w, h);
}

void Window::RenderFilledRect(Rectangle rect) {
  renderer->RenderFilledRect(rect);
}

void Window::RenderOutlinedRect(int x, int y, int w, int h) {
  renderer->RenderOutlinedRect(x, y, w, h);
}

void Window::RenderOutlinedRect(Rectangle rect) {
  renderer->RenderOutlinedRect(rect);
}

void Window::RenderLine(int x1, int y1, int x2, int y2) {
  renderer->RenderLine(x1, y1, x2, y2);
}

void Window::RenderLine(Point p1, Point p2) { renderer->RenderLine(p1, p2); }

void Window::RenderString(const std::string& text, int x, int y) {
  renderer->RenderString(text, x, y);
}

void Window::SetFont(const Font_sptr font) { renderer->SetFont(font); }

void Window::SetColor(Color color) { renderer->SetColor(color); }

void Window::SetRenderTarget(ITexture_sptr texture) noexcept {
  renderer->SetRenderTarget(texture);
}

int Window::GetWidth() const noexcept {
  int w = 0;
  int h = 0;
  SDL_GetWindowSize(sdlWindow, &w, &h);
  return w;
}

int Window::GetHeight() const noexcept {
  int w = 0;
  int h = 0;
  SDL_GetWindowSize(sdlWindow, &w, &h);
  return h;
}

ITexture_sptr Window::CreateTextureFromString(const std::string& str) const {
  return renderer->CreateTextureFromString(str);
}

ITexture_sptr Window::CreateTexture(const std::string& path) const {
  return Texture::CreateShared(path, renderer->GetSDLVersion());
}

ITexture_sptr Window::CreateRawTexture(int width, int height,
                                       SDL_TextureAccess access) {
  Uint32 pixelFormat = SDL_GetWindowPixelFormat(sdlWindow);
  return renderer->CreateRawTexture(width, height, pixelFormat, access);
}

ITexture_sptr Window::CreateSubtexture(ITexture_sptr base, Rectangle src,
                                       int width, int height) {
  Uint32 pixelFormat = SDL_GetWindowPixelFormat(sdlWindow);
  Rectangle dst = Rectangle(0, 0, width, height);
  return renderer->CreateSubtexture(base, src, dst, pixelFormat);
}

Window_sptr Window::CreateShared() { return std::make_shared<Window>(); }

Window_uptr Window::CreateUnique() { return std::make_unique<Window>(); }

Window_wptr Window::CreateWeak() { return CreateShared(); }

}  // namespace visuals
}  // namespace centurion