//
// Created by sterr on 31-7-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_COMPONENT_H
#define ENTITY_COMPONENT_SYSTEM_TEST_COMPONENT_H
#include "TypeIdGenerator.h"

struct TypeComponent {
    const ComponentTypeID ID;
    const size_t Size;
    const size_t Alignment;
};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_COMPONENT_H
