#pragma once
#include "Centurion.h"
#include <SDL.h>

class centurion::CTN_Rectangle {

private:
	SDL_Rect rect;

public:
	CTN_Rectangle(int x, int y, int w, int h);

	CTN_Rectangle(int w, int h);

	~CTN_Rectangle() = default;

	void setLocation(int x, int y);

	void setX(int x);

	void setY(int y);

	bool intersects(centurion::CTN_Rectangle& rect);

	bool contains(int x, int y);

	bool contains(CTN_Point& point);

	int getX();

	int getY();

	int getWidth();

	int getHeight();

	SDL_Rect createSDLRect();
};