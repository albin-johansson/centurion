#pragma once
#include <SDL.h>
#include "centurion.h"

class centurion::Graphics {

private:
	friend class centurion::Window;
	friend class centurion::Image;

	SDL_Renderer* renderer = nullptr;

	void Update();
	
	void Clear();

	void Render(centurion::Image& img, centurion::Rectangle rect);

	void Render(centurion::Image& img, int x, int y, int w, int h);

	void Render(centurion::Image& img, int x, int y);

	void RenderFilledRect(int x, int y, int w, int h);

	void RenderOutlinedRect(int x, int y, int w, int h);
	
	void RenderLine(int x1, int y1, int x2, int y2);

	void RenderLine(centurion::Point p1, centurion::Point p2);

	void SetColor(centurion::Color color);

	void CheckRenderDimensions(int width, int height);
	
public:
	Graphics(SDL_Renderer* renderer);

	~Graphics();
};