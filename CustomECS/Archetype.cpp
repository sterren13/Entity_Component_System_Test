//
// Created by sterr on 11-8-2022.
//

#include "Archetype.h"
#include <memory>

Archetype::Archetype(ArchetypeBuilder& builder) : my_builder(builder) { // TODO check of archetype has data when not do not create buffer and check of has tags
    // calculate buffer layout
    size_t RelativelyAddress = 0;
    std::vector<size_t> ComponentArrayAlignments;

    // calculate component array alignments
    for (size_t i = 0; i < builder.Components.size(); i++){
        size_t ComponentSize = builder.Components[i].Size;
        size_t ComponentAlignment = builder.Components[i].Alignment;

        // find max alignment
        if (BlockAlignment < ComponentAlignment)
            BlockAlignment = ComponentAlignment;

        // calculate alignment form component arrays in buffer
        size_t PendingBinds = RelativelyAddress % ComponentAlignment;
        ComponentArrayAlignments.push_back(PendingBinds);
        RelativelyAddress += ComponentSize + PendingBinds;
    }

    // calculate max block size
    MaxBlockSize = BLOCK_SIZE / RelativelyAddress;
    RelativelyAddress = 0;
    size_t ArrayAlignment = 0;
    for (size_t i = 0; i < builder.Components.size(); i++){ // TODO voeg juiste alignment toe
        size_t ComponentSize = builder.Components[i].Size;
        if (ComponentArrayAlignments.size()-1 != i)
            ArrayAlignment = ComponentArrayAlignments[i+1];
        else
            ArrayAlignment = 0;

        ComponentMap.insert({builder.Components[i].ID,
                             {ComponentSize,
                              i,
                              RelativelyAddress}});
        RelativelyAddress += (ComponentSize * MaxBlockSize) + ArrayAlignment;
    }

    // add tags to ComponentMap
    for (Type_ID TagID : builder.Tags)
        ComponentMap.insert({TagID, {0, ComponentMap.size(), 0}});
}

Archetype::~Archetype() {
    for (Block& block : Blocks){
        _mm_free(block.Ptr);
    }
}

size_t Archetype::AddEntity() {
    size_t Index = LastIndex;
    if (GetLocalBlockIndex(LastIndex) == Blocks.size()){
        Block block;
        block.Ptr = (char*)_mm_malloc(BLOCK_SIZE, BlockAlignment);
        block.CurrentSize = 0;
        Blocks.push_back(block);
    }
    LastIndex++;
    return Index;
}

void Archetype::RemoveEntity(size_t index) {
    size_t DesIndex = GetLocalBlockIndex(index);
    Block& DesBlock = GetBlockFromIndex(index);
    size_t SrcIndex = GetLocalBlockIndex(LastIndex);
    Block& SrcBlock = GetBlockFromIndex(LastIndex);

    for (std::pair<Type_ID, ComponentRecord> pair : ComponentMap){
        char* DesPtr = DesBlock.Ptr + pair.second.StartRowIndex + (DesIndex * pair.second.ComponentSize);
        char* SrcPtr = SrcBlock.Ptr + pair.second.StartRowIndex + (SrcIndex * pair.second.ComponentSize);
        memcpy(DesPtr, SrcPtr, pair.second.ComponentSize);
    }
    LastIndex--;
}

void* Archetype::GetComponentPtr(size_t index, Type_ID ComponentID) {
    Block& block = GetBlockFromIndex(index);
    size_t Index = GetLocalBlockIndex(index);
    ComponentRecord CompRecord = ComponentMap[ComponentID];
    return block.Ptr + CompRecord.StartRowIndex + (Index * CompRecord.ComponentSize);
}

bool Archetype::HasComponent(Type_ID ComponentID) {
    return ComponentMap.find(ComponentID) != ComponentMap.end();
}

size_t Archetype::GetBlockIndexFomGlobalIndex(size_t Index) {
    return Index/MaxBlockSize;
}

Block& Archetype::GetBlockFromIndex(size_t Index) {
    return Blocks[GetBlockIndexFomGlobalIndex(Index)];
}

size_t Archetype::GetLocalBlockIndex(size_t Index) {
    return Index%MaxBlockSize;
}