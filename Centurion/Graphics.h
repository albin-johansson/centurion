#pragma once
#include <SDL.h>

namespace centurion
{
	class Graphics;
}

class centurion::Graphics {

private:
	SDL_Renderer* renderer = nullptr;

public:

	Graphics(SDL_Renderer* renderer);

	~Graphics();

	void update();

};