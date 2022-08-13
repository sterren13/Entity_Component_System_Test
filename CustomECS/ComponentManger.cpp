//
// Created by sterr on 12-8-2022.
//

#include "ComponentManger.h"
#include "Utilites.h"

Type_ID From_typeid_to_ecs_typeid(size_t type_id){
    return Mix(COMPONENT_CONST_ID, type_id);
}

Type_ID CreatePair(Type_ID first, Type_ID second){
   Mix(first, second);
}

void ComponentManger::RegisterComponent(Type_ID ComponentID, size_t size, size_t Alignment) {
    ComponentIndex.insert({ComponentID, {ComponentID, size, Alignment}});
}

Component &ComponentManger::GetComponent(Type_ID ComponentID) {
    return ComponentIndex[ComponentID];
}

bool ComponentManger::isComponentRegistered(Type_ID ComponentID) {
    return ComponentIndex.find(ComponentID) != ComponentIndex.end();
}
