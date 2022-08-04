//
// Created by sterr on 1-8-2022.
//

#include "ArchetypeContainer.h"

ArchetypeContainer::ArchetypeContainer(Archetype& archetype){
    // calculate buffer layout
    size_t RelativelyAdress = 0;
    size_t MaxAlignment = 1;
    std::vector<size_t> ComponentArrayAlignments;
    for (TypeComponent component : archetype.Component_properties) {
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

}

void ArchetypeContainer::AddEntity(EntityID entityId){

}

void ArchetypeContainer::RemoveEntity(EntityID entity){

}

void ArchetypeContainer::GetCompoent(EntityID entity, ComponentTypeID Component,void* DestenationPtr){

}