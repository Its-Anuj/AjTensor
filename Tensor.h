#pragma once

#define SCRATCH_NULLPTR nullptr
// If this is true then __Tensor__Base__ will apply a adaptive padding to the size amount in the capacity decreasing allocations but on deletion simply size
// and capacity equal
#define SCRATCH_TENSOR_SIZE_MULTIPLIER true

#define SCRATCH_TRUE true
#define SCRATCH_FALSE false

#ifdef SCRATCH_BUILD_DEBUG
#define SCRATCH_DEBUG SCRATCH_TRUE
#elif SCRATCH_BUILD_RELEASE
#define SCRATCH_DEBUG SCRATCH_FALSE
#endif
#include <DebugTimer.h>
#include <cstdlib> // For malloc and free

// TODO: Implement operator* as cross prodcut

#define INVOKE_TENSOR_ERROR(x)                      \
    {                                               \
        std::cout << "[TENSOR ERROR]" << x << "\n"; \
        throw std::runtime_error("Error");          \
    }
#include "TensorBase.h"

namespace Mind
{
    using TensorFloat = TensorMetaData<float>;

    struct Tensor
    {
    public:
        using iterator = float *;
        using const_iterator = const float *;

        void Init(TensorStorage<float> *StrPtr, const std::initializer_list<int> &Dims, int Offset)
        {
            _Data = std::make_shared<TensorMetaData<float>>();
            _Data->Init(StrPtr, Dims, Offset);
        }
        bool Init(std::shared_ptr<TensorMetaData<float>> Ptr)
        {
            _Data = Ptr;
            return true;
        }

        float &operator[](const std::initializer_list<int> &idx)
        {
            return _Data->at(idx);
        }

        const float &operator[](const std::initializer_list<int> &idx) const
        {
            return _Data->at(idx);
        }

        Tensor operator[](int idx)
        {
            Tensor NewTensor;
            NewTensor.Init(this->_Data->Slice(idx));
            return NewTensor;
        }

        Tensor operator[](int idx) const
        {
            Tensor NewTensor;
            NewTensor.Init(this->_Data->Slice(idx));
            return NewTensor;
        }

        int Count() const { return _Data->Count; }
        int NDims() const { return _Data->NDims(); }

        const std::vector<int> &Shape() const { return _Data->_Dims; }
        const std::vector<int> &Dims() const { return _Data->_Dims; }

        void PrintInfo();
        void Print();
        void _Print(std::stringstream &ss, int cdim, int i);

        void Fill(float x);

        bool Empty() const { return _Data->Empty(); }

        iterator begin() { return _Data->_Data_Ptr; }
        iterator end() { return _Data->_Data_Ptr + Count(); }

        const_iterator begin() const { return _Data->_Data_Ptr; }
        const_iterator end() const { return _Data->_Data_Ptr + Count(); }

    private:
        std::shared_ptr<TensorMetaData<float>> _Data;
    };

    // Arithmetic operatrions

    void Multiply(Tensor &tensor, float scalar);
    void Divide(Tensor &tensor, float scalar);
    void Add(Tensor &tensor, float scalar);
    void Subtract(Tensor &tensor, float scalar);

    void Range(Tensor &tensor, float start, float end);
} // namespace Mind
