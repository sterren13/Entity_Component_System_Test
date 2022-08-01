//
// Created by sterr on 30-7-2022.
//

#ifndef ENTITY_COMPONENT_SYSTEM_TEST_ALOCATOR_H
#define ENTITY_COMPONENT_SYSTEM_TEST_ALOCATOR_H
#include <cstdlib>

template <typename T, size_t size>
class ArrayPtr {
public:
    ArrayPtr() {
        void* p =  malloc(size * sizeof(T));
        ptr = new(p) T[size];
    }

    ~ArrayPtr() {
        free(ptr);
    }

    T& operator[](size_t idx) {
        return ptr[idx];
    }
private:
    T* ptr = nullptr;
};


template <typename T, size_t size>
class AlignedArrayPtr {
public:
    AlignedArrayPtr() {
        void* p = _aligned_malloc(sizeof(T) * size, alignof(T));
        ptr = new(p) T[size];
    }

    ~AlignedArrayPtr() {
        for (size_t i = 0; i < size; i++) {
            ptr[i].~T();
        }
        _aligned_free(ptr);
    }

    T& operator[](size_t idx) {
        return ptr[idx];
    }
private:
    T* ptr = nullptr;
};

typedef std::chrono::high_resolution_clock Clock;
#define SIZE 100000
#define SAMPELS 10000
#define RIALOCAT_SAMPELS 20

int main(void) {
    long long NormalTime = 0;
    long long Aligned = 0;

    for (int j = 0; j < RIALOCAT_SAMPELS; j++) {
        std::cout << "Re allocate: " << j << " :";
        progressbar bar(SAMPELS*2);
        // test normal array
        {
            ArrayPtr < C, SIZE > t;
            for (int f = 0; f < SAMPELS; f++) {
                // normal array
                auto t1 = Clock::now();
                for (size_t i = 0; i < SIZE; i++) {
                    t[i].B++;
                    t[i].T = t[i].B * t[i].B;
                }
                auto t2 = Clock::now();

                NormalTime += (t2 - t1).count();
                bar.update();
            }
        }
        // test aligned array
        {
            AlignedArrayPtr < C, SIZE> test;
            for (int f = 0; f < SAMPELS; f++) {
                auto t3 = Clock::now();
                for (size_t i = 0; i < SIZE; i++) {
                    test[i].B++;
                    test[i].T = test[i].B * test[i].B;
                }
                auto t4 = Clock::now();
                Aligned += (t4 - t3).count();
                bar.update();
            }
        }
        std::cout << std::endl;
    }
    std::cout << "Normal array time:  " << NormalTime/ (SAMPELS * RIALOCAT_SAMPELS) << "\n";
    std::cout << "Aligned array time: " << Aligned / (SAMPELS * RIALOCAT_SAMPELS) << "\n";
    return 0;
}
#endif //ENTITY_COMPONENT_SYSTEM_TEST_ALOCATOR_H
