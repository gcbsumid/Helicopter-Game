#ifndef PLANEMANAGER_H
#define PLANEMANAGER_H

#include <iostream>
#include <cstdlib>

#include "AIManager.h"
#include "Objects.h"
#include "HelichopterObj.h"
#include "WallObj.h"
#include "TargetObj.h"
#include "MissileObj.h"
#include "PlaneObj.h"


class PlaneManager: public AIManager 
{
public:
    PlaneManager(HelichopterObj* heli, std::vector<MissileObj*>* turretMissiles);
    ~PlaneManager();
    void Update(XInfo* xInfo, unsigned long timeframe, int gameSpeed);
    void Repaint(XInfo* xInfo);

    void CreatePlane();
    std::vector<PlaneObj*>* GetPlaneObjs();
    bool ShouldCreatePlane(unsigned long timeframe);
    void AIFire(XInfo* xInfo, unsigned long timeframe);
    bool DoesPlaneExist();
    int GetScore();
private:
    std::vector<PlaneObj*> mPlaneObjs;
    unsigned long mTimer;
    unsigned long mFireRate;
    int mScore;
};

#endif