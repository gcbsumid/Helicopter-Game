#include "WallObj.h"
#include "Objects.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;

int WallObj::mIdCounter = 0;

// Constructor - Generates the statistics of the Country
WallObj::WallObj(int x, int y, int height, int width) : 
    Objects(x, y, height, width)
{
    setType(OBJECT_TYPE_WALL);
    mId = mIdCounter++;
    mWallHeight = 0;
    // TODO : some other stuff as needed
}

void WallObj::DrawObj(XInfo* xInfo) 
{
    XDrawRectangle(xInfo->display, xInfo->pixmap, xInfo->gc[2], getPosX(), getPosY(), getWidth(), getHeight());
    //cout << "painting" << endl;
}

void WallObj::Update(int width, int height)
{
    //cout << "Updating Wall" << endl;
}

void WallObj::Update(int width, int height, int velX)
{
    //cout << "Updating Wall" << endl;
    //mPosX += velX;
    mPosX -= velX;


    setHitBox(mPosX, mPosY, mPosX+getWidth(), mPosY+getHeight());

}

void WallObj::Destroy()
{
    cout << "Cannot Be Destroyed! This is a wall." << endl;
}

void WallObj::DisplayID()
{
    cout << "ID: " << mId << endl;
}

void WallObj::ExposeUpdate(XInfo* xInfo)
{
    mPosY = xInfo->height - (mWallHeight*getHeight());
}

void WallObj::SetHeightFromGround(int wallHeight)
{
    mWallHeight = wallHeight;
}

int WallObj::GetHeightFromGround()
{
    return mWallHeight;
}