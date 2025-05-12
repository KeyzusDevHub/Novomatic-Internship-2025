#include "FloatType.hpp"

FloatType::FloatType(float v) : value(v) {}

FloatTypeI0 FloatTypeI0::identity() {
    return FloatTypeI0(0.0f);
}

FloatTypeI1 FloatTypeI1::identity() {
    return FloatTypeI1(1.0f);
}

FloatTypeI0 FloatTypeI0::AddOp::operator()(const FloatTypeI0& a, const FloatTypeI0& b) const {
    return FloatTypeI0(a.value + b.value);
}

FloatTypeI1 FloatTypeI1::MultiplyOp::operator()(const FloatTypeI1& a, const FloatTypeI1& b) const {
    return FloatTypeI1(a.value * b.value);
}