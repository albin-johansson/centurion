#include "graphics.h"
#include "image.h"
#include "color.h"
#include "rectangle.h"
#include "point.h"
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

void Graphics::Update()
{
	SDL_RenderPresent(renderer);
}

void Graphics::Clear()
{
	SDL_RenderClear(renderer);
}

void Graphics::Render(Image& img, Rectangle rect)
{
	CheckRenderDimensions(rect.getWidth(), rect.getHeight());
	SDL_RenderCopy(renderer, img.getTexture(), NULL, &rect.createSDLRect());
}

void Graphics::Render(Image& img, int x, int y, int w, int h)
{
	CheckRenderDimensions(w, h);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(renderer, img.getTexture(), NULL, &rect);
}

void Graphics::Render(Image& img, int x, int y)
{
	Render(img, x, y, img.getWidth(), img.getHeight());
}

void Graphics::RenderFilledRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}

void Graphics::RenderOutlinedRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderDrawRect(renderer, &rect);
}

void Graphics::RenderLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Graphics::RenderLine(Point p1, Point p2)
{
	SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void Graphics::SetColor(Color color)
{
	SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
}

void Graphics::CheckRenderDimensions(int width, int height)
{
	if (width < 1 || height < 1) {
		throw std::invalid_argument("Invalid rendering dimensions!");
	}
}