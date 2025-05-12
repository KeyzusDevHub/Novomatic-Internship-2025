#include <gtest/gtest.h>
#include "Triangle.hpp"
#include "config.hpp"

TEST(TriangleCollisionTest, InsideAnother) {
    triangle outer(-0.5f, -0.5f,
                   0.5f, -0.5f,
                   0.0f,  0.5f);

    triangle inner(-0.1f, -0.1f,
                    0.1f, -0.1f,
                    0.0f,  0.1f);

    EXPECT_TRUE(isColliding(outer, inner));
}


TEST(TriangleCollisionTest, SharedEdge) {
    triangle t1(0.0f, 0.0f,
                1.0f, 0.0f,
                0.5f, 1.0f);

    triangle t2(0.0f, 0.0f,
                1.0f, 0.0f,
                0.5f, -1.0f);

    EXPECT_TRUE(isColliding(t1, t2));
}

TEST(TriangleCollisionTest, SharedVertex) {
    triangle t1(0.0f, 0.0f,
                1.0f, 0.0f,
                0.0f, 1.0f);

    triangle t2(0.0f, 0.0f,
               -1.0f, 0.0f,
                0.0f, -1.0f);

    EXPECT_TRUE(isColliding(t1, t2));
}

TEST(TriangleCollisionTest, PointOnEdge) {
    triangle t1(0.0f, 0.0f,
                1.0f, 0.0f,
                0.5f, 1.0f);

    triangle t2(0.5f, 0.0f,
                1.5f, 0.5f,
                1.5f, -0.5f);

    EXPECT_TRUE(isColliding(t1, t2));
}

TEST(TriangleCollisionTest, VertexInsideTriangle) {

    triangle t1(0.0f, 0.0f,
                1.0f, 0.0f,
                0.5f, 1.0f);

    triangle t2(0.5f, 0.25f,
                1.5f, 0.5f,
                1.5f, -0.5f);

    EXPECT_TRUE(isColliding(t1, t2));
}

TEST(TriangleCollisionTest, FarApart1) {
    triangle t1(0.0f, 0.0f,
                1.0f, 0.0f,
                0.5f, 1.0f);

    triangle t2(2.0f, 2.0f,
                3.0f, 2.0f,
                2.5f, 3.0f);

    EXPECT_FALSE(isColliding(t1, t2));
}

TEST(TriangleCollisionTest, FarApart2) {
    triangle t1(0.0f, 0.0f,
                2.0f, 0.0f,
                1.0f, 2.0f);

    triangle t2(2.0f, 2.0f,
                4.0f, 2.0f,
                3.0f, 4.0f);

    EXPECT_FALSE(isColliding(t1, t2));
}

TEST(TriangleCollisionTest, CloseVertex) {
    triangle t1(0.0f, 0.0f,
                2.0f, 0.0f,
                1.0f, 2.0f);

    triangle t2(2.01f, 0.0f,
                3.0f, 1.0f,
                3.0f, -1.0f);

    EXPECT_FALSE(isColliding(t1, t2));
}

TEST(TriangleCollisionTest, MultipleTriangles1) {

    triangle t1(0.0f, 0.0f,
                2.0f, 0.0f,
                1.0f, 2.0f);

    triangle t2(1.0f, 0.0f,
                3.0f, 0.0f,
                2.0f, 2.0f);

    triangle t3(4.0f, 0.0f,
                6.0f, 0.0f,
                5.0f, 2.0f);

    EXPECT_TRUE(isColliding(t1, t2));

    EXPECT_FALSE(isColliding(t1, t3));

    EXPECT_FALSE(isColliding(t2, t3));
}

TEST(TriangleCollisionTest, MultipleTriangles2) {
    triangle t1(0.0f, 0.0f,
                2.0f, 0.0f,
                1.0f, 2.0f);

    triangle t2(1.0f, 0.0f,
                3.0f, 0.0f,
                2.0f, 2.0f);

    triangle t3(1.5f, 0.5f,
                3.0f, 0.5f,
                2.5f, 2.5f);

    EXPECT_TRUE(isColliding(t1, t2));

    EXPECT_TRUE(isColliding(t2, t3));

    EXPECT_TRUE(isColliding(t1, t3));
}

TEST(TriangleCollisionTest, MultipleTriangles3) {

    triangle t1(0.0f, 0.0f,
                2.0f, 0.0f,
                1.0f, 2.0f);

    triangle t2(3.0f, 0.0f,
                5.0f, 0.0f,
                4.0f, 2.0f);

    triangle t3(6.0f, 0.0f,
                8.0f, 0.0f,
                7.0f, 2.0f);

    triangle t4(9.0f, 0.0f,
                11.0f, 0.0f,
                10.0f, 2.0f);

    EXPECT_FALSE(isColliding(t1, t2));

    EXPECT_FALSE(isColliding(t1, t3));

    EXPECT_FALSE(isColliding(t1, t4));

    EXPECT_FALSE(isColliding(t2, t3));

    EXPECT_FALSE(isColliding(t2, t4));

    EXPECT_FALSE(isColliding(t3, t4));
}