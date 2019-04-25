#pragma once
#include <SDL_image.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <memory>
#include <string>
#include "ctn_color.h"
#include "ctn_rectangle.h"

namespace centurion {
namespace visuals {

class AdvancedImage;
typedef std::shared_ptr<AdvancedImage> AdvancedImage_sptr;
typedef std::unique_ptr<AdvancedImage> AdvancedImage_uptr;
typedef std::weak_ptr<AdvancedImage> AdvancedImage_wptr;

class AdvancedImage {
 private:
  SDL_Texture* texture = nullptr;
  SDL_Surface* surface = nullptr;

  // pixel stuff
  void* pixels = nullptr;
  int pitch = 0;
  Uint32 pixelFormat = 0;

  int width = 0;
  int height = 0;

  // settings
  SDL_BlendMode blendMode;
  Color modColor;
  Uint8 alpha;

  void Lock();

  void Unlock();

 public:
  AdvancedImage(const std::string& path, SDL_Renderer* renderer,
                Uint32 pixelFormat);

  // AdvancedImage(SDL_Texture* texture);

  ~AdvancedImage();

  void Reset(SDL_Renderer* renderer);

  void Revalidate(SDL_Renderer* renderer);

  void ModulateColor(Color color);

  void SetPixel(int x, int y, Color color);

  void SetAlpha(Uint8 alpha);

  void SetBlendMode(SDL_BlendMode blendMode);

  // AdvancedImage_sptr CreateSubimage(SDL_Renderer* renderer,
  //                                  centurion::geo::Rectangle src,
  //                                  centurion::geo::Rectangle dst);

  inline int GetWidth() const { return width; }

  inline int GetHeight() const { return height; }

  inline SDL_Texture* GetSDLVersion() { return texture; }
};

}  // namespace visuals
}  // namespace centurion