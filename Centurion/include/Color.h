#pragma once
#include <SDL.h>
#include <stdint.h>
#include "centurion.h"

class centurion::Color {

private:
	SDL_Color color;

public:
	const static uint8_t MAX_VAL = 255;
	const static uint8_t MIN_VAL = 0;
	const static Color RED;
	const static Color GREEN;
	const static Color BLUE;
	const static Color WHITE;
	const static Color BLACK;

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	~Color() = default;

	uint8_t GetRed();

	uint8_t GetGreen();

	uint8_t GetBlue();

	uint8_t GetAlpha();
};