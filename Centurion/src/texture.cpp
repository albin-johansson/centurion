#include "texture.h"
#include "renderer.h"
#include "null_checker.h"
#include <stdexcept>

using centurion::visuals::Texture;
using centurion::visuals::Renderer;
using centurion::tools::NullChecker;

Texture::Texture(const std::string& path, Renderer& renderer)
{
	SDL_Surface* surface = IMG_Load(path.c_str());
	texture = CreateSDLTexture(surface, renderer.GetSDLRenderer());
	width = surface->w;
	height = surface->h;
	SDL_FreeSurface(surface);
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
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

SDL_Texture* Texture::CreateSDLTexture(SDL_Surface* surface, SDL_Renderer* renderer)
{
	if (NullChecker::IsNull(surface) || NullChecker::IsNull(renderer)) {
		throw std::invalid_argument("Null renderer or surface when creating texture!");
	}
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL) {
		SDL_Log("Failed to create texture from surface!");
	}
	return texture;
}
