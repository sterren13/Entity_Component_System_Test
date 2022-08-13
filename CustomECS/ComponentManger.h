//
// Created by sterr on 12-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_COMPONENTMANGER_H
#define ENTITY_COMPONENT_SYSTEM_TEST_COMPONENTMANGER_H
#include <unordered_map>

#include "Types.h"

#define COMPONENT_CONST_ID 0xA6A6A6A6

Type_ID From_typeid_to_ecs_typeid(size_t type_id);
Type_ID CreatePair(Type_ID first, Type_ID second);

struct Component{
    Type_ID ID;
    size_t Size;
    size_t Alignment;
};

// manger holds registered component whit data
class ComponentManger {
public:
    void RegisterComponent(Type_ID ComponentID, size_t size, size_t Alignment); // register component in ecs
    Component& GetComponent(Type_ID ComponentID); // get component data from id
    bool isComponentRegistered(Type_ID ComponentID); // check of component is registered in manger
private:
    std::unordered_map<Type_ID, Component> ComponentIndex;
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_COMPONENTMANGER_H
