#pragma once
#include <SDL.h>
#include <string>

namespace centurion
{
	class Image;
}

class centurion::Image {

private:
	SDL_Texture* texture = nullptr;
	int width;
	int height;

	SDL_Texture* createTexture(std::string path, SDL_Renderer* renderer);

public:
	Image(std::string path, SDL_Renderer* renderer);

	~Image();

	int getWidth();

	int getHeight();

	SDL_Texture* getTexture();
};