#include "Graphics.h"
#include "Image.h"
#include "Color.h"
#include "Rectangle.h"
#include <stdexcept>

using centurion::Graphics;
using centurion::Image;
using centurion::Color;
using centurion::Rectangle;

Graphics::Graphics(SDL_Renderer* renderer)
{
	if (renderer == NULL || renderer == nullptr) {
		throw std::invalid_argument("Null renderer!");
	}
	this->renderer = renderer;
}

Graphics::~Graphics()
{
	SDL_DestroyRenderer(renderer);
}

void Graphics::update()
{
	SDL_RenderPresent(renderer);
}

void Graphics::clear()
{
	SDL_RenderClear(renderer);
}

void Graphics::render(Image& img, int x, int y, int w, int h)
{
	if (w < 1 || h < 1) {
		throw std::invalid_argument("Invalid dimensions for rendering an image!");
	}
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(renderer, img.getTexture(), NULL, &rect);
}

void Graphics::render(Image& img, int x, int y)
{
	render(img, x, y, img.getWidth(), img.getHeight());
}

void Graphics::render(Image& img, Rectangle rect)
{
	render(img, rect.getX(), rect.getY(), rect.getWidth(), rect.getHeight());
}

void Graphics::setColor(Color color)
{
	SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
}