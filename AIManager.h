#ifndef AIMANAGER_H
#define AIMANAGER_H

#include <iostream>
#include <cstdlib>

#include "Objects.h"
#include "HelichopterObj.h"
#include "WallObj.h"
#include "TargetObj.h"
#include "MissileObj.h"
#include "XInfo.h"
#include "pt.h"

class AIManager 
{
public:
    AIManager();
    AIManager(HelichopterObj* heli, std::vector<WallObj*>* walls, 
                    std::vector<TargetObj*>* targets, std::vector<MissileObj*>* heliMissiles,
                    std::vector<MissileObj*>* turretMissiles);
    ~AIManager();

    virtual void AIFire(XInfo* xInfo, unsigned long timeframe);
    bool CanFire(Objects* o, int maxDistance);
    pt CalculateVelocity(Objects* o);
    void FireInTheHole(Objects* o, float x, float y, bool fromTurret);

protected:
    HelichopterObj* mHelichopter;
    std::vector<MissileObj*>* mTurretMissileObjs;

private:
    std::vector<WallObj*>* mWallObjs;
    std::vector<TargetObj*>* mTargetObjs;
    std::vector<MissileObj*>* mHeliMissileObjs;
};

#endif