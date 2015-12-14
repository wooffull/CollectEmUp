#pragma once

#include <iostream>

class Random final
{
public:
    static void seedRandom( unsigned seed );
    static int getNext();
    static float getRange( float min, float max );

protected:
    Random() {} // Prevent instantiation
};

