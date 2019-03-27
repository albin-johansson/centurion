#pragma once
#include "centurion.h"
#include "positionable.h"
#include <SDL_rect.h>

/**
\brief The Rectangle class quite simply represents a rectangle.
*/
class centurion::geo::Rectangle : public centurion::Positionable {

private:
	SDL_Rect rect;

public:
	/**
	\param x - the initial x-coordinate of the rectangle.
	\param y - the initial y-coordinate of the rectangle.
	\param w - the width of the rectangle.
	\param h - the height of the rectangle.
	*/
	Rectangle(int x, int y, int w, int h);

	/**
	\param w - the width of the rectangle.
	\param h - the height of the rectangle.
	*/
	Rectangle(int w, int h);

	~Rectangle() override;

	/**
	\brief Assigns the location of this rectangle.
	\param x - the new x-coordinate.
	\param y - the new y-coordinate.
	*/
	void SetLocation(int x, int y) override;

	/**
	\brief Assigns the x-coordinate of this rectangle.
	\param x - the new x-coordinate.
	*/
	void SetX(int x) override;

	/**
	\brief Assigns the y-coordinate of this rectangle.
	\param y - the new y-coordinate.
	*/
	void SetY(int y) override;

	/**
	\brief Indicates whether or not this rectangle intersects another rectangle. Returns true if
	 the supplied rectangle intersects this rectangle, returns false otherwise.
	\param rect - the rectangle that will be checked with this rectangle.
	*/
	bool Intersects(centurion::geo::Rectangle& rect);

	/**
	\brief Indicates whether or not this rectangle contains the specified point. Returns true if
	 the point is contained in this rectangle, returns false otherwise.
	\param x - the x-coordinate of the point to check.
	\param y - the y-coordinate of the point to check.
	*/
	bool Contains(int x, int y);

	/**
	\brief Indicates whether or not this rectangle contains the specified point. Returns true if
	 the point is contained in this rectangle, returns false otherwise.
	\param point - the point that will be checked.
	*/
	bool Contains(Point& point);

	/**
	\brief Returns the x-coordinate of this rectangle.
	*/
	int GetX() override;

	/**
	\brief Returns the y-coordinate of this rectangle.
	*/
	int GetY() override;

	/**
	\brief Returns the width of this rectangle.
	*/
	int GetWidth();

	/**
	\brief Returns the height of this rectangle.
	*/
	int GetHeight();

	/**
	\brief Creates and returns an SDL_Rect that represents this rectangle.
	*/
	SDL_Rect CreateSDLRect();
};