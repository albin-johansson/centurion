#pragma once
#include "centurion.h"
#include <SDL_rect.h>

class centurion::geo::Rectangle {

private:
	SDL_Rect rect;

public:
	Rectangle(int x, int y, int w, int h);

	Rectangle(int w, int h);

	~Rectangle() = default;

	void SetLocation(int x, int y);

	void SetX(int x);

	void SetY(int y);

	bool Intersects(centurion::geo::Rectangle& rect);

	bool Contains(int x, int y);

	bool Contains(Point& point);

	int GetX();

	int GetY();

	int GetWidth();

	int GetHeight();

	SDL_Rect CreateSDLRect();
};