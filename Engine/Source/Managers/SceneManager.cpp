#include "Managers/SceneManager.h"
#include "Utils/Log.h"

#include <utility>

std::optional<std::string> SceneManager::FetchNextScene()
{
    if (nextScene_)
    {
        if (currentScene_ == *nextScene_)
        {
            LOG_INFO("Restarting scene: {}" + currentScene_);
        }
        else
        {
            LOG_INFO("Changing scene to: {}" + *nextScene_);
        }
        currentScene_ = *nextScene_;

        return std::exchange(nextScene_, std::nullopt);
    }

    return std::nullopt;
}

void SceneManager::ChangeScene(std::string_view scenaName)
{
    if (!nextScene_)
    {
        nextScene_ = scenaName;
    }
}

void SceneManager::RestartCurrentScene()
{
    ChangeScene(currentScene_);
}