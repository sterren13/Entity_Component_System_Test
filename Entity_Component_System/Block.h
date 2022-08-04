//
// Created by sterr on 1-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
#define ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
#include <cstdint>
#include <vector>
#include <set>
#include <iostream>
#include "Archetype.h"

struct BlockLayout {
    size_t Rows;
    size_t Columns;
    size_t Alignment;
    std::vector<size_t> ComponentSize;
    std::vector<size_t> StartComponentArray;
};

class Block {
public:
    Block(BlockLayout& m_Layout);
    ~Block();
    void Set(size_t row, size_t column, void* DataPtr, size_t size);
    void* GetPtr(size_t row, size_t column);
    void GetCopy(size_t row, size_t column, void* DestenationPtr, size_t size);
    inline size_t GetNumberOfRows() { return Layout.Rows; }
    static size_t GetBufferSize() {return BufferSize;}

    // entity functies
    bool HasFreeSlot();
    size_t AddEntity();
    void RemoveEntity(size_t index);
    inline const size_t GetSize() const {return Size;}
private:
    char* ptr;
    char* EndPtr;
    static size_t BufferSize;
    BlockLayout Layout;
    std::set<size_t> FreeSlots;
    size_t Size = 0;
};

#endif //ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
