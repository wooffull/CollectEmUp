#pragma once

class Color
{
public:
	Color();
	Color( unsigned r, unsigned g, unsigned b );
	Color( unsigned r, unsigned g, unsigned b, unsigned a );
	~Color();

	unsigned getRed();
	void setRed( unsigned value );

	unsigned getGreen();
	void setGreen( unsigned value );

	unsigned getBlue();
	void setBlue( unsigned value );

	unsigned getAlpha();
	void setAlpha( unsigned value );

private:
	unsigned _red;
	unsigned _green;
	unsigned _blue;
	unsigned _alpha;
};

