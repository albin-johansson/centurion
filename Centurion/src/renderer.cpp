#include "renderer.h"
#include <stdexcept>
#include <string>
#include "color.h"
#include "dimensioned.h"
#include "font.h"
#include "null_checker.h"
#include "point.h"
#include "positionable.h"
#include "rectangle.h"
#include "texture.h"

using centurion::geo::Dimensioned;
using centurion::geo::Point;
using centurion::geo::Positionable;
using centurion::geo::Rectangle;
using centurion::tools::NullChecker;
using std::invalid_argument;
using std::make_shared;
using std::shared_ptr;
using std::string;

// FIXME fix doc comments refering textures as "images"

namespace centurion {
namespace visuals {

Renderer::Renderer(SDL_Renderer* renderer) {
  if (NullChecker::IsNull(renderer)) {
    throw invalid_argument("Null renderer!");
  }
  this->sdl_renderer = renderer;
}

Renderer::~Renderer() { SDL_DestroyRenderer(sdl_renderer); }

void Renderer::CheckRenderDimensions(int width, int height) {
  if (width < 1 || height < 1) {
    throw invalid_argument("Invalid rendering dimensions!");
  }
}

void Renderer::UpdateColor() {
  SDL_SetRenderDrawColor(sdl_renderer, color.GetRed(), color.GetGreen(),
                         color.GetBlue(), color.GetAlpha());
}

void Renderer::Update() { SDL_RenderPresent(sdl_renderer); }

void Renderer::Clear() { SDL_RenderClear(sdl_renderer); }

void Renderer::Render(Texture& img, int x, int y, int w, int h) {
  CheckRenderDimensions(w, h);
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderCopy(sdl_renderer, &img.GetSDLTexture(), NULL, &rect);
}

void Renderer::Render(Texture& img, const Rectangle& rect) {
  CheckRenderDimensions(rect.GetWidth(), rect.GetHeight());
  SDL_RenderCopy(sdl_renderer, &img.GetSDLTexture(), NULL,
                 &rect.GetSDLVersion());
}

void Renderer::Render(Texture& texture, const Positionable& pos,
                      const Dimensioned& dim) {
  CheckRenderDimensions(dim.GetWidth(), dim.GetHeight());
  SDL_Rect rect = {pos.GetX(), pos.GetY(), dim.GetWidth(), dim.GetHeight()};
  SDL_RenderCopy(sdl_renderer, &texture.GetSDLTexture(), NULL, &rect);
}

void Renderer::Render(Texture& img, int x, int y) {
  Render(img, x, y, img.GetWidth(), img.GetHeight());
}

void Renderer::RenderFilledRect(int x, int y, int w, int h) {
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderFillRect(sdl_renderer, &rect);
}

void Renderer::RenderOutlinedRect(int x, int y, int w, int h) {
  SDL_Rect rect = {x, y, w, h};
  SDL_RenderDrawRect(sdl_renderer, &rect);
}

void Renderer::RenderLine(int x1, int y1, int x2, int y2) {
  SDL_RenderDrawLine(sdl_renderer, x1, y1, x2, y2);
}

void Renderer::RenderLine(Point p1, Point p2) {
  SDL_RenderDrawLine(sdl_renderer, p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
}

SDL_Texture* Renderer::CreateSDLTextureFromString(const string& str, int* width,
                                                  int* height) {
  if (font == nullptr || width == nullptr || height == nullptr) {
    throw invalid_argument("Failed to create texture from string!");
  } else {
    SDL_Surface* surface = TTF_RenderText_Solid(
        font->GetSDLVersion(), str.c_str(), color.GetSDLVersion());
    SDL_Texture* tmp = SDL_CreateTextureFromSurface(GetSDLRenderer(), surface);
    *width = surface->w;
    *height = surface->h;
    SDL_FreeSurface(surface);
    return tmp;
  }
}

void Renderer::RenderText(const string& text, int x, int y) {
  if (font == nullptr) {
    throw invalid_argument("Failed to render tetx!");
  } else {
    int w, h;
    SDL_Texture* t = CreateSDLTextureFromString(text, &w, &h);
    Texture texture = Texture(t, w, h);
    Render(texture, x, y);
  }
}

shared_ptr<Texture> Renderer::CreateTextureFromString(const string& str) {
  if (font == nullptr) {
    throw invalid_argument("Failed to render tetx!");
  } else {
    int w, h;
    SDL_Texture* t = CreateSDLTextureFromString(str, &w, &h);
    return make_shared<Texture>(t, w, h);
  }
}

void Renderer::SetFont(const shared_ptr<Font> font)  // TODO Keep?
{
  this->font = font;
}

void Renderer::SetColor(Color color) {
  this->color = color;
  UpdateColor();
}

}  // namespace visuals
}  // namespace centurion