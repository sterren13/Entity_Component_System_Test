//
// Created by sterr on 11-8-2022.
//

#include "Storage.h"
#include <cassert>

Storage::Storage(ComponentManger& componentManger) : my_componentManger(componentManger) {
    ArchetypeBuilder builder;
    RootArchetype = new Archetype(builder);
}

Storage::~Storage() {
    for (std::pair<Archetype_ID, Archetype*> par : ArchetypeID)
        delete par.second;
}

Archetype_ID Mix(Archetype_ID State, Type_ID ComponentHash){
    return (State * ComponentHash) ^ ((State << 3) + (ComponentHash >> 2));
}

Archetype_ID Storage::CalculateArchetypeID(ArchetypeBuilder &builder) {
    // sort component bay size
    std::sort(builder.Components.begin(), builder.Components.end(),
              [&](const Component &a, const Component &b) {
                  return a.Size < b.Size;
              });
    // sort tag bay id
    std::sort(builder.Tags.begin(), builder.Tags.end(),
              [&](const Type_ID &a, const Type_ID &b) {
                  return a < b;
              });
    Archetype_ID State = 0xA6A6A6A6;
    for (Component Component : builder.Components)
        Mix(State, Component.ID);
    for (Type_ID Tag : builder.Tags)
        Mix(State, Tag);
    builder.ID = State;
    return State;
}

Archetype_ID Storage::CreateArchetype(ArchetypeBuilder &builder) {
    // add sizes and aliment
    for (Component& comp : builder.Components){
        comp.Size = my_componentManger.GetComponent(comp.ID).Size;
        comp.Alignment = my_componentManger.GetComponent(comp.ID).Alignment;
    }

    ArchetypeID.insert({builder.ID, new Archetype(builder)});

    // add archetype to sets
    // TODO add archetype to sets for component
    return 0;
}

Archetype *Storage::GetArchetype(Archetype_ID archetypeId) {
    assert(ArchetypeID.find(archetypeId) == ArchetypeID.end()); // check of archetype exist
    return ArchetypeID[archetypeId];
}

void Storage::AddID(Entity_ID id) {
    RootArchetype->AddEntity();
}

bool Storage::HasArchtype(Archetype_ID archetypeId) {
    return !(ArchetypeID.find(archetypeId) == ArchetypeID.end());
}
