#include "LightSource.h"

const float& LightSource::DEFAULT_BRIGHTNESS = 1.0f;
const Color& LightSource::DEFAULT_COLOR = Color( 1.0f, 1.0f, 1.0f );

LightSource::LightSource( float brightness, Color color ) :
	GameObject()
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