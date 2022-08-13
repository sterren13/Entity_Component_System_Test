//
// Created by sterr on 5-8-2022.
//

#include "Archetype.h"
#include "../CustomECS/Archetype.h"

#include <algorithm>

bool Archetype::HasComponent(ComponentTypeID Component){
    auto it = std::find(Components.begin(), Components.end(), Component);
    if (it == Components.end()){
        return false;
    }
    return true;
}

ArchetypeID Mix(ArchetypeID State, ComponentTypeID ComponentHash){
    return (State * ComponentHash) ^ ((State << 3) + (ComponentHash >> 2));
}

ArchetypeID CreateHash(Archetype& archetype){
    ArchetypeID StartState = 0xA6A6A6A6;

    for (ComponentTypeID component : archetype.Components)
        StartState = Mix(StartState, component);

    return StartState;
}