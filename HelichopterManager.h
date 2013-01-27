#ifndef HELICHOPTERMANAGER_H
#define HELICHOPTERMANAGER_H

#include <iostream>
#include <cstdlib>
#include <vector>

#include "Objects.h"
#include "HelichopterObj.h"
#include "MissileObj.h"
#include "ExplosiveObj.h"
#include "XInfo.h"

class HelichopterManager
{
public:
    HelichopterManager(XInfo* xInfo);
    ~HelichopterManager();

    void Update(XInfo* xInfo, int gameSpeed);
    void Repaint(XInfo* xInfo);

    HelichopterObj* GetHelichopter();
    std::vector<MissileObj*>* GetHeliMissileObjs();
    std::vector<MissileObj*>* GetTurretMissileObjs();
    std::vector<ExplosiveObj*>* GetExplosiveObjs();

    void HandleFireMissiles(bool isBomb);
    bool IsHelichopterDestroyed();
    void AddAcceleration(int x, int y);
    bool ShouldHeliMove(int screenWidth, int screenHeight);
    void UpdateHeli(XInfo* xInfo);
    void ResetXAcceleration();
    void ResetYAcceleration();
    void HandleExplosion();
private:
    HelichopterObj* mHelichopter;
    std::vector<MissileObj*> mHeliMissileObjs;
    std::vector<MissileObj*> mTurretMissileObjs;
    std::vector<ExplosiveObj*> mExplosiveObjs;
    int mExplosiveCount;
};

#endif