#include "TargetObj.h"
#include "Objects.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdlib>

using namespace std;

int TargetObj::mIdCounter = 0;

// Constructor - Generates the statistics of the Country
TargetObj::TargetObj(int x, int y, int height, int width) : 
    Objects(x, y, height, width)
{
    setType(OBJECT_TYPE_TARGET);
    mId = mIdCounter++;
    mWallHeight = 0;
    mFireRate = 1000000*((float)(rand() % 300 + 150)/100); 
    mTimer = 0;
    // TODO : some other stuff as needed
}

void TargetObj::DrawObj(XInfo* xInfo)
{
    XFillArc(xInfo->display, xInfo->pixmap, xInfo->gc[2], mPosX, mPosY, getWidth(), getHeight(), 0, 360*32);

    //XFillRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[2], getPosX(), getPosY(), getWidth(), getHeight());
    //cout << "painting" << endl;
}


void TargetObj::Update(int width, int height)
{
    // TODO: write the update 
    // cout << "Updating Target" << endl;
}

void TargetObj::Update(int width, int height, int velX)
{
    //cout << "Updating Wall" << endl;
    //mPosX += velX;
    mPosX -= velX;
    setHitBox(mPosX, mPosY, mPosX+getWidth(), mPosY+getHeight());
}

void TargetObj::Destroy()
{
    mToBeDestroyed = true;
}

void TargetObj::DisplayID()
{
    cout << "ID: " << mId << endl;
}

void TargetObj::ExposeUpdate(XInfo* xInfo)
{
    mPosY = xInfo->height - (mWallHeight*50) + 35;
}

void TargetObj::SetHeightFromGround(int wallHeight)
{
    mWallHeight = wallHeight;
}

int TargetObj::GetHeightFromGround()
{
    return mWallHeight;
}

bool TargetObj::ShouldFire(unsigned long timeframe)
{
    mTimer += timeframe;
    if(mTimer >= mFireRate)
    {
        mFireRate = 1000000*((float)(rand() % 300 + 150)/100); 
        mTimer = 0;
        return true;
    }
    return false;
}