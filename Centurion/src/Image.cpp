#include "Image.h"
#include <SDL_image.h>
#include <stdexcept>

namespace c = centurion;

c::Image::Image(std::string path, SDL_Renderer* renderer)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	texture = createTexture(surface, renderer);
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
}

c::Image::~Image()
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* c::Image::createTexture(SDL_Surface* surface, SDL_Renderer* renderer)
{
	if (surface == NULL || renderer == NULL) {
		throw std::invalid_argument("Null renderer when creating texture!");
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		SDL_Log("Failed to create texture from surface!");
	}
	return texture;
}

int c::Image::getWidth()
{
	return width;
}

int c::Image::getHeight()
{
	return height;
}

SDL_Texture* c::Image::getTexture()
{
	return texture;
}

centurion::Image* centurion::Image::create(std::string path, SDL_Renderer * renderer)
{
	return new centurion::Image(path, renderer);
}

void centurion::Image::destroy(centurion::Image * img)
{
	delete img;
}
