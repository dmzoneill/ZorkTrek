#include "Planet.h"

/**
* Constructor for planet
*
* @param name the name of the planet
* @param stePointer* the pointer to the startrekenties object
*
*/

Planet::Planet(string name, StarTrekEntities *stePointer) 
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

    // add some moons
    seedMicroPrecision();
    int moonCount = int((double(rand())/RAND_MAX)*3); // random between 0 & 3

    for(int y = 0; y < moonCount; y++)
    {
        CelestialBody *moon = new Moon(stePointer->popMoon());
        this->moons.push_back(moon);
    }

    this->numMoons = moonCount;
}


/**
* destructs the planets moons
*/

Planet::~Planet() 
{
    // http://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=/com.ibm.xlcpp8a.doc/language/ref/cplr380.htm
    // You can use a destructor explicitly to destroy objects, although this practice is not recommended.
    // However to destroy an object created with the placement new operator,

    // delete any stuff on the heap (stack is cleared automatically for us )

    cout << "                  \033[33;2m~Deconstructing Planet\033[0m " << endl;
    for(unsigned int y = 0; y < this->moons.size(); y++)
    {
        delete this->moons[y];
    }
}


/**
* Returns the name of this CelestialObject (planet)
*
* @return string
*/

string Planet::getName()
{
    return this->name;
}


/**
* Accessor for the celestial body data member trianium
*
* @return int
*/

int Planet::getTrianium()
{
    return this->trianium;
}


/**
* Accessor for the celestial body data member dilthium
*
* @return int
*/

int Planet::getDilithium()
{
    return this->dilithium;
}


/**
* Accessor for the celestial body data member food
*
* @return int
*/

int Planet::getFood()
{
    return this->foodSupply;
}


/**
* Accessor for the celestial body data member water
*
* @return int
*/

int Planet::getWater()
{
    return this->waterSupply;
}


/**
* Accessor for the celestial body data member health
*
* @return int
*/

int Planet::getHealth()
{
    return this->health;
}


/**
* Accessor for the celestial body data member athmospheric interferance
*
* @return int
*/

int Planet::getAthmosphericInterference()
{
    return this->athmosphericInterference;
}


/**
* Accessor for the celestial body data member plasma
*
* @return int
*/

int Planet::getPlasma()
{
    return this->plasma;
}


/**
* Accessor for the celestial body data member gasgiant
*
* @return int
*/

bool Planet::getGas()
{
    return this->gasGiant;
}


/**
* returns a copy of this planets moon vector
*
* @return vector<CelestialBody*>
*/

vector<CelestialBody*> Planet::getMoons()
{
    return this->moons;
}


/**
* returns the amount of moons orbiting this planet
*
* @return int
*/

int Planet::getNumMoons()
{
    return this->numMoons;
}


/**
* Scans a moon orbitting this planet
*
* @param i the moon vector index
*
* @return void
*/

void Planet::scanMoon(unsigned int i)
{ 
    if(this->moons.size()==0)
        return;

    if(i > this->moons.size() -1)
        return;

    CelestialBody *mo = this->moons[i];

    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                     Stellar Cartography                                \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;
    cout << "                                    Scanning Moon : '\033[34;1m" << mo->getName() << "\033[0m'   " << endl;
    cout << endl;
    cout << "                Trianium                    : " << mo->getTrianium() << "                            " << endl;
    cout << "                Dilithium                   : " << mo->getDilithium() << "                           " << endl;
    cout << "                Food                        : " << mo->getFood() << "                                " << endl;
    cout << "                Water                       : " << mo->getWater() << "                               " << endl;
    cout << "                Health                      : " << mo->getHealth() << "                              " << endl;
    cout << "                Athmospheric Interference   : " << mo->getAthmosphericInterference() << "            " << endl;
    cout << "                Plasma                      : " << mo->getPlasma() << "                              " << endl;
    cout << "                Gas Giant                   : " << (mo->getGas() ? "Yes" : "No") << "                " << endl;

    //delete mo;
}


/**
* returns a pointer to a moon orbiting this planet
*
* @param the moons vector index
*
* @return CelestialBody*
*/

CelestialBody* Planet::targetMoon(unsigned int i)
{ 
    if(this->moons.size()==0)
        return NULL;

    if(i > this->moons.size() -1)
        return NULL;

    return this->moons[i];
}


/**
* Mutator for the celestial body data member trianium
*
* @param int
*
* @return void
*/

void Planet::setTrianium(int val)
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

void Planet::setDilithium(int val)
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

void Planet::setFood(int val)
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

void Planet::setWater(int val)
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

void Planet::setHealth(int val)
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

void Planet::setAthmosphericInterference(int val)
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

void Planet::setPlasma(int val)
{
    this->plasma = val;
}
