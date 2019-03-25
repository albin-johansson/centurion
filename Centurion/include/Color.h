#pragma once
#include "Centurion.h"
#include <SDL.h>
#include <stdint.h>

class centurion::CTN_Color {

private:
	SDL_Color color;

public:
	const static uint8_t MAX_VAL = 255;
	const static uint8_t MIN_VAL = 0;
	const static CTN_Color RED;
	const static CTN_Color GREEN;
	const static CTN_Color BLUE;
	const static CTN_Color WHITE;
	const static CTN_Color BLACK;

	CTN_Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	~CTN_Color() = default;

	uint8_t getRed();

	uint8_t getGreen();

	uint8_t getBlue();

	uint8_t getAlpha();
};