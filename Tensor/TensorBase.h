#pragma once

#define TENSOR_NULLPTR nullptr

/*
    A Single Array contaning millions of arrays -> TensorStorage

*/
#include <error.h>
#define TESOR_INVOKE_ERROR(x)              \
    {                                      \
        std::cout << x << "\n";            \
        throw std::runtime_error("Error"); \
    }

namespace Tensor
{
    template <typename _T>
    class TensorStorage
    {
    public:
        // Returns the Count of elements in our Tensor Array
        int Count() const { return _Count; }
        // Return Data pointer of our tensor
        _T *Data() { return _Tensor; }
        const _T *Data() const { return _Tensor; }

        _T &operator[](int i)
        {
            if (i > Count() - 1)
                TESOR_INVOKE_ERROR("Index greater than in TensorStorage");
            return _Tensor[i];
        }

        const _T &operator[](int i) const
        {
            if (i > Count() - 1)
                TESOR_INVOKE_ERROR("Index greater than in TensorStorage");
            return _Tensor[i];
        }

        int GetOffset(int Count)
        {
            _NextOffset += Count;
            return _NextOffset - Count;
        }

        // Handles purely the allocation of the Tensor Array
        void _Alloc(int NewSize)
        {
            // When Tensor has not been allocated memory
            if (_Tensor == TENSOR_NULLPTR && _Count == 0)
            {
                // WHen there is no Allocation
                // TODO: make custom alloc function
                _Tensor = (_T *)malloc(int(NewSize * sizeof(_T)));
                _Count = NewSize;

                return;
            }
            // IF there is already data in Tensor

            _T *Temp = (_T *)malloc(NewSize * sizeof(_T));

            // Copy data to newtensor
            if (NewSize > _Count)
                memcpy(Temp, _Tensor, _Count * sizeof(_T));
            else
                memcpy(Temp, _Tensor, NewSize * sizeof(_T));
            delete[] _Tensor;
            _Tensor = Temp;
            _Count = NewSize;
        }

        bool Exist() const { return Count() > 0; }

        // We free and delete our tensor
        void Free()
        {
            if (!Exist())
                return;
            // WE set all variables of count and offset to 0 effectively reseting
            free(_Tensor);
            _Tensor = TENSOR_NULLPTR;
            _Count = 0;
            _NextOffset = 0;
        }

    private:
        _T *_Tensor = TENSOR_NULLPTR;
        int _Count = 0;
        int _NextOffset = 0;
    };

    template <typename _T>
    class TensorMetaData
    {
    public:
        TensorMetaData() {}
        ~TensorMetaData() {}

        int NDims() const { return _Dims.size(); }
        int Count() const { return _Count; }

        _T *Data() { return _StrPtr->Data() + _Offset; }
        const _T *Data() const { return _StrPtr->Data() + _Offset; }

        _T *Flatten() { return Data(); }
        const _T *Flatten() const { return Data(); }

        void _CalculateStride()
        {
            _Stride.resize(_Dims.size());
            for (int i = 0; i < _Stride.size(); i++)
            {
                _Stride[i] = 1;
                if (i != _Stride.size() - 1)
                    for (int j = i + 1; j < _Dims.size(); j++)
                        _Stride[i] *= _Dims[j];
            }
        }

        void _CalculateCount()
        {
            _Count = 1;
            for (auto &dim : _Dims)
                _Count *= dim;
        }

        void Init(TensorStorage<_T> *StrPtr, const std::initializer_list<int> &IDims)
        {
            _Dims.reserve(IDims.size());
            for (auto &dim : IDims)
                _Dims.push_back(dim);

            _CalculateCount();
            _CalculateStride();

            _StrPtr = StrPtr;
            _Offset = StrPtr->GetOffset(_Count);
        }

        _T &Get(const std::vector<int> &dims)
        {
            return Get(dims.begin(), dims.end());
        }

        _T &Get(const std::initializer_list<int> &dims)
        {
            if (dims.size() != _Dims.size())
                TESOR_INVOKE_ERROR("Dims dont match")
            // Flatten the index
            int FinalIndex = 0;
            {
                int i = 0;
                for (auto dim : dims)
                {
                    FinalIndex += dim * _Stride[i];
                    i++;
                }
            }
            return Data()[FinalIndex];
        }

        using Iterator = _T *;
        using Const_Iterator = const _T *;

        Iterator begin() { return Data(); }
        Iterator end() { return Data() + Count(); }

    private:
        TensorStorage<_T> *_StrPtr;
        std::vector<int> _Dims, _Stride;
        // Offset in our StrPtr
        int _Offset = 0;
        int _Count = 0;
    };
} // namespace Tensor
