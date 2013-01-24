#ifndef OBJECTSFACTORY_H
#define OBJECTSFACTORY_H

#include <map>
#include "Objects.h"

class ObjectsFactory {
public:
    virtual ~ObjectsFactory();               // Destructor
    friend class ObjectsFactoryInitializer;  // Initializer class
    
    // Static function so it can be called without 
    // instantiation
    static Objects* CreateObjects(const int id, int x, int y, int height, int width);

private:
    virtual Objects* create(int x, int y, int height, int width) = 0;         // Factory Method
    static std::map<Objects::eObjectType, ObjectsFactory*> ObjectsInit;

};  

class ObjectsFactoryInitializer{
    static ObjectsFactoryInitializer initializer; // creates an initializer object
    ObjectsFactoryInitializer();
    ObjectsFactoryInitializer(const ObjectsFactoryInitializer&);

};

#endif