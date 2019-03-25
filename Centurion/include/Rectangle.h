#pragma once
#include <SDL.h>
#include "centurion.h"

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

	bool contains(Point& point);

	int getX();

	int getY();

	int getWidth();

	int getHeight();

	SDL_Rect createSDLRect();
};