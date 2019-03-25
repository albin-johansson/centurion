#include "rectangle.h"
#include "boolean_converter.h"
#include "point.h"
#include <stdexcept>

using centurion::CTN_Rectangle;
using centurion::CTN_Point;
using centurion::CTN_BooleanConverter;

CTN_Rectangle::CTN_Rectangle(int x, int y, int w, int h)
{
	if (w < 1 || h < 1) {
		throw std::invalid_argument("Invalid dimensions for rectangle!");
	}
	rect = { x, y, w, h };
}

CTN_Rectangle::CTN_Rectangle(int w, int h) : CTN_Rectangle(0, 0, w, h)
{}

void CTN_Rectangle::setLocation(int x, int y)
{
	setX(x);
	setY(y);
}

void CTN_Rectangle::setX(int x)
{
	rect.x = x;
}

void CTN_Rectangle::setY(int y)
{
	rect.y = y;
}

bool CTN_Rectangle::intersects(CTN_Rectangle& otherRect)
{
	SDL_bool result = SDL_HasIntersection(&this->rect, &otherRect.rect);
	return CTN_BooleanConverter::convert(result);
}

bool CTN_Rectangle::contains(int x, int y)
{
	SDL_Point point = { x, y };
	SDL_bool result = SDL_PointInRect(&point, &this->rect);
	return CTN_BooleanConverter::convert(result);
}

bool CTN_Rectangle::contains(CTN_Point& point)
{
	return contains(point.getX(), point.getY());
}

int CTN_Rectangle::getX()
{
	return rect.x;
}

int CTN_Rectangle::getY()
{
	return rect.y;
}

int CTN_Rectangle::getWidth()
{
	return rect.w;
}

int CTN_Rectangle::getHeight()
{
	return rect.h;
}

SDL_Rect CTN_Rectangle::createSDLRect()
{
	return rect;
}