#include "Color.h"
#include <stdint.h>

using centurion::Color;

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	color = { r, g, b, a };
}

uint8_t centurion::Color::getRed()
{
	return color.r;
}

uint8_t centurion::Color::getGreen()
{
	return color.g;
}

uint8_t centurion::Color::getBlue()
{
	return color.b;
}

uint8_t centurion::Color::getAlpha()
{
	return color.a;
}
