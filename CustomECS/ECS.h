//
// Created by sterr on 12-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
#include <unordered_map>

#include "Types.h"
#include "Storage.h"

class ECS {
public:
    ECS();
    ~ECS();

    // entity function
    Entity_ID CreateID();
    void Set(Entity_ID entity, Type_ID TypeID, size_t Size, void* ptr); // add component met data
    void Add(Entity_ID entity, Type_ID TypeID); // add tag
    bool HasComponent(Entity_ID entity, Type_ID ComponentID); // check of entity has component
    void* GetComponent(Entity_ID entity, Type_ID ComponentID); // get ptr from component from entity

    // component manager function
    void RegisterComponent(Type_ID ComponentID, size_t size, size_t Alignment); // register component in component manger
    bool IsComponentRegistered(Type_ID ComponentID); // check of component registered is
    Component& GetComponentProb(Type_ID ComponentID); // return registered component prob
private:
    ComponentManger my_ComponentManger;
    std::unordered_map<Entity_ID, Record> EntityIndex; // index from entity to find archetype
    Storage storage;
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
