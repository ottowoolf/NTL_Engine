#pragma once

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

class TimeManager
{
private:
    sf::Clock clock_;
    sf::Time deltaTime_;
    sf::Time previousTime_;

public:
    float GetDeltaTime();
    float GetElapsedTime();

private:
    friend class Engine;

    void Update();
};