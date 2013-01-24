#include <cstdlib>
#include <vector>
#include "AIManager.h"
#include "Objects.h"
#include "HelichopterObj.h"
#include "WallObj.h"
#include "TargetObj.h"
#include "MissileObj.h"
#include <sys/time.h>
#include <math.h>

using namespace std;


// unsigned long now() {
//     timeval tv;
//     gettimeofday(&tv, NULL);
//     return tv.tv_sec * 1000000 + tv.tv_usec;
// }

// Default Constructor
AIManager::AIManager()
{

}

// Constructor
AIManager::AIManager(HelichopterObj* heli, std::vector<WallObj*>* walls, 
                    std::vector<TargetObj*>* targets, std::vector<MissileObj*>* heliMissiles,
                    std::vector<MissileObj*>* turretMissiles)
{
    mHelichopter = heli;
    mWallObjs = walls;
    mTargetObjs = targets;
    mHeliMissileObjs = heliMissiles;
    mTurretMissileObjs = turretMissiles;
}

AIManager::~AIManager()
{

}

void AIManager::AIFire(XInfo* xInfo, unsigned long timeframe)
{
    vector<TargetObj *>::const_iterator t_begin = mTargetObjs->begin();
    vector<TargetObj *>::const_iterator t_end = mTargetObjs->end();

    while(t_begin != t_end)
    {
        TargetObj *o = *t_begin;
        if(o->IsOnScreen(xInfo->width, xInfo->height) && o->ShouldFire(timeframe) && CanFire((Objects*)o, 600))
        {
            pt velocity = CalculateVelocity((Objects*)o);
            FireInTheHole((Objects*)o, velocity.x, velocity.y, true);
        }
        t_begin++;
    }
}

bool AIManager::CanFire(Objects* o, int maxDistance)
{
    int height = mHelichopter->getPosY() - o->getPosY(); 
    int width = mHelichopter->getPosX() - o->getPosX();

    int distance = sqrt(height*height + width*width);
    if(distance < maxDistance)
    {
        return true;
    }
    return false;
}

pt AIManager::CalculateVelocity(Objects* o)
{
    pt velocity;

    float height = (float)mHelichopter->getPosY() - (float)o->getPosY(); 
    float width = (float)mHelichopter->getPosX() - (float)o->getPosX();

    float distance = sqrt(height*height + width*width);

    velocity.x = width/distance * 10;
    velocity.y = height/distance * 10;

    return velocity;
}

void AIManager::FireInTheHole(Objects* o, float x, float y, bool fromTurret)
{
    int xpos = 0, ypos = 0;
    if(fromTurret)
    {
        xpos = o->getPosX() + (o->getWidth()/2) - 5;
        ypos = o->getPosY() - (o->getHeight()/2) + 3;
    }
    else
    {
        xpos = o->getPosX() - (o->getWidth()/2) + 5;
        ypos = o->getPosY() + (o->getHeight()/2) - 3;
    }
    Objects* obj = ObjectsFactory::CreateObjects(
        Objects::OBJECT_TYPE_MISSILE, 
        xpos, 
        ypos, 
        10, 
        10);
    MissileObj* missileObj = (MissileObj*)obj;
    missileObj->UpdateVelocity((int)x, (int)y, true);
    missileObj->SetTurretMissile();
    mTurretMissileObjs->push_back(missileObj);
}