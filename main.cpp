#include <iostream>
#include <string>
#define PRINT(x)                \
    {                           \
        std::cout << x << "\n"; \
    }
#include "Tensor.h"
#include <cstdlib>
static int _AllCount = 0;

void *operator new(size_t size)
{
    PRINT("Allocated " << size << " bytes");
    _AllCount++;
    return malloc(size);
}

void operator delete(void *ptr)
{
    PRINT("Deallocated");
    free(ptr);
}

void *operator new[](size_t size)
{
    PRINT("Allocated " << size << " bytes");
    _AllCount++;
    return malloc(size);
}

void operator delete[](void *ptr)
{
    PRINT("Deallocated");
    free(ptr);
}
using namespace Scratch;

int main(int, char **)
{
    Mind::TensorStorage<float> tensordata;
    tensordata.Init(40);

    {
        Mind::Tensor tensor;
        tensor.Init(&tensordata, {2, 10, 2}, 0);
        
        Mind::Range(tensor, 1.0f, 200.0f);

        Mind::Divide(tensor, 2.0f);

        tensor.Print();
        tensor.PrintInfo();
    }

    auto success = tensordata.Free();
    if (!success)
        INVOKE_TENSOR_ERROR("Freeing Tensor Data causes error!")
}
