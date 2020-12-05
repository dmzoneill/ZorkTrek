#ifndef STARSHIP_H_
#define STARSHIP_H_

#include <iostream>
#include <string>
#include <signal.h> // signals for thread
#include <pthread.h> // posix threading
#include <unistd.h>

#define FOOD_WEIGHT (2)
#define WATER_WEIGHT (1)
#define TRIANIUM_WEIGHT (10)
#define DILITHIUM_WEIGHT (5)
#define PLASMA_WEIGHT (3)

#define CARGOHOLD_MAX_WEIGHT (10000)

#define TRIANIUM_REQUIRED (500)
#define DILITHIUM_REQUIRED (200)
#define PLASMA_REQUIRED (100)

#define MAX_POWER (1000)
#define MAX_SHIELDS (2500)
#define MAX_ARMOUR (1000)

#define REPAIR_NEEDED_TRIANIUM (350)
#define REPAIR_NEEDED_DILITHIUM (500)

using std::string;
using std::cout;
using std::endl;

class StarShip 
{
    private:

        string name;
        int photons;
        int quantums;
        int shields;
        int shieldRegenRate;
        int armour;

        int food;
        int water;
        int plasma;
        int trianium;
        int dilithium;

        int cargohold;
        int power;

        bool hasTractorLock;
        bool isWreck;

        bool enginesRepaired;

        int usage();

        // posix thread for shield regeneration map
        pthread_t shieldThread;
        bool shieldThreadRunning;
        static void *shieldRegenThread(void *ptr); // function signature for our thread function


    public:

        StarShip(string name, int gameDifficulty);
        ~StarShip();

        string getName();

        int getShieldStrenght();
        int getShieldRegenerativeRate();

        int getArmour();
        int getPhotons();
        int getQuantums();
        int getPower();

        int getFood();
        int getWater();
        int getPlasma();
        int getTrianium();
        int getDilithium();
        int getCargoWeight();

        bool getHasTractorLock();
        bool getIsWreck();

        void setShieldStrenght(int strenght);
        void setShieldRegenerativeRate(int rate);

        void setArmour(int armour);
        void setPhotons(int num);
        void setQuantums(int num);
        void setPower(int num);

        void setFood(int val);
        void setWater(int val);
        void setPlasma(int val, bool transporter);
        void setTrianium(int val);
        void setDilithium(int val);
        void updateCargoWeight();

        void setHasTractorLock(bool has);
        void setWreck();
        bool isRepaired() { return this->enginesRepaired; };

        void repair();

};

#endif /*STARSHIP_H_*/
