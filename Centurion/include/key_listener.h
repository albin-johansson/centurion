#pragma once
#include "centurion.h"

class centurion::KeyListener {

protected:
	KeyListener() = default;

public:
	virtual ~KeyListener() = default;

	virtual void KeyPressed() = 0;

	virtual void KeyReleased() = 0;
};