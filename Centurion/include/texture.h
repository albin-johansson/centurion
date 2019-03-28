#pragma once
#include "centurion.h"
#include "dimensioned.h"
#include <SDL_image.h>

/**
\brief The Texture class represents textures such as images.
*/
class centurion::visuals::Texture : public centurion::Dimensioned {

private:
	SDL_Texture* texture = nullptr;
	int width;
	int height;

public:
	Texture(SDL_Texture* texture, int width, int height);

	~Texture();

	/**
	\brief Returns an SDL_Texture representation of this Texture.
	*/
	SDL_Texture* GetTexture(); //TODO avoid

	/**
	\brief Returns the width of this texture.
	*/
	int GetWidth() const override;

	/**
	\brief Returns the height of this texture.
	*/
	int GetHeight() const override;
};