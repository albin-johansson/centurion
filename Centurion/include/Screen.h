#pragma once
#include "centurion.h"

class centurion::Screen final {

private:
	Screen() = delete;

public:
	~Screen() = default;

	static int getWidth();

	static int getHeight();
};