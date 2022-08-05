//
// Created by sterr on 1-8-2022.
//

#include "ArchetypeContainer.h"

ArchetypeContainer::ArchetypeContainer(Archetype& archetype){
    // calculate buffer layout
    size_t RelativelyAdress = 0;
    size_t MaxAlignment = 1;
    std::vector<size_t> ComponentArrayAlignments;
    for (TypeComponent component : archetype.Component_properties) { // TODO make component map
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
        RelativelyAdress += (Layout.ComponentSize[0] * Layout.Rows) + ComponentArrayAlignments[0];
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
            EntityMap.insert({entity,{BlockIndex, index}});
            return;
        }
    }
    // no free space in blocks --> create new block en add entity to block
    Blocks.push_back(new Block(Layout));
    size_t BlockIndex = Blocks.back()->GetSize();
    size_t index = Blocks.back()->AddEntity();
    EntityMap.insert({entity,{BlockIndex, index}});
}

// TODO fix vector error
void ArchetypeContainer::RemoveEntity(EntityID entity){
    EntityLocation location = EntityMap[entity]; // find location
    Blocks[location.BlockIndex]->RemoveEntity(location.Index); // remove entity from block
    EntityMap.erase(entity); // remove entity form entity map
}

void ArchetypeContainer::GetCompoent(EntityID entity, ComponentTypeID Component,void* DestenationPtr){
    EntityLocation location = EntityMap[entity]; // find location
    // find component index
    size_t ComponentIndex = Layout.ComponentMap[Component];
    Blocks[location.BlockIndex]->GetCopy(location.Index, ComponentIndex, DestenationPtr, Layout.ComponentSize[Component]); // copy data to ptr
}