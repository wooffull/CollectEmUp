#pragma once

#include "GameObject.h"
#include "Color.h"

class LightSource :
	GameObject
{
public:
	LightSource( float brightness = LightSource::DEFAULT_BRIGHTNESS, Color color = LightSource::DEFAULT_COLOR );
	virtual ~LightSource();

	float getBrightness();
	void setBrightness( float value );

protected:
	float _brightness;

private:	
	static const float& DEFAULT_BRIGHTNESS;
	static const Color& DEFAULT_COLOR;
};

