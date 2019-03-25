#pragma once
#include <SDL.h>
#include "centurion.h"

class centurion::visuals::Graphics {

private:
	friend class centurion::Window;
	friend class centurion::visuals::Image;

	SDL_Renderer* renderer = nullptr;

	void Update();
	
	void Clear();

	void Render(centurion::visuals::Image& img, centurion::geo::Rectangle rect);

	void Render(centurion::visuals::Image& img, int x, int y, int w, int h);

	void Render(centurion::visuals::Image& img, int x, int y);

	void RenderFilledRect(int x, int y, int w, int h);

	void RenderOutlinedRect(int x, int y, int w, int h);
	
	void RenderLine(int x1, int y1, int x2, int y2);

	void RenderLine(centurion::geo::Point p1, centurion::geo::Point p2);

	void SetColor(centurion::visuals::Color color);

	void CheckRenderDimensions(int width, int height);
	
public:
	Graphics(SDL_Renderer* renderer);

	~Graphics();
};