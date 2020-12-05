#include "Battle.h"

/**
* Default Constructor
*/

Battle::Battle() 
{

}


/**
* A new instance of a battle must have a pointer to the current players SharShip and the enemy being engaged
*
* @param *ship a pointer to the current player's StarShip
* @param *enemy a pointer to the PVEEntity currently being engaged
* @return constructor does not have a return type
* @see Battle::getIsWreckPVE
*/

Battle::Battle(StarShip *ship, PVEEntity *enemy)
{
    this->player = ship;
    this->enemy = enemy;

    if(this->enemy->getIsWreckPVE() == false)
    {
        cout <<  endl;
        cout << "    +------------------------------------------------------------------------------------------+     " << endl;
        cout << "    | \033[40;31;1m                                   Battle Transmission                                  \033[0m |     " << endl;
        cout << "    +------------------------------------------------------------------------------------------+     " << endl;
        cout << endl;
        cout << "                            Incoming transmission from '\033[31;1m" << enemy->getName() << "\033[0m' "  << endl;
        cout << "                                          We are the Borg                                            " << endl;
        cout << "                                      You will be assimilated                                        " << endl;
        cout << "             Your biological and technological distinctiveness will be added to our own              " << endl;
        cout << "                                       Resistance is futile.                                         " << endl;
        cout <<  endl;
    }	                                                                                                          
}	


/**
* @return deconstructor does not have a return type
*/

Battle::~Battle() 
{
    // nothing on heap (stacked)
    // http://publib.boulder.ibm.com/infocenter/comphelp/v8v101/index.jsp?topic=/com.ibm.xlcpp8a.doc/language/ref/cplr380.htm
    // You can use a destructor explicitly to destroy objects, although this practice is not recommended.
    // However to destroy an object created with the placement new operator,

    // delete any stuff on the heap (stack is cleared automatically for us )

    cout << endl << "     \033[36;2m~Deconstructing Battle\033[0m  " << endl;
}	


/**
* Randomly Performs a enemy move
* returns if the enemy is destroyed
* only performs an action if the enemy have that type of weapon
* seedMicroPrecision decides the action of the switch
*
* @return void
*
* @see Battle::getIsWreckPVE
*
* @see Battle::Phaser
* @see Battle::Phased
* @see Battle::Pulse
* @see Battle::Transphasic
* @see Battle::Chroniton
* @see Battle::Gravimetric
* @see Battle::Spatial
* @see Battle::Tractor
*
* @see seedMicroPrecision
*
* @see PVEEntity::getHasLasers
* @see PVEEntity::getHasPhasedIonCannon
* @see PVEEntity::getHasPulseWeapon
* @see PVEEntity::getHasTransphasicTorpedos
* @see PVEEntity::getHasChronitonTorpedos
* @see PVEEntity::getHasGravimetricTorpedos
* @see PVEEntity::getHasSpatialTorpedos
* @see PVEEntity::getHasTractorLock
*
*/

void Battle::enemyMove()
{
    if(this->enemy->getIsWreckPVE())
        return;

    bool action = false;

    // random move enemy
    seedMicroPrecision();

    int move = 0;

    move = int((double(rand())/RAND_MAX)*7) + 1; // random between 1 & 8

    while(!action)
    {
        switch(move)
        {
            case 1:
                if(this->enemy->getHasLasers())
                {
                    this->Phaser(true);
                    action = true;
                }
                else
                {
                    seedMicroPrecision();
                    move = int((double(rand())/RAND_MAX)*7) + 1;
                }
                break;

            case 2:
                if(this->enemy->getHasPhasedIonCannon())
                {
                    this->Phased(true);
                    action = true;
                }
                else
                {
                    seedMicroPrecision();
                    move = int((double(rand())/RAND_MAX)*7) + 1;
                }
                break;

            case 3:
                if(this->enemy->getHasPulseWeapon())
                {
                    this->Pulse(true);
                    action = true;
                }
                else
                {
                    seedMicroPrecision();
                    move = int((double(rand())/RAND_MAX)*7) + 1;
                }
                break;

            case 4:
                if(this->enemy->getHasTransphasicTorpedos())
                {
                    this->Transphasic(true);
                    action = true;
                }
                else
                {
                    seedMicroPrecision();
                    move = int((double(rand())/RAND_MAX)*7) + 1;
                }
                break;

            case 5:
                if(this->enemy->getHasChronitonTorpedos())
                {
                    this->Chroniton(true);
                    action = true;
                }
                else
                {
                    seedMicroPrecision();
                    move = int((double(rand())/RAND_MAX)*7) + 1;
                }
                break;

            case 6:
                if(this->enemy->getHasGravimetricTorpedos())
                {
                    this->Gravimetric(true);
                    action = true;
                }
                else
                {
                    seedMicroPrecision();
                    move = int((double(rand())/RAND_MAX)*7) + 1;
                }
                break;

            case 7:
                if(this->enemy->getHasSpatialTorpedos())
                {
                    this->Spatial(true);
                    action = true;
                }
                else
                {
                    seedMicroPrecision();
                    move = int((double(rand())/RAND_MAX)*7) + 1;
                }
                break;

            case 8:
                this->Tractor(false, !this->enemy->getHasTractorLock());
                action = true;
                break;
        }
    }
}	


/**
* Updates the enemy or current players shield strength after an attacking action has occurred
* A certain amount of variability is is multiplied by the damage
*
* @param who true = player false = current enemy
* @param damage the damage to inflict on the player / enemy
*
* @return void
*
* @see Battle::getIsWreckPVE
* @see Battle::setArmour
*
* @see StarShip::getShieldStrenght
* @see StarShip::setShieldStrenght
*
* @see seedMicroPrecision
*
* @see PVEEntity::getShieldStrenght
* @see PVEEntity::setShieldStrenghtPVE
*
*/

void Battle::setShielding(bool who, int damage)
{
    // seed the random generator
    seedMicroPrecision();

    // multiple the damage by a random number
    int randdmg = int((double(rand())/RAND_MAX)*75) + 50; // 50  - 125
    damage = (damage * randdmg) / 100;

    int playerShields = this->player->getShieldStrenght();
    int enemyShields = this->enemy->getShieldStrenght();

    // get the damage for the enemy or the current player
    int shieldDamage = who ? (playerShields - damage) : (enemyShields - damage);

    // if the damage is greater than the shields left, set there shield strength to 0
    if(shieldDamage<=0)
    {
        if(who==true)
        {
            this->player->setShieldStrenght(0);
        }
        else
        {
            this->enemy->setShieldStrenghtPVE(0);
        }

        // the damage is greater the the shields left,
        // now starts decreasing the armour
        this->setArmour(who,damage);
        return;
    }

    cout << endl;

    // true player
    // set the players or enemys shield stright to the new value, indicate this to the user
    if(who==true)
    {
        this->player->setShieldStrenght(shieldDamage);
        cout << "                   '\033[34;1m" << this->enemy->getName() << "\033[0m' hit your shileds inflicting '\033[31;1m" << damage << "\033[0m' damage" << endl;
        cout << "                   '\033[34;1m" << this->player->getName() << "'s\033[0m' shields are down to '\033[31;1m" << this->player->getShieldStrenght() << "\033[0m'" << endl;
    }
    else
    {
        this->enemy->setShieldStrenghtPVE(shieldDamage);
        cout << "                   '\033[34;1m" << this->player->getName() << "\033[0m' hit '\033[34;1m" << this->enemy->getName() << "\033[0m' inflicting " << damage << " damage" << endl;
        cout << "                   '\033[34;1m" << this->enemy->getName() << "'s\033[0m' shields are down to '\033[31;1m" << this->enemy->getShieldStrenght() << "\033[0m'" << endl;
    }
}	


/**
* Updates the enemy or current players armour after an attacking action has occurred
*
* @param who true = player false = current enemy
* @param damage the damage to inflict on the player / enemy
*
* @return void
*
* @see Battle::setWreck
*
* @see StarShip::getArmour
* @see StarShip::setArmour
*
* @see PVEEntity::getRegenerativeAdaptivePlating
* @see PVEEntity::setArmourPVE
*
*/

void Battle::setArmour(bool who, int damage)
{
    int playerArmour = this->player->getArmour();
    int enemyArmour = this->enemy->getRegenerativeAdaptivePlating();

    // get the damage for the enemy or the current player
    int armourDamage = who ? (playerArmour - damage) : (enemyArmour - damage);

    // if the damage is greater than the players, enemies armour, they are destoryed
    if(armourDamage<=0)
    {
        this->setWreck(who);
        return;
    }

    cout << endl;

    // true player
    // update there player / enemies armour and indicate this to the user
    if(who==true)
    {
        this->player->setArmour(armourDamage);
        cout << "                   '\033[34;1m" << this->enemy->getName() << "\033[0m' hit your armour inflicting '\033[31;1m" << damage << "\033[0m' damage" << endl;
        cout << "                   '\033[34;1m" << this->player->getName() << "'s\033[0m' amour is down to '\033[31;1m" << this->player->getArmour() << "\033[0m'" << endl;
    }
    else
    {
        this->enemy->setArmourPVE(armourDamage);
        cout << "                   '\033[34;1m" << this->player->getName() << "\033[0m' hit '\033[34;1m" << this->enemy->getName() << "\033[0m' inflicting '\033[31;1m" << damage << "\033[0m' damage" << endl;
        cout << "                   '\033[34;1m" << this->enemy->getName() << "'s\033[0m' armour is down to '\033[31;1m" << this->enemy->getRegenerativeAdaptivePlating() << "\033[0m'" << endl;
    }
}	


/**
* Sets the enemy or the player as destroyed (wrecked)
* disabled an enemies tractor lock also, to avoid deadlock (player cant escape even though enemy has been destroyed)
*
* @param who true = player false = current enemy
*
* @return void
*
* @see StarShip::setWreck
*
* @see PVEEntity::setWreckPVE
* @see PVEEntity::setHasTractorLockPVE
*
*/

void Battle::setWreck(bool who)
{	
    cout << endl;
    // true player
    if(who==true)
    {
        this->player->setWreck();
        cout << "                   '\033[31;1m" << this->player->getName() << "\033[0m' has been destroyed " << endl << endl ;
    }
    else
    {
        this->enemy->setWreckPVE();
        this->enemy->setHasTractorLockPVE(false);
        cout << "                   '\033[31;1m" << this->enemy->getName() << "\033[0m' has been destroyed " << endl << endl;
    }
}	


/**
* enemy or the player fires phasers @ WHO
*
* @param who true = player false = current enemy
*
* @return void
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Phaser(bool who)
{
    if(this->enemy->getIsWreckPVE())
        return;

    this->describeAction(who, "fired phasers at ");
    this->setShielding(who, LASER_DAMAGE);
}	


/**
* enemy or the player fires phased ion cannon @ WHO
*
* @param who true = player false = current enemy
*
* @return void
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Phased(bool who)
{
    if(this->enemy->getIsWreckPVE())
        return;

    this->describeAction(who, "fired phased ion cannon at ");
    this->setShielding(who, PHASED_DAMAGE);
}	


/**
* enemy or the player fires pulse ion cannon @ WHO
*
* @param who true = player false = current enemy
*
* @return void
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Pulse(bool who)
{
    if(this->enemy->getIsWreckPVE())
        return;

    this->describeAction(who, "fired pulse cannon at ");
    this->setShielding(who, PULSE_DAMAGE);
}	


/**
* enemy or the player fires photons @ WHO
* if its the player updates his amount of photons left
*
* @param who true = player false = current enemy
*
* @return void
*
* @see StarShip::getPhotons
* @see StarShip::setPhotons
* @see StarShip::getName
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Photon(bool who)
{
    if(this->enemy->getIsWreckPVE())
        return;

    if(this->player->getPhotons() > 0)
    {
        this->describeAction(who, "launched photon torpedo at ");
        cout << "                   '\033[31;1m" << this->player->getName() << "\033[0m' has " << (this->player->getPhotons() - 1) << " photon torpedos left";
        this->player->setPhotons(this->player->getPhotons() - 1);
        this->setShielding(who, PHOTON_DAMAGE);
    }
    else
    {
        cout << "                   '\033[31;1m" << this->player->getName() << "\033[0m' has 0 photon torpedos left";
    }
}	


/**
* enemy or the player fires quantums @ WHO
* if its the player updates his amount of quantums left
*
* @param who true = player false = current enemy
*
* @return void
*
* @see StarShip::getQuantums
* @see StarShip::setQuantums
* @see StarShip::getName
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Quantum(bool who)
{
    if(this->enemy->getIsWreckPVE())
        return;

    if(this->player->getQuantums() > 0)
    {
        this->describeAction(who, "launched quantum torpedo at ");
        cout << "                   '\033[31;1m" << this->player->getName() << "\033[0m' has " << (this->player->getQuantums() - 1) << " quantum torpedos left";
        this->player->setQuantums(this->player->getQuantums() - 1);
        this->setShielding(who, QUANTUM_DAMAGE);
    }
    else
    {
        cout << "                   '\033[31;1m" << this->player->getName() << "\033[0m' has 0 quantum torpedos left";
    }
}	


/**
* enemy or the player fires Transphasic torps @ WHO
*
* @param who true = player false = current enemy
*
* @return void
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Transphasic(bool who)
{
    if(this->enemy->getIsWreckPVE())
        return;

    this->describeAction(who, "launched transphasic torpedo at ");
    this->setShielding(who, TRANSPHASIC_DAMAGE);
}	


/**
* enemy or the player fires chroniton torps @ WHO
*
* @param who true = player false = current enemy
*
* @return void
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Chroniton(bool who)
{
    if(this->enemy->getIsWreckPVE())
        return;

    this->describeAction(who, "launched chroniton torpedo at ");
    this->setShielding(who, CHRONITON_DAMAGE);
}	


/**
* enemy or the player fires gravimetric torps @ WHO
*
* @param who true = player false = current enemy
*
* @return void
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Gravimetric(bool who)
{
    if(this->enemy->getIsWreckPVE())
        return;

    this->describeAction(who, "launched gravimetric torpedo at ");
    this->setShielding(who, GRAVIMETRIC_DAMAGE);
}


/**
* enemy or the player fires spatial torps @ WHO
*
* @param who true = player false = current enemy
*
* @return void
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Spatial(bool who)
{
    if(this->enemy->getIsWreckPVE())
        return;

    this->describeAction(who, "launched spatial torpedo at ");
    this->setShielding(who, SPATIAL_DAMAGE);
}	


/**
* initiates a tractor on player or enemy
*
* @param who true = player false = current enemy
*
* @return void
*
* @see Battle::describeAction
* @see Battle::setShielding
*
* @see StarShip::setHasTractorLock
* @see StarShip::getHasTractorLock
*
* @see PVEEntity::setHasTractorLockPVE
* @see PVEEntity::getIsWreckPVE
*
*/

void Battle::Tractor(bool who, bool tractor)
{
    if(this->enemy->getIsWreckPVE())
        return;

    this->describeAction(who, "locked tractor beam on ");
    if(who==true)
    {
        this->player->setHasTractorLock(!this->player->getHasTractorLock());
    }
    else
    {
        this->enemy->setHasTractorLockPVE(tractor);
    }
}	


/**
* finds weather the enemy has a tractor on the player
*
* @return bool enemy has a tractor lock
*
* @see PVEEntity::getHasTractorLock
*
*/

bool Battle::enemyHasTractor()
{
    if(this->enemy->getHasTractorLock())
        return true;
    else
        return false;
}	


/**
* returns a pointer to the battles enemy
*
* @return PVEEntity* the enemy
*
*/

PVEEntity* Battle::getEnemy()
{
    return this->enemy;
}


/**
* returns the name of the current enemy
*
* @return string the enemies name
*
* @see PVEEntity::getName
*
*/

string Battle::getEnemyName()
{
    return this->enemy->getName();
}	


/**
* output the action of the attack event
*
* @param who true = player false = current enemy
* @param string string output
*
* @return void
*
* @see StarShip::getName
*
* @see PVEEntity::getName
*
*/

void Battle::describeAction(bool who, string action)
{
    string attacker = who ? this->enemy->getName() : this->player->getName();
    string victim = who ? this->player->getName() : this->enemy->getName();

    cout << endl;
    cout << "                   '\033[31;1m" << attacker << "\033[0m' has " << action << "'\033[31;1m" << victim << "\033[0m'" << endl;
}
