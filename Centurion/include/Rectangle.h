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

	void SetLocation(int x, int y);

	void SetX(int x);

	void SetY(int y);

	bool Intersects(centurion::Rectangle& rect);

	bool Contains(int x, int y);

	bool Contains(Point& point);

	int GetX();

	int GetY();

	int GetWidth();

	int GetHeight();

	SDL_Rect CreateSDLRect();
};