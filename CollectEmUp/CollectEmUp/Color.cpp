#include "Color.h"

Color::Color()
{
	set( 0, 0, 0 );
}

Color::Color( float r, float g, float b )
{
	set( r, g, b );
}

Color::Color( float r, float g, float b, float a )
{
	set( r, g, b, a );
}

float Color::getRed()
{
	return _red;
}
void Color::setRed( float value )
{
	_red = getValidValue( value );
}

float Color::getGreen()
{
	return _green;
}
void Color::setGreen( float value )
{
	_green = getValidValue( value );
}

float Color::getBlue()
{
	return _blue;
}
void Color::setBlue( float value )
{
	_blue = getValidValue( value );
}

float Color::getAlpha()
{
	return _alpha;
}
void Color::setAlpha( float value )
{
	_alpha = getValidValue( value );
}

void Color::set( Color c )
{
	setRed( c.getRed() );
	setGreen( c.getGreen() );
	setBlue( c.getBlue() );
	setAlpha( c.getAlpha() );
}
void Color::set( float r, float g, float b, float a )
{
	setRed( r );
	setGreen( g );
	setBlue( b );
	setAlpha( a );
}

/**
 * Gets a value limited to the range 0 to 1
 */
float Color::getValidValue( float value )
{
	return std::max<float>( 0, std::min<float>( 1.0f, value ) );
}