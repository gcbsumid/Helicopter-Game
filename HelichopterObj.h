#ifndef HELICHOPTEROBJ_H
#define HELICHOPTEROBJ_H

#include "Objects.h"
#include "ObjectsFactory.h"
#include "XInfo.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>

class HelichopterObj : public Objects {
    friend class ObjectsFactoryInitializer;     // Allows Objects factory initializer to access it
    friend class Factory;                       // Allows Factory to create an object (gives access to the constructor)
    HelichopterObj(int x, int y, int height, int width);

    class Factory : public ObjectsFactory {     // Factory class
    friend class ObjectsFactoryInitializer;
    public:
        Objects* create(int x, int y, int height, int width) {
            return new HelichopterObj(x, y, height, width);
        }
    };

public: 
    ~HelichopterObj() {}
    void DrawObj(XInfo* xInfo);         // Returns name
    void Update(int width, int height);
    void AddAcceleration(int x, int y);
    void Destroy();
    bool ShouldHeliMove(int screenWidth, int screenHeight);
    void ResetXAcceleration();
    void ResetYAcceleration();

private:
    static int mIdCounter;
    int mId;

};

#endif