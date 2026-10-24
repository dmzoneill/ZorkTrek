// Copyright (c) David O'Neill
// NOLINTBEGIN
// clang-format off
// jscpd:ignore-start
#ifndef BORGPROBE_H_  // NOLINT(build/header_guard)
#define BORGPROBE_H_

#include "PVEEntity.h"

class BorgProbe : public PVEEntity
{
    public:

        BorgProbe();
        ~BorgProbe();

        string getName();
        int getShieldStrenght();
        int getShieldRegenerativeRate();

        int getRegenerativeAdaptivePlating();
        bool getHasRegenerativeAdaptivePlating();

        int getTransPhasicTorpedos();
        bool getHasTransphasicTorpedos();
        int getChronitonTorpedos();
        bool getHasChronitonTorpedos();

        int getGravimetricTorpedos();
        bool getHasGravimetricTorpedos();
        int getSpatialTorpedos();
        bool getHasSpatialTorpedos();

        bool getHasLasers();
        bool getHasPhasedIonCannon();
        bool getHasPulseWeapon();

        int getBorgComplement();
        bool getHasTractorLock();
        bool getIsWreckPVE();

        void setShieldStrenghtPVE(int strenght); // codespell:ignore strenght
        void setShieldRegenerativeRatePVE(int rate);

        void setArmourPVE(int armour);

        void setTransPhasicTorpedosPVE(int num);
        void setChronitonTorpedosPVE(int num);
        void setGravimetricTorpedosPVE(int num);
        void setSpatialTorpedosPVE(int num);
        void setHasTractorLockPVE(bool has);

        void setWreckPVE();
};

#endif /*BORGPROBE_H_*/
// jscpd:ignore-end
// clang-format on
// NOLINTEND
