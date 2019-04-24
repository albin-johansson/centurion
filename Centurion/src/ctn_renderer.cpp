#include "ctn_renderer.h"
#include <stdexcept>
#include "ctn_texture.h"

using namespace centurion::geo;

namespace centurion {
namespace visuals {

Renderer::Renderer(SDL_Renderer* renderer) : color(Color::WHITE) {
  if (renderer == nullptr) {
    throw std::invalid_argument("Null renderer!");
  }
  this->sdlRenderer = renderer;
  SDL_SetRenderDrawBlendMode(sdlRenderer, SDL_BLENDMODE_BLEND);
}

Renderer::~Renderer() { SDL_DestroyRenderer(sdlRenderer); }

void Renderer::CheckRenderDimensions(int width, int height) {
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid rendering dimensions!");
  }
}

void Renderer::UpdateColor() noexcept {
  SDL_SetRenderDrawColor(sdlRenderer, color.GetRed(), color.GetGreen(),
                         color.GetBlue(), color.GetAlpha());
}

void Renderer::Update() noexcept { SDL_RenderPresent(sdlRenderer); }

void Renderer::Clear() noexcept { SDL_RenderClear(sdlRenderer); }

void Renderer::Render(SDL_Texture* texture, int x, int y, int w, int h) {
  CheckRenderDimensions(w, h);
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderCopy(sdlRenderer, texture, NULL, &rect);
}

void Renderer::Render(ITexture& tex, int x, int y, int w, int h) {
  CheckRenderDimensions(w, h);
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderCopy(sdlRenderer, tex.GetSDLTexture(), NULL, &rect);
}

void Renderer::Render(ITexture& tex, Rectangle rect) {
  CheckRenderDimensions(rect.GetWidth(), rect.GetHeight());
  SDL_RenderCopy(sdlRenderer, tex.GetSDLTexture(), NULL, &rect.GetSDLVersion());
}

void Renderer::Render(ITexture& tex, int x, int y) {
  Render(tex, x, y, tex.GetWidth(), tex.GetHeight());
}

void Renderer::RenderFilledRect(int x, int y, int w, int h) {
  CheckRenderDimensions(w, h);
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderFillRect(sdlRenderer, &rect);
}

void Renderer::RenderFilledRect(Rectangle rect) {
  CheckRenderDimensions(rect.GetWidth(), rect.GetHeight());
  SDL_RenderFillRect(sdlRenderer, &rect.GetSDLVersion());
}

void Renderer::RenderOutlinedRect(int x, int y, int w, int h) {
  CheckRenderDimensions(w, h);
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderDrawRect(sdlRenderer, &rect);
}

void Renderer::RenderOutlinedRect(Rectangle rect) {
  CheckRenderDimensions(rect.GetWidth(), rect.GetHeight());
  SDL_RenderDrawRect(sdlRenderer, &rect.GetSDLVersion());
}

void Renderer::RenderLine(int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(sdlRenderer, x1, y1, x2, y2);
}

void Renderer::RenderLine(Point p1, Point p2) {
  SDL_RenderDrawLine(sdlRenderer, p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
}

SDL_Texture* Renderer::CreateSDLTextureFromString(const std::string& str,
                                                  int* width, int* height) {
  if (font == nullptr || width == nullptr || height == nullptr) {
    throw std::invalid_argument("Failed to create texture from string!");
  } else {
    SDL_Surface* sdlSurface = TTF_RenderText_Solid(
        font->GetSDLVersion(), str.c_str(), color.GetSDLVersion());
    SDL_Texture* tmp =
        SDL_CreateTextureFromSurface(GetSDLVersion(), sdlSurface);
    *width = sdlSurface->w;
    *height = sdlSurface->h;
    SDL_FreeSurface(sdlSurface);
    return tmp;
  }
}

void Renderer::RenderString(const std::string& text, int x, int y) {
  if (font == nullptr) {
    throw std::invalid_argument("Failed to render text!");
  } else {
    int w, h;
    SDL_Texture* t = CreateSDLTextureFromString(text, &w, &h);
    Render(t, x, y, w, h);
  }
}

void Renderer::SetFont(Font_sptr font) { this->font = font; }

void Renderer::SetColor(Color color) noexcept {
  this->color = color;
  UpdateColor();
}

void Renderer::SetRenderTarget(ITexture_sptr texture) noexcept {
  if (texture == nullptr) {
    SDL_SetRenderTarget(sdlRenderer, NULL);
  } else {
    SDL_SetRenderTarget(sdlRenderer, texture->GetSDLTexture());
  }
}

ITexture_sptr Renderer::CreateTextureFromString(const std::string& str) {
  if (font == nullptr) {
    throw std::invalid_argument("Failed to render text!");
  } else {
    int w = 0;
    int h = 0;
    SDL_Texture* tex = CreateSDLTextureFromString(str, &w, &h);
    return Texture::CreateShared(tex);
  }
}

ITexture_sptr Renderer::CreateSubtexture(ITexture_sptr base, Rectangle src,
                                         Rectangle dst, Uint32 pixelFormat) {
  if (!SDL_RenderTargetSupported(sdlRenderer)) {
    throw std::exception("Subtextures are not available!");
  }
  ITexture_sptr target = CreateRawTexture(
      dst.GetWidth(), dst.GetHeight(), pixelFormat, SDL_TEXTUREACCESS_TARGET);
  SetRenderTarget(target);
  SDL_RenderCopy(sdlRenderer, base->GetSDLTexture(), &src.GetSDLVersion(),
                 &dst.GetSDLVersion());
  Update();
  SetRenderTarget(nullptr);
  return target;
}

ITexture_sptr Renderer::CreateRawTexture(int width, int height,
                                         Uint32 pixelFormat,
                                         SDL_TextureAccess access) {
  if (width < 1 || height < 1) {
    throw std::invalid_argument("Invalid dimensions for raw texture!");
  } else {
    SDL_Texture* t =
        SDL_CreateTexture(sdlRenderer, pixelFormat, access, width, height);
    SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);
    if (t == nullptr) {
      throw std::exception("Failed to create texture!");
    }
    return Texture::CreateShared(t);
  }
}

Renderer_sptr Renderer::CreateShared(SDL_Renderer* renderer) {
  return std::make_shared<Renderer>(renderer);
}

Renderer_uptr Renderer::CreateUnique(SDL_Renderer* renderer) {
  return std::make_unique<Renderer>(renderer);
}

Renderer_wptr Renderer::CreateWeak(SDL_Renderer* renderer) {
  return CreateShared(renderer);
}

}  // namespace visuals
}  // namespace centurion