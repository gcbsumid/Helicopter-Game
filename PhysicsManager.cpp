#include <cstdlib>
#include <vector>
#include "PhysicsManager.h"
#include "Objects.h"
#include "HelichopterObj.h"
#include "WallObj.h"
#include "TargetObj.h"
#include "MissileObj.h"

using namespace std;

// Constructor
PhysicsManager::PhysicsManager(HelichopterObj* heli, std::vector<WallObj*>* walls, 
                    std::vector<TargetObj*>* targets, std::vector<MissileObj*>* heliMissiles,
                    std::vector<MissileObj*>* turretMissiles,  std::vector<PlaneObj*>* planes) : mGodMode(false)
{
    mHelichopter = heli;
    mWallObjs = walls;
    mTargetObjs = targets;
    mHeliMissileObjs = heliMissiles;
    mTurretMissileObjs = turretMissiles;
    mPlaneObjs = planes;
}

PhysicsManager::~PhysicsManager()
{

}

// TODO: update function
void PhysicsManager::Update()
{
    //cout << "Helichopter hit box:" << endl;
    //cout << "minX=" << mHelichopter->getHitBoxMinX() << " minY=" << mHelichopter->getHitBoxMinY() <<
    //    " maxX=" << mHelichopter->getHitBoxMaxX() << " maxY=" << mHelichopter->getHitBoxMaxY() << endl;

    vector<MissileObj *>::const_iterator mh_begin = mHeliMissileObjs->begin();
    vector<MissileObj *>::const_iterator mh_end = mHeliMissileObjs->end();

    vector<MissileObj *>::const_iterator mt_begin = mTurretMissileObjs->begin();
    vector<MissileObj *>::const_iterator mt_end = mTurretMissileObjs->end();

    vector<WallObj *>::const_iterator w_begin = mWallObjs->begin();
    vector<WallObj *>::const_iterator w_end = mWallObjs->end();
    while(w_begin != w_end)
    {
        // Check for helichopter against walls
        Objects *obj = (Objects*)*w_begin;

        if(!mGodMode && HasColided((Objects*)mHelichopter, obj))
        {
            mHelichopter->Destroy();
        }

        mh_begin = mHeliMissileObjs->begin();
        while(mh_begin != mh_end)
        {
            // Check each missile against the helichopter
            Objects *missileObj = (Objects*)*mh_begin;

            // Check each missile against walls
            if(HasColided(missileObj, obj))
            {
                missileObj->Destroy();
            }
            mh_begin++;
        }

        mt_begin = mTurretMissileObjs->begin();
        while(mt_begin != mt_end)
        {
            // Check each missile against the helichopter
            Objects *missileObj = (Objects*)*mt_begin;

            // Check each missile against walls
            if(HasColided(missileObj, obj))
            {
                missileObj->Destroy();
            }
            mt_begin++;
        }

        // Incrememnt the wall pointer
        w_begin++;
    }

    // Turret bullets   
    mt_begin = mTurretMissileObjs->begin();
    while(mt_begin != mt_end)
    {
        // Check for helichopter against walls
        Objects *obj = (Objects*)*mt_begin;

        if(!mGodMode && HasColided((Objects*)mHelichopter, obj))
        {
            mHelichopter->Destroy();
            obj->Destroy();
        }

        // Incrememnt the wall pointer
        mt_begin++;
    }

    // check helicopter against planes
    vector<PlaneObj *>::const_iterator p_begin = mPlaneObjs->begin();
    vector<PlaneObj *>::const_iterator p_end = mPlaneObjs->end();

    p_begin = mPlaneObjs->begin();
    while(p_begin != p_end)
    {
        // Check for helichopter against walls
        Objects *obj = (Objects*)*p_begin;

        if(!mGodMode && HasColided((Objects*)mHelichopter, obj))
        {
            mHelichopter->Destroy();
            obj->Destroy();
        }

        mh_begin = mHeliMissileObjs->begin();
        while(mh_begin != mh_end)
        {
            // Check each missile against the helichopter
            Objects *missileObj = (Objects*)*mh_begin;

            // Check each missile against walls
            if(HasColided(missileObj, obj))
            {
                obj->Destroy();
                missileObj->Destroy();
            }
            mh_begin++;
        }

        // Incrememnt the wall pointer
        p_begin++;
    }


    vector<TargetObj *>::const_iterator t_begin = mTargetObjs->begin();
    vector<TargetObj *>::const_iterator t_end = mTargetObjs->end();
    while(t_begin != t_end)
    {
        // Check for helichopter against targets
        Objects *obj = (Objects*)*t_begin;
        if(!mGodMode && HasColided((Objects*)mHelichopter, obj))
        {
            mHelichopter->Destroy();
        }

        // Check each missile against targets
        mh_begin = mHeliMissileObjs->begin();
        while(mh_begin != mh_end)
        {
            Objects *missileObj = (Objects*)*mh_begin;
            if(HasColided(missileObj, obj))
            {
                missileObj->Destroy();
                obj->Destroy();
            }
            mh_begin++;
        }

        t_begin++;
    }
}

// TODO: collision detection
bool PhysicsManager::HasColided(Objects* obj1, Objects* obj2)
{
    //cout << "Checking Collision." << endl;
    // Fix this for objects

    if (obj1->getHitBoxMaxX() < obj2->getHitBoxMinX() || 
        obj1->getHitBoxMaxY() < obj2->getHitBoxMinY() || 
        obj1->getHitBoxMinX() > obj2->getHitBoxMaxX() || 
        obj1->getHitBoxMinY() > obj2->getHitBoxMaxY()) 
    {
        return false;
    }

    // Debug Collisions
    // cout << "Did Collide." << endl;
    // cout << "Object 1:" << endl;
    // cout << "minX=" << obj1->getHitBoxMinX() << " minY=" << obj1->getHitBoxMinY() <<
    //         " maxX=" << obj1->getHitBoxMaxX() << " maxY=" << obj1->getHitBoxMaxY() << endl;


    // cout << "Object 2:" << endl;
    // cout << "minX=" << obj2->getHitBoxMinX() << " minY=" << obj2->getHitBoxMinY() <<
    //         " maxX=" << obj2->getHitBoxMaxX() << " maxY=" << obj2->getHitBoxMaxY() << endl;

    return true;
}

void PhysicsManager::GodMode()
{
    if(mGodMode)
    {
        mGodMode = false;
    }
    else 
    {
        mGodMode = true;
    }
}

bool PhysicsManager::IsInGodMode()
{
    return mGodMode;
}