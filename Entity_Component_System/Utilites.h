//
// Created by sterr on 6-8-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_UTILITES_H
#define ENTITY_COMPONENT_SYSTEM_TEST_UTILITES_H
#include <functional>
#include <numeric>

template<class T> struct DefaultFuncComparar {
    bool operator()(T const& a, T const& b) {
        return a < b;
    }
};

template<class T, class U, class FuncComparar = std::function<bool(T const&, T const&)>>
void OrdenarVectores( std::vector<T>& a, std::vector<U>& b, FuncComparar comparar = DefaultFuncComparar<T>()) {
    std::vector<T> copiaA{a}; std::vector<U> copiaB{b};
    std::vector<std::size_t> vector_indices(a.size());
    std::iota(vector_indices.begin(), vector_indices.end(), 0);
    std::sort(vector_indices.begin(), vector_indices.end(), [&](std::size_t i, std::size_t j){
        return comparar(a[i], a[j]);
    });
    std::transform(vector_indices.begin(), vector_indices.end(), a.begin(), [&](std::size_t i){ return copiaA[i]; });
    std::transform(vector_indices.begin(), vector_indices.end(), b.begin(), [&](std::size_t i){ return copiaB[i]; });
}

#endif //ENTITY_COMPONENT_SYSTEM_TEST_UTILITES_H
