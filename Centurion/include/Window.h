#pragma once
#include <SDL.h>
#include <string>
#include "Centurion.h"

class centurion::Window {

private:
	SDL_Window* window;
	centurion::Graphics* graphics;

	void initComps(const std::string& title, int w, int h, Uint32 flags);

public:
	/*
	\brief	Creates a window with the supplied dimensions.

	\param	title the title of the window
	\param	width the width of the window.
	\param	height the height of the window.
	*/
	Window(const std::string& title, int width, int height);

	/*
	\brief	Creates a fullscreen window.

	\param	title the title of the window
	*/
	Window(const std::string& title);

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

	void render(centurion::Image& img, int x, int y);

	void render(centurion::Image& img, int x, int y, int w, int h);

	centurion::Image* createImage(std::string path);
};