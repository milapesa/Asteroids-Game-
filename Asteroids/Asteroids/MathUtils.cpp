#include "MathUtils.h"
#include <cmath>

bool MathUtils::isNearlyZero(float number)
{
    return std::abs(number) < 0.0001f;
}

sf::Vector2f MathUtils::normalize(const sf::Vector2f& vec)
{
    const float length = len(vec);
    if (isNearlyZero(length))
    {
        return {0, 0};
    }
    return {vec.x / length, vec.y / length};
}

float MathUtils::len(const sf::Vector2f vec)
{
    return std::sqrt(vec.x * vec.x + vec.y * vec.y);
}

sf::Vector2f MathUtils::rot(const sf::Vector2f vec, float deg)
{
    constexpr float r = 3.14159265F / 180;
    sf::Vector2f out;
    out.x = vec.x * std::cos(r * deg) - vec.y * std::sin(r * deg);
    out.y = vec.x * std::sin(r * deg) + vec.y * std::cos(r * deg);
    return out;
}

float MathUtils::randRange(float min, float max)
{
    return min + static_cast<float>(rand()) / static_cast<float>(RAND_MAX / (max - min));
}

float MathUtils::dot(const sf::Vector2f& a, const sf::Vector2f& b)
{
    return a.x * b.x + a.y * b.y;
}

float MathUtils::angle(const sf::Vector2f& a, const sf::Vector2f& b)
{
    const float det = a.x * b.y - a.y * b.x;
    return atan2(det, dot(a, b));
}
