#include "point.h"

using centurion::CTN_Point;

CTN_Point::CTN_Point(int x, int y)
{
	point = { x, y };
}

void CTN_Point::setLocation(int x, int y)
{
	setX(x);
	setY(y);
}

void CTN_Point::setX(int x)
{
	point.x = x;
}

void CTN_Point::setY(int y)
{
	point.y = y;
}

int CTN_Point::getX()
{
	return point.x;
}

int CTN_Point::getY()
{
	return point.y;
}