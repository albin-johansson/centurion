#pragma once
#include "centurion.h"
#include <SDL_video.h>
#include <SDL_image.h>
#include <string>

/**
\brief The Texture class represents textures such as images.
*/
class centurion::visuals::Texture {

private:
	int width;
	int height;
	SDL_Texture* texture = nullptr;

	Texture(const std::string& path, centurion::visuals::Renderer& renderer);

public:
	~Texture();

	/**
	\brief Returns the width of this texture.
	*/
	int GetWidth();

	/**
	\brief Returns the height of this texture.
	*/
	int GetHeight();

	/**
	\brief Returns a pointer to the internal SDL_Texture representation of this Texture.
	*/
	SDL_Texture* GetTexture(); //TODO avoid

	/**
	\brief Returns a pointer to an SDL_Texture.
	\param surface - the SDL_Surface to base the texture on.
	\param renderer - the SDL_Renderer used to create the texture.
	*/
	static SDL_Texture* CreateTexture(SDL_Surface* surface, SDL_Renderer* renderer);

	/**
	\brief Returns a pointer to a Texture, based on the image at the specified path.
	\param path - the path to the image file which the texture will be based on.
	\param renderer - the Renderer used to create the texture.
	*/
	static centurion::visuals::Texture* Create(const std::string& path, centurion::visuals::Renderer& renderer);

	/**
	\brief Returns a pointer to a Texture, based on the supplied SDL_Texture.
	\param texture - the SDL_Texture to base the Texture on.
	*/
	static centurion::visuals::Texture* Create(SDL_Texture* texture);

	/**
	\brief Destroys a Texture.
	*/
	static void Destroy(centurion::visuals::Texture* img);
};