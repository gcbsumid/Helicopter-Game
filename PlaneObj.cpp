#include "PlaneObj.h"
#include "Objects.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

int PlaneObj::mIdCounter = 0;

// Constructor - Generates the statistics of the Country
PlaneObj::PlaneObj(int x, int y, int height, int width) : 
    Objects(x, y, height, width)
{
    setType(OBJECT_TYPE_HELICHOPTER);
    mId = mIdCounter++;
    mFireRate = 1000000*((float)(rand() % 200 + 50)/100);
    mTimer = 0;
    mVelCounterX = 50;
    mVelCounterY = 0;
    mStartY = false;
    mXStartCounter = 0;
    mRandomXStart = rand() % 500 + 50;
    // TODO : some other stuff as needed
}

void PlaneObj::DrawObj(XInfo* xInfo) 
{
    //XDrawRectangle(xInfo->display, xInfo->window, xInfo->gc[0], mPosX, mPosY, getWidth(), getHeight());
    // Body
    XDrawArc(xInfo->display, 
             xInfo->pixmap, 
             xInfo->gc[3], 
             mPosX+6, 
             mPosY+3, 
             getWidth()-6, 
             getHeight()-6, 
             0, 
             360*64);
    XDrawArc(xInfo->display, 
             xInfo->pixmap, 
             xInfo->gc[3], 
             mPosX+16, 
             mPosY, 
             getWidth()-16, 
             getHeight(), 
             0, 
             360*64);
    // Top Blades

    XDrawRectangle(xInfo->display,
                   xInfo->pixmap,
                   xInfo->gc[3],
                   mPosX,
                   mPosY+7,
                   getWidth()-5,
                   getHeight()-14);
}

void PlaneObj::Update(int width, int height, int gameSpeed)
{
    mGameSpeed = gameSpeed;
    if(!mStartY)
    {
        mPosX -= 30;
        mXStartCounter += 30;
    }
    else
    {
        if(mVelCounterX <= 12)
        {
            mVelX++;
        } 
        else if(mVelCounterX >= 38)
        {
            mVelX--;
        }

        if(mVelCounterY <= 25)
        {
            mVelY++;
        } 
        else if(mVelCounterY >= 75)
        {
            mVelY--;
        }
    }

    if(mXStartCounter >= mRandomXStart)
    {
        mStartY = true;
    }

    mPosX += mVelX;
    mPosY += mVelY;
    mVelCounterX += mVelX;
    mVelCounterY += mVelY;

    setHitBox(mPosX, mPosY, mPosX+getWidth(), mPosY+getHeight());
}

void PlaneObj::Destroy()
{
    cout << "Helichopter should be destroyed" << endl;
    mToBeDestroyed = true;
}

bool PlaneObj::ShouldFire(unsigned long timeframe)
{
    mTimer += timeframe;
    if(mTimer >= mFireRate)
    {
        mFireRate = 1000000*((float)(rand() % 200 + 50)/100); 
        mTimer = 0;
        return true;
    }
    return false;
}

void PlaneObj::DisplayID()
{
    cout << "ID: " << mId << endl;
}