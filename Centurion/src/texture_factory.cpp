#include "texture_factory.h"
#include "null_checker.h"
#include <stdexcept>

using centurion::visuals::TextureFactory;
using centurion::visuals::Renderer;
using centurion::visuals::Texture;
using centurion::tools::NullChecker;
using std::string;
using std::shared_ptr;
using std::make_shared;
using std::invalid_argument;

SDL_Texture* TextureFactory::CreateSDLTexture(SDL_Surface* surface, SDL_Renderer* renderer)
{
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

shared_ptr<Texture> TextureFactory::CreateTexture(const string& path, SDL_Renderer* renderer)
{
	if (NullChecker::IsNull(renderer)) {
		throw invalid_argument("Null SDL_Renderer when creating Texture!");
	} else {
		SDL_Surface* surface = IMG_Load(path.c_str());
		SDL_Texture* texture = TextureFactory::CreateSDLTexture(surface, renderer);
		int width = surface->w;
		int height = surface->h;
		SDL_FreeSurface(surface);
		return make_shared<Texture>(texture, width, height);
	}
}

shared_ptr<Texture> TextureFactory::CreateTexture(const string& path, const Renderer& renderer)
{
	return TextureFactory::CreateTexture(path, renderer.sdl_renderer);
}