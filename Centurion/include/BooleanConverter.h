#pragma once
#include <SDL.h>

class BooleanConverter final {

private:
	BooleanConverter() = delete;

public:
	~BooleanConverter() = default;
	
	static bool convert(SDL_bool b);

	static SDL_bool convert(bool b);
};