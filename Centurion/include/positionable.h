#pragma once
#include "centurion.h"

class centurion::Positionable {

protected:
	Positionable() = default;

public:
	virtual ~Positionable() = default;

	virtual void SetX(int x) = 0;

	virtual void SetY(int y) = 0;

	virtual void SetLocation(int x, int y) = 0;

	virtual int GetX() = 0;

	virtual int GetY() = 0;
};