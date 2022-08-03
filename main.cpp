#include <iostream>
#include "Entity_Component_System/Block.h"
#include <chrono>
#include <algorithm>
#include <array>

template<typename T>
void AddComponent(Archetype& archetype) {
    //std::cout << "Add Comp2 Size: " << sizeof(T) << ", alig: " << alignof(T) << "\n";
    archetype.Components.push_back(typeid(T).hash_code());
    archetype.Component_properties.push_back({ typeid(T).hash_code(), sizeof(T), alignof(T) });
}

template<typename T>
void SetComponent(size_t index, Block& block, Archetype& archtype, T& component) {
    size_t hashCode = typeid(T).hash_code();
    auto it = std::find(archtype.Components.begin(), archtype.Components.end(), hashCode);
    size_t index_Component = 0;
    if (it != archtype.Components.end()) {
        index_Component = it - archtype.Components.begin();
    }
    else {
        std::cout << "Error archtype bevat het component niet \n";
        return;
    }
    block.Set(index, index_Component, &component, sizeof(T));
}

template<typename T>
T* GetComponetPtr(size_t index, Block& block, Archetype& archtype) {
    size_t hashCode = typeid(T).hash_code();
    auto it = std::find(archtype.Components.begin(), archtype.Components.end(), hashCode);
    size_t index_Component = 0;
    if (it != archtype.Components.end()) {
        index_Component = it - archtype.Components.begin();
    }
    else {
        std::cout << "Error archtype bevat het component niet \n";
        return nullptr;
    }
    return (T*)(block.GetPtr(index, index_Component));
}

template<typename T>
T GetComponent(size_t index, Block& block, Archetype& archtype) {
    T component;
    size_t hashCode = typeid(T).hash_code();
    auto it = std::find(archtype.Components.begin(), archtype.Components.end(), hashCode);
    size_t index_Component = 0;
    if (it != archtype.Components.end()) {
        index_Component = it - archtype.Components.begin();
    }
    else {
        std::cout << "Error archtype bevat het component niet \n";
        return component;
    }
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

void TestBlock(Archetype& archetype) {
    Block block(archetype);
    Comp1 c1;
    for (int i = 0; i < block.GetNumberOfRows(); i++) {
        SetComponent<Comp1>(i, block, archetype, c1);
    }
    Comp2 c2;
    for (int i = 0; i < block.GetNumberOfRows(); i++) {
        SetComponent<Comp2>(i, block, archetype, c2);
        c2.s += 100;
    }
    for (int i = 0; i < block.GetNumberOfRows(); i++) {
        Comp1 c = GetComponent<Comp1>(i, block, archetype);
        //std::cout << "Comp1: " << c1ptr.x << ", " << c1ptr.y << ", " << c1ptr.z << "\n";
    }
    for (int i = 0; i < block.GetNumberOfRows(); i++) {
        Comp2 c = GetComponent<Comp2>(i, block, archetype);
        //std::cout << "Comp2: " << c.s << ", " << c.t << "\n";
    }
    return;
}

struct Combo {
    Comp1 c1;
    Comp2 c2;
};
void TestNatifArray() {
    std::array<Combo, 500> combo;
    Comp1 c1;
    for (int i = 0; i < 500; i++) {
        combo[i].c1 = c1;
    }
    Comp2 c2;
    for (int i = 0; i < 500; i++) {
        combo[i].c2 = c2;
        c2.s += 100;
    }
    for (int i = 0; i < 500; i++) {
        Comp1 c1ptr = combo[i].c1;
        //std::cout << "Comp1: " << c1ptr->x << ", " << c1ptr->y << ", " << c1ptr->z << "\n";
    }
    for (int i = 0; i < 500; i++) {
        Comp2 c = combo[i].c2;
        //std::cout << "Comp2: " << c.s << ", " << c.t << "\n";
    }
}

int main(){
    Archetype archetype;
    archetype.ID = 1;

    AddComponent<Comp1>(archetype);
    AddComponent<Comp2>(archetype);

    auto start = std::chrono::high_resolution_clock::now();
    TestBlock(archetype);
    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken Block: "
        << duration.count() << " microseconds" << std::endl;

    start = std::chrono::high_resolution_clock::now();
    TestNatifArray();
    stop = std::chrono::high_resolution_clock::now();

     duration = duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "Time taken Array: "
        << duration.count() << " microseconds" << std::endl;
    return 0;
}