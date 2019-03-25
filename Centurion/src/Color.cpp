#include "Color.h"
#include <stdint.h>
#include <stdexcept>

using centurion::Color;
const Color Color::RED = Color(Color::MAX_VAL, Color::MIN_VAL, Color::MIN_VAL, Color::MAX_VAL);
const Color Color::GREEN = Color(Color::MIN_VAL, Color::MAX_VAL, Color::MIN_VAL, Color::MAX_VAL);
const Color Color::BLUE = Color(Color::MIN_VAL, Color::MIN_VAL, Color::MAX_VAL, Color::MAX_VAL);
const Color Color::WHITE = Color(Color::MAX_VAL, Color::MAX_VAL, Color::MAX_VAL, Color::MAX_VAL);
const Color Color::BLACK = Color(Color::MIN_VAL, Color::MIN_VAL, Color::MIN_VAL, Color::MAX_VAL);

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
