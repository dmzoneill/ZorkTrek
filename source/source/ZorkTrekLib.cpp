#include "ZorkTrekLib.h"


/**
* seeds the random number generator with microseconds
* from the timeval struct
*/

void seedMicroPrecision()
{
    struct timeval tv;
    gettimeofday(&tv, 0);

    // use microsecond precision as seed
    long int n = tv.tv_usec;
    srand(n);
}
