#pragma once
#include <SDL.h>
#include <string>
#include <memory>
#include "centurion.h"

using centurion::CTN_Graphics;
using std::unique_ptr;

class centurion::CTN_Window {

private:
	SDL_Window* window;
	unique_ptr<CTN_Graphics> graphics;

	void InitComps(const std::string& title, int w, int h, Uint32 flags);

public:
	/*
	\brief	Creates a window with the supplied dimensions.

	\param	title the title of the window
	\param	width the width of the window.
	\param	height the height of the window.
	*/
	CTN_Window(const std::string& title, int width, int height);

	/*
	\brief	Creates a fullscreen window.

	\param	title the title of the window
	*/
	CTN_Window(const std::string& title);

	~CTN_Window();

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

	void AddKeyListener(centurion::CTN_KeyListener& kl);

	// TODO add listener methods

	void ClearWindow();

	void Render(centurion::CTN_Image& img, int x, int y);

	void Render(centurion::CTN_Image& img, int x, int y, int w, int h);

	void Render(centurion::CTN_Image& img, centurion::CTN_Rectangle rect);

	void RenderFilledRect(int x, int y, int w, int h);

	void RenderOutlinedRect(int x, int y, int w, int h);

	void RenderLine(int x1, int y1, int x2, int y2);

	void RenderLine(centurion::CTN_Point p1, centurion::CTN_Point p2);

	void SetRenderingColor(centurion::CTN_Color color);

	centurion::CTN_Image* CreateImage(std::string path);
};