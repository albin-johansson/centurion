#include "texture.h"
#include "graphics.h"
#include <stdexcept>

using centurion::visuals::Texture;
using centurion::visuals::Graphics;

Texture::Texture(const std::string& path, Graphics& graphics)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	texture = CreateTexture(surface, graphics.renderer);
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::CreateTexture(SDL_Surface* surface, SDL_Renderer* renderer)
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

int Texture::GetWidth()
{
	return width;
}

int Texture::GetHeight()
{
	return height;
}

SDL_Texture* Texture::GetTexture()
{
	return texture;
}

Texture* Texture::Create(const std::string& path, Graphics& graphics)
{
	return new Texture(path, graphics);//FIXME don't use raw pointer
}

void Texture::Destroy(Texture* img)
{
	delete img; //This should be unnecessary
}
