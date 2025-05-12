#ifndef _TRIANGLE_HPP_
#define _TRIANGLE_HPP_

#include "config.hpp"

struct vec2 {
    float x, y;

    vec2(float x_, float y_);
    vec2(const vec2& other);
    vec2(vec2&& other) noexcept;
};

struct triangle {
    std::array<vec2, 3> points;
    vec2 position;
    float rotation;

    triangle(vec2 p1, vec2 p2, vec2 p3);
    triangle(float x1, float y1, float x2, float y2, float x3, float y3);
    triangle(std::array<vec2, 3> pts);
    ~triangle() = default;

    std::array<float, 6> arrayRepresentation();
    std::array<vec2, 3> pointsWithTransition() const;
    void changeRotation(float angle);
    void changePosition(float x, float y);
};

bool isColliding(triangle const& t1, triangle const& t2);

#endif