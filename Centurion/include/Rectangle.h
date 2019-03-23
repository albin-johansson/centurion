#pragma once
#include "Centurion.h"
#include <SDL.h>

class centurion::Rectangle {

private:
	SDL_Rect rect;

public:
	Rectangle(int x, int y, int w, int h);

	Rectangle(int w, int h);

	~Rectangle() = default;

	void setLocation(int x, int y);

	void setX(int x);

	void setY(int y);

	bool intersects(centurion::Rectangle& rect);

	bool contains(int x, int y);

	int getX();

	int getY();
};