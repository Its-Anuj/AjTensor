#include <iostream>
#include <string>
#include <ostream>
#include <sstream>
#define PRINT(x)        \
    {                   \
        std::cout << x; \
    }
#define PRINTLN(x)              \
    {                           \
        std::cout << x << "\n"; \
    }
#include "Tensor.h"

namespace Mind
{
    void Tensor::PrintInfo()
    {
        PRINTLN("Count: " << Count());
        PRINT("Dims: [");
        for (auto &dim : this->Dims())
            PRINT(dim << ",")
        PRINTLN("]")
        PRINTLN("Size: " << sizeof(float) * Count());
    }

    void Tensor::Print()
    {
        std::stringstream ss;

        ss << "[";
        for (int i = 0; i < Dims()[0]; i++)
        {
            ss << "[";
            _Print(ss, 1, i * _Data->_Stride[0]);

            if (i + 1 == Dims()[0])
                ss << "]";
            else
                ss << "],";
        }
        ss << "]";

        PRINTLN(ss.str());
    }

    void Tensor::_Print(std::stringstream &ss, int cdim, int x)
    {
        // If we still have further parent dimensions we go to them
        if (NDims() - cdim > 1)
        {
            for (int i = 0; i < Dims()[cdim]; i++)
            {
                ss << "[";
                // We give offset
                _Print(ss, cdim + 1, x + i * this->_Data->_Stride[cdim]);

                if (i + 1 == Dims()[cdim])
                    ss << "]";
                else
                    ss << "],";
            }
            return;
        }
        for (int i = 0; i < Dims()[cdim]; i++)
        {
            if (i + 1 == Dims()[cdim])
                ss << this->_Data->Get(i + x);
            else
                ss << this->_Data->Get(i + x) << ',';
        }
    }

    void Tensor::Fill(float x)
    {
        _Data->Fill(x);
    }

    // ---- Airthmetic operations ----

    void Multiply(Tensor &tensor, float scalar)
    {
        if (tensor.Empty() == true)
            return;
        for (auto &x : tensor)
            x *= scalar;
    }

    void Divide(Tensor &tensor, float scalar)
    {
        if (tensor.Empty() == true)
            return;
        for (auto &x : tensor)
            x /= scalar;
    }

    void Add(Tensor &tensor, float scalar)
    {
        if (tensor.Empty() == true)
            return;
        for (auto &x : tensor)
            x += scalar;
    }

    void Subtract(Tensor &tensor, float scalar)
    {
        if (tensor.Empty() == true)
            return;
        for (auto &x : tensor)
            x /= scalar;
    }

    void Range(Tensor &tensor, float start, float end)
    {
        float step = (end - start) / (tensor.Count() - 1);
        int i = 0;
        for (auto &x : tensor)
        {
            x = start + i * step;;
            i++;
        }
    }
} // namespace Mind
