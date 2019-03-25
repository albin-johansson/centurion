#include "image.h"
#include "graphics.h"
#include <SDL_image.h>
#include <stdexcept>

using centurion::CTN_Image;
using centurion::CTN_Graphics;

CTN_Image::CTN_Image(const std::string& path, CTN_Graphics& graphics)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	texture = createTexture(surface, graphics.renderer);
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
}

CTN_Image::~CTN_Image()
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* CTN_Image::createTexture(SDL_Surface* surface, SDL_Renderer* renderer)
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

int CTN_Image::getWidth()
{
	return width;
}

int CTN_Image::getHeight()
{
	return height;
}

SDL_Texture* CTN_Image::getTexture()
{
	return texture;
}

CTN_Image* CTN_Image::create(const std::string& path, CTN_Graphics& graphics)
{
	return new CTN_Image(path, graphics);
}

void CTN_Image::destroy(CTN_Image* img)
{
	delete img;
}
