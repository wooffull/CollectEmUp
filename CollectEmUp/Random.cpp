#include "Random.h"

void Random::seedRandom( unsigned seed )
{
    srand( seed );
}

int Random::getNext()
{
    return rand();
}

float Random::getRange( float min, float max )
{
    return min + static_cast<float>( getNext() ) / ( static_cast<float>( RAND_MAX / ( max - min ) ) );
}
