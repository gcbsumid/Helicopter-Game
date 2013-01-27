/***************************************************
/ PhysicsManager.h                                  /
/ Description:                                      /
/   Contains all the physics involved in the game.  /
 ***************************************************/
#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <iostream>
#include <cstdlib>

#include "Objects.h"
#include "HelichopterObj.h"
#include "WallObj.h"
#include "TargetObj.h"
#include "MissileObj.h"
#include "PlaneObj.h"
#include "ExplosiveObj.h"

class PhysicsManager {
public:

    PhysicsManager(HelichopterObj* heli, std::vector<WallObj*>* walls, 
                    std::vector<TargetObj*>* targets, std::vector<MissileObj*>* heliMissiles,
                    std::vector<MissileObj*>* turretMissiles, std::vector<PlaneObj*>* planes,
                    std::vector<ExplosiveObj*>* explosion);
    ~PhysicsManager();

    // or private, I'm not sure yet.
    void Update();

    bool HasColided(Objects* obj1, Objects* obj2);
    void GodMode();
    bool IsInGodMode();

private:
    HelichopterObj* mHelichopter;
    std::vector<WallObj*>* mWallObjs;
    std::vector<TargetObj*>* mTargetObjs;
    std::vector<MissileObj*>* mHeliMissileObjs;
    std::vector<MissileObj*>* mTurretMissileObjs;
    std::vector<PlaneObj*>* mPlaneObjs;
    std::vector<ExplosiveObj*>* mExplosiveObjs;

    bool mGodMode;

};

// TODO:
// Create a collision detection

#endif 