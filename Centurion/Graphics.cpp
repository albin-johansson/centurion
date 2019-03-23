#include "Graphics.h"
#include "Window.h"
#include "Image.h"
#include <stdexcept>

namespace ctn = centurion;

ctn::Graphics::Graphics(SDL_Renderer* renderer)
{
	if (renderer == NULL) {
		throw std::invalid_argument("Null renderer!");
	}
	this->renderer = renderer;
}

ctn::Graphics::~Graphics()
{
	SDL_DestroyRenderer(renderer);
}

void ctn::Graphics::update()
{
	SDL_RenderPresent(renderer);
}

void ctn::Graphics::render(Image& img, int x, int y)
{
	render(img, x, y, img.getWidth(), img.getHeight());
}

//TODO add 

void ctn::Graphics::render(Image& img, int x, int y, int w, int h)
{
	if (w < 1 || h < 1) {
		throw std::invalid_argument("Invalid dimensions for rendering an image!");
	}
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(renderer, img.getTexture(), NULL, &rect);
}