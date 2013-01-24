#ifndef MISSILEOBJ_H
#define MISSILEOBJ_H

#include "Objects.h"
#include "ObjectsFactory.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class MissileObj : public Objects {
    friend class ObjectsFactoryInitializer;     // Allows Objects factory initializer to access it
    friend class Factory;                       // Allows Factory to create an object (gives access to the constructor)
    MissileObj(int x, int y, int height, int width);

    class Factory : public ObjectsFactory {     // Factory class
    friend class ObjectsFactoryInitializer;
    public:
        Objects* create(int x, int y, int height, int width) {
            return new MissileObj(x, y, height, width);
        }
    };

public: 
    ~MissileObj() {}
    void DrawObj(XInfo* xInfo);         // Returns name
    void Update(int width, int height) {}
    void Update(int width, int height, int gameSpeed);
    void AddAcceleration(int x, int y);
    void UpdateVelocity(int velX, int velY, bool isBomb);
    void Destroy();
    void SetTurretMissile();
    bool IsTurretBullet();

private:
    static int mIdCounter;
    int mId;
    bool mTurretMissile;
    bool mIsBomb;
};

#endif