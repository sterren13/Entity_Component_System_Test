//
// Created by sterr on 12-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_UTILITES_H
#define ENTITY_COMPONENT_SYSTEM_TEST_UTILITES_H
#include "Types.h"

Type_ID Mix(Type_ID first, Type_ID second){
     return (first * second) ^ ((first << 3) + (second >> 2));
}

#endif //ENTITY_COMPONENT_SYSTEM_TEST_UTILITES_H
