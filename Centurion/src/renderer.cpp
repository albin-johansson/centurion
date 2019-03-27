#include "renderer.h"
#include "texture.h"
#include "color.h"
#include "rectangle.h"
#include "point.h"
#include "font.h"
#include "null_checker.h"
#include <stdexcept>

namespace ctn = centurion;
using ctn::visuals::Renderer;
using ctn::visuals::Texture;
using ctn::visuals::Color;
using ctn::tools::NullChecker;
using ctn::geo::Rectangle;
using ctn::geo::Point;
using ctn::Font;
using std::shared_ptr;

//FIXME fix doc comments refering textures as "images"

Renderer::Renderer(SDL_Renderer* renderer)
{
	if (NullChecker::IsNull(renderer)) {
		throw std::invalid_argument("Null renderer!");
	}
	this->renderer = renderer;
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(renderer);
}

void Renderer::Update()
{
	SDL_RenderPresent(renderer);
}

void Renderer::Clear()
{
	SDL_RenderClear(renderer);
}

void Renderer::Render(Texture& img, Rectangle rect)
{
	CheckRenderDimensions(rect.GetWidth(), rect.GetHeight());
	SDL_RenderCopy(renderer, img.GetTexture(), NULL, &rect.CreateSDLRect());
}

void Renderer::Render(Texture& img, int x, int y, int w, int h)
{
	Render(img.GetTexture(), x, y, w, h);
}

void Renderer::Render(Texture& img, int x, int y)
{
	Render(img, x, y, img.GetWidth(), img.GetHeight());
}

void Renderer::Render(SDL_Texture* texture, int x, int y, int w, int h) //FIXME don't take pointer to texture
{
	if (NullChecker::IsNull(texture)) {
		throw std::invalid_argument("Null texture when rendering!");
	}
	CheckRenderDimensions(w, h);
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderCopy(renderer, texture, NULL, &rect);
}

void Renderer::RenderFilledRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderFillRect(renderer, &rect);
}

void Renderer::RenderOutlinedRect(int x, int y, int w, int h)
{
	SDL_Rect rect = { x, y, w, h };
	SDL_RenderDrawRect(renderer, &rect);
}

void Renderer::RenderLine(int x1, int y1, int x2, int y2)
{
	SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void Renderer::RenderLine(Point p1, Point p2)
{
	SDL_RenderDrawLine(renderer, p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY());
}

//TODO don't keep this method, instead use method that converts a string into a texture
void Renderer::RenderText(const std::string& text, int x, int y, int w, int h)
{
	SDL_Surface* surf = TTF_RenderText_Solid(font->GetSDLVersion(), text.c_str(), color.GetSDLVersion());
	SDL_Texture* texture = Texture::CreateSDLTexture(surf, renderer);
	Render(texture, x, y, w, h);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surf);
}

void Renderer::SetFont(const std::shared_ptr<centurion::Font>& font) //TODO Keep?
{
	this->font = font;
}

void Renderer::SetColor(Color color)
{
	this->color = color;
	UpdateColor();
}

void Renderer::UpdateColor()
{
	SDL_SetRenderDrawColor(renderer, color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
}

void Renderer::CheckRenderDimensions(int width, int height)
{
	if (width < 1 || height < 1) {
		throw std::invalid_argument("Invalid rendering dimensions!");
	}
}

SDL_Renderer* Renderer::GetSDLRenderer()
{
	return renderer;
}