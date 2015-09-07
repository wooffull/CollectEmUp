#pragma once

#include "FixedObject.h"
#include "Color.h"

class LightSource :
	FixedObject
{
public:
	LightSource( float brightness = DEFAULT_BRIGHTNESS, Color color = DEFAULT_COLOR );
	virtual ~LightSource();

	float getBrightness();
	void setBrightness( float value );

	Color getColor();
	void setColor( Color value );

protected:
	float _brightness;
	Color _color;

private:	
	static const float& DEFAULT_BRIGHTNESS;
	static const Color& DEFAULT_COLOR;
};

