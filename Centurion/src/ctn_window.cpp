#include "ctn_window.h"
#include <stdexcept>
#include "ctn_bool_converter.h"
#include "ctn_texture_factory.h"

using namespace centurion::geo;
using centurion::tools::BoolConverter;

namespace centurion {
namespace visuals {

// TODO use methods rather than the flags parameter
Window::Window(const std::string& title, int width, int height)
    : width(width), height(height) {
  CheckWindowDimensions(width, height);
  Uint32 flags = SDL_WINDOW_HIDDEN;
  sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                               SDL_WINDOWPOS_CENTERED, width, height, flags);

  Uint32 rendererFlags = SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_SOFTWARE;
  SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, rendererFlags);

  renderer = Renderer::CreateUnique(sdlRenderer);
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

/*
void toggleWindowed()
{
        //Grab the mouse so that we don't end up with unexpected movement when
the dimensions/position of the sdlWindow changes.
        SDL_SetRelativeMouseMode(SDL_TRUE);
        windowed = !windowed;
        if (windowed)
        {
                int i = SDL_GetWindowDisplayIndex(win);
                screenWidth = windowedWidth;
                screenHeight = windowedHeight;
                SDL_SetWindowFullscreen(win, 0);
        }
        else
        {
                int i = SDL_GetWindowDisplayIndex(win);
                SDL_Rect j;
                SDL_GetDisplayBounds(i, &j);
                screenWidth = j.w;
                screenHeight = j.h;
                SDL_SetWindowFullscreen(win, SDL_WINDOW_FULLSCREEN_DESKTOP);
        }
        recalculateResolution(); //This function sets appropriate font sizes/UI
positions
}
*/
void Window::SetFullscreen(bool fullscreen) {
  // TODO implement
}

void Window::SetBordered(bool bordered) {
  SDL_bool b = BoolConverter::Convert(bordered);
  SDL_SetWindowBordered(sdlWindow, b);
}

void Window::SetWindowIcon(Texture_sptr icon) {
  // TODO implement
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

void Window::SetSize(int width, int height) {
  SDL_SetWindowSize(sdlWindow, width, height);
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

void Window::Render(Image& texture, int x, int y, int w, int h) {
  renderer->Render(texture, x, y, w, h);
}

void Window::Render(Image& texture, const Rectangle rect) {
  renderer->Render(texture, rect);
}

void Window::Render(Image& texture, int x, int y) {
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

void Window::SetRenderTarget(Texture_sptr texture) {
  renderer->SetRenderTarget(texture);
}

Texture_sptr Window::CreateTextureFromString(const std::string& str) const {
  return renderer->CreateTextureFromString(str);
}

Texture_sptr Window::CreateTexture(const std::string& path) const {
  return TextureFactory::CreateTexture(path, renderer->GetSDLVersion());
}

Texture_sptr Window::CreateRawTexture(int width, int height,
                                      SDL_TextureAccess access) {
  Uint32 pixelFormat = SDL_GetWindowPixelFormat(sdlWindow);
  return renderer->CreateRawTexture(width, height, pixelFormat, access);
}

Texture_sptr Window::CreateSubtexture(Texture_sptr base, Rectangle src,
                                      int width, int height) {
  Uint32 pixelFormat = SDL_GetWindowPixelFormat(sdlWindow);
  Rectangle dst = Rectangle(0, 0, width, height);
  return renderer->CreateSubtexture(base, src, dst, pixelFormat);
}

Window_sptr Window::CreateShared(const std::string& title, int width,
                                 int height) {
  return std::make_shared<Window>(title, width, height);
}

Window_uptr Window::CreateUnique(const std::string& title, int width,
                                 int height) {
  return std::make_unique<Window>(title, width, height);
}

Window_wptr Window::CreateWeak(const std::string& title, int width,
                               int height) {
  return CreateShared(title, width, height);
}

}  // namespace visuals
}  // namespace centurion