#include "Random.h"

void Random::seedRandom( unsigned seed )
{
	srand( seed );
}

int Random::getNext()
{
	return rand();
}