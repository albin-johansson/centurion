#include "graphics.h"
#include "texture.h"
#include "color.h"
#include "rectangle.h"
#include "point.h"
#include "font.h"
#include <stdexcept>

using centurion::visuals::Graphics;
using centurion::visuals::Texture;
using centurion::visuals::Color;
using centurion::geo::Rectangle;
using centurion::geo::Point;
using centurion::Font;
using std::shared_ptr;

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

void Graphics::Render(Texture& img, Rectangle rect)
{
	CheckRenderDimensions(rect.GetWidth(), rect.GetHeight());
	SDL_RenderCopy(renderer, img.GetTexture(), NULL, &rect.CreateSDLRect());
}

void Graphics::Render(Texture& img, int x, int y, int w, int h)
{
	Render(img.GetTexture(), x, y, w, h);
}

void Graphics::Render(Texture& img, int x, int y)
{
	Render(img, x, y, img.GetWidth(), img.GetHeight());
}

void Graphics::Render(SDL_Texture* texture, int x, int y, int w, int h)
{
	if (texture == nullptr || texture == NULL) {
		throw std::invalid_argument("Null texture when rendering!");
	}
	CheckRenderDimensions(w, h);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
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
	SDL_RenderDrawLine(renderer, p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
}

void Graphics::RenderText(const std::string& text, int x, int y, int w, int h)
{

	SDL_Surface* surf = TTF_RenderText_Solid(font->GetSDLFont(), text.c_str(), color.CreateSDLColor());
	SDL_Texture* texture = Texture::CreateTexture(surf, renderer);
	Render(texture, x, y, w, h);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
}

void Graphics::SetFont(const std::shared_ptr<centurion::Font>& font)
{
	this->font = font;
}

void Graphics::SetColor(Color color)
{
	this->color = color;
	UpdateColor();
}

void Graphics::UpdateColor()
{
	SDL_SetRenderDrawColor(renderer, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

void Graphics::CheckRenderDimensions(int width, int height)
{
	if (width < 1 || height < 1) {
		throw std::invalid_argument("Invalid rendering dimensions!");
	}
}