#include "Image.h"
#include <SDL_image.h>

namespace ctn = centurion;

ctn::Image::Image(std::string path, SDL_Renderer* renderer)
{
	texture = createTexture(path, renderer);
}

ctn::Image::~Image()
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* ctn::Image::createTexture(std::string path, SDL_Renderer* renderer)
{
	SDL_Texture* texture = NULL;
	SDL_Surface* surface = IMG_Load(path.c_str());
	if (surface == NULL) {
		SDL_Log("Failed to create surface!");
	} else {
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (texture == NULL) {
			SDL_Log("Failed to create texture from surface!");
		}
		SDL_FreeSurface(surface);
	}
	return texture;
}

int ctn::Image::getWidth()
{
	return width;
}

int ctn::Image::getHeight()
{
	return height;
}

SDL_Texture * centurion::Image::getTexture()
{
	return texture;
}