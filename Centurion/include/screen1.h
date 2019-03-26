#pragma once
#include "centurion1.h"

class centurion::Screen final {

private:
	Screen() = delete;

public:
	~Screen() = default;

	static int GetWidth();

	static int GetHeight();
};