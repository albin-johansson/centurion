#pragma once
#include <SDL.h>
#include <string>
#include "centurion.h"

class centurion::Image {

private:
	int width;
	int height;
	SDL_Texture* texture = nullptr;

	SDL_Texture* CreateTexture(SDL_Surface* surface, SDL_Renderer* renderer);

	Image(const std::string& path, centurion::Graphics& graphics);
	
public:
	~Image();

	int GetWidth();

	int GetHeight();

	SDL_Texture* GetTexture();

	static centurion::Image* Create(const std::string& path, centurion::Graphics& graphics);

	static void Destroy(centurion::Image* img);
};