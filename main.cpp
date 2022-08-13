#include <iostream>
#include <chrono>
#include <entt/entt.hpp>

struct Comp1 {
    float x=0.0f, y=0.0f, z=0.0f;
};
struct Comp2 {
    long long s = 0;
    bool t = true;
};
struct Comp3 {
    bool p = true;
    bool c = false;
};
struct Comp4 {
    long test = 0;
    long test2 = 5;
};

void TestEnttAddComponents(entt::registry& registry, std::vector<entt::entity>& entitys) {
    Comp1 c1;
    for (entt::entity entity : entitys) {
        registry.emplace<Comp1>(entity, c1);
    }
    Comp2 c2;
    for (entt::entity entity : entitys) {
        registry.emplace<Comp2>(entity, c2);
    }
}

void TestenttSystems(entt::registry& registry) {
    
    auto viewc1 = registry.view<Comp1>();
    viewc1.each([](auto& c1) {c1.x += 100.5f; });
    auto viewc2 = registry.view<Comp2>();
    viewc2.each([](auto& c2) {c2.s += 100; });
}

#define TestSize 1000

int main(){
    {
        auto start = std::chrono::high_resolution_clock::now();

        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "ECS: Create registry + entitys: "
            << duration.count() << " microseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();

        stop = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken Add components ECS: "
            << duration.count() << " microseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();

        stop = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken Run Systems ECS: "
            << duration.count() << " microseconds" << "\n" << std::endl;
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
        std::cout << "entt: Create registry + entitys: "
            << duration.count() << " microseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        TestEnttAddComponents(registry, entitys);
        stop = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken add components entt: "
            << duration.count() << " microseconds" << std::endl;

        start = std::chrono::high_resolution_clock::now();
        TestenttSystems(registry);
        stop = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "Time taken run systems entt: "
            << duration.count() << " microseconds" << std::endl;
    }
    return 0;
}