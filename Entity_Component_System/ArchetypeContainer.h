//
// Created by sterr on 1-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPECONTAINER_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPECONTAINER_H
#include <vector>
#include <unordered_map>
#include "Block.h"
#include "TypeIdGenerator.h"

struct EntityLocation {
    size_t BlockIndex;
    size_t Index;
};

class ArchetypeContainer {
public:
    ArchetypeContainer(Archetype& archetype, std::unordered_map<ArchetypeID , TypeComponent>& Components);
    ~ArchetypeContainer();

    void AddEntity(EntityID entity);
    void RemoveEntity(EntityID entity);
    void GetCompoent(EntityID entity, ComponentTypeID Component,void* DestenationPtr);
    void* GetComponentPtr(EntityID entity, ComponentTypeID Component);

    struct BlockIterator {
        std::vector<Block*>::iterator begin() { return Blocks.begin(); }
        std::vector<Block*>::iterator end() { return Blocks.end(); }
        std::vector<Block*>& Blocks;
    };

    BlockIterator eachBlcok() {return {Blocks};}

private:
    BlockLayout Layout;
    std::vector<Block*> Blocks;
    std::vector<std::pair<EntityID, EntityLocation>> EntityMap;

private:
    std::vector<std::pair<EntityID, EntityLocation>>::iterator GetEnity(EntityID entity);
    EntityLocation GetEntityLocation(EntityID entity);
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPECONTAINER_H
