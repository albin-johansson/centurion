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

	Image(std::string path, SDL_Renderer* renderer);

public:
	~Image();

	int getWidth();

	int getHeight();

	SDL_Texture* getTexture();

	static centurion::Image* create(std::string path, SDL_Renderer* renderer);

	static void destroy(centurion::Image* img);
};