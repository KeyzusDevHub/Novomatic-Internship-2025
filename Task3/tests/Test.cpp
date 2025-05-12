#include <gtest/gtest.h>
#include "config.hpp"
#include "FloatType.hpp"
#include "Binary.hpp"

TEST(FloatTypeTest, ZeroAddition) {
    FloatTypeI0 input(2.0f);
    FloatTypeI0::AddOp add;

    FloatTypeI0 result = calculate(0, input, add);
    EXPECT_TRUE(result == FloatTypeI0::identity());
}

TEST(FloatTypeTest, SingleAddition) {
    FloatTypeI0 input(2.5f);
    FloatTypeI0::AddOp add;

    FloatTypeI0 result = calculate(1, input, add);
    EXPECT_TRUE(result == FloatTypeI0(2.5f));
}

TEST(FloatTypeTest, Addition1) {
    FloatTypeI0 input(2.5f);
    FloatTypeI0::AddOp add;

    FloatTypeI0 result = calculate(3, input, add);
    EXPECT_TRUE(result == FloatTypeI0(7.5f));
}

TEST(FloatTypeTest, Addition2) {
    FloatTypeI0 input(3.1f);
    FloatTypeI0::AddOp add;

    FloatTypeI0 result = calculate(10, input, add);
    EXPECT_TRUE(result == FloatTypeI0(31.0f));
}

TEST(FloatTypeTest, Addition3) {
    FloatTypeI0 input(5.1f);
    FloatTypeI0::AddOp add;

    FloatTypeI0 result = calculate(5, input, add);
    EXPECT_TRUE(result == FloatTypeI0(25.5f));
}

TEST(FloatTypeTest, ZeroMultiplication) {
    FloatTypeI1 input(2.0f);
    FloatTypeI1::MultiplyOp mul;

    FloatType result = calculate(0, input, mul);
    EXPECT_TRUE(result == FloatTypeI1::identity());
}

TEST(FloatTypeTest, SingleMultiplication) {
    FloatTypeI1 input(2.0f);
    FloatTypeI1::MultiplyOp mul;

    FloatType result = calculate(1, input, mul);
    EXPECT_TRUE(result == FloatTypeI1(2.0f));
}

TEST(FloatTypeTest, Multiplication1) {
    FloatTypeI1 input(2.0f);
    FloatTypeI1::MultiplyOp mul;

    FloatType result = calculate(3, input, mul);
    EXPECT_TRUE(result == FloatTypeI1(8.0f));
}

TEST(FloatTypeTest, Multiplication2) {
    FloatTypeI1 input(3.3f);
    FloatTypeI1::MultiplyOp mul;

    FloatType result = calculate(5, input, mul);
    EXPECT_TRUE(result == FloatTypeI1(std::pow(3.3, 5)));
}

TEST(FloatTypeTest, Multiplication3) {
    FloatTypeI1 input(2.0f);
    FloatTypeI1::MultiplyOp mul;

    FloatType result = calculate(10, input, mul);
    EXPECT_TRUE(result == FloatTypeI1(1024.0f));
}