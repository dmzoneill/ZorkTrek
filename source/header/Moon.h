#ifndef MOON_H_
#define MOON_H_

#include "CelestialBody.h"
#include <iostream>
#include <string>

using std::string;

class Moon : public CelestialBody
{
    public:

        Moon(string name);
        ~Moon();

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

};

#endif /*MOON_H_*/
