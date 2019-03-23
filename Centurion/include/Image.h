#pragma once
#include <SDL.h>
#include <string>
#include "Centurion.h"

class centurion::Image {

private:
	int width;
	int height;
	SDL_Texture* texture = nullptr;

	SDL_Texture* createTexture(SDL_Surface* surface, SDL_Renderer* renderer);

	Image(const std::string& path, centurion::Graphics& graphics);

public:
	~Image();

	int getWidth();

	int getHeight();

	SDL_Texture* getTexture();

	static centurion::Image* create(const std::string& path, centurion::Graphics& graphics);

	static void destroy(centurion::Image* img);
};