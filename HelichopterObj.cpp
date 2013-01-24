#include "HelichopterObj.h"
#include "Objects.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

int HelichopterObj::mIdCounter = 0;

// Constructor - Generates the statistics of the Country
HelichopterObj::HelichopterObj(int x, int y, int height, int width) : 
    Objects(x, y, height, width)
{
    setType(OBJECT_TYPE_HELICHOPTER);
    mId = mIdCounter++;
    // TODO : some other stuff as needed
}

void HelichopterObj::DrawObj(XInfo* xInfo) 
{
    //XDrawRectangle(xInfo->display, xInfo->window, xInfo->gc[0], mPosX, mPosY, getWidth(), getHeight());
    // Body
    XDrawArc(xInfo->display, xInfo->pixmap, xInfo->gc[3], mPosX+10, mPosY+15, getWidth()-10, getHeight()-15, 0, 360*64);
    // Top Blades
    XDrawLine(xInfo->display, xInfo->pixmap, xInfo->gc[3], mPosX+35, mPosY+15, mPosX+35, mPosY+10);
    XDrawArc(xInfo->display, xInfo->pixmap, xInfo->gc[3], mPosX+22, mPosY, getWidth()-25, getHeight()-20, 0, 360*64);
    // Back Blades
    XDrawLine(xInfo->display, xInfo->pixmap, xInfo->gc[3], mPosX+13, mPosY+18, mPosX+8, mPosY+17);
    XDrawArc(xInfo->display, xInfo->pixmap, xInfo->gc[3], mPosX, mPosY+12, 7, 7, 0, 360*64);
}

void HelichopterObj::AddAcceleration(int x, int y)
{
    mAccX += x;
    mAccY += y;
    SetNeedUpdate(true);
}

void HelichopterObj::ResetXAcceleration()
{
    mAccX = 0;
}

void HelichopterObj::ResetYAcceleration()
{
    mAccY = 0;
}

void HelichopterObj::Update(int width, int height)
{
    if(ShouldHeliMove(width, height))
    {
        mPosX += mVelX;
        mPosY += mVelY;
    }

    // velocity is capped at 10
    if(mVelX < 10 && mVelX > -10)
    {
        mVelX += mAccX;
    }
    else 
    {
        if(mVelX > 0)
        {
            mVelX--;
        }
        else 
        {
            mVelX++;
        }
    }
    if(mVelY < 10 && mVelY > -10)
    {
        mVelY += mAccY;
    }
    else
    {
        if(mVelY > 0)
        {
            mVelY--;
        }
        else 
        {
            mVelY++;
        }
    }

    if(mAccX == 0)
    {
        mVelX = (int)((float)mVelX * 0.95);
    } 

    if(mAccY == 0)
    {
        mVelY = (int)((float)mVelY * 0.95);
    } 

    if(ShouldHeliMove(width, height))
    {
        if(mVelX == 0 && mVelY == 0 && mAccY == 0 && mAccX == 0) 
        {
            SetNeedUpdate(false);
        }
        setHitBox(mPosX, mPosY, mPosX+getWidth(), mPosY+getHeight());
    }
}

void HelichopterObj::Destroy()
{
    cout << "Helichopter should be destroyed" << endl;
    mToBeDestroyed = true;
}

bool HelichopterObj::ShouldHeliMove(int screenWidth, int screenHeight)
{
    if(mVelY >= 0)
    {
        if(mPosY < 0)
        {
            mPosY++;
        }
    }
    else if(mVelY <= 0)
    {
        if(mPosX + getWidth() > screenHeight)
        {
            mPosY--;
        }
    }
    if(mVelX >= 0) 
    {
        if(mPosX < screenWidth*0.05)
        {
            mPosX++;
        }
    }
    else if(mVelX <= 0)
    {
        if(mPosX + getWidth() > screenWidth*0.95)
        {
            mPosX--;
        }
    }

    if(((mPosX + getWidth()) > screenWidth*0.95) ||
        (mPosX < screenWidth*0.05))
    {
        return false;
    }

    if(((mPosY + getHeight()) > screenHeight) ||
        (mPosY < 0))
    {
        return false;
    }
    return true;
}
