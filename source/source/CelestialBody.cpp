#include "CelestialBody.h"

CelestialBody::CelestialBody()
{

}

CelestialBody::~CelestialBody()
{
    cout << "              \033[35;2m~ Virtual Destructor Celestial Body\033[0m " << endl;
}


/**
* To be overridden by the sub class
* returns a copy of the moons vector
*
* @return vector<CelestialBody*>
*/

vector<CelestialBody*> CelestialBody::getMoons()
{
    return this->moons;
}


/**
* To be overridden by the sub class
* gets the amount of celestialbody moons
*
* @return int number of moons
*/

int CelestialBody::getNumMoons()
{
    return this->numMoons;
}


/**
* To be overridden by the sub class
* scans a celestialbody (moon) in he vector
*
* @param i the moon index in the vector
*
* @return void
*/

void CelestialBody::scanMoon(unsigned int i)
{
    // should be overridden
}


/**
* To be overridden by the sub class
* gets a pointer to a moon
*
* @param i the index in the moons vector
*
* @return CelestialBody* a pointer to a moon
*/

CelestialBody* CelestialBody::targetMoon(unsigned int i)
{
    return NULL;
}

