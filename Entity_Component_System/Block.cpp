//
// Created by sterr on 1-8-2022.
//

#include "Block.h"
#include <type_traits>
#include <assert.h>
#include <malloc.h>

Block::Block(Archetype& archetype) {
    assert(isPowerOfTwo(BufferSize));
    ptr = static_cast<char*>(_mm_malloc(BufferSize, BufferSize));
    // calculate buffer layout
    std::vector<size_t> ComponentArrayAlignments;
    size_t relativelyAddress = 0;
    for (TypeComponent component : archetype.Component_properties) {
        // set component size
        Layout.ComponentSize.push_back(component.Size);
        // calculate total component size for each component
        size_t size = component.Size + component.Alignment;
        Layout.RSize.push_back(size);
        // calculate pending size component array
        size_t PendingSize = relativelyAddress % size;
        ComponentArrayAlignments.push_back(PendingSize);
        relativelyAddress += size + PendingSize;
    }
    // calculate amount of entity in one block
    int amount = BufferSize / relativelyAddress;
    Layout.Rows = amount; // set amount of entity's
    Layout.Columns = archetype.Component_properties.size(); // set amount of component types
    // calculate relative address of component arrays
    relativelyAddress = (Layout.RSize[0] * amount) + ComponentArrayAlignments[0];
    Layout.CSize.push_back(0);
    for (int i = 1; i < Layout.Columns; i++){
        Layout.CSize.push_back(relativelyAddress);
        relativelyAddress += (Layout.RSize[i] * amount) + ComponentArrayAlignments[i];
    }
}

Block::~Block() {
    _mm_free(ptr);
}

void Block::Set(int row, int column, void* DataPtr, size_t size){
    assert((row < Layout.Rows) && (column < Layout.Columns)); // row or column out of bounds
    assert(size = Layout.ComponentSize[column]); // size component not de same
    char* ComponentPtr = ptr + Layout.CSize[column] + (Layout.RSize[column] * row);
    memcpy(ComponentPtr, DataPtr, size);
}

void* Block::GetPtr(int row, int column) {
    assert((row < Layout.Rows) && (column < Layout.Columns)); // row or column out of bounds
    char *ComponentPtr = ptr + Layout.CSize[column] + (Layout.RSize[column] * row);
    return ComponentPtr;
}

void Block::GetCopy(int row, int column, void* DestenationPtr, size_t size){
    assert((row < Layout.Rows) && (column < Layout.Columns)); // row or column out of bounds
    assert(size = Layout.ComponentSize[column]); // size component not de same
    char* ComponentPtr = ptr + Layout.CSize[column] + (Layout.RSize[column] * row);
    memcpy(DestenationPtr, ComponentPtr, size);
}

bool Block::isPowerOfTwo(size_t n) {
    return (ceil(log2(n)) == floor(log2(n)));
}