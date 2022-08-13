//
// Created by sterr on 12-8-2022.
//

#include "ECS.h"

ECS::ECS() {

}

ECS::~ECS() {

}

void ECS::AddEntity() {

}

void ECS::Set(Entity_ID entity, Type_ID TypeID, size_t Size, void *ptr) {

}

void ECS::Add(Entity_ID entity, Type_ID TypeID) {

}

bool ECS::HasComponent(Entity_ID entity, Type_ID ComponentID) {
    return false;
}

void *ECS::GetComponent(Entity_ID entity, Type_ID ComponentID) {
    return nullptr;
}
