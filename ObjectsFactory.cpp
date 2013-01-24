#include "ObjectsFactory.h"
#include "WallObj.h"
#include "TargetObj.h"
#include "MissileObj.h"
#include "HelichopterObj.h"
#include "PlaneObj.h"
#include <map>

using namespace std;

// Destructor
ObjectsFactory::~ObjectsFactory() {
    // Deletes all factories.
    std::map<Objects::eObjectType, ObjectsFactory*>::iterator it = ObjectsFactory::ObjectsInit.begin();
    while (it != ObjectsFactory::ObjectsInit.end()) {
        delete it++->second;
    }
}

Objects* ObjectsFactory::CreateObjects(const int id, int x, int y, int height, int width) {
    // Creates a Objects based on what the string ID is.
    if ((id < Objects::OBJECT_TYPE_COUNT) && (id >= Objects::OBJECT_TYPE_FIRST)) {
        // returns a pointer to a newly generated Objects from the
        // individual factory pointers 
        return ObjectsInit[(Objects::eObjectType)id]->create(x, y, height, width);
    } else {
        return NULL;
    }
}

//Static member
map<Objects::eObjectType, ObjectsFactory*> ObjectsFactory::ObjectsInit;

ObjectsFactoryInitializer::ObjectsFactoryInitializer() {
    // Creates a map that contains a pointer to factories of each 
    // Objects. 
    ObjectsFactory::ObjectsInit[Objects::OBJECT_TYPE_WALL] = new WallObj::Factory;
    ObjectsFactory::ObjectsInit[Objects::OBJECT_TYPE_TARGET] = new TargetObj::Factory;
    ObjectsFactory::ObjectsInit[Objects::OBJECT_TYPE_MISSILE] = new MissileObj::Factory;
    ObjectsFactory::ObjectsInit[Objects::OBJECT_TYPE_HELICHOPTER] = new HelichopterObj::Factory;
    ObjectsFactory::ObjectsInit[Objects::OBJECT_TYPE_PLANE] = new PlaneObj::Factory;
}

//Static member defination:
ObjectsFactoryInitializer ObjectsFactoryInitializer::initializer;