#include "Window.h"
#include "Graphics.h"
#include "Screen.h"
#include "Image.h"
#include "BooleanConverter.h"
#include "Rectangle.h"
#include "Point.h"
#include "Color.h"
#include "key_listener.h"
#include <stdexcept>

using centurion::CTN_Window;
using centurion::CTN_Graphics;
using centurion::CTN_Screen;
using centurion::CTN_Image;
using centurion::CTN_Rectangle;
using centurion::CTN_Point;
using centurion::CTN_Color;
using centurion::CTN_BooleanConverter;
using centurion::CTN_KeyListener;

CTN_Window::CTN_Window(const std::string& title, int width, int height)
{
	Uint32 flags = SDL_WindowFlags::SDL_WINDOW_OPENGL | SDL_WindowFlags::SDL_WINDOW_HIDDEN;
	InitComps(title, width, height, flags);
}

CTN_Window::CTN_Window(const std::string& title)
{
	Uint32 flags = SDL_WindowFlags::SDL_WINDOW_OPENGL |
		SDL_WindowFlags::SDL_WINDOW_FULLSCREEN |
		SDL_WindowFlags::SDL_WINDOW_HIDDEN;
	InitComps(title, CTN_Screen::getWidth(), CTN_Screen::getHeight(), flags);
}

CTN_Window::~CTN_Window()
{
	SDL_HideWindow(window);
	SDL_Delay(1);
	SDL_DestroyWindow(window);
}

void CTN_Window::InitComps(const std::string& title, int w, int h, Uint32 flags)
{
	if (w < 1 || h < 1) {
		throw std::invalid_argument("Invalid dimensions for window!");
	}
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	graphics = std::make_unique<CTN_Graphics>(renderer);
}

void CTN_Window::Show()
{
	SDL_ShowWindow(window);
}

void CTN_Window::Hide()
{
	SDL_HideWindow(window);
}

void CTN_Window::SetResizable(bool resizable)
{
	SDL_bool b = CTN_BooleanConverter::convert(resizable);
	SDL_SetWindowResizable(window, b);
}

int CTN_Window::GetWidth()
{
	int w = -1;
	int h = -1;
	SDL_GetWindowSize(window, &w, &h);
	return w;
}

int CTN_Window::GetHeight()
{
	int w = -1;
	int h = -1;
	SDL_GetWindowSize(window, &w, &h);
	return h;
}

void CTN_Window::Update()
{
	//SDL_Event e;
	//while (SDL_PollEvent(&e)) {
	//
	//}
	graphics->Update();
}

void CTN_Window::AddKeyListener(CTN_KeyListener& kl)
{
	//TODO
}

void centurion::CTN_Window::ClearWindow()
{
	graphics->clear();
}

void CTN_Window::Render(CTN_Image& img, int x, int y)
{
	graphics->Render(img, x, y);
}

void CTN_Window::Render(CTN_Image& img, int x, int y, int w, int h)
{
	graphics->Render(img, x, y, w, h);
}

void CTN_Window::Render(CTN_Image& img, CTN_Rectangle rect)
{
	graphics->Render(img, rect);
}

void CTN_Window::RenderFilledRect(int x, int y, int w, int h)
{
	graphics->RenderFilledRect(x, y, w, h);
}

void CTN_Window::RenderOutlinedRect(int x, int y, int w, int h)
{
	graphics->RenderOutlinedRect(x, y, w, h);
}

void CTN_Window::RenderLine(int x1, int y1, int x2, int y2)
{
	graphics->RenderLine(x1, y1, x2, y2);
}

void CTN_Window::RenderLine(CTN_Point p1, CTN_Point p2)
{
	graphics->RenderLine(p1, p2);
}

void CTN_Window::SetRenderingColor(CTN_Color color)
{
	graphics->setColor(color);
}

CTN_Image* CTN_Window::CreateImage(std::string path)
{
	return CTN_Image::create(path, *graphics);
}