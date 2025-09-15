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
        Tensor Flatten();

        int NDims() const { return _Data->NDims(); }
        int Count() const { return _Data->Count(); }

        float &operator[](const std::initializer_list<int> &dims) { return _Data->Get(dims); }
        const float &operator[](const std::initializer_list<int> &dims) const { return _Data->Get(dims); }

    private:
        std::shared_ptr<TensorMetaData<float>> _Data;
    };
} // namespace Tensor
