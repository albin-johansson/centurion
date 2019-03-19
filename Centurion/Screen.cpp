#include "Screen.h"

int Screen::getWidth()
{
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	return dm.w;
}

int Screen::getHeight()
{
	SDL_DisplayMode dm;
	SDL_GetDesktopDisplayMode(0, &dm);
	return dm.h;
}