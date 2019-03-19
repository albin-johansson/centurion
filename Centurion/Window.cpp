#include "Window.h"
#include "Image.h"
#include "Screen.h"
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

ctn::Window::Window(std::string & title)
{
	int w = Screen::getWidth();
	int h = Screen::getHeight();
	Uint32 winFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN | SDL_WINDOW_FULLSCREEN;
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, winFlags);

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

void ctn::Window::setResizable(bool resizable)
{
	SDL_bool b = (resizable) ? SDL_TRUE : SDL_FALSE;
	SDL_SetWindowResizable(window, b);
}

int ctn::Window::getWidth()
{
	int w = -1;
	int h = -1;
	SDL_GetWindowSize(window, &w, &h);
	return w;
}

int ctn::Window::getHeight()
{
	int w = -1;
	int h = -1;
	SDL_GetWindowSize(window, &w, &h);
	return h;
}

void ctn::Window::update()
{
	graphics->update();
}

void ctn::Window::render(Image& img, int x, int y)
{
	graphics->render(img, x, y);
}

void ctn::Window::render(Image& img, int x, int y, int w, int h)
{
	graphics->render(img, x, y, w, h);
}

ctn::Image* ctn::Window::createImage(std::string path)
{
	return new ctn::Image(path, graphics->getRenderer());
}