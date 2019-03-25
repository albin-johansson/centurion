#include "BooleanConverter.h"
#include <SDL.h>

using centurion::CTN_BooleanConverter;

bool CTN_BooleanConverter::convert(SDL_bool b)
{
	return (b) ? true : false;
}

SDL_bool CTN_BooleanConverter::convert(bool b)
{
	return (b) ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE;
}