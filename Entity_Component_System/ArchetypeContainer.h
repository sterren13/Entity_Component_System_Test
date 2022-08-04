//
// Created by sterr on 1-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPECONTAINER_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPECONTAINER_H
#include <vector>
#include <unordered_map>
#include "Block.h"
#include "TypeIdGenerator.h"

class ArchetypeContainer {
public:
    ArchetypeContainer(Archetype& archetype);
    ~ArchetypeContainer();

    void AddEntity(EntityID entityId);
    void RemoveEntity(EntityID entity);
    void GetCompoent(EntityID entity, ComponentTypeID Component,void* DestenationPtr);

    struct BlockIterator {
        std::vector<Block>::iterator begin() { return Blocks.begin(); }
        std::vector<Block>::iterator end() { return Blocks.end(); }
        std::vector<Block>::const_iterator begin() const { return Blocks.begin(); }
        std::vector<Block>::const_iterator end() const { return Blocks.end(); }

        std::vector<Block>& Blocks;
    };

    BlockIterator eachBlcok() {return {Blocks};}
private:
    BlockLayout Layout;
    std::vector<Block> Blocks;
    struct EntityLocation {
        size_t BlockIndex;
        size_t Index;
    };
    std::unordered_map<EntityID, EntityLocation> EntityMap;
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPECONTAINER_H
