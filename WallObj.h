#ifndef WALLOBJ_H
#define WALLOBJ_H

#include "XInfo.h"
#include "Objects.h"
#include "ObjectsFactory.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class WallObj : public Objects {
    friend class ObjectsFactoryInitializer;     // Allows Objects factory initializer to access it
    friend class Factory;                       // Allows Factory to create an object (gives access to the constructor)
    WallObj(int x, int y, int height, int width);

    class Factory : public ObjectsFactory {     // Factory class
    friend class ObjectsFactoryInitializer;
    public:
        Objects* create(int x, int y, int height, int width) {
            return new WallObj(x, y, height, width);
        }
    };

public: 
    ~WallObj() {}
    void DrawObj(XInfo* xInfo);         // Returns name
    void Update(int width, int height);
    void Update(int width, int height, int velX);
    void Destroy();
    void DisplayID();
    void ExposeUpdate(XInfo* xInfo);
    void SetHeightFromGround(int wallHeight);
    int GetHeightFromGround();

private:
    int mWallHeight;
    static int mIdCounter;
    int mId;
};

#endif