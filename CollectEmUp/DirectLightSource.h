#pragma once

#include "LightSource.h"

class DirectLightSource :
	public LightSource
{
public:
	DirectLightSource( float brightness, Color color );
	virtual ~DirectLightSource();
};

