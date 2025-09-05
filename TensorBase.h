#pragma once

#define MIND_TENSOR_NULL NULL
#define MIND_FALSE false
#define MIND_TRUE true

#include <vector>
#include <memory>

namespace Mind
{
    template <typename _T>
    struct TensorStorage
    {
    private:
        _T *_Tensor = MIND_TENSOR_NULL;
        size_t _Size = 0;

    public:
        _T *Data() { return _Tensor; }

        size_t Size() const { return _Size; }

        _T &operator[](int i)
        {
            if (i >= _Size)
                INVOKE_TENSOR_ERROR("Given index is greater than the Size of: " << _Size);
            return _Tensor[i];
        }

        bool Init(size_t AllocCount)
        {
            if (_Size > 0)
            {
                _T *NewTensor = (_T *)malloc(sizeof(_T) * AllocCount);

                // Copy data to newtensor
                if (AllocCount > _Size)
                    memcpy(NewTensor, _Tensor, _Size * sizeof(_T));
                else
                    memcpy(NewTensor, _Tensor, AllocCount * sizeof(_T));

                free(_Tensor);
                _Size = AllocCount;
                _Tensor = NewTensor;

                return MIND_TRUE;
            }

            _Tensor = (_T *)malloc(sizeof(_T) * AllocCount);
            if (_Tensor == NULL)
            {
                INVOKE_TENSOR_ERROR("Allocating " << AllocCount << " Failed!");
                return MIND_FALSE;
            }
            _Size = AllocCount;
            return MIND_TRUE;
        }

        bool Free()
        {
            if (Empty() == true)
                return MIND_FALSE;

            if (_Tensor == MIND_TENSOR_NULL)
                return MIND_FALSE;
            free(_Tensor);

            PRINT("Tensor Freed: " << _Size * sizeof(_T));

            _Tensor = MIND_TENSOR_NULL;
            _Size = 0;
            return MIND_TRUE;
        }

        bool Empty() const
        {
            return _Size == 0;
        }
    };

    template <typename _T>
    struct TensorMetaData
    {
        // Holds the pointer to the Type T data
        TensorStorage<_T> *_Storage = NULL;
        std::vector<int> _Dims;
        std::vector<int> _Stride;
        // Stores shapes and etc
        int Count = 0;
        // How much the tensor we are showing is offseted from start
        int __Offset = 0;

        // Poiints to the slice of the tensor this view is interpreting
        _T *_Data_Ptr = NULL;

        TensorMetaData() {}
        ~TensorMetaData()
        {
            PRINT("Meta Data Freed");
            _Data_Ptr = NULL;
        }

        _T &at(const std::initializer_list<int> &idx) const
        {
            if (idx.size() != _Dims.size())
                INVOKE_TENSOR_ERROR("Given list of indexes dont match the dimensions")

            int Index = 0;
            int dimindex = 0;
            for (auto &i : idx)
            {
                if (dimindex + 1 == _Dims.size())
                    Index += i;
                else
                    Index += i * _Stride[dimindex];
                dimindex++;
            }
            if (Index > Count)
                INVOKE_TENSOR_ERROR("Given list of index cant be used!")
            return this->_Data_Ptr[Index];
        }

        std::shared_ptr<TensorMetaData<_T>> at(int i)
        {
            return this->Slice(i);
        }

        int NDims() const { return _Dims.size(); }

        _T &operator[](const std::initializer_list<int> &idx)
        {
            return this->at(idx);
        }

        const _T &operator[](const std::initializer_list<int> &idx) const
        {
            return this->at(idx);
        }

        std::shared_ptr<TensorMetaData<_T>> operator[](int i)
        {
            return this->Slice(i);
        }

        void __CalculateStride()
        {
            if (NDims() == 1)
            {
                _Stride.resize(1);
                _Stride.emplace_back(1);
                return;
            }

            _Stride.reserve(_Dims.size() - 1);

            for (int i = 0; i < _Dims.size() - 1; i++)
            {
                int stride = 1;
                for (int j = 1 + i; j < _Dims.size(); j++)
                    stride *= _Dims[j];
                _Stride.push_back(stride);
            }
        }

        // TODO: Make our tensorstorage global
        void Init(TensorStorage<_T> *StrPtr, const std::initializer_list<int> &IDims, int Offset)
        {
            if (_Dims.size() != IDims.size())
            { // First load the dim to our dimensions array
                _Dims.reserve(IDims.size());
                for (auto &i : IDims)
                    _Dims.push_back(i);
            }

            // Calculate stride and count
            this->__CalculateStride();
            this->Count = 1;
            for (auto &d : _Dims)
                this->Count *= d;

            if (Count > StrPtr->Size())
            {
            }

            // Now for data_ptr and tensorstorage
            this->_Storage = StrPtr;
            this->_Data_Ptr = _Storage->Data() + Offset;
            this->__Offset = Offset;
        }

        // TODO: Make our tensorstorage global
        void Init(TensorStorage<_T> *StrPtr, const std::vector<int> &IDims, int Offset)
        {
            if (_Dims.size() != IDims.size())
            { // First load the dim to our dimensions array
                _Dims.reserve(IDims.size());
                for (auto &i : IDims)
                    _Dims.push_back(i);
            }

            // Calculate stride and count
            this->__CalculateStride();
            this->Count = 1;
            for (auto &d : _Dims)
                this->Count *= d;

            if (Count > StrPtr->Size())
            {
                INVOKE_TENSOR_ERROR("The dimensions with the total count of elements surpass the size of tensor!")
                // TODO: i guess make it resize
            }

            // Now for data_ptr and tensorstorage
            this->_Storage = StrPtr;
            this->_Data_Ptr = _Storage->Data() + Offset;
            this->__Offset = Offset;
        }

        void Init()
        {
        }

        std::shared_ptr<TensorMetaData<_T>> Slice(int i) const
        {
            if (i > _Dims[0])
                INVOKE_TENSOR_ERROR("Given i is greater than first dimensions!")

            std::shared_ptr<Mind::TensorMetaData<float>> SliceData = std::make_shared<Mind::TensorMetaData<float>>();
            if (NDims() >= 2)
            {
                SliceData->_Dims.reserve(NDims() - 1);
                for (int x = 1; x < NDims(); x++)
                {
                    SliceData->_Dims.push_back(_Dims[x]);
                }
                SliceData->Init(this->_Storage, SliceData->_Dims, this->__Offset + i * _Stride[0]);
            }
            return SliceData;
        }

        float &Get(int i)
        {
            return _Data_Ptr[i];
        }

        void Fill(const _T &value)
        {
            for (int i = 0; i < Count; i++)
            {
                _Data_Ptr[i] = value;
            }
        }

        void Push_Back(int idx, const _T &val)
        {
            // TODO: Validate the index exists
            _Data_Ptr[idx] = val;
        }

        bool Empty() const { return _Storage->Empty(); }
    };
} // namespace Mind
