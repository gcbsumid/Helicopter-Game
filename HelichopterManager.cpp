#include <iostream>
#include <cstdlib>
#include <vector>
#include "HelichopterManager.h"
#include "Objects.h"
#include "HelichopterObj.h"
#include "MissileObj.h"
#include "XInfo.h"

using namespace std;

HelichopterManager::HelichopterManager(XInfo* xInfo)
{
    cout << "Creating Helichopter" << endl;
    Objects* obj = ObjectsFactory::CreateObjects(
        Objects::OBJECT_TYPE_HELICHOPTER, xInfo->width*0.20, xInfo->height *0.15, 30, 50);
    mHelichopter = (HelichopterObj*)obj; 
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