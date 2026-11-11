#pragma once

#include <SFML/System/Clock.hpp>

class Cooldown
{
private:
    sf::Clock clock_;
    float cooldownDuration_;

public:
    Cooldown(float cooldownDuration = 0);

    void Start();
    void Stop();

    void Restart();
    void Reset();

    void SetDuration(float cooldownDuration);
    float GetDuration() const;

    float GetElapsedTime() const;

    bool IsRunning() const;
    bool IsOver() const;
};