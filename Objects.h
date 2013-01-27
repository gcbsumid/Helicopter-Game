/***************************************************
/ Object.h                                  /
/ Description:                                      /
/   Contains all the physics involved in the game.  /
 ***************************************************/

#ifndef OBJECT_H
#define OBJECT_H

#include <iostream>
#include <cstdlib>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include "XInfo.h"

class Objects 
{
public:

    enum eObjectType {
        OBJECT_TYPE_FIRST       = 0,

        OBJECT_TYPE_WALL        = OBJECT_TYPE_FIRST,
        OBJECT_TYPE_TARGET      = 1,
        OBJECT_TYPE_MISSILE     = 2,
        OBJECT_TYPE_HELICHOPTER = 3,
        OBJECT_TYPE_PLANE       = 4,
        OBJECT_TYPE_EXPLOSION   = 5,

        OBJECT_TYPE_LAST        = OBJECT_TYPE_EXPLOSION,
        OBJECT_TYPE_COUNT       = 6
    };

    virtual ~Objects();
    virtual void DrawObj(XInfo* xInfo) = 0;
    virtual void Update(int width, int height) = 0;
    virtual void Destroy() = 0;

    /****** getters and setters ******/
    int getPosX();

    int getPosY();

    int getVelX();

    int getVelY();

    int getAccX();

    int getAccY();

    bool DoesNeedUpdate();
    void SetNeedUpdate(bool needUpdate);
    bool IsToBeDestroyed();

    eObjectType getType();
    void setType(eObjectType objectType);
    int getWidth();
    int getHeight();

    void setHitBox(int minX, int minY, int maxX, int maxY);
    int getHitBoxMinX();
    int getHitBoxMinY();
    int getHitBoxMaxX();
    int getHitBoxMaxY();
    void setDimensions(int width, int height);

    bool IsOnScreen(int screenWidth, int screenHeight);

protected:
    Objects(int x, int y, int height, int width);

    int mPosX;           // position X  
    int mPosY;           // position Y
    int mVelX;           // velocity X
    int mVelY;           // velocity Y
    int mAccX;           // acceleration X
    int mAccY;           // acceleration Y
    bool mToBeDestroyed;
    eObjectType mType;

private:

    // Bounding box
    struct HitBox {
        int minX;
        int minY;
        int maxX;
        int maxY;
    };

    bool mDoesNeedUpdate;
    int mWidth;
    int mHeight;
    HitBox mHitBox;
};

#endif