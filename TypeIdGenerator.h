//
// Created by sterr on 29/07/2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_TYPEIDGENERATOR_H
#define ENTITY_COMPONENT_SYSTEM_TEST_TYPEIDGENERATOR_H

#include <cstdint>

typedef std::uint32_t IDType;
typedef IDType EntityID;
typedef IDType ComponentTypeID;

template<class T>
class TypeIdGenerator{
public:
    template<class U>
    static const IDType GetNewID(){
        static const IDType idCounter = m_count++;
        return idCounter;
    }
private:
    static IDType m_count;
};

template<class T> IDType TypeIdGenerator<T>::m_count = 0;


#endif //ENTITY_COMPONENT_SYSTEM_TEST_TYPEIDGENERATOR_H
