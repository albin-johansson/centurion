#pragma once
#include "Centurion.h"
#include <SDL.h>
#include <stdint.h>

class centurion::Color {

private:
	SDL_Color color;

public:
	const static uint8_t MAX_VAL = 255;
	const static uint8_t MIN_VAL = 0;
	const static centurion::Color RED;
	const static centurion::Color GREEN;
	const static centurion::Color BLUE;
	const static centurion::Color WHITE;
	const static centurion::Color BLACK;

	Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

	~Color() = default;

	uint8_t getRed();

	uint8_t getGreen();

	uint8_t getBlue();

	uint8_t getAlpha();
};