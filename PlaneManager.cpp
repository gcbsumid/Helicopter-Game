#include <cstdlib>
#include <vector>
#include "PlaneManager.h"
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


// Constructor
PlaneManager::PlaneManager(HelichopterObj* heli, std::vector<MissileObj*>* turretMissiles) 
    : AIManager(), mScore(0), mTimer(0)
{
    mHelichopter = heli;
    mTurretMissileObjs = turretMissiles;
    mFireRate = 1000000*((float)(rand() % 1000 + 500)/100);
}

PlaneManager::~PlaneManager()
{
    while(!mPlaneObjs.empty())
    {
        mPlaneObjs.pop_back();
    }
}

void PlaneManager::Update(XInfo* xInfo, unsigned long timeframe, int gameSpeed)
{
    if(ShouldCreatePlane(timeframe))
    {
        cout << "Creating an Object." << endl;
        int randomY = rand() % 100 + 20;
        Objects* obj = ObjectsFactory::CreateObjects(
            Objects::OBJECT_TYPE_PLANE, xInfo->width, randomY, 20, 30);
        mPlaneObjs.push_back((PlaneObj*)obj); 
    }

    if(!mPlaneObjs.empty())
    {
        vector<PlaneObj *>::const_iterator begin = mPlaneObjs.begin();
        vector<PlaneObj *>::const_iterator end = mPlaneObjs.end();
        int counter = 0;
        while(begin != end)
        {
            PlaneObj *o = *begin;
            o->Update(xInfo->width, xInfo->height, gameSpeed);
            if(o->IsToBeDestroyed())
            {
                mPlaneObjs.erase(mPlaneObjs.begin()+counter);
            
            // Update m_end
                end = mPlaneObjs.end();
                begin--;
                mScore += 3;
                counter--;
            }
            begin++;
            counter++;
        }
    }
}

void PlaneManager::Repaint(XInfo* xInfo)
{
    vector<PlaneObj *>::const_iterator begin = mPlaneObjs.begin();
    vector<PlaneObj *>::const_iterator end = mPlaneObjs.end();

    while(begin != end)
    {
        Objects *o = *begin;
        if(o->IsOnScreen(xInfo->width, xInfo->height))
        {
            o->DrawObj(xInfo);
        }
        begin++;
    }
}

bool PlaneManager::ShouldCreatePlane(unsigned long timeframe)
{
    mTimer += timeframe;
    if(mTimer >= mFireRate)
    {
        mFireRate = 1000000*((float)(rand() % 1000 + 500)/100); 
        mTimer = 0;
        return true;
    }
    return false;
}

void PlaneManager::AIFire(XInfo* xInfo, unsigned long timeframe)
{
    vector<PlaneObj *>::const_iterator begin = mPlaneObjs.begin();
    vector<PlaneObj *>::const_iterator end = mPlaneObjs.end();

    while(begin != end)
    {
        PlaneObj *o = *begin;
        if(o->IsOnScreen(xInfo->width, xInfo->height) && o->ShouldFire(timeframe) && CanFire((Objects*)o, 750))
        {
            pt velocity = CalculateVelocity((Objects*)o);
            this->FireInTheHole((Objects*)o, velocity.x, velocity.y, false);
        }
        begin++;
    }
}

bool PlaneManager::DoesPlaneExist()
{
    if(mPlaneObjs.empty())
    {
        return false;
    }
    return true;
}

std::vector<PlaneObj*>* PlaneManager::GetPlaneObjs()
{
    return &mPlaneObjs;
}

int PlaneManager::GetScore()
{
    return mScore;
}