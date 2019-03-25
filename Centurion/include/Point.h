#pragma once
#include <SDL.h>
#include "centurion.h"

class centurion::Point {

private:
	SDL_Point point;

public:
	Point(int x, int y);

	~Point() = default;

	void setLocation(int x, int y);

	void setX(int x);

	void setY(int y);

	int getX();

	int getY();
};