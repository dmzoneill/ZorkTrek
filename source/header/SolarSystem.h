#ifndef SOLARSYSTEM_H_
#define SOLARSYSTEM_H_

#include "ZorkTrekLib.h"
#include "Planet.h"

#include "PVEEntity.h"
#include "BorgCube.h"
#include "BorgProbe.h"
#include "BorgQueen.h"
#include "BorgRogue.h"
#include "BorgScout.h"
#include "BorgSphere.h"
#include "BorgTactical.h"

#include "StarTrekEntities.h"

#include <iostream>
#include <string>
#include <map>
#include <vector>

using std::string;
using std::vector;
using std::map;

class SolarSystem 
{
    private:

        string name;
        map<string, SolarSystem*> exits;
        string exitString();
        vector<CelestialBody*> systemPlanets;
        vector<PVEEntity*> enemyShips;

    public:

        SolarSystem(string name, StarTrekEntities *stePointer, unsigned int gameDifficulty);
        ~SolarSystem();

        void setExits(SolarSystem *ahead, SolarSystem *port, SolarSystem *back, SolarSystem *starboard);
        string getName();
        SolarSystem* nextSolarSystem(string direction);

        CelestialBody* targetPlanet(unsigned int i);
        PVEEntity* targetPVEEntity(unsigned int pve_i);
        CelestialBody* targetPlanetMoon(unsigned int planet_i, unsigned int moon_i);

        void scanPlanet(unsigned int i);
        void scanPlanetMoon(unsigned int planet_i, unsigned int moon_i);
        void scanPVEEntity(unsigned int pve_i);

        vector<PVEEntity*> getPVEEntity();
        vector<CelestialBody*> getSystemPlanets();

        PVEEntity* randomAttack(unsigned int difficulty);

        void scanSystem();
        void moveEnemies();
        void addEnemy(PVEEntity* visitor);

        /* operator overloading */
        void operator--();
};

#endif /*SOLARSYSTEM_H_*/
