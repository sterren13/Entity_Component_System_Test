//
// Created by sterr on 11-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPE_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPE_H
#include <vector>
#include <unordered_map>

#include "Block.h"
#include "Types.h"
#include "ComponentManger.h"

struct ArchetypeBuilder{
    Archetype_ID ID = 0;
    std::vector<Component> Components; // list of all component from archetype
    std::vector<Type_ID> Tags; // list of all tags (components with no data)
};

class Archetype {
public:
    Archetype(ArchetypeBuilder& builder);
    ~Archetype();
    ArchetypeBuilder&  GetBuilder() { return my_builder;}
    size_t AddEntity(); // add new entity to archetype and returns index
    void RemoveEntity(size_t index); // removes entity and copy data from last entity en movies it
    void* GetComponentPtr(size_t index, Type_ID ComponentID); // returns pointer to component from entity bay index
    bool HasComponent(Type_ID ComponentID); // returns true when archetype has component

private:
    size_t GetBlockIndexFomGlobalIndex(size_t Index);
    Block& GetBlockFromIndex(size_t Index);
    size_t GetLocalBlockIndex(size_t Index);

private:
    ArchetypeBuilder my_builder;
    size_t MaxBlockSize; // max entity in one block
    size_t LastIndex = 0; // last index of all blocks
    size_t BlockAlignment = 1;
    std::vector<Block> Blocks;
    struct ComponentRecord {
        size_t ComponentSize; // size of component
        size_t Row; // row number for component
        size_t StartRowIndex; // relative address to row of components
    };
    std::unordered_map<Type_ID, ComponentRecord> ComponentMap; // map from all components and row index in data block
                                                               // component with no data while bie de last row
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_ARCHETYPE_H
