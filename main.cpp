#include <iostream>
#include <type_traits>
#define ERRORE(msg) std::cout << "[Error] " << msg << "\n";

// https://unix.stackexchange.com/questions/94809/know-when-a-memory-address-is-aligned-or-unaligned

struct TypeComponent {
    TypeComponent(const size_t s, const size_t a) : Size(s), Alignment(a) {}
    const size_t Size;
    const size_t Alignment;
};

template<typename T>
TypeComponent CreateTypeComponent() {
    std::cout << typeid(T).name() << ": Size = " << sizeof(T) << " alig: " << alignof(T) << "\n";
    TypeComponent type(sizeof(T), alignof(T));
    return type;
}

template<size_t size>
class Chunk {
public:
    Chunk() {
        if(!isPowerOfTwo(size)) ERRORE("No opwer of 2");
        ptr = _mm_malloc(size,16);
        AbsoluutEndAdres = static_cast<char*>(ptr);
        std::cout << "Start adres= " << ptr << "\n";
    }
    ~Chunk() {
        _mm_free(ptr);
    }

    template <typename T>
    void AddComponent(void* Data, TypeComponent Type) {
        size_t pend = reinterpret_cast<size_t>(AbsoluutEndAdres) % (Type.Size + Type.Alignment);
        if ((CurrentEndAdres + Type.Alignment + Type.Size + pend) > size) {
            ERRORE("Out of range");
            return;
        }
        memcpy(AbsoluutEndAdres + pend, Data, Type.Size);
        if (((reinterpret_cast<size_t>(AbsoluutEndAdres)) & 0x3)){
            ERRORE("not aligned");
            std::cout << "Pending bits = " << pend << "\n";
            std::cout << "Adres = " << reinterpret_cast<size_t>(AbsoluutEndAdres) << "\n";
        }
;
        AbsoluutEndAdres += Type.Size + Type.Alignment + pend;
        CurrentEndAdres += Type.Size + Type.Alignment + pend;
    }

private:
    bool isPowerOfTwo(size_t n) {
        return (ceil(log2(n)) == floor(log2(n)));
    }
    void* ptr = nullptr;
    size_t CurrentEndAdres = 0;
    char* AbsoluutEndAdres = nullptr;
};

struct TestComp1 {
    float x = 0.0f, y = 0.0f, z = 0.0f;
};

struct TestComp2 {
    //int Held = 10;
    bool Deat = true;
};

int main(){
    //Chunk<64> c;
    //TestComp1 t1;
    //c.AddComponent<TestComp1>(&t1, CreateTypeComponent<TestComp1>());
    //TestComp2 t2;
    //c.AddComponent<TestComp2>(&t2, CreateTypeComponent<TestComp2>());
    //c.AddComponent<TestComp1>(&t1, CreateTypeComponent<TestComp1>());
    //std::cout << "Hallo World!!! \n";
    std::cout << 85 % 16 << "\n";
    size_t a = 5/2;
    std::cout << a << "\n";
    return 0;
}