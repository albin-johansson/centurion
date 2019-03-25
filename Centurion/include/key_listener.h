#pragma once
#include "centurion.h"

class centurion::CTN_KeyListener {

protected:
	CTN_KeyListener() = default;

public:
	virtual ~CTN_KeyListener() = default;

	virtual void KeyPressed() = 0;

	virtual void KeyReleased() = 0;
};