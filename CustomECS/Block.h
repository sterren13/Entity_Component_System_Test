//
// Created by sterr on 12-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
#define ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
#include <cstdint>

#define BLOCK_SIZE 16*1000

struct Block{
    char* Ptr; // pointer to data block
    size_t CurrentSize; // amount of entity's
};

#endif //ENTITY_COMPONENT_SYSTEM_TEST_BLOCK_H
