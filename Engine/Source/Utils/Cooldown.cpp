#include "Utils/Cooldown.h"

#include <SFML/System/Time.hpp>

Cooldown::Cooldown(float cooldownDuration)
    : cooldownDuration_(cooldownDuration)
{
}

void Cooldown::Start()
{
    clock_.restart();
}

void Cooldown::Stop()
{
    clock_.stop();
}

void Cooldown::Restart()
{
    clock_.restart();
}

void Cooldown::Reset()
{
    clock_.reset();
}

void Cooldown::SetDuration(float cooldownDuration)
{
    cooldownDuration_ = cooldownDuration;
}

float Cooldown::GetDuration() const
{
    return cooldownDuration_;
}

float Cooldown::GetElapsedTime() const
{
    return clock_.getElapsedTime().asSeconds();
}

bool Cooldown::IsRunning() const
{
    return clock_.isRunning();
}

bool Cooldown::IsOver() const
{
    return GetElapsedTime() >= GetDuration();
}