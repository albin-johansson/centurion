#include "graphics.h"
#include "image.h"
#include "color.h"
#include "rectangle.h"
#include "point.h"
#include <stdexcept>

using centurion::CTN_Graphics;
using centurion::CTN_Image;
using centurion::CTN_Color;
using centurion::CTN_Rectangle;
using centurion::CTN_Point;

CTN_Graphics::CTN_Graphics(SDL_Renderer* renderer)
{
	if (renderer == NULL || renderer == nullptr) {
		throw std::invalid_argument("Null renderer!");
	}
	this->renderer = renderer;
}

CTN_Graphics::~CTN_Graphics()
{
	SDL_DestroyRenderer(renderer);
}

void CTN_Graphics::Update()
{
	SDL_RenderPresent(renderer);
}

void CTN_Graphics::Clear()
{
	SDL_RenderClear(renderer);
}

void CTN_Graphics::Render(CTN_Image& img, CTN_Rectangle rect)
{
	CheckRenderDimensions(rect.getWidth(), rect.getHeight());
	SDL_RenderCopy(renderer, img.getTexture(), NULL, &rect.createSDLRect());
}

void CTN_Graphics::Render(CTN_Image& img, int x, int y, int w, int h)
{
	CheckRenderDimensions(w, h);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(renderer, img.getTexture(), NULL, &rect);
}

void CTN_Graphics::Render(CTN_Image& img, int x, int y)
{
	Render(img, x, y, img.getWidth(), img.getHeight());
}

void CTN_Graphics::RenderFilledRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}

void CTN_Graphics::RenderOutlinedRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderDrawRect(renderer, &rect);
}

void CTN_Graphics::RenderLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void CTN_Graphics::RenderLine(CTN_Point p1, CTN_Point p2)
{
	SDL_RenderDrawLine(renderer, p1.getX(), p1.getY(), p2.getX(), p2.getY());
}

void CTN_Graphics::SetColor(CTN_Color color)
{
	SDL_SetRenderDrawColor(renderer, color.getRed(), color.getGreen(), color.getBlue(), color.getAlpha());
}

void CTN_Graphics::CheckRenderDimensions(int width, int height)
{
	if (width < 1 || height < 1) {
		throw std::invalid_argument("Invalid rendering dimensions!");
	}
}