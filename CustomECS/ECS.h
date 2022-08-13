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

    void AddEntity();
    void Set(Entity_ID entity, Type_ID TypeID, size_t Size, void* ptr); // add component met data
    void Add(Entity_ID entity, Type_ID TypeID); // add tag
    bool HasComponent(Entity_ID entity, Type_ID ComponentID); // check of entity has component
    void* GetComponent(Entity_ID entity, Type_ID ComponentID); // get ptr from component from entity

private:
    std::unordered_map<Entity_ID, Record> EntityIndex; // index from entity to find archetype
    Storage storage;
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
