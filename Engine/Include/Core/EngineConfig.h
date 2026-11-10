#pragma once

#include <SFML/System/Vector2.hpp>

#include <string>

struct EngineConfig
{
    sf::Vector2f windowSize;
    std::string windowTitle;

    bool disableSfmlLogs;

    EngineConfig();
};

inline const EngineConfig gConfig;