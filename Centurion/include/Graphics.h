#pragma once
#include <SDL.h>
#include "Centurion.h"

class centurion::Graphics {

private:
	friend class centurion::Window;
	friend class centurion::Image;

	SDL_Renderer* renderer = nullptr;

	Graphics(SDL_Renderer* renderer);

	void update();

	void clear();

	void render(centurion::Image& img, int x, int y);

	void render(centurion::Image& img, int x, int y, int w, int h);

	void setColor(centurion::Color color);

public:
	~Graphics();
};