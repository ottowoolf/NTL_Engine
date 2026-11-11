#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>

#include <string>

struct EngineConfig
{
    sf::Vector2f windowSize;
    std::string windowTitle;
    bool disableSfmlLogs;
    sf::Time maximumDeltaTime;
    float globalVolume;
    sf::Color backgroundColor;
    float cursorRadius;
    float cursorSpeed;
    sf::Color cursorColor;
    float joyStickDeadZone;
    bool showCursor;

    EngineConfig();
};

inline const EngineConfig gConfig;