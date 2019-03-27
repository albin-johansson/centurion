#include "window.h"
#include "renderer.h"
#include "screen.h"
#include "texture.h"
#include "boolean_converter.h"
#include "rectangle.h"
#include "point.h"
#include "color.h"
#include "key_listener.h"
#include <stdexcept>
#include <memory>

namespace ctn = centurion;
using ctn::Window;
using ctn::Screen;
using ctn::visuals::Renderer;
using ctn::visuals::Texture;
using ctn::visuals::Color;
using ctn::geo::Rectangle;
using ctn::geo::Point;
using ctn::tools::BooleanConverter;
using ctn::events::KeyListener;

Window::Window(const std::string& title, int width, int height, Uint32 flags)
{
	CheckWindowDimensions(width, height);
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  width, height, flags);
	SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	renderer = std::make_unique<Renderer>(sdl_renderer);
}

Window::~Window()
{
	SDL_HideWindow(window);
	SDL_Delay(1);
	SDL_DestroyWindow(window);
}

void Window::CheckWindowDimensions(int width, int height)
{
	if (width < 1 || height < 1) {
		throw std::invalid_argument("Invalid dimensions for window!");
	}
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
	renderer->Update();
}

void Window::AddKeyListener(KeyListener& kl)
{
	//TODO
}

void centurion::Window::ClearWindow()
{
	renderer->Clear();
}

void Window::Render(Texture& img, int x, int y)
{
	renderer->Render(img, x, y);
}

void Window::Render(Texture& img, int x, int y, int w, int h)
{
	renderer->Render(img, x, y, w, h);
}

void Window::Render(Texture& img, Rectangle rect)
{
	renderer->Render(img, rect);
}

void Window::RenderFilledRect(int x, int y, int w, int h)
{
	renderer->RenderFilledRect(x, y, w, h);
}

void Window::RenderOutlinedRect(int x, int y, int w, int h)
{
	renderer->RenderOutlinedRect(x, y, w, h);
}

void Window::RenderLine(int x1, int y1, int x2, int y2)
{
	renderer->RenderLine(x1, y1, x2, y2);
}

void Window::RenderLine(Point p1, Point p2)
{
	renderer->RenderLine(p1, p2);
}

void Window::SetRenderingColor(Color color)
{
	renderer->SetColor(color);
}

Texture* Window::CreateImage(std::string path)
{
	return Texture::Create(path, *renderer);
}