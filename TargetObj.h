#ifndef TARGETOBJ_H
#define TARGETOBJ_H

#include "Objects.h"
#include "ObjectsFactory.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class TargetObj : public Objects {
    friend class ObjectsFactoryInitializer;     // Allows Objects factory initializer to access it
    friend class Factory;                       // Allows Factory to create an object (gives access to the constructor)
    TargetObj(int x, int y, int height, int width);

    class Factory : public ObjectsFactory {     // Factory class
    friend class ObjectsFactoryInitializer;
    public:
        Objects* create(int x, int y, int height, int width) {
            return new TargetObj(x, y, height, width);
        }
    };

public: 
    ~TargetObj() {}
    void DrawObj(XInfo* xInfo);         // Returns name
    void Update(int width, int height);
    void Update(int width, int height, int velX);
    void Destroy();
    void DisplayID();
    void ExposeUpdate(XInfo* xInfo);
    void SetHeightFromGround(int wallHeight);
    int GetHeightFromGround();
    bool ShouldFire(unsigned long timeframe);

private:
    int mWallHeight;
    unsigned long mTimer;
    unsigned long mFireRate;
    static int mIdCounter;
    int mId;
};

#endif