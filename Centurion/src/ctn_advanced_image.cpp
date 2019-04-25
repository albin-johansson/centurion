#include "ctn_advanced_image.h"

using centurion::geo::Rectangle;

namespace centurion {
namespace visuals {

// ---------------------------------- Private ----------------------------------

void AdvancedImage::Lock() { SDL_LockTexture(texture, NULL, &pixels, &pitch); }

void AdvancedImage::Unlock() {
  SDL_UnlockTexture(texture);
  pixels = nullptr;
  pitch = 0;
}

// -------------------------------- End private --------------------------------

// ----------------------------------- Public ----------------------------------

AdvancedImage::AdvancedImage(const std::string& path, SDL_Renderer* renderer,
                             Uint32 pixelFormat)
    : modColor(Color(255, 255, 255)) {
  this->pixelFormat = pixelFormat;
  this->blendMode = SDL_BLENDMODE_BLEND;
  this->alpha = 255;

  SDL_Surface* src = IMG_Load(path.c_str());
  SDL_SetSurfaceBlendMode(src, blendMode);

  surface = SDL_ConvertSurfaceFormat(src, pixelFormat, NULL);
  SDL_FreeSurface(src);

  SDL_SetSurfaceBlendMode(surface, blendMode);

  width = surface->w;
  height = surface->h;
  Reset(renderer);
  // texture = SDL_CreateTexture(renderer, pixelFormat,
  //                            SDL_TEXTUREACCESS_STREAMING, width, height);
  // SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
  //
  // Lock();
  // if (pixels != nullptr) {
  //  memcpy(pixels, surface->pixels, surface->pitch * surface->h);
  //}
  // Unlock();
}

// AdvancedImage::AdvancedImage(SDL_Texture* texture) {
//  this->texture = texture;
//  Uint32 format = 0;
//  int access = 0;
//  SDL_QueryTexture(texture, &format, &access, &width, &height);
//}

AdvancedImage::~AdvancedImage() {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void AdvancedImage::Reset(SDL_Renderer* renderer) {
  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }

  texture = SDL_CreateTexture(renderer, pixelFormat,
                              SDL_TEXTUREACCESS_STREAMING, width, height);
  SDL_SetTextureBlendMode(texture, blendMode);
  Lock();
  if (pixels != nullptr) {
    memcpy(pixels, surface->pixels, surface->pitch * surface->h);
  }
  Unlock();
}

void AdvancedImage::Revalidate(SDL_Renderer* renderer) {
  // if (texture != nullptr) {
  //  SDL_DestroyTexture(texture);
  //}
  //
  // texture = SDL_CreateTexture(renderer, pixelFormat,
  //                            SDL_TEXTUREACCESS_STREAMING, width, height);
  // SDL_SetTextureBlendMode(texture, blendMode);
  // Lock();
  // if (pixels != nullptr) {
  //  memcpy(pixels, surface->pixels, surface->pitch * surface->h);
  //}
  // Unlock();
  Reset(renderer);
  ModulateColor(modColor);
  SetAlpha(alpha);
  SetBlendMode(blendMode);
}

void AdvancedImage::ModulateColor(Color c) {
  this->modColor = c;
  SDL_SetTextureColorMod(texture, c.GetRed(), c.GetGreen(), c.GetBlue());
}

void AdvancedImage::SetPixel(int x, int y, Color color) {
  Lock();

  // TODO ...

  Unlock();
}

void AdvancedImage::SetAlpha(Uint8 alpha) {
  this->alpha = alpha;
  SDL_SetTextureAlphaMod(texture, alpha);
}

void AdvancedImage::SetBlendMode(SDL_BlendMode blendMode) {
  this->blendMode = blendMode;
  SDL_SetTextureBlendMode(texture, blendMode);
}

// AdvancedImage_sptr AdvancedImage::CreateSubimage(SDL_Renderer* renderer,
//                                                 Rectangle src, Rectangle dst)
//                                                 {
//  if (!SDL_RenderTargetSupported(renderer)) {
//    throw std::exception("Subimages are not available!");
//  }
//
//  Uint32 format = SDL_PIXELFORMAT_RGBA8888;
//  int access = SDL_TEXTUREACCESS_TARGET;
//
//  SDL_Texture* texture =
//      SDL_CreateTexture(renderer, format, access, width, height);
//  SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
//
//  SDL_SetRenderTarget(renderer, texture);
//  SDL_RenderCopy(renderer, texture, &src.GetSDLVersion(),
//  &dst.GetSDLVersion()); SDL_RenderPresent(renderer);
//  SDL_SetRenderTarget(renderer, nullptr);
//
//  return std::make_shared<AdvancedImage>(texture);
//}

// AdvancedImage_sptr AdvancedImage::CreateRawImage(SDL_Renderer* renderer) {
//  // TODO ...
//  return nullptr;
//}

// --------------------------------- End public --------------------------------

}  // namespace visuals
}  // namespace centurion