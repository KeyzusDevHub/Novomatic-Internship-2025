#ifndef _FLOATTYPE_HPP_
#define _FLOATTYPE_HPP_

#include "config.hpp"

class FloatType {
    public:
        float value;

        FloatType(float v);

        static FloatType identity();

        friend std::ostream& operator<<(std::ostream& os, const FloatType& mi) {
            return os << mi.value;
        }

        bool operator==(const FloatType& other) const {
            return std::abs(value - other.value) < 1e-4;
        }
};

class FloatTypeI1 : public FloatType{
    public:
    
        using FloatType::FloatType;
    
        static FloatTypeI1 identity();
    
        struct MultiplyOp {
            FloatTypeI1 operator()(const FloatTypeI1& a, const FloatTypeI1& b) const;
        };
};

class FloatTypeI0 : public FloatType {
    public:
    
        using FloatType::FloatType;
    
        static FloatTypeI0 identity();
    
        struct AddOp {
            FloatTypeI0 operator()(const FloatTypeI0& a, const FloatTypeI0& b) const;
        };
};

#endif