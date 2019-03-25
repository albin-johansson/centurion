#pragma once
#include <SDL.h>
#include "Centurion.h"

class centurion::CTN_BooleanConverter final {

private:
	CTN_BooleanConverter() = delete;

public:
	~CTN_BooleanConverter() = default;
	
	static bool convert(SDL_bool b);

	static SDL_bool convert(bool b);
};