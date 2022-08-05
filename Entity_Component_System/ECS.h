//
// Created by sterr on 30-7-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
#include <vector>
#include "ArchetypeContainer.h"

class ECS {
public:
    ECS();
    ~ECS();

    void CreateEntity();
    bool IsComponentRegistered();
    void* AddComponent(void* Data_ptr);
    void RemoveComponent();
    void* GedComponent();
    bool HasComponent();
    void RemoveEntity();

private:
    std::vector<std::pair<EntityID, ArchetypeID>> EntityArchetypeMap;
    std::vector<ArchetypeContainer> ArchetypeContainers;
};

#endif //ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
