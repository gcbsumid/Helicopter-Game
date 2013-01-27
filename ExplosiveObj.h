#ifndef EXPLOSIVEOBJ_H
#define EXPLOSIVEOBJ_H

#include "MissileObj.h"
#include "Objects.h"
#include "ObjectsFactory.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class ExplosiveObj : public Objects {
    friend class ObjectsFactoryInitializer;     // Allows Objects factory initializer to access it
    friend class Factory;                       // Allows Factory to create an object (gives access to the constructor)
    ExplosiveObj(int x, int y, int height, int width);

    class Factory : public ObjectsFactory {     // Factory class
    friend class ObjectsFactoryInitializer;
    public:
        Objects* create(int x, int y, int height, int width) {
            return new ExplosiveObj(x, y, height, width);
        }
    };

public: 
    ~ExplosiveObj() {
        std::cout << mId << " was deleted." << std::endl;
    }
    void DrawObj(XInfo* xInfo);         // Returns name
    void Update(int width, int height) {}
    void Update(int width, int height, int gameSpeed);
    void AddAcceleration(int x, int y);
    void UpdateVelocity(int velX, int velY);
    void Destroy();
    void DisplayID();

private:
    static int mIdCounter;
    int mId;
};

#endif