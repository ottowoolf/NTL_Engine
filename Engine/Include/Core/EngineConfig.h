#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

#include <string>

struct EngineConfig
{
    sf::Vector2f windowSize;
    std::string windowTitle;
    bool disableSfmlLogs;
    sf::Time maximumDeltaTime;

    EngineConfig();
};

inline const EngineConfig gConfig;