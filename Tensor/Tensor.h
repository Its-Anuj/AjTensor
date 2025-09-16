#pragma once

#include "TensorBase.h"

namespace Tensor
{
    class Tensor
    {
    public:
        Tensor() {}
        ~Tensor() {}

        inline void Init(TensorStorage<float> *StrPtr, const std::initializer_list<int> &IDims)
        {
            _Data = std::make_shared<TensorMetaData<float>>();
            _Data->Init(StrPtr, IDims);
        }

        void Init(std::shared_ptr<TensorMetaData<float>> data) { _Data = data; }

        float &at(const std::initializer_list<int> &dims) { return _Data->Get(dims); }
        const float &at(const std::initializer_list<int> &dims) const { return _Data->Get(dims); }

        // Preferably a Tensor
        Tensor Flatten(TensorStorage<float> *StrPtr);

        float *Data() { return _Data->Data(); }
        const float *Data() const { return _Data->Data(); }

        const std::vector<int> &Dims() const { return _Data->Dims(); }
        const std::vector<int> &Stride() const { return _Data->Stride(); }

        int NDims() const { return _Data->NDims(); }
        int Count() const { return _Data->Count(); }

        Tensor operator[](int i);

        float &Get(const std::initializer_list<int> &dims) { return _Data->Get(dims); }
        const float &Get(const std::initializer_list<int> &dims) const { return _Data->Get(dims); }

        float &operator[](const std::initializer_list<int> &dims) { return _Data->Get(dims); }
        const float &operator[](const std::initializer_list<int> &dims) const { return _Data->Get(dims); }

        void PrintInfo();
        void Fill(float x) { _Data->Fill(x); }

        Tensor &operator=(float i);

        void _PrintRecursive(int dim, std::stringstream &os, int Offset);
        void Print();

        void SetShape(TensorStorage<float> *StrPtr, const std::initializer_list<int> &NewDims);

    private:
        std::shared_ptr<TensorMetaData<float>> _Data;
    };
} // namespace Tensor
