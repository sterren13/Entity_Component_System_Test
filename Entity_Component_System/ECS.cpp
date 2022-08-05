//
// Created by sterr on 30-7-2022.
//

#include "ECS.h"

ECS::ECS(){

}

ECS::~ECS(){

}

void ECS::CreateEntity(){

}

bool ECS::IsComponentRegistered(){
    return false;
}

void* ECS::AddComponent(void* Data_ptr){
// 1. stel niew arch type op voor entity
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
    return nullptr;
}

void ECS::RemoveComponent(){

}

void* ECS::GedComponent(){
    return nullptr;
}

bool ECS::HasComponent(){
    return false;
}

void ECS::RemoveEntity(){

}