#pragma once
#include "centurion.h"
#include <SDL_video.h>
#include <SDL_image.h>
#include <string>

class centurion::visuals::Texture {

private:
	int width;
	int height;
	SDL_Texture* texture = nullptr;

	Texture(const std::string& path, centurion::visuals::Graphics& graphics);
	
public:
	~Texture();

	int GetWidth();

	int GetHeight();

	SDL_Texture* GetTexture();

	static SDL_Texture* CreateTexture(SDL_Surface* surface, SDL_Renderer* renderer);

	static centurion::visuals::Texture* Create(const std::string& path, centurion::visuals::Graphics& graphics);

	static centurion::visuals::Texture* Create(SDL_Texture* texture);

	static void Destroy(centurion::visuals::Texture* img);
};