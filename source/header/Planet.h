#ifndef PLANET_H_
#define PLANET_H_

#include "CelestialBody.h"
#include "ZorkTrekLib.h"
#include "StarTrekEntities.h"
#include "Moon.h"

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Planet : public CelestialBody
{
    public:

        Planet(string name, StarTrekEntities *stePointer);
        ~Planet();

        /* override from base class */

        string getName();

        int getTrianium();
        int getDilithium();
        int getFood();
        int getWater();
        int getHealth();
        int getAthmosphericInterference();
        int getPlasma();

        void setTrianium(int val);
        void setDilithium(int val);
        void setFood(int val);
        void setWater(int val);
        void setHealth(int val);
        void setAthmosphericInterference(int val);
        void setPlasma(int val);

        bool getGas();

        /* non PURE virtual functions (these do not exist in moon) */

        void scanMoon(unsigned int i);
        CelestialBody* targetMoon(unsigned int i);
        vector<CelestialBody*> getMoons();
        int getNumMoons();

};

#endif /*PLANET_H_*/
