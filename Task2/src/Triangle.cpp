#include "Triangle.hpp"

vec2::vec2(float x_, float y_) : x(x_), y(y_) {}

vec2::vec2(const vec2& other) : x(other.x), y(other.y) {}

vec2::vec2(vec2&& other) noexcept : x(other.x), y(other.y) {}

triangle::triangle(vec2 p1, vec2 p2, vec2 p3) : points{p1, p2, p3}, position(0.0f, 0.0f), rotation(0.0f) {}

triangle::triangle(float x1, float y1, float x2, float y2, float x3, float y3)
    : points{vec2(x1, y1), vec2(x2, y2), vec2(x3, y3)}, position(0.0f, 0.0f), rotation(0.0f) {}

triangle::triangle(std::array<vec2, 3> pts) : points(pts), position(0.0f, 0.0f), rotation(0.0f) {}

std::array<float, 6> triangle::arrayRepresentation(){
    float radians = rotation * (std::numbers::pi / 180.0f);
    float cosA = std::cos(radians);
    float sinA = std::sin(radians);

    std::array<float, 6> vertices = {
        points[0].x * cosA - points[0].y * sinA + position.x, points[0].x * sinA + points[0].y * cosA + position.y,
        points[1].x * cosA - points[1].y * sinA + position.x, points[1].x * sinA + points[1].y * cosA + position.y,
        points[2].x * cosA - points[2].y * sinA + position.x, points[2].x * sinA + points[2].y * cosA + position.y
    };
    return vertices;
}

std::array<vec2, 3> triangle::pointsWithTransition() const{
    float radians = rotation * (std::numbers::pi / 180.0f);
    float cosA = std::cos(radians);
    float sinA = std::sin(radians);

    std::array<vec2, 3> vertices = {
        vec2(points[0].x * cosA - points[0].y * sinA + position.x, points[0].x * sinA + points[0].y * cosA + position.y),
        vec2(points[1].x * cosA - points[1].y * sinA + position.x, points[1].x * sinA + points[1].y * cosA + position.y),
        vec2(points[2].x * cosA - points[2].y * sinA + position.x, points[2].x * sinA + points[2].y * cosA + position.y)
    };
    return vertices;
}

void triangle::changeRotation(float angle){
    rotation += angle;
}

void triangle::changePosition(float x, float y){
    position.x += x;
    position.y += y;
}

vec2 getNormal(vec2 const& a, vec2 const& b) {
    float dx = b.x - a.x;
    float dy = b.y - a.y;
    return vec2(-dy, dx);
}

float dot(vec2 const& a, vec2 const& b) {
    return a.x * b.x + a.y * b.y;
}

void projectPolygon(std::array<vec2, 3> const& points, vec2 const& axis, float& min, float& max) {
    min = max = dot(points[0], axis);
    for (int i = 1; i < 3; ++i) {
        float projection = dot(points[i], axis);
        if (projection < min) min = projection;
        if (projection > max) max = projection;
    }
}

bool isSeparated(vec2 const& axis, std::array<vec2, 3> const& pts1, std::array<vec2, 3> const& pts2) {
    float min1, max1, min2, max2;
    projectPolygon(pts1, axis, min1, max1);
    projectPolygon(pts2, axis, min2, max2);
    return max1 < min2 || max2 < min1;
}

bool isColliding(triangle const& t1, triangle const& t2) {
    std::array<vec2, 3> pts1 = t1.pointsWithTransition();
    std::array<vec2, 3> pts2 = t2.pointsWithTransition();

    auto hasSeparatingAxis = [&](const std::array<vec2, 3>& ptsA, const std::array<vec2, 3>& ptsB) {
        return std::ranges::any_of(std::views::iota(0, 3), [&](int i) {
            vec2 a = ptsA[i];
            vec2 b = ptsA[(i + 1) % 3];
            vec2 axis = getNormal(a, b);
            return isSeparated(axis, pts1, pts2);
        });
    };

    if (hasSeparatingAxis(pts1, pts2)) return false;
    if (hasSeparatingAxis(pts2, pts1)) return false;

    return true;
}