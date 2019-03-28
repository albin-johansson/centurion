#include "texture.h"
#include "null_checker.h"
#include <stdexcept>

using centurion::visuals::Texture;
using centurion::tools::NullChecker;
using std::invalid_argument;

Texture::Texture(SDL_Texture* texture, int width, int height)
{
	if (NullChecker::IsNull(texture)) {
		throw invalid_argument("Null SDL_Texture!");
	}
	this->texture = texture;
	this->width = width;
	this->height = height;
}

Texture::~Texture()
{
	SDL_DestroyTexture(texture);
}

SDL_Texture* Texture::GetTexture()
{
	return texture;
}

int Texture::GetWidth() const
{
	return width;
}

int Texture::GetHeight() const
{
	return height;
}