#include "window.h"
#include "drawable.h"
#include "renderer.h"
#include "boolean_converter.h"
#include <stdexcept>
#include <memory>

using centurion::Window;
using centurion::visuals::Drawable;
using centurion::visuals::Renderer;
using centurion::tools::BooleanConverter;
using std::make_unique;
using std::shared_ptr;

Window::Window(const std::string& title, int width, int height, Uint32 flags)
	: width(width), height(height)
{
	CheckWindowDimensions(width, height);
	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
							  width, height, flags);
	SDL_Renderer* sdl_renderer = SDL_CreateRenderer(window, -1, SDL_RendererFlags::SDL_RENDERER_ACCELERATED);
	renderer = make_unique<Renderer>(sdl_renderer);
	drawable = nullptr;
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
	return width;
}

int Window::GetHeight()
{
	return height;
}

void Window::Render()
{
	renderer->Clear();
	if (drawable != nullptr) {
		drawable->Draw(*renderer);
	}
	renderer->Update();
}

void Window::SetDrawable(shared_ptr<Drawable>& drawable)
{
	this->drawable = drawable;
}