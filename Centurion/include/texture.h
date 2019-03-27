#pragma once
#include "centurion.h"
#include "renderer.h"
#include <SDL_video.h>
#include <SDL_image.h>
#include <memory>
#include <string>

/**
\brief The Texture class represents textures such as images.
*/
class centurion::visuals::Texture {

private:
	SDL_Texture* texture = nullptr;
	int width;
	int height;

public:
	Texture(const std::string& path, centurion::visuals::Renderer& renderer);

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
	\brief Returns an SDL_Texture representation of this Texture.
	*/
	SDL_Texture* GetTexture(); //TODO avoid

	/**
	\brief Returns a pointer to an SDL_Texture.
	\param surface - the SDL_Surface to base the texture on.
	\param renderer - the SDL_Renderer used to create the texture.
	*/
	static SDL_Texture* CreateSDLTexture(SDL_Surface* surface, SDL_Renderer* renderer); //TODO remove

	static std::shared_ptr<centurion::visuals::Texture> CreateTexture(const std::string& path,
																	  centurion::visuals::Renderer& renderer);
};