//
// Created by sterr on 30-7-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ECS_H


class ECS {
public:
    ECS();
    ~ECS();

    void CreateEntity(); // TODO make entity id type
    void RegisterComponent(); // TODO make component id
    bool IsComponentRegistered(); // TODO make component id
    void* AddComponent(void* Data_ptr); // TODO add entity id, add component id
    void RemoveComponent(); // TODO add component id
    void* GedComponent(); // TODO add entity id
    bool HasComponent(); // TODO add component id
    void RemoveEntity(); // TODO add entity id

private:

};


#endif //ENTITY_COMPONENT_SYSTEM_TEST_ECS_H
