#include "ctn_abstract_window.h"
#include <stdexcept>
#include <string>
#include "ctn_renderer.h"

using namespace centurion::geo;

namespace centurion {
namespace visuals {

AbstractWindow::AbstractWindow(SDL_Window* sdlWindow) {
  if (sdlWindow == nullptr) {
    throw std::invalid_argument("Null SDL_Window pointer!");
  }
  this->sdlWindow = sdlWindow;
  Uint32 flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE |
                 SDL_RENDERER_PRESENTVSYNC;
  SDL_Renderer* sdlRenderer = SDL_CreateRenderer(sdlWindow, -1, flags);
  SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
  renderer = Renderer::CreateShared(sdlRenderer);
}

AbstractWindow::~AbstractWindow() { SDL_DestroyWindow(sdlWindow); }

void AbstractWindow::ApplyRendering() noexcept { renderer->ApplyRendering(); }

void AbstractWindow::RenderClear() noexcept { renderer->RenderClear(); }

void AbstractWindow::Render(ITexture& texture, int x, int y) noexcept {
  renderer->Render(texture, x, y);
}

void AbstractWindow::Render(ITexture& texture, Rectangle src,
                            Rectangle dst) noexcept {
  renderer->Render(texture, src, dst);
}

void AbstractWindow::Render(ITexture& texture, int x, int y, int w,
                            int h) noexcept {
  renderer->Render(texture, x, y, w, h);
}

void AbstractWindow::Render(ITexture& texture, int x, int y, int angle,
                            SDL_RendererFlip flip) noexcept {
  renderer->Render(texture, x, y, angle, flip);
}

void AbstractWindow::Render(ITexture& texture, int x, int y,
                            SDL_RendererFlip flip) noexcept {
  renderer->Render(texture, x, y, flip);
}

void AbstractWindow::Render(ITexture& texture, int x, int y,
                            int angle) noexcept {
  renderer->Render(texture, x, y, angle);
}

void AbstractWindow::RenderOutlinedRect(Rectangle rect) noexcept {
  renderer->RenderOutlinedRect(rect);
}

void AbstractWindow::RenderFilledRect(Rectangle rect) noexcept {
  renderer->RenderFilledRect(rect);
}

void AbstractWindow::RenderLine(Point p1, Point p2) noexcept {
  renderer->RenderLine(p1, p2);
}

void AbstractWindow::RenderString(const std::string& str, int x, int y) {
  renderer->RenderString(str, x, y);
}

void AbstractWindow::SetRenderTarget(ITexture_sptr texture) noexcept {
  renderer->SetRenderTarget(texture);
}

void AbstractWindow::SetFont(Font_sptr font) noexcept {
  renderer->SetFont(font);
}

void AbstractWindow::SetColor(Color color) noexcept {
  renderer->SetColor(color);
}

ITexture_sptr AbstractWindow::CreateTextureFromString(const std::string& str) {
  return renderer->CreateTextureFromString(str);
}

ITexture_sptr AbstractWindow::CreateTextureFromStringShaded(
    const std::string& str) {
  return renderer->CreateTextureFromStringShaded(str);
}

ITexture_sptr AbstractWindow::CreateTextureFromStringWrapped(
    const std::string& str, int wrap) {
  return renderer->CreateTextureFromStringWrapped(str, wrap);
}

ITexture_sptr AbstractWindow::CreateSubtexture(ITexture_sptr base,
                                               Rectangle cutout, int w, int h,
                                               Uint32 format) {
  return renderer->CreateSubtexture(base, cutout, w, h, format);
}

ITexture_sptr AbstractWindow::CreateEmptyTexture(int width, int height,
                                                 Uint32 format,
                                                 SDL_TextureAccess access) {
  return renderer->CreateEmptyTexture(width, height, format, access);
}

ITexture_sptr AbstractWindow::CreateRenderTarget(int width, int height) {
  return renderer->CreateRenderTarget(width, height);
}

void AbstractWindow::Show() noexcept { SDL_ShowWindow(sdlWindow); }

void AbstractWindow::Hide() noexcept { SDL_HideWindow(sdlWindow); }

int AbstractWindow::GetWidth() const noexcept {
  int w = 0;
  SDL_GetWindowSize(sdlWindow, &w, NULL);
  return w;
}

int AbstractWindow::GetHeight() const noexcept {
  int h = 0;
  SDL_GetWindowSize(sdlWindow, NULL, &h);
  return h;
}

}  // namespace visuals
}  // namespace centurion