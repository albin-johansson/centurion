#include "image.h"
#include "graphics.h"
#include <SDL_image.h>
#include <stdexcept>

using centurion::Image;
using centurion::Graphics;

Image::Image(const std::string& path, Graphics& graphics)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	texture = CreateTexture(surface, graphics.renderer);
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
}

Image::~Image()
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* Image::CreateTexture(SDL_Surface* surface, SDL_Renderer* renderer)
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

int Image::GetWidth()
{
	return width;
}

int Image::GetHeight()
{
	return height;
}

SDL_Texture* Image::GetTexture()
{
	return texture;
}

Image* Image::Create(const std::string& path, Graphics& graphics)
{
	return new Image(path, graphics);
}

void Image::Destroy(Image* img)
{
	delete img;
}
