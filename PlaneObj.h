#ifndef PLANEOBJ_H
#define PLANEOBJ_H

#include "Objects.h"
#include "ObjectsFactory.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class PlaneObj : public Objects {
    friend class ObjectsFactoryInitializer;     // Allows Objects factory initializer to access it
    friend class Factory;                       // Allows Factory to create an object (gives access to the constructor)
    PlaneObj(int x, int y, int height, int width);

    class Factory : public ObjectsFactory {     // Factory class
    friend class ObjectsFactoryInitializer;
    public:
        Objects* create(int x, int y, int height, int width) {
            return new PlaneObj(x, y, height, width);
        }
    };

public: 
    ~PlaneObj() {}
    void DrawObj(XInfo* xInfo);         // Returns name
    void Update(int width, int height) {}
    void Update(int width, int height, int gameSpeed);
    void Destroy();
    void DisplayID();
    bool ShouldFire(unsigned long timeframe);

private:
    static int mIdCounter;
    unsigned long mTimer;
    unsigned long mFireRate;
    int mId;
    int mVelCounterX;
    int mVelCounterY;
    bool mStartY;
    int mRandomXStart;
    int mXStartCounter;

    int mGameSpeed;

};

#endif