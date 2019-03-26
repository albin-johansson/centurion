#pragma once
#include "centurion.h"
#include <SDL_video.h>
#include <string>

/**
\brief The Window class represents a top-level frame.
*/
class centurion::Window {

private:
	SDL_Window* window;
	std::unique_ptr<centurion::visuals::Renderer> graphics;

	void InitComps(const std::string& title, int w, int h, Uint32 flags);

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
	void Show();

	/*
	\brief	Makes this window invisible.
	*/
	void Hide();

	/*
	\brief	Sets whether this window is resizable or not.

	\param	resizable true if the window is resizable, false otherwise.
	*/
	void SetResizable(bool resizable);

	int GetWidth();

	int GetHeight();

	void Update();

	void AddKeyListener(centurion::events::KeyListener& kl);

	// TODO add listener methods

	void ClearWindow();

	void Render(centurion::visuals::Texture& img, int x, int y);

	void Render(centurion::visuals::Texture& img, int x, int y, int w, int h);

	void Render(centurion::visuals::Texture& img, centurion::geo::Rectangle rect);

	void RenderFilledRect(int x, int y, int w, int h);

	void RenderOutlinedRect(int x, int y, int w, int h);

	void RenderLine(int x1, int y1, int x2, int y2);

	void RenderLine(centurion::geo::Point p1, centurion::geo::Point p2);

	void SetRenderingColor(centurion::visuals::Color color);

	centurion::visuals::Texture* CreateImage(std::string path);
};