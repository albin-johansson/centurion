#include "Window.h"
#include "Image.h"
#include "Screen.h"
#include <stdexcept>

namespace c = centurion;

c::Window::Window(std::string& title, int width, int height)
{
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_HIDDEN;
	initComps(title, width, height, flags);
}

c::Window::Window(std::string & title)
{
	Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIDDEN;
	initComps(title, c::Screen::getWidth(), c::Screen::getHeight(), flags);
}

c::Window::~Window()
{
	SDL_HideWindow(window);
	SDL_Delay(1);

	delete graphics;
	SDL_DestroyWindow(window);
}

void centurion::Window::initComps(std::string title, int w, int h, Uint32 flags)
{
	if (w < 1 || h < 1) {
		throw std::invalid_argument("Invalid dimensions for window!");
	}
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);

	Uint32 rendererFlags = SDL_RENDERER_ACCELERATED;
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, rendererFlags);
	graphics = new c::Graphics(renderer);
}

void c::Window::show()
{
	SDL_ShowWindow(window);
}

void c::Window::hide()
{
	SDL_HideWindow(window);
}

void c::Window::setResizable(bool resizable)
{
	SDL_bool b = (resizable) ? SDL_bool::SDL_TRUE : SDL_bool::SDL_FALSE;
	SDL_SetWindowResizable(window, b);
}

int c::Window::getWidth()
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
	return ctn::Image::create(path, graphics->renderer);
}