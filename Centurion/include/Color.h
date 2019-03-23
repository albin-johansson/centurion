#pragma once
#include "Centurion.h"
#include <SDL.h>
#include <stdint.h>

class centurion::Color {

private:
	SDL_Color color;

public:
	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	~Color();

	uint8_t getRed();

	uint8_t getGreen();

	uint8_t getBlue();

	uint8_t getAlpha();
};