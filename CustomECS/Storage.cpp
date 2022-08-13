//
// Created by sterr on 11-8-2022.
//

#include "Storage.h"
#include <cassert>

Storage::Storage() {

}

Storage::~Storage() {

}

Archetype_ID Storage::CreateArchetype(ArchetypeBuilder &builder) {
    // sort component bay size
    // sort tag bay id
    // add sizes and aliment
    return 0;
}

Archetype *Storage::GetArchetype(Archetype_ID archetypeId) {
    assert(ArchetypeID.find(archetypeId) == ArchetypeID.end()); // check of archetype exist
    return ArchetypeID[archetypeId];
}
