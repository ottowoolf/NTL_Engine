#include "Managers/ScreenshotManager.h"
#include "Utils/Log.h"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <chrono>
#include <format>
#include <string>

ScreenshotManager::ScreenshotManager(const sf::RenderWindow &window)
    : window_(window)
{
}

void ScreenshotManager::TakeScreenshot() const
{
    // Build the filename with the current timestamp
    std::string filename = std::format("Screenshot_{:%Y-%m-%d_%H-%M-%S}.png",
                                       floor<std::chrono::milliseconds>(std::chrono::system_clock::now()));

    filename.replace(filename.find('.'), 1, "_"); // Replace '.' with '_' for filename compatibility

    sf::Texture scrteenshot(window_.getSize());
    scrteenshot.update(window_);

    if (scrteenshot.copyToImage().saveToFile("Content/Screenshots/" + filename))
    {
        LOG_INFO("Screenshot saved as {}", filename);
    }
    else
    {
        LOG_WARNING("Failed to save screenshot as {}", filename);
    }
}