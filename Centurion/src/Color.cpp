#include "color.h"

using centurion::CTN_Color;
const CTN_Color CTN_Color::RED = CTN_Color(CTN_Color::MAX_VAL, CTN_Color::MIN_VAL, CTN_Color::MIN_VAL, CTN_Color::MAX_VAL);
const CTN_Color CTN_Color::GREEN = CTN_Color(CTN_Color::MIN_VAL, CTN_Color::MAX_VAL, CTN_Color::MIN_VAL, CTN_Color::MAX_VAL);
const CTN_Color CTN_Color::BLUE = CTN_Color(CTN_Color::MIN_VAL, CTN_Color::MIN_VAL, CTN_Color::MAX_VAL, CTN_Color::MAX_VAL);
const CTN_Color CTN_Color::WHITE = CTN_Color(CTN_Color::MAX_VAL, CTN_Color::MAX_VAL, CTN_Color::MAX_VAL, CTN_Color::MAX_VAL);
const CTN_Color CTN_Color::BLACK = CTN_Color(CTN_Color::MIN_VAL, CTN_Color::MIN_VAL, CTN_Color::MIN_VAL, CTN_Color::MAX_VAL);

CTN_Color::CTN_Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	color = { r, g, b, a };
}

uint8_t centurion::CTN_Color::getRed()
{
	return color.r;
}

uint8_t centurion::CTN_Color::getGreen()
{
	return color.g;
}

uint8_t centurion::CTN_Color::getBlue()
{
	return color.b;
}

uint8_t centurion::CTN_Color::getAlpha()
{
	return color.a;
}
