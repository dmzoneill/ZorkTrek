#ifndef CELESTIALBODY_H_
#define CELESTIALBODY_H_

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::string;
using std::vector;
using std::endl;

// Abstract data type
// having one or more pure virtual functions is consider an ADT

class CelestialBody
{
    protected:

        string name;
        int trianium;
        int dilithium;
        int foodSupply;
        int waterSupply;
        int health;
        int athmosphericInterference;
        int plasma;
        bool gasGiant;

        // specifically for moons
        // percolated upwards from the moon base class
        // should avoid this in general (otherwise use of RTTI run time type identification required)
        vector<CelestialBody*> moons;
        int numMoons;

    public:

        CelestialBody();
        virtual ~CelestialBody();

        /* following PURE virtual functions should be overridden by the sub class */

        virtual string getName() = 0;

        virtual int getTrianium() = 0;
        virtual int getDilithium() = 0;
        virtual int getFood() = 0;
        virtual int getWater() = 0;
        virtual int getHealth() = 0;
        virtual int getAthmosphericInterference() = 0;
        virtual int getPlasma() = 0;

        virtual void setTrianium(int val) = 0;
        virtual void setDilithium(int val) = 0;
        virtual void setFood(int val) = 0;
        virtual void setWater(int val) = 0;
        virtual void setHealth(int val) = 0;
        virtual void setAthmosphericInterference(int val) = 0;
        virtual void setPlasma(int val) = 0;

        virtual bool getGas() = 0;

        /* non PURE virtual functions (these do not exist in moon) */

        virtual vector<CelestialBody*> getMoons();
        virtual int getNumMoons();
        virtual void scanMoon(unsigned int i);
        virtual CelestialBody* targetMoon(unsigned int i);

};

#endif /*CELESTIALBODY_H_*/
