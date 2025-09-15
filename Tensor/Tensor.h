#pragma once

#include "TensorBase.h"

namespace Tensor
{
    class Tensor
    {
        public:
        private:
            std::shared_ptr<TensorMetaData<float>> _Data;
    };
} // namespace Tensor
