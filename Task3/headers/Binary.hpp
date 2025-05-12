#ifndef _BINARY_HPP_
#define _BINARY_HPP_

#include "config.hpp"

template <class T, class Op>
concept IsSupported = requires(T first, T second, Op operation)
{
    { operation(first, second) } -> std::convertible_to<T>;
    { T::identity() } -> std::convertible_to<T>;
};
template <class BinaryOp, class ValueType>
    requires IsSupported<ValueType, BinaryOp>
ValueType calculate(int n, ValueType value, const BinaryOp& f) {
    ValueType result = ValueType::identity();
    while (n > 0) {
        if (n % 2 == 1) {
            result = f(result, value);
        }
        value = f(value, value);
        n /= 2;
    }
    return result;
}

#endif