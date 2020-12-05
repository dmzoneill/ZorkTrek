#include "SolarSystem.h"

/**
* Constructor for Solarsystem
*
* @param name the name of the solar system
* @param stePointer pointer to the StarTrekEntities object names from file)
* @param gameDifficulty the game difficulty of the game
*
*/

SolarSystem::SolarSystem(string name, StarTrekEntities *stePointer, unsigned int gameDifficulty) 
{
    this->name = name;

    // populate the solar system with pve enemies
    seedMicroPrecision();
    unsigned int enemyCount = int((double(rand())/RAND_MAX)*3) + gameDifficulty;
    int enemyType = 0;

    for(unsigned int y = 0; y < enemyCount; y++)
    {
        seedMicroPrecision();

        PVEEntity *enemy;
        enemyType = int((double(rand())/RAND_MAX)*7);

        switch(enemyType)
        {
            case 1:
                enemy = new BorgQueen();
            break;

            case 2:
                enemy = new BorgRogue();
            break;

            case 3:
                enemy = new BorgScout();
            break;

            case 4:
                enemy = new BorgSphere();
            break;

            case 5:
                enemy = new BorgTactical();
            break;

            case 6:
                enemy = new BorgProbe();
            break;

            default:
                enemy = new BorgCube();

        }
        this->enemyShips.push_back(enemy);
    }

    // populate the solar system with planets
    seedMicroPrecision();
    unsigned int planetCount = int((double(rand())/RAND_MAX)*5) + 1;

    for(unsigned int y = 0; y < planetCount; y++)
    {
        CelestialBody *planet = new Planet(stePointer->popPlanet(),stePointer);
        this->systemPlanets.push_back(planet);
    }
}


/**
* destructor for the solar system
* deletes the pointers to the planets and PVEentities
*/

SolarSystem::~SolarSystem() 
{	
    // http://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=/com.ibm.xlcpp8a.doc/language/ref/cplr380.htm
    // You can use a destructor explicitly to destroy objects, although this practice is not recommended.
    // However to destroy an object created with the placement new operator,

    // delete any stuff on the heap (stack is cleared automatically for us )

    cout << "             \033[31;2m~Deconstructing solar system\033[0m " << endl;

    for(unsigned int y = 0; y < this->enemyShips.size(); y++)
    {
        delete this->enemyShips[y];
    }

    for(unsigned int y = 0; y < this->systemPlanets.size(); y++)
    {
        delete this->systemPlanets[y];
    }
}


/**
* sets the exits for the solar system
*
* @param ahead pointer to a solarsystem
* @param port pointer to a solarsystem
* @param back pointer to a solarsystem
* @param starboard pointer to a solarsystem
*
* @return void
*
*/

void SolarSystem::setExits(SolarSystem *ahead, SolarSystem *port, SolarSystem *back, SolarSystem *starboard) 
{
    if (ahead != NULL)
    {
        exits["ahead"] = ahead;
    }
    if (port != NULL)
    {
        exits["port"] = port;
    }
    if (back != NULL)
    {
        exits["back"] = back;
    }
    if (starboard != NULL)
    {
        exits["starboard"] = starboard;
    }
}


/**
* gets the name of this solar system
*
* @return string the name of the solarsystem
*/

string SolarSystem::getName() 
{
    return this->name;
}


/**
* returns a string of exits
*
* @return string
*/

string SolarSystem::exitString() 
{
    string returnString = "Bearings :";
    for (map<string, SolarSystem*>::iterator i = exits.begin(); i != exits.end(); i++)
    {
        returnString += " " + i->first;
    }
    return returnString;
}


/**
* returns the exit to the requested solar system or null if it does not
* have an exit in that direction
*
* @param direction to travel
*
* @return the pointer to the directed solarsystem or null
*/

SolarSystem* SolarSystem::nextSolarSystem(string direction) 
{
    map<string, SolarSystem*>::iterator next = exits.find(direction);
    if (next == exits.end())
    {
        return NULL;
    }
    return next->second;
}


/**
* prints out information about this solar system
* including enemies, planets & their moons
*
* @return void
*/

void SolarSystem::scanSystem()
{
    int planetMaxL = 20;
    int planetCurL = 0;

    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                 Tactical Officer Report                                \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;

    cout << "                                    The '\033[34;1m" << this->name << "\033[0m' solar system" << endl << endl;

    if(this->systemPlanets.size()>0)
    {
        cout << "         \033[31;1mPlanets \033[0m:" << endl;

        vector<CelestialBody*> moons;

        for (unsigned int i = 0; i < this->systemPlanets.size(); i++)
        {
            cout <<  "             [\033[31;1m" << i << "\033[0m] " << this->systemPlanets[i]->getName() << " ";
            moons = this->systemPlanets[i]->getMoons();
            planetCurL = this->systemPlanets[i]->getName().length();

            if(moons.size()>0)
            {
                for(int k = planetCurL; k < planetMaxL; k++)
                    cout << " ";

                cout << "\033[31;1mMoons \033[0m: ";

                for (unsigned int f = 0; f < moons.size(); f++)
                {
                    cout << "[\033[31;1m" << f << "\033[0m] " << moons[f]->getName() << " ";
                }
            }
            cout << endl;
        }
    }
    else
    {
        cout << endl <<"         \033[31;1mNo Planets \033[0m" << endl;
    }

    if(this->systemPlanets.size()>0 && this->enemyShips.size()>0)
    {
        cout << endl;
    }

    if(this->enemyShips.size()>0)
    {
        cout << "         \033[31;1mBorg Vessels \033[0m:" << endl;

        for (unsigned int i = 0; i < this->enemyShips.size(); i++)
        {
            cout << "             " << "[\033[31;1m" << i << "\033[0m] " << this->enemyShips[i]->getName() << endl;
        }
    }
    else
    {
        cout << endl << "         \033[31;1mNo Borg Vessels \033[0m" << endl;
    }
}


/**
* prints out information about the selected pve in this solarsystem
*
* @param pve_i the pve in the vector to scan
*
* @return void
*/

void SolarSystem::scanPVEEntity(unsigned int pve_i)
{
    if(this->enemyShips.size()==0)
        return;

    if(pve_i > this->enemyShips.size() -1)
        return;

    PVEEntity *pve = this->enemyShips[pve_i];

    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                       Tactical Report                                  \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;
    cout << "                                    Scanning vessel : '\033[31;1m" << pve->getName() << "\033[0m'                  " << endl;
    cout <<  endl;
    cout << "                Shield Strenght            : " << pve->getShieldStrenght() << "                           " << endl;
    cout << "                Shield Regenerative Rate   : " << pve->getShieldRegenerativeRate() << "                   " << endl;
    if(pve->getHasRegenerativeAdaptivePlating())
        cout << "                Adaptive Plating           : " << pve->getRegenerativeAdaptivePlating() << "          " << endl;
    if(pve->getHasTransphasicTorpedos())
        cout << "                Transphasic torpedos       : " << pve->getTransPhasicTorpedos() << "                  " << endl;
    if(pve->getHasChronitonTorpedos())
        cout << "                Chroniton torpedos         : " << pve->getChronitonTorpedos() << "                    " << endl;
    if(pve->getHasGravimetricTorpedos())
        cout << "                Gravimetric torpedos       : " << pve->getGravimetricTorpedos() << "                  " << endl;
    if(pve->getHasSpatialTorpedos())
        cout << "                Spatial torpedos           : " << pve->getSpatialTorpedos() << "                      " << endl;
    if(pve->getHasLasers())
        cout << "                Lasers                     : " << pve->getHasLasers() << "                            " << endl;
    if(pve->getHasPhasedIonCannon())
        cout << "                Phased Ion Cannon          : " << pve->getHasPhasedIonCannon() << "                   " << endl;
    if(pve->getHasPulseWeapon())
        cout << "                Pulse Weapon               : " << pve->getHasPulseWeapon() << "                       " << endl;

    cout << "                Borg Ship Complement       : " << pve->getBorgComplement() << "                           " << endl;
    if(pve->getHasTractorLock())
        cout << "                Tractor lock               : true                                                     " << endl;
    if(pve->getIsWreckPVE())
        cout << "                Wrecked                    : true                                                     " << endl;
    cout <<  endl;
}


/**
* if a target is request for this solar system pve entity, check to see if it exists first
* and return a pointer to the object
*
* @param pve_i the pve entiry to target
*
* @return a pointer to a PVEEntity or null
*/

PVEEntity* SolarSystem::targetPVEEntity(unsigned int pve_i)
{
    if(this->enemyShips.size()==0)
        return NULL;

    if(pve_i > this->enemyShips.size() -1)
        return NULL;

    return this->enemyShips[pve_i];
}


/**
* prints out information about a planet in this solar system
*
* @param i the planet to scan
*
* @return void
*/

void SolarSystem::scanPlanet(unsigned int i)
{
    if(this->systemPlanets.size()==0)
        return;

    if(i > this->systemPlanets.size() -1)
        return;

    CelestialBody *pl = this->systemPlanets[i];

    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << "    | \033[40;31;1m                                     Stellar Cartography                                \033[0m |" << endl;
    cout << "    +------------------------------------------------------------------------------------------+     " << endl;
    cout << endl;
    cout << "                                    Scanning Planet : '\033[34;1m" << pl->getName() << "\033[0m'   " << endl;
    cout << endl;
    cout << "                Trianium                    : " << pl->getTrianium() << "                            " << endl;
    cout << "                Dilithium                   : " << pl->getDilithium() << "                           " << endl;
    cout << "                Food                        : " << pl->getFood() << "                                " << endl;
    cout << "                Water                       : " << pl->getWater() << "                               " << endl;
    cout << "                Health                      : " << pl->getHealth() << "                              " << endl;
    cout << "                Athmospheric Interference   : " << pl->getAthmosphericInterference() << "            " << endl;
    cout << "                Plasma                      : " << pl->getPlasma() << "                              " << endl;
    cout << "                Gas Giant                   : " << (pl->getGas() ? "Yes" : "No") << "                " << endl;
    cout << "                Moons                       : " << pl->getNumMoons() << "                            " << endl;
}


/**
* if a target is request for this solar system planet, check to see if it exists first
* and return a pointer to the object
*
* @param i the planet to target in the vector
*
* @return pointer to CelestialBody(planet) or null
*/

CelestialBody* SolarSystem::targetPlanet(unsigned int i)
{
    if(this->systemPlanets.size()==0)
        return NULL;

    if(i > this->systemPlanets.size() -1)
        return NULL;

    return this->systemPlanets[i];
}


/**
* calls a planets moon and pointer out information about it in the function called
*
* @param planet_i the planet that the moon belongs too
* @param moon_i the moon belong to the planet
*
* @return void
*
*/

void SolarSystem::scanPlanetMoon(unsigned int planet_i,unsigned int moon_i)
{
    if(this->systemPlanets.size()==0)
        return;

    if(planet_i > this->systemPlanets.size() -1)
        return;

    CelestialBody *pl = this->systemPlanets[planet_i];
    pl->scanMoon(moon_i);
}


/**
* if a target is request for this solar system moon, check to see if it exists first
* and return a pointer to the object
*
* @param planet_i the planet that the moon belongs too
* @param moon_i the moon belong to the planet
*
* @return a pointer to the CelestialBody (moon)
*
*/

CelestialBody* SolarSystem::targetPlanetMoon(unsigned int planet_i,unsigned int moon_i)
{
    if(this->systemPlanets.size()==0)
        return NULL;

    if(planet_i > this->systemPlanets.size() -1)
        return NULL;

    CelestialBody *pl = this->systemPlanets[planet_i];
    return pl->targetMoon(moon_i);
}


/**
* once you enter into this solar system enemies will attack based upon the game difficulty
*
* @param difficulty the game difficulty
*
* @return a pointer to a PVEEntity or null
*/

PVEEntity* SolarSystem::randomAttack(unsigned int difficulty)
{
    if(this->enemyShips.size()==0)
        return NULL;

    seedMicroPrecision();
    int randomEnemy = int((double(rand())/RAND_MAX)*(this->enemyShips.size() -1));

    seedMicroPrecision();
    int chance = int((double(rand())/RAND_MAX)*5) + 1; // avoid division by 0 (+1)

    if(difficulty==5) // you will be attacked
    {
        return this->enemyShips[randomEnemy];
    }
    else if(difficulty==4)
    {
        if((chance % 3) >= 1) // 4 in 5 chance
            return this->enemyShips[randomEnemy];
    }
    else if(difficulty==3)
    {
        if((chance % 2) >= 1) // 3 in 5 chance
            return this->enemyShips[randomEnemy];
    }
    else if(difficulty==2)
    {
        if((chance % 3) == 0) // 1 in 5 chance
            return this->enemyShips[randomEnemy];
    }
    else
    {
        // you will not be attacked ( difficulty 1 )
        return NULL;
    }

    // your luck is going to run out!
    return NULL;
}


/**
* returns a copy of the PVE vector
*
* @return vector<PVEEntity*>
*/

vector<PVEEntity*> SolarSystem::getPVEEntity()
{
    return this->enemyShips;
}


/**
* returns a copy of the planets vector
*
* @return vector<CelestialBody*>
*/

vector<CelestialBody*> SolarSystem::getSystemPlanets()
{
    return this->systemPlanets;
}


/**
 * Takes an enemy pointer and adds it to this system
 * Used in conjunction with enemy movement
 *
 * @param visitor the enemy pointer
 */

void SolarSystem::addEnemy(PVEEntity *visitor)
{
    this->enemyShips.push_back(visitor);
}


/**
 * Moves enemies form this solar system to another
 *
 * @return void
 */

void SolarSystem::moveEnemies()
{
    map <string, SolarSystem*> :: const_iterator exitAhead, exitBack, exitPort, exitStarboard;

    exitAhead = this->exits.find("ahead");
    exitBack = this->exits.find("back");
    exitPort = this->exits.find("port");
    exitStarboard = this->exits.find("starboard");

    SolarSystem* enemyEscapeRoute;

    bool randomExit = false;
    unsigned int num = 0;

    while(!randomExit)
    {
        seedMicroPrecision();
        num = int((double(rand())/RAND_MAX)*4)+1;
        switch(num)
        {
            case 1:
                if(exitAhead != this->exits.end())
                {
                    enemyEscapeRoute = exitAhead->second;
                    randomExit = true;
                }
            break;

            case 2:
                if(exitBack != this->exits.end())
                {
                    enemyEscapeRoute = exitBack->second;
                    randomExit = true;
                }
            break;

            case 3:
                if(exitPort != this->exits.end())
                {
                    enemyEscapeRoute = exitPort->second;
                    randomExit = true;
                }
            break;

            case 4:
                if(exitStarboard != this->exits.end())
                {
                    enemyEscapeRoute = exitStarboard->second;
                    randomExit = true;
                }
            break;
        }
    }

    seedMicroPrecision();
    unsigned int amountToMove = 0;
    amountToMove = this->enemyShips.size() - int((double(rand())/RAND_MAX)*(this->enemyShips.size() -1));

    for(unsigned int y = this->enemyShips.size() -1; y > amountToMove; y--)
    {
         enemyEscapeRoute->addEnemy(this->enemyShips[y]);
         this->enemyShips.pop_back();
    }
}


/**
 * Seriously bad example of operator overloading
 *
 * @return void
 */

void SolarSystem::operator--()
{
    // ouch dont call your own destructor?
    this->~SolarSystem();
}
