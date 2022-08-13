//
// Created by sterr on 30-7-2022.
//

#include "ECS.h"
#include "Utilites.h"
#include <algorithm>

ECS::ECS(){

}

ECS::~ECS(){
    for (ArchetypeContainer* container : ArchetypeContainers){
        delete container;
    }
}

EntityID ECS::CreateEntity(){
    EntityID entityId = TypeIDGenerator<EntityID>::GetNewID();
    EntityArchetypeMap.emplace_back(entityId, 0); // add entity and 0 archtype
    return entityId;
}

void ECS::RemoveEntity(EntityID entity){
    ArchetypeID ID = GetEntityArchetypeFromEntity(entity);
    if (ID != 0){
        ArchetypeContainers[ArchetypeContainerMap[ID]]->RemoveEntity(entity);
    }
    EntityArchetypeMap.erase(FindEntity(entity));
}

void ECS::RegisterComponent(ComponentTypeID ID, size_t size, size_t Alignment){
    // TODO chek of component has registerd
    ComponentMap.insert({ID, {ID, size, Alignment}});
}

bool ECS::IsComponentRegister(ComponentTypeID ID){
    return ComponentMap.find(ID) == ComponentMap.end();
}

// 1. stel niew archtype op voor entity
// 2. chek of archt type al bestaat
// 2.1 arch type bestaat al
// 2.1.1 copy entity data to new archtypecontainer
// 2.1.2 remove entity from old archtypecontainer
// 2.1.3 change entity archtype in map
// 2.2 archtype bestaat niet
// 2.2.1 make newe archtypecontainer van newe arctype
// 2.2.2 copy enity data to new arctypecontainer
// 2.2.3 remove data entity old archtypecontainer
// 2.2.4 change entity archtype in map
void ECS::AddComponent(EntityID entity, ComponentTypeID componentTypeId){
    // TODO check of compoinent is registerd
    if (!GetEntityArchetypeFromEntity(entity) == 0) {
        if (!HasComponent(entity, componentTypeId)) {
            ArchetypeID oldID = GetEntityArchetypeFromEntity(entity);
            Archetype archetype = ArchetypeMap[oldID];
            archetype.Components.push_back(componentTypeId);
            // sort bay component size
            std::sort(archetype.Components.begin(), archetype.Components.end(),
                      [&](const ComponentTypeID &a, const ComponentTypeID &b) {
                          return ComponentMap[a].Size < ComponentMap[b].Size;
                      });
            archetype.ID = CreateHash(archetype);

            if (ArchetypeMap.find(archetype.ID) != ArchetypeMap.end()) {
                // move entity to new archetype container
                MoveEntity(entity, oldID, archetype.ID);
            } else {
                // create new archetype container
                CreateNewArchtypeContainer(archetype);
                // move entity to new archetype container
                MoveEntity(entity, oldID, archetype.ID);
            }
        } else {
            std::cout << "[Error] entity has component \n";
        }
    } else { // Component has no archetype
        Archetype archetype;
        archetype.Components.push_back(componentTypeId);
        archetype.ID = CreateHash(archetype);
        if (ArchetypeMap.find(archetype.ID) != ArchetypeMap.end()){ // archetype exist
            // add entity to archetype container
            ArchetypeContainers[ArchetypeContainerMap[entity]]->AddEntity(entity);
            FindEntity(entity)->second = archetype.ID;
        } else { // archetype dos not exist
            // create new archetype container
            CreateNewArchtypeContainer(archetype);
            // add entity to archetype container
            ArchetypeContainers[ArchetypeContainerMap[entity]]->AddEntity(entity);
            FindEntity(entity)->second = archetype.ID;
        }
    }
}

void ECS::RemoveComponent(){
    // TODO implement
}

void* ECS::GedComponent(EntityID entity, ComponentTypeID Component){
    // TODO check of entity exist
    // TODO Check of component is registerd
    ArchetypeID archetypeId = GetEntityArchetypeFromEntity(entity);
    size_t index = ArchetypeContainerMap[archetypeId];
    return ArchetypeContainers[index]->GetComponentPtr(entity, Component);
}

bool ECS::HasComponent(EntityID entity, ComponentTypeID Component){
    // TODO check of entity exist
    // TODO Check of component is registerd
    return ArchetypeMap[GetEntityArchetypeFromEntity(entity)].HasComponent(Component);
}

std::vector<std::pair<EntityID, ArchetypeID>>::iterator ECS::FindEntity(EntityID entity){
   return std::find_if(EntityArchetypeMap.begin(), EntityArchetypeMap.end(),
                           [&entity](std::pair<EntityID, ArchetypeID>& element) {
                               return element.first == entity;
                           });
}

ArchetypeID ECS::GetEntityArchetypeFromEntity(EntityID entity){
    return FindEntity(entity)->second;
}

void ECS::MoveEntity(EntityID entity, ArchetypeID OldArchetypeID, ArchetypeID NewArchetypeID){
    size_t oldindex = ArchetypeContainerMap[OldArchetypeID]; // get old container index
    size_t newIndex = ArchetypeContainerMap[NewArchetypeID]; // ge new container index
    // add entity to new archtype container
    ArchetypeContainers[newIndex]->AddEntity(entity);
    // copy entity data from old archtype container to new archtype container
    for (ComponentTypeID Component : ArchetypeMap[OldArchetypeID].Components){
        void* oldDataPtr = ArchetypeContainers[oldindex]->GetComponentPtr(entity, Component);
        void* newDataPtr = ArchetypeContainers[newIndex]->GetComponentPtr(entity, Component);
        memcpy(newDataPtr, oldDataPtr, ComponentMap[Component].Size);
    }
    // remove data in old archtype container
    ArchetypeContainers[oldindex]->RemoveEntity(entity);
    // change archtype id in entity map
    FindEntity(entity)->second = NewArchetypeID;
}

void ECS::CreateNewArchtypeContainer(Archetype& archetype){
    ArchetypeMap.insert({archetype.ID, archetype});
    size_t index = ArchetypeContainers.size();
    ArchetypeContainers.emplace_back(new ArchetypeContainer(archetype, ComponentMap));
    ArchetypeContainerMap.insert({archetype.ID, index});
}