#include "StarTrekEntities.h"


/**
* constructor
*/

StarTrekEntities::StarTrekEntities() 
{
    StarTrekEntities::readSolarSystems("./data/systems.txt");
    StarTrekEntities::readPlanets("./data/planets.txt");
    StarTrekEntities::readMoons("./data/moons.txt");
}


/**
* destructor
*/

StarTrekEntities::~StarTrekEntities() 
{
    // http://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=/com.ibm.xlcpp8a.doc/language/ref/cplr380.htm
    // You can use a destructor explicitly to destroy objects, although this practice is not recommended.
    // However to destroy an object created with the placement new operator,
    // delete any stuff on the heap (stack is cleared automatically for us )
}


/**
* reads the solar systems file
* populates the vector with the list of names
*
* @param filename
*
* @return void
*/

void StarTrekEntities::readSolarSystems(string filename) 
{
    int fileCharLen = filename.length();
    char fname[fileCharLen];

    for (int a=0;a<=fileCharLen;a++)
        fname[a]=filename[a]; // to char array

    try
    {
        ifstream file(fname);
        string line;
        getline(file, line);
        while ( file.good() )
        {
            this->solarSystems.push_back(line);
            getline(file, line);
        }
        this->numSolarSystems = this->solarSystems.size();

        seedMicroPrecision();

        random_shuffle(this->solarSystems.begin(), this->solarSystems.end());
    }
    catch(...)
    {
        cout << "       Catastrophic failure reading star trek entities, check that the files exist and you have read permissions " << endl;
        cout << "              ./data/systems.txt";
        exit(8); // exit failure
        // http://publib.boulder.ibm.com/infocenter/zos/v1r10/index.jsp?topic=/com.ibm.zos.r10.bpxbd00/rtexi.htm
    }
}


/**
* reads the planets file
* populates the vector with the list of names
*
* @param filename
*
* @return void
*/

void StarTrekEntities::readPlanets(string filename) 
{
    int fileCharLen = filename.length();
    char fname[fileCharLen];

    for (int a=0;a<=fileCharLen;a++)
        fname[a]=filename[a]; // to char array

    try
    {
        ifstream file(fname);

        string line;
        getline(file, line);
        while ( file.good() )
        {
            this->planets.push_back(line);
            getline(file, line);
        }
        this->numPlanets = this->planets.size();

        seedMicroPrecision();

        random_shuffle(this->planets.begin(), this->planets.end());
    }
    catch(...)
    {
        cout << "       Catastrophic failure reading star trek entities, check that the files exist and you have read permissions " << endl;
        cout << "             ./data/planets.txt ";
        exit(8); // exit failure
        // http://publib.boulder.ibm.com/infocenter/zos/v1r10/index.jsp?topic=/com.ibm.zos.r10.bpxbd00/rtexi.htm
    }

}


/**
* reads the moons file
* populates the vector with the list of names
*
* @param filename
*
* @return void
*/

void StarTrekEntities::readMoons(string filename) 
{
    int fileCharLen = filename.length();
    char fname[fileCharLen];

    for (int a=0;a<=fileCharLen;a++)
        fname[a]=filename[a]; // to char array

    try
    {
        ifstream file(fname);
        string line;
        getline(file, line);
        while ( file.good() )
        {
            this->moons.push_back(line);
            getline(file, line);
        }
        this->numMoons = this->moons.size();

        seedMicroPrecision();

        random_shuffle(this->moons.begin(), this->moons.end());
    }
    catch(...)
    {
        cout << "       Catastrophic failure reading star trek entities, check that the files exist and you have read permissions " << endl;
        cout << "              ./data/moons.txt";
        exit(8); // exit failure
        // http://publib.boulder.ibm.com/infocenter/zos/v1r10/index.jsp?topic=/com.ibm.zos.r10.bpxbd00/rtexi.htm
    }
}


/**
* Return the number of solar systems names in the vector
*
* @return int
*/

int StarTrekEntities::getNumSolarSystems()
{
    return this->numSolarSystems;
}


/**
* Return the number of planet names in the vector
*
* @return int
*/

int StarTrekEntities::getNumPlanets()
{
    return this->numPlanets;
}


/**
* Return the number of moon names in the vector
*
* @return int
*/

int StarTrekEntities::getNumMoons()
{
    return this->numMoons;
}


/**
* Pop a solar system name from the vector
*
* @return string
*/

string StarTrekEntities::popSolarSystem()
{
    string last = this->solarSystems.back();
    this->solarSystems.pop_back();
    this->numSolarSystems--;
    return last;
}


/**
* Pop a planet name from the vector
*
* @return string
*/

string StarTrekEntities::popPlanet()
{
    string last = this->planets.back();
    this->planets.pop_back();
    this->numPlanets--;
    return last;
}


/**
* Pop a moon name from the vector
*
* @return string
*/

string StarTrekEntities::popMoon()
{
    string last = this->moons.back();
    this->moons.pop_back();
    this->numMoons--;
    return last;
}


/**
* returns the galaxy dimensions sqrt(lenght)
*
* @return int
*/

int StarTrekEntities::getGalaxyMatrixDimensions()
{
    int temp = this->numSolarSystems;
    double sqr = sqrt(temp);
    return (int) ceil(sqr);
}
