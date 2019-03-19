#pragma once
#include <SDL.h>

class Screen final {

public:
	Screen() = delete;

	~Screen() = default;

	static int getWidth();

	static int getHeight();
};