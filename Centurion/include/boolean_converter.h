#pragma once
#include <SDL.h>
#include "centurion.h"

class centurion::tools::BooleanConverter final {

private:
	BooleanConverter() = delete;

public:
	~BooleanConverter() = default;
	
	static bool Convert(SDL_bool b);

	static SDL_bool Convert(bool b);
};