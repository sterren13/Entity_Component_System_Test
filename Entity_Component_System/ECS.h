//
// Created by sterr on 30-7-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
#include <vector>
#include <unordered_map>
#include "ArchetypeContainer.h"

class ECS {
public:
    ECS();
    ~ECS();

    EntityID CreateEntity();
    void RemoveEntity(EntityID entity);
    void RegisterComponent(ComponentTypeID ID, size_t size, size_t Alignment);
    bool IsComponentRegister(ComponentTypeID ID);
    void AddComponent(EntityID entity, ComponentTypeID componentTypeId);
    void RemoveComponent();
    void* GedComponent(EntityID entity, ComponentTypeID Component);
    bool HasComponent(EntityID entity, ComponentTypeID Component);

private:
    std::vector<std::pair<EntityID, ArchetypeID>>::iterator FindEntity(EntityID entity);
    ArchetypeID GetEntityArchetypeFromEntity(EntityID entity);
    void MoveEntity(EntityID entity, ArchetypeID OldArchetypeID, ArchetypeID NewArchetypeID);
    void CreateNewArchtypeContainer(Archetype& archetype);

private:
    std::vector<std::pair<EntityID, ArchetypeID>> EntityArchetypeMap;
    std::unordered_map<ArchetypeID, Archetype> ArchetypeMap;
    std::unordered_map<ComponentTypeID, TypeComponent> ComponentMap;
    std::unordered_map<ArchetypeID, size_t> ArchetypeContainerMap; // TODO kan opgeloste worden met std::find_if functie
    std::vector<ArchetypeContainer*> ArchetypeContainers;
};

#endif //ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
