#pragma once
#include <SDL.h>
#include "Centurion.h"

class centurion::BooleanConverter final {

private:
	BooleanConverter() = delete;

public:
	~BooleanConverter() = default;
	
	static bool convert(SDL_bool b);

	static SDL_bool convert(bool b);
};