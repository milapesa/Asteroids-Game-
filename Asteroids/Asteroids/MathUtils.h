#pragma once
#include <SFML/System/Vector2.hpp>

class MathUtils
{

public:
	/** Checks whether vector is near to zero within a specified tolerance */
    static bool isNearlyZero(float number);
	
    /** Normalizes the  given vector */
    static sf::Vector2f normalize(const sf::Vector2f& vec);

	/** Returns the lenght of the given vector */
    static float len(const sf::Vector2f vec);

	/** Rotates a vector with a given degree */
    static sf::Vector2f rot(const sf::Vector2f vec, float deg);

	/** Returns a random float between min and max */
    static float randRange(float min, float max);

    static float dot(const sf::Vector2f& a, const sf::Vector2f& b);

    static float angle(const sf::Vector2f& a, const sf::Vector2f& b);
};
