#include "Graphics.h"
#include "Image.h"
#include "Color.h"
#include "Rectangle.h"
#include "Point.h"
#include <stdexcept>

using centurion::Graphics;
using centurion::Image;
using centurion::Color;
using centurion::Rectangle;
using centurion::Point;

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

void Graphics::render(Image& img, Rectangle rect)
{
	checkRenderDimensions(rect.getWidth(), rect.getHeight());
	SDL_RenderCopy(renderer, img.getTexture(), NULL, &rect.createSDLRect());
}

void Graphics::render(Image& img, int x, int y, int w, int h)
{
	checkRenderDimensions(w, h);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(renderer, img.getTexture(), NULL, &rect);
}

void Graphics::render(Image& img, int x, int y)
{
	render(img, x, y, img.getWidth(), img.getHeight());
}

void Graphics::renderFilledRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}

void Graphics::renderOutlinedRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderDrawRect(renderer, &rect);
}

void Graphics::renderLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Graphics::renderLine(Point p1, Point p2)
{
	SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void Graphics::setColor(Color color)
{
	SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
}

void Graphics::checkRenderDimensions(int width, int height)
{
	if (width < 1 || height < 1) {
		throw std::invalid_argument("Invalid rendering dimensions!");
	}
}