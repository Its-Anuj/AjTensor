# AjTensor

AjTensor is an educational C++ implementation inspired by PyTorch's tensor architecture. It demonstrates a layered approach to tensor management, focusing on separation of concerns and encapsulation.

## Design Overview

AjTensor is built on three main components:

- **TensorStorage**: Handles raw memory allocation and data storage for tensors. This class is internal and not intended for direct user access.
- **TensorMetaData**: Manages metadata such as shape, stride, and offset. It provides methods for slicing, flattening, and element access.
- **Tensor**: The user-facing class, which holds a pointer to its associated `TensorMetaData`. All tensor operations are performed through this handle.

A singleton class, **TensorBase**, is planned to centrally manage all storage and metadata, further abstracting resource management from the user.

## Principles

- **Encapsulation**: Users interact only with the `Tensor` class. Direct access to `TensorStorage` is restricted.
- **Modularity**: Clear separation between storage, metadata, and tensor interface for flexibility and extensibility.
- **Centralized Control**: The `TensorBase` singleton will manage all storage and metadata objects.

## Example Usage

```cpp
#include "Tensor.h"

int main(int, char **)
{
    Tensor::TensorStorage<float> Storage;
    Storage._Alloc(20);
    for (int i = 0; i < 20; i++)
    {
        Storage[i] = i;
    }

    Tensor::Tensor Tensor;
    Tensor.Init(&Storage, {2, 2, 3});
    Tensor.Print();
    Tensor.PrintInfo();

    Storage.Free();
}

