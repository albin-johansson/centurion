#include "window.h"
#include <SDL_stdinc.h>
#include <SDL_video.h>
#include <stdexcept>
#include "ctn_bool_converter.h"
#include "ctn_positionable.h"
#include "ctn_texture_factory.h"

using centurion::geo::IPositionable;
using centurion::geo::Point;
using centurion::geo::Rectangle;
using centurion::tools::BoolConverter;

namespace centurion {
namespace visuals {

Window::Window(const std::string& title, int width, int height, uint32_t flags)
    : width(width), height(height) {
  CheckWindowDimensions(width, height);
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, flags);
  SDL_Renderer* sdl_renderer = SDL_CreateRenderer(
      window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
  renderer = std::make_unique<Renderer>(sdl_renderer);
  drawable = nullptr;
}

Window::~Window() {
  SDL_HideWindow(window);
  SDL_DestroyWindow(window);
}

void Window::CheckWindowDimensions(int width, int height) {
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid dimensions for window!");
  }
}

void Window::Show() { SDL_ShowWindow(window); }

void Window::Hide() { SDL_HideWindow(window); }

void Window::SetResizable(bool resizable) {
  SDL_bool b = BoolConverter::Convert(resizable);
  SDL_SetWindowResizable(window, b);
}

void Window::Render() {
  if (drawable != nullptr) {
    drawable->Draw(*renderer);
  }
  renderer->Update();
}

void Window::SetDrawable(const std::shared_ptr<IDrawable> drawable) {
  this->drawable = drawable;
}

void Window::Clear() { renderer->Clear(); }

void Window::Render(Texture& texture, int x, int y, int w, int h) {
  renderer->Render(texture, x, y, w, h);
}

void Window::Render(Texture& texture, const Rectangle rect) {
  renderer->Render(texture, rect);
}

void Window::Render(Texture& texture, int x, int y) {
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

void Window::SetFont(const std::shared_ptr<Font> font) {
  renderer->SetFont(font);  // TODO change signature to Font_sptr
}

void Window::SetColor(Color color) { renderer->SetColor(color); }

void Window::SetRenderTarget(Texture_sptr texture) {
  renderer->SetRenderTarget(texture);
}

std::shared_ptr<Texture> Window::CreateTextureFromString(
    const std::string& str) const {
  return renderer->CreateTextureFromString(str);
}

std::shared_ptr<Texture> Window::CreateTexture(const std::string& path) const {
  return TextureFactory::CreateTexture(path, renderer->GetSDLVersion());
}

Texture_sptr Window::CreateRawTexture(int width, int height,
                                      SDL_TextureAccess access) {
  Uint32 pixelFormat = SDL_GetWindowPixelFormat(window);
  return renderer->CreateRawTexture(width, height, pixelFormat, access);
}

Texture_sptr Window::CreateSubtexture(Texture_sptr base, Rectangle src,
                                      int width, int height) {
  Uint32 pixelFormat = SDL_GetWindowPixelFormat(window);
  Rectangle dst = Rectangle(0, 0, width, height);
  return renderer->CreateSubtexture(base, src, dst, pixelFormat);
}

Window_sptr Window::CreateShared(const std::string& title, int width,
                                 int height, uint32_t flags) {
  return std::make_shared<Window>(title, width, height, flags);
}

Window_uptr Window::CreateUnique(const std::string& title, int width,
                                 int height, uint32_t flags) {
  return std::make_unique<Window>(title, width, height, flags);
}

Window_wptr Window::CreateWeak(const std::string& title, int width, int height,
                               uint32_t flags) {
  return CreateShared(title, width, height, flags);
}

}  // namespace visuals
}  // namespace centurion