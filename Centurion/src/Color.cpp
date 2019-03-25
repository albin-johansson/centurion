#include "color.h"

using centurion::visuals::Color;
const Color Color::RED = Color(Color::MAX_VAL, Color::MIN_VAL, Color::MIN_VAL, Color::MAX_VAL);
const Color Color::GREEN = Color(Color::MIN_VAL, Color::MAX_VAL, Color::MIN_VAL, Color::MAX_VAL);
const Color Color::BLUE = Color(Color::MIN_VAL, Color::MIN_VAL, Color::MAX_VAL, Color::MAX_VAL);
const Color Color::WHITE = Color(Color::MAX_VAL, Color::MAX_VAL, Color::MAX_VAL, Color::MAX_VAL);
const Color Color::BLACK = Color(Color::MIN_VAL, Color::MIN_VAL, Color::MIN_VAL, Color::MAX_VAL);

Color::Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	color = { r, g, b, a };
}

uint8_t Color::GetRed()
{
	return color.r;
}

uint8_t Color::GetGreen()
{
	return color.g;
}

uint8_t Color::GetBlue()
{
	return color.b;
}

uint8_t Color::GetAlpha()
{
	return color.a;
}
