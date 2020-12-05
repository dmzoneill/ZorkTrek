#include "Moon.h"

/**
* Constructor
*
* @param string the name of the moon
*/

Moon::Moon(string name) 
{
    this->name = name;
    this->trianium = 100;
    this->dilithium = 100;
    this->foodSupply = 297;
    this->waterSupply = 300;
    this->health = 9999999;
    this->athmosphericInterference = 20;
    this->plasma = 33;
    this->gasGiant = false;
}

/*
 * Destructor
 */

Moon::~Moon() 
{
    cout << "                       \033[34;2m~Deconstructing Moon\033[0m " << endl;
}


/**
* Returns the name of this CelestialObject (moon)
*
* @return string
*/

string Moon::getName()
{
    return this->name;
}


/**
* Accessor for the celestial body data member trianium
*
* @return int
*/

int Moon::getTrianium()
{
    return this->trianium;
}


/**
* Accessor for the celestial body data member dilthium
*
* @return int
*/

int Moon::getDilithium()
{
    return this->dilithium;
}


/**
* Accessor for the celestial body data member food
*
* @return int
*/

int Moon::getFood()
{
    return this->foodSupply;
}


/**
* Accessor for the celestial body data member water
*
* @return int
*/

int Moon::getWater()
{
    return this->waterSupply;
}


/**
* Accessor for the celestial body data member health
*
* @return int
*/

int Moon::getHealth()
{
    return this->health;
}


/**
* Accessor for the celestial body data member athmospheric interferance
*
* @return int
*/

int Moon::getAthmosphericInterference()
{
    return this->athmosphericInterference;
}


/**
* Accessor for the celestial body data member plasma
*
* @return int
*/

int Moon::getPlasma()
{
    return this->plasma;
}


/**
* Accessor for the celestial body data member gasgiant
*
* @return int
*/

bool Moon::getGas()
{
    return this->gasGiant;
}


/**
* Mutator for the celestial body data member trianium
*
* @param int
*
* @return void
*/

void Moon::setTrianium(int val)
{
    this->trianium = val;
}


/**
* Mutator for the celestial body data member dilithium
*
* @param int
*
* @return void
*/

void Moon::setDilithium(int val)
{
    this->dilithium = val;
}


/**
* Mutator for the celestial body data member food
*
* @param int
*
* @return void
*/

void Moon::setFood(int val)
{
    this->foodSupply = val;
}


/**
* Mutator for the celestial body data member water
*
* @param int
*
* @return void
*/

void Moon::setWater(int val)
{
    this->waterSupply = val;
}


/**
* Mutator for the celestial body data member health
*
* @param int
*
* @return void
*/

void Moon::setHealth(int val)
{
    this->health = val;
}


/**
* Mutator for the celestial body data member athmospheric interferance
*
* @param int
*
* @return void
*/

void Moon::setAthmosphericInterference(int val)
{
    this->athmosphericInterference = val;
}


/**
* Mutator for the celestial body data member plasma
*
* @param int
*
* @return void
*/

void Moon::setPlasma(int val)
{
    this->plasma = val;
}
