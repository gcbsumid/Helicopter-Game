#include "ExplosiveObj.h"
#include "Objects.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

int ExplosiveObj::mIdCounter = 0;

// Constructor - Generates the statistics of the Country
ExplosiveObj::ExplosiveObj(int x, int y, int height, int width) : 
    Objects(x, y, height, width)
{
    setType(OBJECT_TYPE_EXPLOSION);
    mId = mIdCounter++;
    // TODO : some other stuff as needed
}

void ExplosiveObj::DrawObj(XInfo* xInfo) 
{
    XFillArc(xInfo->display, xInfo->pixmap, xInfo->gc[3], mPosX, mPosY, getWidth(), getHeight(), 0, 360*64);
}

void ExplosiveObj::AddAcceleration(int x, int y)
{
    // TODO: do this
}

void ExplosiveObj::UpdateVelocity(int velX, int velY)
{
    mVelX = velX;
    mVelY = velY;
    SetNeedUpdate(true);
}

void ExplosiveObj::Update(int width, int height, int gameSpeed)
{
    mPosX += mVelX;
    mPosX -= gameSpeed;
    mPosY += mVelY;
    // Moves with map
    //mPosX++;

    if(mPosX >= width || mPosX <= 0 || mPosY >= height)
    {
        mToBeDestroyed = true;
    }

    setHitBox(mPosX, mPosY, mPosX+getWidth(), mPosY+getHeight());
    // TODO: do this
    // cout << "Updating Target" << endl;
}

void ExplosiveObj::Destroy()
{
    mToBeDestroyed = true;
}

void ExplosiveObj::DisplayID()
{
    cout << "Explosive ID: " << mId << endl;
}
