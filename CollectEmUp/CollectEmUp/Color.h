#pragma once

#include <algorithm>

class Color
{
public:
	Color();
	Color( float r, float g, float b );
	Color( float r, float g, float b, float a );
	~Color() {}

	float getRed();
	void setRed( float value );

	float getGreen();
	void setGreen( float value );

	float getBlue();
	void setBlue( float value );

	float getAlpha();
	void setAlpha( float value );

	void set( Color c );
	void set( float r, float g, float b, float a = 1.0f );

private:
	float _red;
	float _green;
	float _blue;
	float _alpha;

	float getValidValue( float value );
};

