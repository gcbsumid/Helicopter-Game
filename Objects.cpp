#include "Objects.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

using namespace std;


Objects::Objects(int x, int y, int height, int width) : 
    mPosX(x), mPosY(y), 
    mVelX(0), mVelY(0),
    mAccX(0), mAccY(0),
    mToBeDestroyed(false),
    mDoesNeedUpdate(false),
    mWidth(width), mHeight(height)    
{
    mHitBox.minX = mPosX;
    mHitBox.minY = mPosY;
    mHitBox.maxX = mPosX + mWidth;
    mHitBox.maxY = mPosY + mHeight;
}

Objects::~Objects(){}

// TODO: EVERYTHING BELOW THIS LINE

/****** getters and setters ******/
int Objects::getPosX()
{
    return mPosX;
}

int Objects::getPosY()
{
    return mPosY;
}

int Objects::getVelX()
{
    return mVelX;
}

int Objects::getVelY()
{
    return mVelY;
}

int Objects::getAccX()
{
    return mAccX;
}

int Objects::getAccY()
{
    return mAccY;
}
    
bool Objects::DoesNeedUpdate()
{
    return mDoesNeedUpdate;
}

void Objects::SetNeedUpdate(bool needUpdate)
{
    mDoesNeedUpdate = needUpdate;
}

Objects::eObjectType Objects::getType()
{
    return mType;
}

void Objects::setType(eObjectType objectType)
{
    mType = objectType;
}

int Objects::getWidth()
{
    return mWidth;
}

int Objects::getHeight()
{
    return mHeight;
}
void Objects::setHitBox(int minimumX, int minimumY, int maximumX, int maximumY)
{
    mHitBox.minX = minimumX;
    mHitBox.minY = minimumY;
    mHitBox.maxX = maximumX;
    mHitBox.maxY = maximumY;
}

int Objects::getHitBoxMinX()
{
    return mHitBox.minX;
}

int Objects::getHitBoxMinY()
{
    return mHitBox.minY;
}

int Objects::getHitBoxMaxX()
{
    return mHitBox.maxX;
}

int Objects::getHitBoxMaxY()
{
    return mHitBox.maxY;
}

bool Objects::IsToBeDestroyed()
{
    return mToBeDestroyed;
}

bool Objects::IsOnScreen(int screenWidth, int screenHeight)
{
    if(mHitBox.maxX < 0 ||
        mHitBox.minX > screenWidth ||
        mHitBox.maxY < 0 ||
        mHitBox.minY > screenHeight)
    {
        return false;
    }
    return true;
}

void Objects::setDimensions(int width, int height)
{
    mWidth = width;
    mHeight = height;
}
