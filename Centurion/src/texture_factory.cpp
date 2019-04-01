#include "texture_factory.h"
#include <stdexcept>
#include "null_checker.h"

using centurion::tools::NullChecker;
using centurion::visuals::Renderer;
using centurion::visuals::Texture;
using centurion::visuals::TextureFactory;
using std::invalid_argument;
using std::make_shared;
using std::shared_ptr;
using std::string;

SDL_Texture* TextureFactory::CreateSDLTexture(SDL_Surface* surface,
                                              SDL_Renderer* renderer) {
  if (NullChecker::IsNull(surface) || NullChecker::IsNull(renderer)) {
    throw invalid_argument("Null renderer or surface when creating texture!");
  } else {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) {
      SDL_Log("Failed to create texture from surface!");
    }
    return texture;
  }
}

shared_ptr<Texture> TextureFactory::CreateTexture(const string& path,
                                                  SDL_Renderer* renderer) {
  if (NullChecker::IsNull(renderer)) {
    throw invalid_argument("Null SDL_Renderer when creating Texture!");
  } else {
    SDL_Surface* surface = IMG_Load(path.c_str()); //TODO error msg when invalid path is used
    SDL_Texture* texture = TextureFactory::CreateSDLTexture(surface, renderer);
    int width = surface->w;
    int height = surface->h;
    SDL_FreeSurface(surface);
    return make_shared<Texture>(texture, width, height);
  }
}

shared_ptr<Texture> TextureFactory::CreateTexture(const string& path,
                                                  const Renderer& renderer) {
  return TextureFactory::CreateTexture(path, renderer.GetSDLRenderer());
}