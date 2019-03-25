#include "point.h"

using centurion::Point;

Point::Point(int x, int y)
{
	point = { x, y };
}

void Point::SetLocation(int x, int y)
{
	SetX(x);
	SetY(y);
}

void Point::SetX(int x)
{
	point.x = x;
}

void Point::SetY(int y)
{
	point.y = y;
}

int Point::GetX()
{
	return point.x;
}

int Point::GetY()
{
	return point.y;
}