#pragma once
#include "centurion1.h"

class centurion::events::KeyListener {

protected:
	KeyListener() = default;

public:
	virtual ~KeyListener() = default;

	virtual void KeyPressed() = 0;

	virtual void KeyReleased() = 0;
};