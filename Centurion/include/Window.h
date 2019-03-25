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

	void clearWindow();

	void render(centurion::Image& img, int x, int y);

	void render(centurion::Image& img, int x, int y, int w, int h);

	void render(centurion::Image& img, centurion::Rectangle rect);

	void renderFilledRect(int x, int y, int w, int h);

	void renderOutlinedRect(int x, int y, int w, int h);

	void renderLine(int x1, int y1, int x2, int y2);

	void renderLine(centurion::Point p1, centurion::Point p2);

	void setRenderingColor(centurion::Color color);

	centurion::Image* createImage(std::string path);
};