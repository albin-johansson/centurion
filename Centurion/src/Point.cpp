#include "point.h"

using centurion::Point;

Point::Point(int x, int y)
{
	point = { x, y };
}

void Point::setLocation(int x, int y)
{
	setX(x);
	setY(y);
}

void Point::setX(int x)
{
	point.x = x;
}

void Point::setY(int y)
{
	point.y = y;
}

int Point::getX()
{
	return point.x;
}

int Point::getY()
{
	return point.y;
}