#include "MissileObj.h"
#include "Objects.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

int MissileObj::mIdCounter = 0;

// Constructor - Generates the statistics of the Country
MissileObj::MissileObj(int x, int y, int height, int width) : 
    Objects(x, y, height, width), mTurretMissile(false), mIsBomb(false)
{
    setType(OBJECT_TYPE_MISSILE);
    mId = mIdCounter++;
    // TODO : some other stuff as needed
}

void MissileObj::DrawObj(XInfo* xInfo) 
{
    XDrawArc(xInfo->display, xInfo->pixmap, xInfo->gc[3], mPosX, mPosY, getWidth(), getHeight(), 0, 360*64);
}

void MissileObj::AddAcceleration(int x, int y)
{
    // TODO: do this
}

void MissileObj::UpdateVelocity(int velX, int velY, bool isBomb)
{
    mVelX = velX;
    mVelY = velY;
    mIsBomb = isBomb;
    SetNeedUpdate(true);
}

void MissileObj::Update(int width, int height, int gameSpeed)
{
    mPosX += mVelX;
    mPosX -= gameSpeed;
    if(mIsBomb)
    {
        mPosY += mVelY;
    }
    // Moves with map
    //mPosX++;

    if(mPosX >= width || mPosX <= 0 || mPosY >= height)
    {
        mToBeDestroyed = true;
    }

    if(!mTurretMissile)
    {
        mVelY++;
    }

    setHitBox(mPosX, mPosY, mPosX+getWidth(), mPosY+getHeight());
    // TODO: do this
    // cout << "Updating Target" << endl;
}

void MissileObj::Destroy()
{
    mToBeDestroyed = true;
}

void MissileObj::SetTurretMissile()
{
    mTurretMissile = true;
}

bool MissileObj::IsTurretBullet()
{
    return mTurretMissile;
}
