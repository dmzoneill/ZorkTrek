#ifndef BATTLE_H_
#define BATTLE_H_

#include "ZorkTrekLib.h"
#include "Starship.h"
#include "PVEEntity.h"

#define LASER_DAMAGE (10)
#define PHASED_DAMAGE (20)
#define PULSE_DAMAGE (30)
#define PHOTON_DAMAGE (30)
#define QUANTUM_DAMAGE (60)
#define TRANSPHASIC_DAMAGE (35)
#define CHRONITON_DAMAGE (45)
#define GRAVIMETRIC_DAMAGE (55)
#define SPATIAL_DAMAGE (65)

/**
* Battle handles fight interaction
* holds a pointer to the player
* holds a pointer to the current targeted enemy
*
*/

class Battle
{
    private:

        PVEEntity *enemy;
        StarShip *player;
        void setShielding(bool who, int damage);
        void setArmour(bool who, int damage);
        void setWreck(bool who);
        void describeAction(bool who, string action);

    public:

        Battle();
        Battle(StarShip *ship, PVEEntity *enemy);
        ~Battle();

        void enemyMove();
        void Phaser(bool who);
        void Phased(bool who);
        void Pulse(bool who);
        void Photon(bool who);
        void Quantum(bool who);
        void Transphasic(bool who);
        void Chroniton(bool who);
        void Gravimetric(bool who);
        void Spatial(bool who);
        void Tractor(bool who, bool tractor);
        bool enemyHasTractor();

        PVEEntity* getEnemy();
        string getEnemyName();

};

#endif /*BATTLE_H_*/
