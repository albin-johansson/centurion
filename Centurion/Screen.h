#pragma once
#include <SDL.h>

namespace centurion
{
	class Screen;
}

class centurion::Screen final {

public:
	Screen() = delete;

	~Screen() = default;

	static int getWidth();

	static int getHeight();
};