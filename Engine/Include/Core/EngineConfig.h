#pragma once

#include <SFML/System/Vector2.hpp>

#include <string>

struct EngineConfig
{
    sf::Vector2f windowSize;
    std::string windowTitle;

    EngineConfig();
};

inline const EngineConfig gConfig;