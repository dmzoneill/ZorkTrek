#include "BorgProbe.h"

/**
* Constructor for pve entity
* sets up data embers based on preloaded variables arrays usning random index
*/

BorgProbe::BorgProbe()
{
    // set up this instances data members

    this->type = "Borg probe";
    this->shieldStrenght = 250;
    this->shieldRegenerativeRate = 3;

    this->regenerativeAdaptivePlating = 0;
    this->hasRegenerativeAdaptivePlating = false;

    this->transPhasicTorpedos = 0;
    this->hasTransPhasicTorpedos = false;
    this->chronitonTorpedos = 5;
    this->hasTransPhasicTorpedos = true;
    this->gravimetricTorpedos = 20;
    this->hasGravimetricTorpedos = true;
    this->spatialTorpedos = 15;
    this->hasSpatialTorpedos = true;

    this->hasLasers = true;
    this->hasPhasedIonCannon = false;

    this->hasPulseWeapon = true;
    this->borgDrones = 42320;
    this->hasTractorLock = false;

    this->isWreck = false;
}


/**
* Destructor for the enemy
*
*/

BorgProbe::~BorgProbe()
{

    cout << "                      \033[32;2m~Deconstructing Borg Probe\033[0m " << endl;
}


/**
* mutator for the enemies shield strength
*
* @param strenght the value to set the data member
*
* @return void
*
*/

void BorgProbe::setShieldStrenghtPVE(int strenght)
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

void BorgProbe::setShieldRegenerativeRatePVE(int rate)
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

void BorgProbe::setArmourPVE(int armour)
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

void BorgProbe::setTransPhasicTorpedosPVE(int num)
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

void BorgProbe::setChronitonTorpedosPVE(int num)
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

void BorgProbe::setGravimetricTorpedosPVE(int num)
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

void BorgProbe::setSpatialTorpedosPVE(int num)
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

void BorgProbe::setHasTractorLockPVE(bool has)
{
    this->hasTractorLock = has;
}


/**
* mutator for the enemies wreck state
*
* @return void
*
*/

void BorgProbe::setWreckPVE()
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

string BorgProbe::getName()
{
    return this->type;
}


/**
* accessor for the enemies shield strength
*
* @return int the shield strength data member
*
*/

int BorgProbe::getShieldStrenght()
{
    return this->shieldStrenght;
}


/**
* accessor for the enemies shield regenerative rate
*
* @return int the shield regenerative rate data member
*
*/

int BorgProbe::getShieldRegenerativeRate()
{
    return this->shieldRegenerativeRate;
}


/**
* accessor for the enemies regenerative adaptive plating
*
* @return int the regenerative adaptive plating data member
*
*/

int BorgProbe::getRegenerativeAdaptivePlating()
{
    return this->regenerativeAdaptivePlating;
}


/**
* accessor for the enemies has regenerative adaptive plating
*
* @return bool the has regenerative adaptive plating data member
*
*/

bool BorgProbe::getHasRegenerativeAdaptivePlating()
{
    return this->hasRegenerativeAdaptivePlating;
}


/**
* accessor for the enemies has regenerative adaptive plating
*
* @return bool the has regenerative adaptive plating data member
*
*/

int BorgProbe::getTransPhasicTorpedos()
{
    return this->transPhasicTorpedos;
}


/**
* accessor for the enemies has transphasic torps
*
* @return bool the has transphasic torps data member
*
*/

bool BorgProbe::getHasTransphasicTorpedos()
{
    return this->hasTransPhasicTorpedos;
}


/**
* accessor for the enemies chroniton torps
*
* @return int the chroniton torps data member
*
*/

int BorgProbe::getChronitonTorpedos()
{
    return this->chronitonTorpedos;
}


/**
* accessor for the enemies has chroniton torps
*
* @return bool the has chroniton torps data member
*
*/

bool BorgProbe::getHasChronitonTorpedos()
{
    return this->hasChronitonTorpedos;
}


/**
* accessor for the enemies gravimetric torps
*
* @return int the chroniton torps data member
*
*/

int BorgProbe::getGravimetricTorpedos()
{
    return this->gravimetricTorpedos;
}


/**
* accessor for the enemies has gravimetric torps
*
* @return bool the has chroniton torps data member
*
*/

bool BorgProbe::getHasGravimetricTorpedos()
{
    return this->hasGravimetricTorpedos;
}


/**
* accessor for the enemies spatial torps
*
* @return int the spatial torps data member
*
*/

int BorgProbe::getSpatialTorpedos()
{
    return this->spatialTorpedos;
}


/**
* accessor for the enemies has spatial torps
*
* @return bool the has spatial torps data member
*
*/

bool BorgProbe::getHasSpatialTorpedos()
{
    return this->hasSpatialTorpedos;
}


/**
* accessor for the enemies has lasers
*
* @return bool the has lasers data member
*
*/

bool BorgProbe::getHasLasers()
{
    return this->hasLasers;
}


/**
* accessor for the enemies has phased ion cannon
*
* @return bool the has phased ion cannon data member
*
*/

bool BorgProbe::getHasPhasedIonCannon()
{
    return this->hasPhasedIonCannon;
}


/**
* accessor for the enemies has pulse weapons
*
* @return bool the has pulse weapons data member
*
*/

bool BorgProbe::getHasPulseWeapon()
{
    return this->hasPulseWeapon;
}


/**
* accessor for the enemies borg complement
*
* @return int the borg complement data member
*
*/

int BorgProbe::getBorgComplement()
{
    return this->borgDrones;
}


/**
* accessor for the enemies tractor lock
*
* @return bool the tractor lock data member
*
*/

bool BorgProbe::getHasTractorLock()
{
    return this->hasTractorLock;
}


/**
* accessor for the enemies wreck status
*
* @return bool the wreck status data member
*
*/

bool BorgProbe::getIsWreckPVE()
{
    return this->isWreck;
}

