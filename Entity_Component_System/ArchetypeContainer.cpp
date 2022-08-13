//
// Created by sterr on 1-8-2022.
//

#include "ArchetypeContainer.h"

ArchetypeContainer::ArchetypeContainer(Archetype& archetype, std::unordered_map<ArchetypeID , TypeComponent>& Components){
    // calculate buffer layout
    size_t RelativelyAdress = 0;
    size_t MaxAlignment = 1;
    std::vector<size_t> ComponentArrayAlignments;
    for (ComponentTypeID componentID : archetype.Components) { // TODO make component map
        // get component
        TypeComponent component = Components[componentID];
        // add component size's
        Layout.ComponentSize.push_back(component.Size);
        RelativelyAdress += component.Size;

        // get max size alignment
        if (MaxAlignment < component.Alignment)
            MaxAlignment = component.Alignment;

        // caculate alignment
        size_t PendingBinds = RelativelyAdress % component.Alignment;
        ComponentArrayAlignments.push_back(PendingBinds);
        RelativelyAdress += PendingBinds;
    }

    // set max
    Layout.Alignment = MaxAlignment;

    // caculate rows
    Layout.Rows = Block::GetBufferSize() / RelativelyAdress;
    Layout.Columns = Layout.ComponentSize.size();

    Layout.StartComponentArray.push_back(0);
    RelativelyAdress = (Layout.ComponentSize[0] * Layout.Rows) + ComponentArrayAlignments[0];
    for (int i = 1; i < Layout.Columns; i++) {
        Layout.StartComponentArray.push_back(RelativelyAdress);
        RelativelyAdress += (Layout.ComponentSize[i] * Layout.Rows) + ComponentArrayAlignments[0];
    }
    // TODO check of buffer groot genoeg is voor mintstens een component
}

ArchetypeContainer::~ArchetypeContainer(){
    for (Block* block : Blocks) {
        delete block;
    }
}

void ArchetypeContainer::AddEntity(EntityID entity){
    // lock for space for entity in blocks
    for (auto it = Blocks.begin(); it != Blocks.end(); ++it){
        if ((*it)->HasFreeSlot()){
            size_t index = (*it)->AddEntity();
            size_t BlockIndex = it - Blocks.begin();
            EntityMap.push_back({entity,{BlockIndex, index}});
            return;
        }
    }
    // no free space in blocks --> create new block en add entity to block
    Blocks.push_back(new Block(Layout));
    size_t BlockIndex = Blocks.back()->GetSize();
    size_t index = Blocks.back()->AddEntity();
    EntityMap.push_back({entity,{BlockIndex, index}});
}

void ArchetypeContainer::RemoveEntity(EntityID entity){ // TODO change all entity after removed entity in block
    EntityLocation location = GetEntityLocation(entity); // find location
    Blocks[location.BlockIndex]->RemoveEntity(location.Index); // remove entity from block
    for (std::pair<EntityID, EntityLocation>& element : EntityMap) {
        if ((location.BlockIndex == element.second.BlockIndex) && (location.Index < element.second.Index)) {
            element.second.Index--;
        }
    }
    EntityMap.erase(GetEnity(entity)); // remove entity form entity map
}

void ArchetypeContainer::GetCompoent(EntityID entity, ComponentTypeID Component,void* DestenationPtr){
    EntityLocation location = GetEntityLocation(entity); // find location
    // find component index
    size_t ComponentIndex = Layout.ComponentMap[Component];
    Blocks[location.BlockIndex]->GetCopy(location.Index, ComponentIndex, DestenationPtr, Layout.ComponentSize[Component]); // copy data to ptr
}

void* ArchetypeContainer::GetComponentPtr(EntityID entity, ComponentTypeID Component){
    EntityLocation location = GetEntityLocation(entity); // find location
    // find component index
    size_t ComponentIndex = Layout.ComponentMap[Component];
    return Blocks[ComponentIndex]->GetPtr(location.Index, ComponentIndex);
}

std::vector<std::pair<EntityID, EntityLocation>>::iterator ArchetypeContainer::GetEnity(EntityID entity) {
    return std::find_if(EntityMap.begin(), EntityMap.end(), [&](std::pair<EntityID, EntityLocation> element) {
        return element.first == entity;
        });
}

EntityLocation ArchetypeContainer::GetEntityLocation(EntityID entity) {
    return GetEnity(entity)->second;
}