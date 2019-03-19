#pragma once
#include <SDL.h>
#include <string>
#include "Image.h"

namespace centurion
{
	class Window;
}

class centurion::Window {

private:

	class Graphics {

	private:
		SDL_Renderer* renderer = nullptr;

	public:
		Graphics(SDL_Renderer* renderer);

		~Graphics();

		void update();

		void render(Image& img, int x, int y);

		void render(Image& img, int x, int y, int w, int h);

		SDL_Renderer* getRenderer();
	};

	SDL_Window* window;
	Graphics* graphics;

public:

	Window(std::string& title, int width, int height);

	~Window();

	void show();

	void hide();

	void update();

	void setResizable(bool resizable);

	Image* createImage(std::string path);
};