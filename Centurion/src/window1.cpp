#include "window.h"
#include "graphics.h"
#include "screen.h"
#include "image.h"
#include "boolean_converter.h"
#include "rectangle.h"
#include "point.h"
#include "color1.h"
#include "key_listener.h"
#include <stdexcept>
#include <memory>

namespace ctn = centurion;
using ctn::Window;
using ctn::Screen;
using ctn::visuals::Graphics;
using ctn::visuals::Image;
using ctn::visuals::Color;
using ctn::geo::Rectangle;
using ctn::geo::Point;
using ctn::tools::BooleanConverter;
using ctn::events::KeyListener;

Window::Window(const std::string& title, int width, int height)
{
	Uint32 flags = SDL_WindowFlags::SDL_WINDOW_OPENGL | SDL_WindowFlags::SDL_WINDOW_HIDDEN;
	InitComps(title, width, height, flags);
}

Window::Window(const std::string& title)
{
	Uint32 flags = SDL_WindowFlags::SDL_WINDOW_OPENGL |
		SDL_WindowFlags::SDL_WINDOW_FULLSCREEN |
		SDL_WindowFlags::SDL_WINDOW_HIDDEN;
	InitComps(title, Screen::GetWidth(), Screen::GetHeight(), flags);
}

Window::~Window()
{
	SDL_HideWindow(window);
	SDL_Delay(1);
	SDL_DestroyWindow(window);
}

void Window::InitComps(const std::string& title, int w, int h, Uint32 flags)
{
	if (w < 1 || h < 1) {
		throw std::invalid_argument("Invalid dimensions for window!");
	}
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	graphics = std::make_unique<Graphics>(renderer);
}

void Window::Show()
{
	SDL_ShowWindow(window);
}

void Window::Hide()
{
	SDL_HideWindow(window);
}

void Window::SetResizable(bool resizable)
{
	SDL_bool b = BooleanConverter::Convert(resizable);
	SDL_SetWindowResizable(window, b);
}

int Window::GetWidth()
{
	int w = -1;
	int h = -1;
	SDL_GetWindowSize(window, &w, &h);
	return w;
}

int Window::GetHeight()
{
	int w = -1;
	int h = -1;
	SDL_GetWindowSize(window, &w, &h);
	return h;
}

void Window::Update()
{
	//SDL_Event e;
	//while (SDL_PollEvent(&e)) {
	//
	//}
	graphics->Update();
}

void Window::AddKeyListener(KeyListener& kl)
{
	//TODO
}

void centurion::Window::ClearWindow()
{
	graphics->Clear();
}

void Window::Render(Image& img, int x, int y)
{
	graphics->Render(img, x, y);
}

void Window::Render(Image& img, int x, int y, int w, int h)
{
	graphics->Render(img, x, y, w, h);
}

void Window::Render(Image& img, Rectangle rect)
{
	graphics->Render(img, rect);
}

void Window::RenderFilledRect(int x, int y, int w, int h)
{
	graphics->RenderFilledRect(x, y, w, h);
}

void Window::RenderOutlinedRect(int x, int y, int w, int h)
{
	graphics->RenderOutlinedRect(x, y, w, h);
}

void Window::RenderLine(int x1, int y1, int x2, int y2)
{
	graphics->RenderLine(x1, y1, x2, y2);
}

void Window::RenderLine(Point p1, Point p2)
{
	graphics->RenderLine(p1, p2);
}

void Window::SetRenderingColor(Color color)
{
	graphics->SetColor(color);
}

Image* Window::CreateImage(std::string path)
{
	return Image::Create(path, *graphics);
}