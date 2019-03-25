#pragma once
#include "centurion.h"
#include <SDL_rect.h>

class centurion::geo::Point {

private:
	SDL_Point point;

public:
	Point(int x, int y);

	~Point() = default;

	void SetLocation(int x, int y);

	void SetX(int x);

	void SetY(int y);

	int GetX();

	int GetY();
};