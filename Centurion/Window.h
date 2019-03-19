#pragma once
#include <SDL.h>
#include <string>
#include "Graphics.h"

namespace centurion
{
	class Window;
}

class centurion::Window {

private:
	SDL_Window* window;
	Graphics*  graphics;

public:

	Window(std::string& title, int width, int height);

	~Window();

	void show();

	void hide();

	void update();

	void setResizable(bool resizable);
};