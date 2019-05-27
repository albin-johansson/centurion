#include "ctn_image_impl.h"
#include <SDL_image.h>
#include <stdexcept>

using centurion::geo::Rectangle;

namespace centurion {
namespace visuals {

ImageImpl::ImageImpl(const std::string& path, SDL_Renderer* renderer,
                     Uint32 pixelFormat)
    : modColor(Color(255, 255, 255)) {
  if (renderer == nullptr) {
    throw std::invalid_argument("Null SDL_Renderer pointer!");
  }
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
}

ImageImpl::ImageImpl(const std::string& path, SDL_Renderer* renderer)
    : ImageImpl(path, renderer, SDL_PIXELFORMAT_RGBA8888) {}

ImageImpl::~ImageImpl() {
  SDL_FreeSurface(surface);
  SDL_DestroyTexture(texture);
}

void ImageImpl::Lock() { SDL_LockTexture(texture, NULL, &pixels, &pitch); }

void ImageImpl::Unlock() {
  SDL_UnlockTexture(texture);
  pixels = nullptr;
  pitch = 0;
}

void ImageImpl::Reset(SDL_Renderer* renderer) {
  if (renderer == nullptr) {
    return;
  }

  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }

  texture = SDL_CreateTexture(renderer, pixelFormat,
                              SDL_TEXTUREACCESS_STREAMING, width, height);
  SDL_SetTextureBlendMode(texture, blendMode);
  Lock();
  if (pixels != nullptr) {
    memcpy(pixels, surface->pixels, (surface->pitch * surface->h));
  }
  Unlock();
}

void ImageImpl::Revalidate(SDL_Renderer* renderer) {
  if (renderer == nullptr) {
    return;
  }
  Reset(renderer);
  ModulateColor(modColor);
  SetAlpha(alpha);
  SetBlendMode(blendMode);
}

void ImageImpl::ModulateColor(Color c) noexcept {
  this->modColor = c;
  SDL_SetTextureColorMod(texture, c.GetRed(), c.GetGreen(), c.GetBlue());
}

void ImageImpl::SetPixel(int x, int y, Color color) {
  Lock();

  int nPixels = (pitch / 4) * height;
  int index = (y * width) + x;
  if ((index >= 0) && (index < nPixels)) {
    SDL_PixelFormat* pixFormat = SDL_AllocFormat(pixelFormat);

    Uint8 r = color.GetRed();
    Uint8 g = color.GetGreen();
    Uint8 b = color.GetBlue();
    Uint8 a = color.GetAlpha();
    Uint32 colorKey = SDL_MapRGBA(pixFormat, r, g, b, a);

    Uint32* pixelArr = (Uint32*)pixels;

    pixelArr[index] = colorKey;

    SDL_FreeFormat(pixFormat);
  }
  Unlock();
}

void ImageImpl::SetAlpha(Uint8 alpha) noexcept {
  this->alpha = alpha;
  SDL_SetTextureAlphaMod(texture, alpha);
}

void ImageImpl::SetBlendMode(SDL_BlendMode blendMode) noexcept {
  this->blendMode = blendMode;
  SDL_SetTextureBlendMode(texture, blendMode);
}

IImage_sptr ImageImpl::CreateShared(const std::string& path,
                                    SDL_Renderer* renderer,
                                    Uint32 pixelFormat) {
  return std::make_shared<ImageImpl>(path, renderer, pixelFormat);
}

IImage_sptr ImageImpl::CreateShared(const std::string& path,
                                    SDL_Renderer* renderer) {
  return std::make_shared<ImageImpl>(path, renderer);
}

IImage_uptr ImageImpl::CreateUnique(const std::string& path,
                                    SDL_Renderer* renderer,
                                    Uint32 pixelFormat) {
  return std::make_unique<ImageImpl>(path, renderer, pixelFormat);
}

IImage_uptr ImageImpl::CreateUnique(const std::string& path,
                                    SDL_Renderer* renderer) {
  return std::make_unique<ImageImpl>(path, renderer);
}

}  // namespace visuals
}  // namespace centurion