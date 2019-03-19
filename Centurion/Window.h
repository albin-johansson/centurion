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

	/*
	\brief	Creates a window with the supplied dimensions.

	\param	title the title of the window
	\param	width the width of the window.
	\param	height the height of the window.
	*/
	Window(std::string& title, int width, int height);

	/*
	\brief	Creates a fullscreen window.

	\param	title the title of the window
	*/
	Window(std::string& title);

	~Window();

	/*
	\brief	Makes this window visible.
	*/
	void show();

	/*
	\brief	Makes this window invisible.
	*/
	void hide();

	/*
	\brief	Sets whether this window is resizable or not.

	\param	resizable true if the window is resizable, false otherwise.
	*/
	void setResizable(bool resizable);

	int getWidth();

	int getHeight();

	void update();

	void render(Image& img, int x, int y);

	void render(Image& img, int x, int y, int w, int h);

	Image* createImage(std::string path);
};