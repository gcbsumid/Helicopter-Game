#include <iostream>
#include <cstdlib>
#include <vector>
#include <cmath>
#include "HelichopterManager.h"
#include "Objects.h"
#include "HelichopterObj.h"
#include "MissileObj.h"
#include "XInfo.h"

using namespace std;

static float ExplosionDirection[] = {
    cos(0)*15,          sin(0)*15,
    cos(M_PI/4)*15,     sin(M_PI/4)*15,
    cos(M_PI/2)*15,     sin(M_PI/2)*15,
    cos(3*M_PI/4)*15,   sin(3*M_PI/4)*15,
    cos(M_PI)*15,       sin(M_PI)*15,
    cos(5*M_PI/4)*15,   sin(5*M_PI/4)*15,
    cos(3*M_PI/2)*15,   sin(3*M_PI/2)*15,
    cos(7*M_PI/4)*15,   sin(7*M_PI/4)*15
};

HelichopterManager::HelichopterManager(XInfo* xInfo)
{
    cout << "Creating Helichopter" << endl;
    Objects* obj = ObjectsFactory::CreateObjects(
        Objects::OBJECT_TYPE_HELICHOPTER, xInfo->width*0.20, xInfo->height *0.15, 30, 50);
    mHelichopter = (HelichopterObj*)obj; 
    mExplosiveCount = 0;
}

HelichopterManager::~HelichopterManager()
{
    while(!mHeliMissileObjs.empty()) {
        mHeliMissileObjs.pop_back();
    }
    while(!mTurretMissileObjs.empty()) {
        mTurretMissileObjs.pop_back();
    }
    delete mHelichopter;
}

void HelichopterManager::Update(XInfo* xInfo, int gameSpeed)
{

    if(mHelichopter->DoesNeedUpdate())
    {
        mHelichopter->Update(xInfo->width, xInfo->height);
    }

    // Update the Missiles
    vector<MissileObj *>::const_iterator mh_begin = mHeliMissileObjs.begin();
    vector<MissileObj *>::const_iterator mh_end = mHeliMissileObjs.end();
    int counter = 0;
    while(mh_begin != mh_end) 
    {
        MissileObj* obj = *mh_begin;
        if(obj->DoesNeedUpdate())
        {
            obj->Update(xInfo->width, xInfo->height, gameSpeed);
        }
        if(obj->IsToBeDestroyed() || 
            !obj->IsOnScreen(xInfo->width, xInfo->height))
        {
            mHeliMissileObjs.erase(mHeliMissileObjs.begin()+counter);
            
            // Update m_end
            mh_end = mHeliMissileObjs.end();
            mh_begin--;
            counter--;
        }
        mh_begin++;
        counter++;
    }

    vector<MissileObj *>::const_iterator mt_begin = mTurretMissileObjs.begin();
    vector<MissileObj *>::const_iterator mt_end = mTurretMissileObjs.end();
    counter = 0;
    while(mt_begin != mt_end) 
    {
        MissileObj* obj = *mt_begin;
        if(obj->DoesNeedUpdate())
        {
            obj->Update(xInfo->width, xInfo->height, gameSpeed);
        }
        if(obj->IsToBeDestroyed() || 
            !obj->IsOnScreen(xInfo->width, xInfo->height))
        {
            mTurretMissileObjs.erase(mTurretMissileObjs.begin()+counter);
            
            // Update m_end
            mt_end = mTurretMissileObjs.end();
            mt_begin--;
            counter--;
        }
        mt_begin++;
        counter++;
    }
    // Update Explosive Objects
    vector<ExplosiveObj *>::const_iterator e_begin = mExplosiveObjs.begin();
    vector<ExplosiveObj *>::const_iterator e_end = mExplosiveObjs.end();
    counter = 0;
    while(e_begin != e_end) 
    {
        ExplosiveObj* obj = *e_begin;
        if(obj->DoesNeedUpdate())
        {
            obj->Update(xInfo->width, xInfo->height, gameSpeed);
        }
        if(obj->IsToBeDestroyed() || 
            !obj->IsOnScreen(xInfo->width, xInfo->height))
        {
            mExplosiveObjs.erase(mExplosiveObjs.begin()+counter);
            // Update m_end
            e_end = mExplosiveObjs.end();
            e_begin--;
            counter--;
        }
        e_begin++;
        counter++;
    }

}

void HelichopterManager::UpdateHeli(XInfo* xInfo)
{
}

void HelichopterManager::Repaint(XInfo* xInfo)
{
    if(mHelichopter->IsOnScreen(xInfo->width, xInfo->height))
    {
        mHelichopter->DrawObj(xInfo);
    }

    vector<MissileObj *>::const_iterator mh_begin = mHeliMissileObjs.begin();
    vector<MissileObj *>::const_iterator mh_end = mHeliMissileObjs.end();

    while(mh_begin != mh_end)
    {
        Objects *o = *mh_begin;
        if(o->IsOnScreen(xInfo->width, xInfo->height))
        {
            o->DrawObj(xInfo);
        }
        mh_begin++;
    }

    vector<MissileObj *>::const_iterator mt_begin = mTurretMissileObjs.begin();
    vector<MissileObj *>::const_iterator mt_end = mTurretMissileObjs.end();

    while(mt_begin != mt_end)
    {
        Objects *o = *mt_begin;
        if(o->IsOnScreen(xInfo->width, xInfo->height))
        {
            o->DrawObj(xInfo);
        }
        mt_begin++;
    }

    vector<ExplosiveObj *>::const_iterator e_begin = mExplosiveObjs.begin();
    vector<ExplosiveObj *>::const_iterator e_end = mExplosiveObjs.end();

    while(e_begin != e_end)
    {
        Objects *o = *e_begin;
        if(o->IsOnScreen(xInfo->width, xInfo->height))
        {
            o->DrawObj(xInfo);
        }
        e_begin++;
    }
}

HelichopterObj* HelichopterManager::GetHelichopter()
{
    return mHelichopter;
}

std::vector<MissileObj*>* HelichopterManager::GetHeliMissileObjs()
{
    return &mHeliMissileObjs;
}

std::vector<MissileObj*>* HelichopterManager::GetTurretMissileObjs()
{
    return &mTurretMissileObjs;
}

std::vector<ExplosiveObj*>* HelichopterManager::GetExplosiveObjs()
{
    return &mExplosiveObjs;
}


void HelichopterManager::HandleFireMissiles(bool isBomb)
{
    Objects* obj = ObjectsFactory::CreateObjects(
        Objects::OBJECT_TYPE_MISSILE, 
        mHelichopter->getPosX()+(mHelichopter->getWidth()/2), 
        mHelichopter->getPosY()+mHelichopter->getHeight()+3, 
        10, 
        10);
    MissileObj* missileObj = (MissileObj*)obj;
    if(isBomb)
    {
        missileObj->UpdateVelocity(mHelichopter->getVelX(), 0, isBomb);
    }
    else
    {
        missileObj->UpdateVelocity(10, 0, isBomb);
    }
    mHeliMissileObjs.push_back(missileObj);
}

bool HelichopterManager::IsHelichopterDestroyed()
{
    if(mHelichopter->IsToBeDestroyed())
    {
        return true;
    }
    return false;
}

void HelichopterManager::AddAcceleration(int x, int y)
{
    mHelichopter->AddAcceleration(x, y);
    cout << "Adding acceleration x: " << x << " and y: " << y << endl;
}

bool HelichopterManager::ShouldHeliMove(int screenWidth, int screenHeight)
{
    return mHelichopter->ShouldHeliMove(screenWidth, screenHeight);
}

void HelichopterManager::ResetXAcceleration()
{
    mHelichopter->ResetXAcceleration();
}

void HelichopterManager::ResetYAcceleration()
{
    mHelichopter->ResetYAcceleration();
}

void HelichopterManager::HandleExplosion()
{
    if(mExplosiveObjs.empty())
    {
        mExplosiveCount = 0;
        Objects* obj = ObjectsFactory::CreateObjects(
            Objects::OBJECT_TYPE_EXPLOSION, 
            mHelichopter->getPosX()+(mHelichopter->getWidth()/2), 
            mHelichopter->getPosY()+mHelichopter->getHeight()+3, 
            10, 
            10);
        ExplosiveObj* explosiveObj = (ExplosiveObj*)obj;
        explosiveObj->UpdateVelocity(10, 0);
        mExplosiveObjs.push_back(explosiveObj);
    }
    else
    {
        if(mExplosiveCount < 3)
        {
            int explosiveNum = mExplosiveObjs.size();
            for(int explosiveCounter = 0; explosiveCounter < explosiveNum; explosiveCounter++)
            {
                ExplosiveObj* o = mExplosiveObjs.at(explosiveCounter);

                for(int i = 0; i < 8; i++)
                {
                    Objects* obj = ObjectsFactory::CreateObjects(
                        Objects::OBJECT_TYPE_EXPLOSION, 
                        o->getPosX(), 
                        o->getPosY(), 
                        10, 
                        10);
                    ExplosiveObj* explosiveObj = (ExplosiveObj*)obj;
                    explosiveObj->UpdateVelocity(ExplosionDirection[i*2], ExplosionDirection[i*2+1]);
                    mExplosiveObjs.push_back(explosiveObj);
                }
                o->Destroy();
            }
            mExplosiveCount++;
        }
    }
}