//
// Created by sterr on 1-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
#define ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
#include <cstdint>
#include <vector>
#include <iostream>
#include "Archetype.h"

struct BlockLayout {
    size_t Rows;
    size_t Columns;
    std::vector<size_t> ComponentSize;
    std::vector<size_t> StartComponentArray;
};

class Block {
public:
    Block(Archetype& archetype);
    ~Block();
    void Set(size_t row, size_t column, void* DataPtr, size_t size);
    void* GetPtr(size_t row, size_t column);
    void GetCopy(size_t row, size_t column, void* DestenationPtr, size_t size);
    inline size_t GetNumberOfRows() { return Layout.Rows; }
private:
    char* ptr;
    char* EndPtr;
    static size_t BufferSize;
    BlockLayout Layout;
    std::vector<size_t> ComponentAlayments;
};

#endif //ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
