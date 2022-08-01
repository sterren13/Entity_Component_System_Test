//
// Created by sterr on 1-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
#define ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
#include <cstdint>
#include <vector>
#include "Archetype.h"

struct BlockLayout {
    int Rows;
    int Columns;
    std::vector<size_t> ComponentSize;
    std::vector<size_t> RSize;
    std::vector<size_t> CSize;
};

class Block {
public:
    Block(Archetype& archetype);
    ~Block();
    void Set(int row, int column, void* DataPtr, size_t size);
    void* GetPtr(int row, int column);
    void GetCopy(int row, int column, void* DestenationPtr, size_t size);
private:
    char* ptr;
    size_t BufferSize = 10;
    bool isPowerOfTwo(size_t n);
    BlockLayout Layout;
};

#endif //ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
