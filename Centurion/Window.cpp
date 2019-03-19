#include "Window.h"
#include <stdexcept>

namespace ctn = centurion;

ctn::Window::Window(std::string& title, int width, int height)
{
	if (width < 1 || height < 1) {
		throw std::invalid_argument("Invalid dimensions for window!");
	}

	Uint32 winFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN;
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, winFlags);

	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
	graphics = new Graphics(SDL_CreateRenderer(window, -1, rendererFlags));
}

ctn::Window::~Window()
{
	SDL_HideWindow(window);
	SDL_Delay(1);

	delete graphics;
	SDL_DestroyWindow(window);
}

void ctn::Window::show()
{
	SDL_ShowWindow(window);
}

void ctn::Window::hide()
{
	SDL_HideWindow(window);
}

void centurion::Window::update()
{
	graphics->update();
}

void ctn::Window::setResizable(bool resizable)
{
	SDL_bool b = (resizable) ? SDL_TRUE : SDL_FALSE;
	SDL_SetWindowResizable(window, b);
}