#ifndef STARTREKENTITES_H_
#define STARTREKENTITES_H_

#include "ZorkTrekLib.h"
#include <algorithm> // shuffle
#include <string>
#include <fstream> // files
#include <iostream> // input output stream
#include <vector>
#include <cmath> // sqr ceil etc

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;

class StarTrekEntities 
{
    private:

        void readSolarSystems(string filename);
        void readPlanets(string filename);
        void readMoons(string filename);

        vector<string> solarSystems;
        vector<string> moons;
        vector<string> planets;

        int numSolarSystems;
        int numPlanets;
        int numMoons;

    public:

        StarTrekEntities();
        ~StarTrekEntities();

        int getNumSolarSystems();
        int getNumPlanets();
        int getNumMoons();

        string popSolarSystem();
        string popPlanet();
        string popMoon();

        int getGalaxyMatrixDimensions();


};

#endif /*STARTREKENTITES_H_*/
