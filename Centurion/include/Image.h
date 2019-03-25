#pragma once
#include <SDL.h>
#include <string>
#include "centurion.h"

class centurion::CTN_Image {

private:
	int width;
	int height;
	SDL_Texture* texture = nullptr;

	SDL_Texture* createTexture(SDL_Surface* surface, SDL_Renderer* renderer);

	CTN_Image(const std::string& path, centurion::CTN_Graphics& graphics);
	
public:
	~CTN_Image();

	int getWidth();

	int getHeight();

	SDL_Texture* getTexture();

	static centurion::CTN_Image* create(const std::string& path, centurion::CTN_Graphics& graphics);

	static void destroy(centurion::CTN_Image* img);
};