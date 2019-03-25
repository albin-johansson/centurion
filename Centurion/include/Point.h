#pragma once
#include "Centurion.h"
#include <SDL.h>

class centurion::CTN_Point {

private:
	SDL_Point point;

public:
	CTN_Point(int x, int y);

	~CTN_Point() = default;

	void setLocation(int x, int y);

	void setX(int x);

	void setY(int y);

	int getX();

	int getY();
};