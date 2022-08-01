//
// Created by sterr on 31-7-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_TYPEIDGENERATOR_H
#define ENTITY_COMPONENT_SYSTEM_TEST_TYPEIDGENERATOR_H
#include <cstdint>

#if defined(__LP64__) || defined(_WIN64) || (defined(__x86_64__) &&     !defined(__ILP32__) ) || defined(_M_X64) || defined(__ia64) || defined (_M_IA64) || defined(__aarch64__) || defined(__powerpc64__)
  typedef std::uint64_t IDType;
#else
  typedef std::uint32_t IDType;
#endif

typedef IDType EntityID;
typedef IDType EntityID;
typedef IDType ArchetypeID;
typedef IDType ComponentTypeID;
const IDType NULL_ENTITY = 0;

template<class T>
class TypeIDGenerator {
public:
    static const IDType GetNewID(){
        static const IDType idCounter = m_counter++;
        return idCounter;
    }
private:
    static IDType m_counter;
};

template<class T>
IDType TypeIDGenerator<T>::m_counter = 0;

#endif //ENTITY_COMPONENT_SYSTEM_TEST_TYPEIDGENERATOR_H
