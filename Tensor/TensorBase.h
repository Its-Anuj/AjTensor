#pragma once

namespace Tensor
{
    template <typename _T>
    class TensorStorage
    {
    public:
    private:
        _T *_Tensor;
        int _Count;
        int _NextOffset;
    };

    template <typename _T>
    class TensorMetaData
    {
    public:
    private:
        TensorStorage<_T> *_StrPtr;
        std::vector<int> _Dims, _Stride;
    };
} // namespace Tensor
