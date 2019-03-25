#pragma once
#include <SDL.h>
#include "Centurion.h"

class centurion::CTN_Graphics {

private:
	friend class centurion::CTN_Window;
	friend class centurion::CTN_Image;

	SDL_Renderer* renderer = nullptr;

	void Update();

	void clear();

	void Render(centurion::CTN_Image& img, centurion::CTN_Rectangle rect);

	void Render(centurion::CTN_Image& img, int x, int y, int w, int h);

	void Render(centurion::CTN_Image& img, int x, int y);

	void RenderFilledRect(int x, int y, int w, int h);

	void RenderOutlinedRect(int x, int y, int w, int h);
	
	void RenderLine(int x1, int y1, int x2, int y2);

	void RenderLine(centurion::CTN_Point p1, centurion::CTN_Point p2);

	void setColor(centurion::CTN_Color color);

	void checkRenderDimensions(int width, int height);
	
public:
	CTN_Graphics(SDL_Renderer* renderer);

	~CTN_Graphics();
};