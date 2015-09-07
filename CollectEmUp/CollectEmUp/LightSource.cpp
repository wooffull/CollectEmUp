#include "LightSource.h"

const float& LightSource::DEFAULT_BRIGHTNESS = 1.0f;
const Color& LightSource::DEFAULT_COLOR = Color(255, 255, 255);

LightSource::LightSource( float brightness, Color color ) :
	FixedObject()
{
	setBrightness( brightness );
	setColor( color );
}

LightSource::~LightSource()
{
}

float LightSource::getBrightness()
{
	return _brightness;
}
void LightSource::setBrightness( float value )
{
	_brightness = value;
}

Color LightSource::getColor()
{
	return _color;
}
void LightSource::setColor( Color value )
{
	_color = value;
}