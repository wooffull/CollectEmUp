#include "Color.h"

Color::Color()
{
	_red = 0;
	_green = 0;
	_blue = 0;
	_alpha = 255;
}

Color::Color( unsigned r, unsigned g, unsigned b )
{
	_red = r;
	_green = g;
	_blue = b;
	_alpha = 255;
}

Color::Color( unsigned r, unsigned g, unsigned b, unsigned a )
{
	_red = r;
	_green = g;
	_blue = b;
	_alpha = a;
}

Color::~Color()
{
}

unsigned Color::getRed()
{
	return _red;
}
void Color::setRed( unsigned value )
{
	_red = value;
}

unsigned Color::getGreen()
{
	return _green;
}
void Color::setGreen( unsigned value )
{
	_green = value;
}

unsigned Color::getBlue()
{
	return _blue;
}
void Color::setBlue( unsigned value )
{
	_blue = value;
}

unsigned Color::getAlpha()
{
	return _alpha;
}
void Color::setAlpha( unsigned value )
{
	_alpha = value;
}