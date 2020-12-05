#ifndef PVEENTITY_H_
#define PVEENTITY_H_

#include "ZorkTrekLib.h"
#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::string;
using std::endl;

class PVEEntity 
{
    protected:

        string type; // name

        int regenerativeAdaptivePlating;
        bool hasRegenerativeAdaptivePlating;

        int shieldStrenght;
        int shieldRegenerativeRate;

        int transPhasicTorpedos;
        bool hasTransPhasicTorpedos;
        int chronitonTorpedos;
        bool hasChronitonTorpedos;
        int gravimetricTorpedos;
        bool hasGravimetricTorpedos;
        int spatialTorpedos;
        bool hasSpatialTorpedos;

        bool hasLasers;
        bool hasPhasedIonCannon;
        bool hasPulseWeapon;

        int borgDrones;

        bool hasTractorLock;
        bool isWreck;

    public:

        PVEEntity();
        virtual ~PVEEntity();

        /* pure virtual functions should be over ridden in the derived class */

        virtual string getName() = 0;
        virtual int getShieldStrenght() = 0;
        virtual int getShieldRegenerativeRate() = 0;

        virtual int getRegenerativeAdaptivePlating() = 0;
        virtual bool getHasRegenerativeAdaptivePlating() = 0;

        virtual int getTransPhasicTorpedos() = 0;
        virtual bool getHasTransphasicTorpedos() = 0;
        virtual int getChronitonTorpedos() = 0;
        virtual bool getHasChronitonTorpedos() = 0;

        virtual int getGravimetricTorpedos() = 0;
        virtual bool getHasGravimetricTorpedos() = 0;
        virtual int getSpatialTorpedos() = 0;
        virtual bool getHasSpatialTorpedos() = 0;

        virtual bool getHasLasers() = 0;
        virtual bool getHasPhasedIonCannon() = 0;
        virtual bool getHasPulseWeapon() = 0;

        virtual int getBorgComplement() = 0;
        virtual bool getHasTractorLock() = 0;
        virtual bool getIsWreckPVE() = 0;

        virtual void setShieldStrenghtPVE(int strenght) = 0;
        virtual void setShieldRegenerativeRatePVE(int rate) = 0;

        virtual void setArmourPVE(int armour) = 0;

        virtual void setTransPhasicTorpedosPVE(int num) = 0;
        virtual void setChronitonTorpedosPVE(int num) = 0;
        virtual void setGravimetricTorpedosPVE(int num) = 0;
        virtual void setSpatialTorpedosPVE(int num) = 0;
        virtual void setHasTractorLockPVE(bool has) = 0;

        virtual void setWreckPVE() = 0;

};

#endif /*PVEENTITY_H_*/
