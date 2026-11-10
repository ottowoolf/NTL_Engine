#include <algorithm>
#include "Managers/TimeManager.h"
#include "Core/EngineConfig.h"

void TimeManager::Update()
{
    const sf::Time currentTime = clock_.getElapsedTime();
    deltaTime_ = std::min(currentTime - previousTime_, gConfig.maximumDeltaTime);
    previousTime_ = currentTime;
}

float TimeManager::GetDeltaTime()
{
    return deltaTime_.asSeconds();
}

float TimeManager::GetElapsedTime()
{
    return clock_.getElapsedTime().asSeconds();
}