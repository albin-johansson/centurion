#pragma once
#include "centurion.h"
#include <SDL_ttf.h>
#include <string>

class centurion::Font {

private:
	TTF_Font* font;
	int size;

public:
	Font(const std::string& path, int size);

	~Font();

	int getSize();

	TTF_Font* GetSDLFont();
};