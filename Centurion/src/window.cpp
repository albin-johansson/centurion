#include "window.h"
#include <memory>
#include <stdexcept>
#include "boolean_converter.h"
#include "drawable.h"
#include "renderer.h"

using centurion::tools::BooleanConverter;
using centurion::visuals::Drawable;
using centurion::visuals::Renderer;
using centurion::visuals::Window;
using std::invalid_argument;
using std::make_unique;
using std::shared_ptr;

Window::Window(const std::string& title, int width, int height, Uint32 flags)
    : width(width), height(height) {
  CheckWindowDimensions(width, height);
  window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, width, height, flags);
  SDL_Renderer* sdl_renderer = SDL_CreateRenderer(
      window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
  renderer = make_unique<Renderer>(sdl_renderer);
  drawable = nullptr;
}

Window::~Window() {
  SDL_HideWindow(window);
  SDL_Delay(1);
  SDL_DestroyWindow(window);
}

void Window::CheckWindowDimensions(int width, int height) {
  if (width < 1 || height < 1) {
    throw invalid_argument("Invalid dimensions for window!");
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

void Window::SetDrawable(const shared_ptr<Drawable> drawable) {
  this->drawable = drawable;
}

void Window::Clear() { renderer->Clear(); }

void Window::Render(centurion::visuals::Texture& texture, int x, int y, int w,
                    int h) {
  renderer->Render(texture, x, y, w, h);
}

void Window::Render(centurion::visuals::Texture& texture,
                    const centurion::geo::Rectangle& rect) {
  renderer->Render(texture, rect);
}

void Window::Render(centurion::visuals::Texture& texture, int x, int y) {
  renderer->Render(texture, x, y);
}

void Window::Render(centurion::visuals::Texture& texture,
                    const centurion::geo::Positionable& posit,
                    const centurion::geo::Dimensioned& dimensioned) {
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

void Window::RenderLine(centurion::geo::Point p1, centurion::geo::Point p2) {
  renderer->RenderLine(p1, p2);
}

void Window::RenderText(const std::string& text, int x, int y) {
  renderer->RenderText(text, x, y);
}

void Window::SetFont(const std::shared_ptr<centurion::visuals::Font> font) {
  renderer->SetFont(font);
}

void Window::SetColor(centurion::visuals::Color color) {
  renderer->SetColor(color);
}