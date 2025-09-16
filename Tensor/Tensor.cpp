#include <iostream>
#include <vector>
#include <memory>
#include <sstream>
#include "Tensor.h"

namespace Tensor
{
    Tensor Tensor::Flatten(TensorStorage<float> *StrPtr)
    {
        auto NewData = std::make_shared<TensorMetaData<float>>();
        NewData->Init(StrPtr, {this->Count()}, _Data->Offset());

        Tensor FlatTensor;
        FlatTensor.Init(NewData);
        return FlatTensor;
    }

    Tensor Tensor::operator[](int i)
    {
        Tensor NewTensor;
        NewTensor.Init(this->_Data->Slice(i));
        return NewTensor;
    }

    void Tensor::PrintInfo()
    {
        std::cout << "NDims: " << NDims() << "\n";
        std::cout << "Count: " << Count() << "\n";
        std::cout << "Dims: [";

        for (int i = 0; i < NDims(); i++)
            if (i == NDims() - 1)
                std::cout << Dims()[i];
            else
                std::cout << Dims()[i] << ",";

        std::cout << "]\n";
        std::cout << "Size In Bytes: " << Count() * sizeof(float) << "\n";
    }

    Tensor &Tensor::operator=(float i)
    {
        if (NDims() > 1)
        {
            std::cout << NDims() << " Dim Tensor cant be assgined a single float\n";
            return *this;
        }

        operator[]({0}) = i;

        return *this;
    }

    void Tensor::_PrintRecursive(int dim, std::stringstream &os, int Offset)
    {
        if (NDims() - dim - 1 == 0)
        {
            for (int i = 0; i < Dims()[dim]; i++)
                if (i == Dims()[dim] - 1)
                    os << Data()[i + Offset];

                else
                    os << Data()[i + Offset] << ",";
            return;
        }

        for (int i = 0; i < Dims()[dim]; i++)
        {
            os << "[";
            _PrintRecursive(dim + 1, os, i * Stride()[dim]);

            if (i == Dims()[dim] - 1)
                os << "]";
            else
                os << "],";
        }
    }

    void Tensor::Print()
    {
        std::stringstream os;

        if (NDims() == 1)
        {
            os << "[";

            for (int i = 0; i < Count(); i++)
            {
                if (i != Count() - 1)
                    os << Get({i}) << ",";
                else
                    os << Get({i});
            }

            os << "]";
        }

        if (NDims() >= 2)
        {
            os << "[";

            for (int i = 0; i < Dims()[0]; i++)
            {
                os << "[";
                _PrintRecursive(1, os, i * Stride()[0]);

                if (i == Dims()[0] - 1)
                    os << "]";
                else
                    os << "],";
            }

            std::cout << os.str() << "\n";
        }
    } // namespace Tensor

    void Tensor::SetShape(TensorStorage<float>* StrPtr, const std::initializer_list<int> &NewDims)
    {
        // TODO: Put inside a wrapper SIngelton to know what what is freed and as much as possible lessen reallocations
        auto NewData = std::make_shared<TensorMetaData<float>>();
        NewData->Init(StrPtr, NewDims);
        
        
    }
}
