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
    Storage._Alloc(20);
    for (int i = 0; i < 20; i++)
    {
        Storage[i] = i;
    }

    Tensor::Tensor Tensor;
    Tensor.Init(&Storage, {2,2, 3});
    Tensor.Print();
    Tensor.PrintInfo();

    Storage.Free();
}
