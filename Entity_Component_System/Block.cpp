//
// Created by sterr on 1-8-2022.
//

#include "Block.h"
#include <algorithm>
#include "assert.h"
#include <malloc.h>
#include <memory>

size_t Block::BufferSize = 16*1000;

inline bool is_aligned(const void* ptr, size_t alignment) noexcept {
    auto iptr = reinterpret_cast<std::uintptr_t>(ptr);
    return !(iptr % alignment);
}

void ZoekAlimend(const void* ptr) {
    if (is_aligned(ptr, 1))
        std::cout << "Alimend bij: 1 \n";
    if (is_aligned(ptr, 2))
        std::cout << "Alimend bij: 2 \n";
    if (is_aligned(ptr, 4))
        std::cout << "Alimend bij: 4 \n";
    if (is_aligned(ptr, 8))
        std::cout << "Alimend bij: 8 \n";
    if (is_aligned(ptr, 16))
        std::cout << "Alimend bij: 16 \n";
    if (is_aligned(ptr, 32))
        std::cout << "Alimend bij: 32 \n";
    if (is_aligned(ptr, 64))
        std::cout << "Alimend bij: 64 \n";
}

Block::Block(BlockLayout& m_Layout) : Layout(m_Layout) {
    // create buffer whit bigest alignment
    void* p = _mm_malloc(BufferSize, Layout.Alignment);
    ptr = static_cast<char*>(p);
    EndPtr = ptr + BufferSize;
    //std::cout << "Amount of entity: " << Layout.Rows << "\n";
}

Block::~Block() { // TODO delete buffer
    //_mm_free(ptr);
}

void Block::Set(size_t row, size_t column, void* DataPtr, size_t size){
    //std::cout << "Row: " << row << " > " << Layout.Rows << ", Columns: " << column << " > " << Layout.Columns << "\n";
    assert((row < Layout.Rows) && (column < Layout.Columns)); // row or column out of bounds
    assert(size = Layout.ComponentSize[column]); // size component not de same
    char* ComponentPtr = ptr + Layout.StartComponentArray[column] + (Layout.ComponentSize[column] * row);
    assert(EndPtr > ComponentPtr);
    memcpy(ComponentPtr, DataPtr, size);
}

void* Block::GetPtr(size_t row, size_t column) {
    assert((row < Layout.Rows) && (column < Layout.Columns)); // row or column out of bounds
    char* ComponentPtr = ptr + Layout.StartComponentArray[column] + (Layout.ComponentSize[column] * row);
    return ComponentPtr;
}

void Block::GetCopy(size_t row, size_t column, void* DestenationPtr, size_t size){
    assert((row < Layout.Rows) && (column < Layout.Columns)); // row or column out of bounds
    assert(size = Layout.ComponentSize[column]); // size component not de same
    char* ComponentPtr = ptr + Layout.StartComponentArray[column] + (Layout.ComponentSize[column] * row);
    memcpy(DestenationPtr, ComponentPtr, size);
}

bool Block::HasFreeSlot(){
    return !(Size == Layout.Rows);
}

size_t Block::AddEntity(){
    size_t index = Size;
    Size++;
    return index;
}

void Block::RemoveEntity(size_t index){ // TODO change indexes from movet entitys
    // check of index lost index
    if (!(index == Size-1)) {
        // move data to close de gab from de remove entity
        //std::cout << "Index: " << index << ", Size: " << Size << "\n";
        for (int i = 0; i < Layout.Columns; i++) {
            char *CompoentPtr = (char *) GetPtr(index, i);
            size_t CopySize = (Size - index + 1) * Layout.ComponentSize[i]; // calculate size to copy
            char* src = (CompoentPtr + Layout.ComponentSize[i]);
            assert(EndPtr > (src + CopySize) && ptr < src);
            memmove(CompoentPtr, src, CopySize); // copy data use memmove for overlaping dst en src
        }
        Size--;
    }
    else { // is las index
        Size--;
    }
}