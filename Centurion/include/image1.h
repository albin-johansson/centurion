#pragma once
#include "centurion1.h"
#include <SDL_video.h>
#include <SDL_image.h>
#include <string>

class centurion::visuals::Image {

private:
	int width;
	int height;
	SDL_Texture* texture = nullptr;

	Image(const std::string& path, centurion::visuals::Graphics& graphics);
	
public:
	~Image();

	int GetWidth();

	int GetHeight();

	SDL_Texture* GetTexture();

	static SDL_Texture* CreateTexture(SDL_Surface* surface, SDL_Renderer* renderer);

	static centurion::visuals::Image* Create(const std::string& path, centurion::visuals::Graphics& graphics);

	static centurion::visuals::Image* Create(SDL_Texture* texture);

	static void Destroy(centurion::visuals::Image* img);
};