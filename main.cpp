#include <iostream>
#include <vector>
#include <memory>
#include "Tensor.h"

#define PRINT(x)        \
    {                   \
        std::cout << x; \
    }
#define PRINTLN(x)              \
    {                           \
        std::cout << x << "\n"; \
    }

int main(int, char **)
{
    Tensor::TensorStorage<float> Storage;
    Storage._Alloc(10);
    for (int i = 0; i < 10; i++)
    {
        Storage[i] = i;
    }

    Tensor::Tensor Tensor;
    Tensor.Init(&Storage, {2, 3});
    std::cout << Tensor[{0, 2}] << "\n";

    Storage.Free();
}
