#include "window.h"
#include <memory>
#include <stdexcept>
#include <string>
#include "boolean_converter.h"
#include "drawable.h"
#include "font.h"
#include "positionable.h"
#include "rectangle.h"
#include "renderer.h"

using centurion::geo::Point;
using centurion::geo::Positionable;
using centurion::geo::Rectangle;
using centurion::tools::BooleanConverter;
using centurion::visuals::Font;

namespace centurion {
namespace visuals {

Window::Window(const std::string& title, int width, int height, Uint32 flags)
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
  SDL_Delay(1);
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
  SDL_bool b = BooleanConverter::Convert(resizable);
  SDL_SetWindowResizable(window, b);
}

void Window::Render() {
  // renderer->Clear();
  if (drawable != nullptr) {
    drawable->Draw(*renderer);
  }
  renderer->Update();
}

void Window::SetDrawable(const std::shared_ptr<Drawable> drawable) {
  this->drawable = drawable;
}

void Window::Clear() { renderer->Clear(); }

void Window::Render(Texture& texture, int x, int y, int w, int h) {
  renderer->Render(texture, x, y, w, h);
}

void Window::Render(Texture& texture, const Rectangle& rect) {
  renderer->Render(texture, rect);
}

void Window::Render(Texture& texture, int x, int y) {
  renderer->Render(texture, x, y);
}

void Window::Render(Texture& texture, const Positionable& posit,
                    const Dimensioned& dimensioned) {
  renderer->Render(texture, posit, dimensioned);
}

void Window::RenderFilledRect(int x, int y, int w, int h) {
  renderer->RenderFilledRect(x, y, w, h);
}

void Window::RenderOutlinedRect(int x, int y, int w, int h) {
  renderer->RenderOutlinedRect(x, y, w, h);
}

void Window::RenderLine(int x1, int y1, int x2, int y2) {
  renderer->RenderLine(x1, y1, x2, y2);
}

void Window::RenderLine(Point p1, Point p2) { renderer->RenderLine(p1, p2); }

void Window::RenderText(const std::string& text, int x, int y) {
  renderer->RenderText(text, x, y);
}

void Window::SetFont(const std::shared_ptr<Font> font) {
  renderer->SetFont(font);
}

void Window::SetColor(Color color) { renderer->SetColor(color); }

}  // namespace visuals
}  // namespace centurion