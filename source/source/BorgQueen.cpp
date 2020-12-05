#include "BorgQueen.h"


/**
* Constructor for pve entity
* sets up data embers based on preloaded variables arrays usning random index
*/

BorgQueen::BorgQueen()
{
    // set up this instances data members

    this->type = "Borg Queen";
    this->shieldStrenght = 400;
    this->shieldRegenerativeRate = 6;

    this->regenerativeAdaptivePlating = 200;
    this->hasRegenerativeAdaptivePlating = true;

    this->transPhasicTorpedos = 30;
    this->hasTransPhasicTorpedos = true;
    this->chronitonTorpedos = 5;
    this->hasTransPhasicTorpedos = true;
    this->gravimetricTorpedos = 20;
    this->hasGravimetricTorpedos = true;
    this->spatialTorpedos = 15;
    this->hasSpatialTorpedos = true;

    this->hasLasers = true;
    this->hasPhasedIonCannon = true;

    this->hasPulseWeapon = true;
    this->borgDrones = 23320;
    this->hasTractorLock = false;

    this->isWreck = false;
}


/**
* Destructor for the enemy
*
*/

BorgQueen::~BorgQueen()
{

    cout << "                      \033[32;2m~Deconstructing Borg Queen\033[0m " << endl;
}


/**
* mutator for the enemies shield strength
*
* @param strenght the value to set the data member
*
* @return void
*
*/

void BorgQueen::setShieldStrenghtPVE(int strenght)
{
    this->shieldStrenght = strenght;
}


/**
* mutator for the enemies regenerative rate
*
* @param rate the value to set the data member
*
* @return void
*
*/

void BorgQueen::setShieldRegenerativeRatePVE(int rate)
{
    this->shieldRegenerativeRate = rate;
}


/**
* mutator for the enemies armour
*
* @param armour the value to set the data member
*
* @return void
*
*/

void BorgQueen::setArmourPVE(int armour)
{
    this->regenerativeAdaptivePlating = armour;
}


/**
* mutator for the enemies trans phasic torps
*
* @param num the value to set the data member
*
* @return void
*
*/

void BorgQueen::setTransPhasicTorpedosPVE(int num)
{
    this->transPhasicTorpedos = num;
}


/**
* mutator for the enemies chroniton torps
*
* @param num the value to set the data member
*
* @return void
*
*/

void BorgQueen::setChronitonTorpedosPVE(int num)
{
    this->chronitonTorpedos = num;
}


/**
* mutator for the enemies gravimetric torps
*
* @param num the value to set the data member
*
* @return void
*
*/

void BorgQueen::setGravimetricTorpedosPVE(int num)
{
    this->gravimetricTorpedos = num;
}


/**
* mutator for the enemies spatial torps
*
* @param num the value to set the data member
*
* @return void
*
*/

void BorgQueen::setSpatialTorpedosPVE(int num)
{
    this->spatialTorpedos = num;
}


/**
* mutator for the enemies tractor beam
*
* @param has the bool value to set the data member
*
* @return void
*
*/

void BorgQueen::setHasTractorLockPVE(bool has)
{
    this->hasTractorLock = has;
}


/**
* mutator for the enemies wreck state
*
* @return void
*
*/

void BorgQueen::setWreckPVE()
{
    this->borgDrones = 0;
    this->shieldStrenght = 0;
    this->shieldRegenerativeRate = 0;
    this->isWreck = true;
}


/**
* accessor for the enemies name
*
* @return string the enemies name
*
*/

string BorgQueen::getName()
{
    return this->type;
}


/**
* accessor for the enemies shield strength
*
* @return int the shield strength data member
*
*/

int BorgQueen::getShieldStrenght()
{
    return this->shieldStrenght;
}


/**
* accessor for the enemies shield regenerative rate
*
* @return int the shield regenerative rate data member
*
*/

int BorgQueen::getShieldRegenerativeRate()
{
    return this->shieldRegenerativeRate;
}


/**
* accessor for the enemies regenerative adaptive plating
*
* @return int the regenerative adaptive plating data member
*
*/

int BorgQueen::getRegenerativeAdaptivePlating()
{
    return this->regenerativeAdaptivePlating;
}


/**
* accessor for the enemies has regenerative adaptive plating
*
* @return bool the has regenerative adaptive plating data member
*
*/

bool BorgQueen::getHasRegenerativeAdaptivePlating()
{
    return this->hasRegenerativeAdaptivePlating;
}


/**
* accessor for the enemies has regenerative adaptive plating
*
* @return bool the has regenerative adaptive plating data member
*
*/

int BorgQueen::getTransPhasicTorpedos()
{
    return this->transPhasicTorpedos;
}


/**
* accessor for the enemies has transphasic torps
*
* @return bool the has transphasic torps data member
*
*/

bool BorgQueen::getHasTransphasicTorpedos()
{
    return this->hasTransPhasicTorpedos;
}


/**
* accessor for the enemies chroniton torps
*
* @return int the chroniton torps data member
*
*/

int BorgQueen::getChronitonTorpedos()
{
    return this->chronitonTorpedos;
}


/**
* accessor for the enemies has chroniton torps
*
* @return bool the has chroniton torps data member
*
*/

bool BorgQueen::getHasChronitonTorpedos()
{
    return this->hasChronitonTorpedos;
}


/**
* accessor for the enemies gravimetric torps
*
* @return int the chroniton torps data member
*
*/

int BorgQueen::getGravimetricTorpedos()
{
    return this->gravimetricTorpedos;
}


/**
* accessor for the enemies has gravimetric torps
*
* @return bool the has chroniton torps data member
*
*/

bool BorgQueen::getHasGravimetricTorpedos()
{
    return this->hasGravimetricTorpedos;
}


/**
* accessor for the enemies spatial torps
*
* @return int the spatial torps data member
*
*/

int BorgQueen::getSpatialTorpedos()
{
    return this->spatialTorpedos;
}


/**
* accessor for the enemies has spatial torps
*
* @return bool the has spatial torps data member
*
*/

bool BorgQueen::getHasSpatialTorpedos()
{
    return this->hasSpatialTorpedos;
}


/**
* accessor for the enemies has lasers
*
* @return bool the has lasers data member
*
*/

bool BorgQueen::getHasLasers()
{
    return this->hasLasers;
}


/**
* accessor for the enemies has phased ion cannon
*
* @return bool the has phased ion cannon data member
*
*/

bool BorgQueen::getHasPhasedIonCannon()
{
    return this->hasPhasedIonCannon;
}


/**
* accessor for the enemies has pulse weapons
*
* @return bool the has pulse weapons data member
*
*/

bool BorgQueen::getHasPulseWeapon()
{
    return this->hasPulseWeapon;
}


/**
* accessor for the enemies borg complement
*
* @return int the borg complement data member
*
*/

int BorgQueen::getBorgComplement()
{
    return this->borgDrones;
}


/**
* accessor for the enemies tractor lock
*
* @return bool the tractor lock data member
*
*/

bool BorgQueen::getHasTractorLock()
{
    return this->hasTractorLock;
}


/**
* accessor for the enemies wreck status
*
* @return bool the wreck status data member
*
*/

bool BorgQueen::getIsWreckPVE()
{
    return this->isWreck;
}
