#include "Screen.h"

namespace c = centurion;

int c::Screen::getWidth()
{
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	return dm.w;
}

int c::Screen::getHeight()
{
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	return dm.h;
}