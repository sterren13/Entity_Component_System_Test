//
// Created by sterr on 11-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_TYPES_H
#define ENTITY_COMPONENT_SYSTEM_TEST_TYPES_H
#include <cstdint>
#include <unordered_set>

typedef size_t IDType;
typedef IDType Entity_ID;
typedef IDType Archetype_ID;
typedef IDType Type_ID;

typedef std::unordered_set<Archetype_ID> ArchetypeSet;

struct  Record {
    Archetype_ID Archetype;
    size_t row;
};

#endif //ENTITY_COMPONENT_SYSTEM_TEST_TYPES_H
