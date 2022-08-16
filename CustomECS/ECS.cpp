//
// Created by sterr on 12-8-2022.
//

#include "ECS.h"

ECS::ECS() : storage(my_ComponentManger) {

}

ECS::~ECS() {

}

Entity_ID ECS::CreateID() {
    // TODO EntityIDGenerator
    storage.AddID(0);
}

void ECS::Set(Entity_ID entity, Type_ID TypeID, size_t Size, void *ptr) {
    Archetype* archetype = storage.GetArchetype(EntityIndex[entity].Archetype);
    if (archetype->HasComponent(TypeID)){
        // TODO set data
        return;
    }

    ArchetypeBuilder builder = archetype->GetBuilder();
    builder.Components.push_back({TypeID});
    Storage::CalculateArchetypeID(builder);

    if(storage.HasArchtype(builder.ID)){
        // TODO move entity to archetype
        // TODO set component data
    } else{
        // TODO create archetype
        // TODO move entity to archetype
        // TODO set component data
    }
}

void ECS::Add(Entity_ID entity, Type_ID TypeID) {
    Archetype* archetype = storage.GetArchetype(EntityIndex[entity].Archetype);
    if (archetype->HasComponent(TypeID))
        return;

    ArchetypeBuilder builder = archetype->GetBuilder();
    builder.Tags.push_back(TypeID);
    Storage::CalculateArchetypeID(builder);

    if(storage.HasArchtype(builder.ID)){
        // TODO move entity to archetype
    } else{
        // TODO create archetype
        // TODO move entity to archetype
    }
}

bool ECS::HasComponent(Entity_ID entity, Type_ID ComponentID) {
    return storage.GetArchetype(EntityIndex[entity].Archetype)->HasComponent(ComponentID);
}

void *ECS::GetComponent(Entity_ID entity, Type_ID ComponentID) {
    Record entityRecord = EntityIndex[entity];
    if (storage.GetArchetype(entityRecord.Archetype)->HasComponent(ComponentID))
        return storage.GetArchetype(entityRecord.Archetype)->GetComponentPtr(ComponentID, entityRecord.row);
    else
        return nullptr;
}

void ECS::RegisterComponent(Type_ID ComponentID, size_t size, size_t Alignment) {
    my_ComponentManger.RegisterComponent(ComponentID, size, Alignment);
}

bool ECS::IsComponentRegistered(Type_ID ComponentID) {
    return my_ComponentManger.isComponentRegistered(ComponentID);
}

Component &ECS::GetComponentProb(Type_ID ComponentID) {
    return my_ComponentManger.GetComponent(ComponentID);
}
