#pragma once
#include "centurion.h"

class centurion::Dimensioned {

protected:
	Dimensioned() = default;

public:
	virtual ~Dimensioned() = default;

	virtual int GetWidth() const = 0;

	virtual int GetHeight() const = 0;
};