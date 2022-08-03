//
// Created by sterr on 1-8-2022.
//

#include "Block.h"
#include <math.h>
#include <assert.h>
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

Block::Block(Archetype& archetype) {
    // calculate buffer layout
    size_t RelativelyAdress = 0;
    size_t MaxAlignment = 1;
    std::vector<size_t> ComponentArrayAlignments;
    for (TypeComponent component : archetype.Component_properties) {
        // add component size's
        Layout.ComponentSize.push_back(component.Size);
        ComponentAlayments.push_back(component.Alignment);
        RelativelyAdress += component.Size;

        // get max size alignment
        if (MaxAlignment < component.Alignment)
            MaxAlignment = component.Alignment;

        // caculate alignment
        size_t PendingBinds = RelativelyAdress % component.Alignment;
        ComponentArrayAlignments.push_back(PendingBinds);
        RelativelyAdress += PendingBinds;
    }

    // caculate rows
    Layout.Rows = BufferSize / RelativelyAdress;
    Layout.Columns = Layout.ComponentSize.size();

    Layout.StartComponentArray.push_back(0);
    RelativelyAdress = (Layout.ComponentSize[0] * Layout.Rows) + ComponentArrayAlignments[0];
    for (int i = 1; i < Layout.Columns; i++) {
        Layout.StartComponentArray.push_back(RelativelyAdress);
        RelativelyAdress += (Layout.ComponentSize[0] * Layout.Rows) + ComponentArrayAlignments[0];
    }

    // TODO check of buffer groot genoeg is voor minstens een component

    // create buffer whit bigest alignment
    void* p = _mm_malloc(BufferSize, MaxAlignment);
    ptr = static_cast<char*>(p);
    EndPtr = ptr + BufferSize;
    std::cout << "Amount of entity: " << Layout.Rows << "\n";
}

Block::~Block() {
    _mm_free(ptr);
}

void Block::Set(size_t row, size_t column, void* DataPtr, size_t size){
    //std::cout << "Row: " << row << " > " << Layout.Rows << ", Columns: " << column << " > " << Layout.Columns << "\n";
    assert((row < Layout.Rows) && (column < Layout.Columns)); // row or column out of bounds
    assert(size = Layout.ComponentSize[column]); // size component not de same
    char* ComponentPtr = ptr + Layout.StartComponentArray[column] + (Layout.ComponentSize[column] * row);
    assert(EndPtr > ComponentPtr);
    //std::cout << "    Adres: " << static_cast<const void*>(ComponentPtr) << "\n";
    //if (is_aligned(ComponentPtr, ComponentAlayments[column]))
    //    std::cout << "    aligned \n";
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