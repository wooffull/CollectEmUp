#pragma once

#include <iostream>

class Random final
{
public:
	static void seedRandom( unsigned seed );
	static int getNext();

protected:
	Random() {} // Prevent instantiation
};

