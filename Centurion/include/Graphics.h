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

	void render(centurion::Image& img, centurion::Rectangle rect);

	void render(centurion::Image& img, int x, int y, int w, int h);

	void render(centurion::Image& img, int x, int y);

	void renderFilledRect(int x, int y, int w, int h);

	void renderOutlinedRect(int x, int y, int w, int h);
	
	void renderLine(int x1, int y1, int x2, int y2);

	void renderLine(centurion::Point p1, centurion::Point p2);

	void setColor(centurion::Color color);

	void checkRenderDimensions(int width, int height);

public:
	~Graphics();
};