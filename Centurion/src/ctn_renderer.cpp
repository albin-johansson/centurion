#include "ctn_renderer.h"
#include <stdexcept>
#include "ctn_texture.h"

using namespace centurion::geo;

namespace centurion {
namespace visuals {

Renderer::Renderer(SDL_Renderer* sdlRenderer) {
  if (sdlRenderer == nullptr) {
    throw std::invalid_argument("Null pointer to SDL_Renderer!");
  }
  this->sdlRenderer = sdlRenderer;
}

Renderer::~Renderer() { SDL_DestroyRenderer(sdlRenderer); }

SDL_Texture* Renderer::CreateSDLTextureFromString(const std::string& str) {
  if (font == nullptr) {
    throw std::exception("Failed to create texture!");
  }
  TTF_Font* f = font->GetSDLVersion();
  SDL_Color c = color.GetSDLVersion();

  SDL_Surface* surface = TTF_RenderText_Solid(f, str.c_str(), c);
  SDL_Texture* texture = SDL_CreateTextureFromSurface(GetSDLVersion(), surface);
  SDL_FreeSurface(surface);

  return texture;
}

void Renderer::ApplyRendering() noexcept { SDL_RenderPresent(sdlRenderer); }

void Renderer::RenderClear() noexcept { SDL_RenderClear(sdlRenderer); }

void Renderer::Render(ITexture& texture, int x, int y, int w, int h) noexcept {
  if (IsValid(w, h)) {
    SDL_Rect dst = {x, y, w, h};
    SDL_RenderCopy(sdlRenderer, texture.GetSDLTexture(), NULL, &dst);
  }
}

void Renderer::Render(ITexture& texture, Rectangle src,
                      Rectangle dst) noexcept {
  SDL_Rect s = src.GetSDLVersion();
  SDL_Rect d = dst.GetSDLVersion();
  SDL_RenderCopy(sdlRenderer, texture.GetSDLTexture(), &s, &d);
}

void Renderer::Render(ITexture& texture, int x, int y) noexcept {
  SDL_Rect dst = {x, y, texture.GetWidth(), texture.GetHeight()};
  SDL_RenderCopy(sdlRenderer, texture.GetSDLTexture(), NULL, &dst);
}

void Renderer::Render(ITexture& texture, int x, int y, int angle,
                      SDL_RendererFlip flip) noexcept {
  SDL_Rect dst = {x, y, texture.GetWidth(), texture.GetHeight()};
  angle %= 360;
  SDL_RenderCopyEx(sdlRenderer, texture.GetSDLTexture(), NULL, &dst, angle,
                   NULL, flip);
}

void Renderer::Render(ITexture& texture, int x, int y,
                      SDL_RendererFlip flip) noexcept {
  Render(texture, x, y, 0, flip);
}

void Renderer::Render(ITexture& texture, int x, int y, int angle) noexcept {
  Render(texture, x, y, angle, SDL_FLIP_NONE);
}

void Renderer::RenderOutlinedRect(Rectangle rect) noexcept {
  SDL_RenderDrawRect(sdlRenderer, &rect.GetSDLVersion());
}

void Renderer::RenderFilledRect(Rectangle rect) noexcept {
  SDL_RenderFillRect(sdlRenderer, &rect.GetSDLVersion());
}

void Renderer::RenderLine(Point p1, Point p2) noexcept {
  SDL_RenderDrawLine(sdlRenderer, p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
}

void Renderer::RenderString(const std::string& str, int x, int y) {
  if (font == nullptr) {
    return;
  }
  SDL_Texture* texture = CreateSDLTextureFromString(str);
  Texture tmp = Texture(texture);
  Render(tmp, x, y);
}

void Renderer::SetRenderTarget(ITexture_sptr texture) noexcept {
  if (texture == nullptr) {
    SDL_SetRenderTarget(sdlRenderer, NULL);
  } else {
    SDL_SetRenderTarget(sdlRenderer, texture->GetSDLTexture());
  }
}

void Renderer::SetFont(Font_sptr font) noexcept { this->font = font; }

void Renderer::SetColor(Color c) noexcept {
  SDL_SetRenderDrawColor(sdlRenderer, c.GetRed(), c.GetGreen(), c.GetBlue(),
                         c.GetAlpha());
}

ITexture_sptr Renderer::CreateTextureFromString(const std::string& str) {
  SDL_Texture* texture = CreateSDLTextureFromString(str);
  return Texture::CreateShared(texture);
}

ITexture_sptr Renderer::CreateSubtexture(ITexture_sptr base, Rectangle cutout,
                                         int w, int h, Uint32 format) {
  if (!SDL_RenderTargetSupported(sdlRenderer)) {
    throw std::exception("Subtextures are not available!");
  }

  SDL_TextureAccess access = SDL_TEXTUREACCESS_TARGET;
  ITexture_sptr result = CreateEmptyTexture(w, h, format, access);

  SDL_Rect src = cutout.GetSDLVersion();
  SDL_Rect dst = {0, 0, w, h};

  SetRenderTarget(result);
  SDL_RenderCopy(sdlRenderer, base->GetSDLTexture(), &src, &dst);
  ApplyRendering();
  SetRenderTarget(nullptr);

  return result;
}

ITexture_sptr Renderer::CreateEmptyTexture(int w, int h, Uint32 format,
                                           SDL_TextureAccess access) {
  if (!IsValid(w, h)) {
    throw std::invalid_argument("Invalid dimensions!");
  }

  SDL_Texture* t = SDL_CreateTexture(sdlRenderer, format, access, w, h);

  if (t == nullptr) {
    throw std::exception("Failed to create texture!");
  }

  SDL_SetTextureBlendMode(t, SDL_BLENDMODE_BLEND);

  return Texture::CreateShared(t);
}

ITexture_sptr Renderer::CreateRenderTarget(int w, int h) {
  Uint32 format = SDL_PIXELFORMAT_RGBA8888;
  SDL_TextureAccess access = SDL_TEXTUREACCESS_TARGET;
  return CreateEmptyTexture(w, h, format, access);
}

IRenderer_sptr Renderer::CreateShared(SDL_Renderer* renderer) {
  return std::make_shared<Renderer>(renderer);
}

IRenderer_uptr Renderer::CreateUnique(SDL_Renderer* renderer) {
  return std::make_unique<Renderer>(renderer);
}

IRenderer_wptr Renderer::CreateWeak(SDL_Renderer* renderer) {
  return CreateShared(renderer);
}

}  // namespace visuals
}  // namespace centurion