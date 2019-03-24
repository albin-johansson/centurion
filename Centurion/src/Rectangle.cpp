#include "Rectangle.h"
#include "BooleanConverter.h"
#include "Point.h"
#include <stdexcept>

using centurion::Rectangle;
using centurion::Point;

Rectangle::Rectangle(int x, int y, int w, int h)
{
	if (w < 1 || h < 1) {
		throw std::invalid_argument("Invalid dimensions for rectangle!");
	}
	rect = { x, y, w, h };
}

Rectangle::Rectangle(int w, int h) : Rectangle(0, 0, w, h)
{}

void Rectangle::setLocation(int x, int y)
{
	setX(x);
	setY(y);
}

void Rectangle::setX(int x)
{
	rect.x = x;
}

void Rectangle::setY(int y)
{
	rect.y = y;
}

bool Rectangle::intersects(Rectangle& otherRect)
{
	SDL_bool result = SDL_HasIntersection(&this->rect, &otherRect.rect);
	return BooleanConverter::convert(result);
}

bool Rectangle::contains(int x, int y)
{
	SDL_Point point = { x, y };
	SDL_bool result = SDL_PointInRect(&point, &this->rect);
	return BooleanConverter::convert(result);
}

bool Rectangle::contains(Point& point)
{
	return contains(point.getX(), point.getY());
}

int Rectangle::getX()
{
	return rect.x;
}

int Rectangle::getY()
{
	return rect.y;
}

int Rectangle::getWidth()
{
	return rect.w;
}

int Rectangle::getHeight()
{
	return rect.h;
}

SDL_Rect Rectangle::createSDLRect()
{
	return rect;
}