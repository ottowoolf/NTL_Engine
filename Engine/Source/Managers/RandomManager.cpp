#include "Managers/RandomManager.h"

int RandomManager::Int(int min, int max)
{
    return std::uniform_int_distribution<int>(min, max)(randomGenerator_);
}

float RandomManager::Float(float min, float max)
{
    return std::uniform_real_distribution<float>(min, max)(randomGenerator_);
}

bool RandomManager::Bool(float probability)
{
    return std::bernoulli_distribution(probability)(randomGenerator_);
}

sf::Vector2f RandomManager::Position(sf::Vector2f min, sf::Vector2f max)
{
    return {Float(min.x, max.x), Float(min.y, max.y)};
}

sf::Angle RandomManager::Angle(sf::Angle min, sf::Angle max)
{
    return sf::degrees(Float(min.asDegrees(), max.asDegrees()));
}

sf::Color RandomManager::Color(sf::Color min, sf::Color max)
{
    return {(uint8_t)Int(std::min(min.r, max.r), std::max(min.r, max.r)), (uint8_t)Int(std::min(min.g, max.g), std::max(min.g, max.g)), (uint8_t)Int(std::min(min.b, max.b), std::max(min.b, max.b))};
}
