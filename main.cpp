#include <iostream>
#include "Entity_Component_System/ArchetypeContainer.h"
#include <chrono>
#include <algorithm>
#include <array>
#include <entt/entt.hpp>

template<typename T>
void AddComponent(Archetype& archetype) {
    //std::cout << "Add Comp2 Size: " << sizeof(T) << ", alig: " << alignof(T) << "\n";
    archetype.Components.push_back(typeid(T).hash_code());
    archetype.Component_properties.push_back({ typeid(T).hash_code(), sizeof(T), alignof(T) });
}

template<typename T>
void SetComponent(size_t index, Block& block, size_t index_Component, T& component) {
    block.Set(index, index_Component, &component, sizeof(T));
}

template<typename T>
T* GetComponetPtr(size_t index, Block& block, size_t index_Component) {
    return (T*)(block.GetPtr(index, index_Component));
}

template<typename T>
T GetComponent(size_t index, Block& block, size_t index_Component) {
    T component;
    block.GetCopy(index, index_Component, &component, sizeof(T));
    return component;
}

struct Comp1 {
    float x=0.0f, y=0.0f, z=0.0f;
};
struct Comp2 {
    long long s = 0;
    bool t = true;
};

void TestBlock(ArchetypeContainer& container) {
    Comp1 C1;
    for (Block* block : container.eachBlcok()) {
        for (int i = 0; i < block->GetSize(); i++) {
            block->Set(i, 0, &C1, sizeof(C1));
        }
    }
    Comp2 C2;
    for (Block* block : container.eachBlcok()) {
        for (int i = 0; i < block->GetSize(); i++) {
            block->Set(i, 1, &C2, sizeof(C2));
        }
    }

    for (Block* block : container.eachBlcok()) {
        for (int i = 0; i < block->GetSize(); i++) {
            Comp1* c = (Comp1*)block->GetPtr(i, 0);
            c->x += 100.0f * i;
        }
    }
    for (Block* block : container.eachBlcok()) {
        for (int i = 0; i < block->GetSize(); i++) {
            Comp2* c = (Comp2*)block->GetPtr(i, 1);
            c->s += 100 * i;
        }
    }
}

#define TestSize 5000

void Testentt(entt::registry& registry, std::vector<entt::entity>& entitys) {
    Comp1 c1;
    for (entt::entity entity : entitys) {
        registry.emplace<Comp1>(entity, c1);
    }
    Comp2 c2;
    for (entt::entity entity : entitys) {
        registry.emplace<Comp2>(entity, c2);
    }
    auto viewc1 = registry.view<Comp1>();
    viewc1.each([](auto& c1) {c1.x += 100.5f; });
    auto viewc2 = registry.view<Comp2>();
    viewc2.each([](auto& c2) {c2.s += 100; });
}

int main(){
    {
        // entity component system
        Archetype archetype;
        archetype.ID = 1;

        AddComponent<Comp1>(archetype);
        AddComponent<Comp2>(archetype);

        auto start = std::chrono::high_resolution_clock::now();
        ArchetypeContainer container(archetype);
        for (int i = 0; i<TestSize; i++)
            container.AddEntity(i);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time create Block: "
            << duration.count() << " microseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        TestBlock(container);
        stop = std::chrono::high_resolution_clock::now();

        duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken Block: "
            << duration.count() << " microseconds \n" << std::endl;
        container.RemoveEntity(1);
        //for (Block* block : container.eachBlcok()) {
        //    for (int i = 0; i < block->GetSize(); i++) {
        //        Comp1* c = (Comp1*)block->GetPtr(i, 0);
        //        Comp2* c2 = (Comp2*)block->GetPtr(i, 1);
        //        std::cout << "ptr: " << (void*)c << ", xyz: " << c->x << ", " << c->y << ", " << c->z << ", st: " << c2->s << ", " << c2->t << "\n";
        //    }
        //}
        //std::cout << "\n";
    }
    {
        // entt
        auto start = std::chrono::high_resolution_clock::now();
        entt::registry registry;
        std::vector<entt::entity> entitys;
        for (int i = 0; i < TestSize; i++) {
            entitys.push_back(registry.create());
        }
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Create registry + entitys: "
            << duration.count() << " microseconds" << std::endl;
        start = std::chrono::high_resolution_clock::now();
        Testentt(registry, entitys);
        stop = std::chrono::high_resolution_clock::now();

        duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken entt: "
            << duration.count() << " microseconds" << std::endl;
    }
    return 0;
}