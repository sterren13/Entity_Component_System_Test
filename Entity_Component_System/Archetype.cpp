//
// Created by sterr on 5-8-2022.
//

#include "Archetype.h"
#include <algorithm>

bool Archetype::HasComponent(ComponentTypeID Component){
    auto it = std::find(Components.begin(), Components.end(), Component);
    if (it == Components.end()){
        return false;
    }
    return true;
}