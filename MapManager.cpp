#include <iostream>
#include <cstdlib>
#include <vector>
#include <math.h>
#include <time.h>
#include "MapManager.h"
#include "Objects.h"
#include "WallObj.h"
#include "TargetObj.h"

using namespace std;

MapManager::MapManager(XInfo* xInfo) : mMapCounter(0), 
    mWallHeight(0), mScore(0), mWallGenHeight(50),
    mWallGenWidth(50), mTargetGenHeight(30), 
    mTargetGenWidth(30)
{
    srand(time(0));
    cout << "Creating Walls and Targets" << endl;
    while(mMapCounter < xInfo->width)
    {
        GenerateWall(xInfo);
        mMapCounter += mWallGenWidth;
    }
}

MapManager::~MapManager()
{
    while(!mWallObjs.empty())
    {
        mWallObjs.pop_back();
    }

    while(!mTargetObjs.empty())
    {
        mTargetObjs.pop_back();
    }
}

void MapManager::Update(XInfo* xInfo)
{
    // Update the Targets
    vector<TargetObj *>::const_iterator t_begin = mTargetObjs.begin();
    vector<TargetObj *>::const_iterator t_end = mTargetObjs.end();
    int counter = 0;
    while(t_begin != t_end) 
    {
        TargetObj *obj = *t_begin;
        if(obj->IsToBeDestroyed() || obj->getHitBoxMaxX() < 0)
        {
            // cout << "Erasing ";
            // obj->DisplayID();
            mTargetObjs.erase(mTargetObjs.begin()+counter);
            t_end = mTargetObjs.end();
            t_begin--;
            if(obj->IsToBeDestroyed())
            {
                mScore++;
            }
            counter--;
        }
        t_begin++;
        counter++;
    }
}

void MapManager::UpdateMap(XInfo* xInfo, int velX)
{
    // Update the Map
    mMapCounter -= velX; // += velX;

    if(mMapCounter < xInfo->width)
    {
        if(mTargetObjs.empty() || mWallObjs.back()->getHitBoxMaxX() > 
            mTargetObjs.back()->getHitBoxMaxX())
        {
            mMapCounter = mWallObjs.back()->getHitBoxMaxX();
        }
        else 
        {
            mMapCounter = mWallObjs.back()->getHitBoxMaxX() + 10;
        }

        if(mWallHeight == 0)
        {
            mMapCounter += mWallGenWidth;
        }
        GenerateWall(xInfo);
        mMapCounter+=mWallGenWidth;
    }

    vector<WallObj *>::const_iterator w_begin = mWallObjs.begin();
    vector<WallObj *>::const_iterator w_end = mWallObjs.end();
    while(w_begin != w_end) 
    {
        WallObj *obj = *w_begin;
        obj->Update(xInfo->width, xInfo->height, velX);

        w_begin++;
    }

    vector<TargetObj *>::const_iterator t_begin = mTargetObjs.begin();
    vector<TargetObj *>::const_iterator t_end = mTargetObjs.end();
    while(t_begin != t_end) 
    {
        TargetObj *obj = *t_begin;
            // cout << "Updating: ";
            // obj->DisplayID();
        obj->Update(xInfo->width, xInfo->height, velX);

        t_begin++;
    }

}

void MapManager::Repaint(XInfo* xInfo)
{
    vector<TargetObj *>::const_iterator t_begin = mTargetObjs.begin();
    vector<TargetObj *>::const_iterator t_end = mTargetObjs.end();

    while(t_begin != t_end)
    {
        Objects *o = *t_begin;
        if(o->IsOnScreen(xInfo->width, xInfo->height))
        {
            o->DrawObj(xInfo);
        }
        t_begin++;
    }

    vector<WallObj *>::const_iterator w_begin = mWallObjs.begin();
    vector<WallObj *>::const_iterator w_end = mWallObjs.end();

    while(w_begin != w_end)
    {
        Objects *o = *w_begin;
        if(o->IsOnScreen(xInfo->width, xInfo->height))
        {
            o->DrawObj(xInfo);
        }
        w_begin++;
    }
}

std::vector<WallObj*>* MapManager::GetWallObjVector()
{
    return &mWallObjs;
}

std::vector<TargetObj*>* MapManager::GetTargetObjVector()
{
    return &mTargetObjs;
}

void MapManager::GenerateWall(XInfo* xInfo)
{
    //cout << "Creating Wall " << i << " with x = " << xInfo.width - wallPoints[i*2] << " and y = " << xInfo.height - wallPoints[i*2+1] << endl;
    int randNum = rand() % 10 + 1;
    int randTarget = rand() % 10 + 1;
    if(mWallHeight <= 1)
    {
        if(randNum > 3)
        {
            mWallHeight++;
        }
    }
    else if(mWallHeight >= 5)
    {
        if(randNum >= 3)
        {
            mWallHeight--;
        }
        else 
        {
            mWallHeight++;
        }
    }
    else 
    {
        if(randNum == 1)
        {
            mWallHeight -= 2;
        }
        else if(randNum < 4)
        {
            mWallHeight--;
        }
        else if(randNum > 6)
        {
            mWallHeight++;
        }
        else if(randNum == 10)
        {
            mWallHeight += 2;
        }
    }

    for(int i = 0; i < mWallHeight; i++)
    {
        Objects* obj = ObjectsFactory::CreateObjects(
            Objects::OBJECT_TYPE_WALL, 
            mMapCounter, 
            xInfo->height - (mWallGenHeight*(i+1)), 
            mWallGenHeight, 
            mWallGenWidth);
        mWallObjs.push_back((WallObj*)obj);
        ((WallObj*)obj)->SetHeightFromGround(i+1);
    }

    if(randTarget > 7)
    {
        Objects* obj = ObjectsFactory::CreateObjects(
            Objects::OBJECT_TYPE_TARGET, 
            mMapCounter + ((mWallGenWidth - mTargetGenWidth)/2), 
            xInfo->height - (mWallGenHeight*(mWallHeight+1)) + 35, //(mWallGenHeight - mTargetGenHeight)*2, 
            mTargetGenHeight, 
            mTargetGenWidth);
        mTargetObjs.push_back((TargetObj*)obj);
        ((WallObj*)obj)->SetHeightFromGround(mWallHeight+1);
    }
}

int MapManager::GetScore()
{
    return mScore;
}

void MapManager::ExposeUpdate(XInfo* xInfo)
{
    vector<WallObj *>::const_iterator w_begin = mWallObjs.begin();
    vector<WallObj *>::const_iterator w_end = mWallObjs.end();
    while(w_begin != w_end) 
    {
        WallObj *obj = *w_begin;
        obj->ExposeUpdate(xInfo);

        w_begin++;
    }

    vector<TargetObj *>::const_iterator t_begin = mTargetObjs.begin();
    vector<TargetObj *>::const_iterator t_end = mTargetObjs.end();
    while(t_begin != t_end) 
    {
        TargetObj *obj = *t_begin;
            // cout << "Updating: ";
            // obj->DisplayID();
        obj->ExposeUpdate(xInfo);

        t_begin++;
    }
}