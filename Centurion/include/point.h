#pragma once
#include "centurion.h"
#include <SDL_rect.h>

/**
\brief The Point class represents a two-dimensional point.
*/
class centurion::geo::Point {

private:
	SDL_Point point;

public:
	/**
	\param x - the desired initial x-coordinate.
	\param y - the desired initial y-coordinate.
	*/
	Point(int x, int y);

	~Point() = default;

	/**
	\brief Assigns the location of this point.
	\param x - the new x-coordinate.
	\param y - the new y-coordinate.
	*/
	void SetLocation(int x, int y);

	/**
	\brief Assigns the x-coordinate of this point.
	\param x - the new x-coordinate.
	*/
	void SetX(int x);

	/**
	\brief Assigns the y-coordinate of this point.
	\param y - the new y-coordinate.
	*/
	void SetY(int y);

	/**
	\brief Returns the x-coordinate of this point.
	*/
	int GetX();

	/**
	\brief Returns the y-coordinate of this point.
	*/
	int GetY();
};