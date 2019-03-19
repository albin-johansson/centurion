#include "Graphics.h"
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
