
#include "Core/Engine.h"
#include "Core/EngineConfig.h"
#include "Utils/Log.h"

Engine::Engine()
    : window_(sf::VideoMode(sf::Vector2u(gConfig.windowSize)), gConfig.windowTitle)
{

    window_.setIcon(sf::Image("Content/Textures/Logos/NTL_Icon.png"));
    window_.setMinimumSize(window_.getSize() / 2u);
    window_.setKeyRepeatEnabled(false); // Disable key repeat to avoid multiple key press events for a single press

    if (gConfig.disableSfmlLogs)
    {
        sf::err().rdbuf(nullptr); // Disable SFML logs if the configuration flag is set
    }

    context_.audio.SetGlobalVolume(gConfig.globalVolume);
    LOG_INFO("Engine initialized and Window created!");
}

bool Engine::IsRunning() const
{
    return window_.isOpen();
}

void Engine::processEvents()
{
    while (const auto event = window_.pollEvent())
    {
        event->visit(EngineVisitor{*this});
    }
}

void Engine::update()
{
    context_.time.Update();
}

void Engine::render()
{
    window_.clear(sf::Color(243, 240, 255)); // Clear the window with a light purple color

    // Render game objects here

    window_.display();
}

void Engine::EventWindowClosed()
{
    window_.close();
    LOG_INFO("Window closed. Engine shutting down.");
    LOG_INFO("Window closed after {:.2f} seconds of runtime.", context_.time.GetElapsedTime());
}

void Engine::EventWindowResized(sf::Vector2u size)
{
    LOG_INFO("Window resized to: {}x{}", size.x, size.y);
}

void Engine::EventFocusLost()
{
    LOG_INFO("Window focus lost.");
}

void Engine::EventFocusGained()
{
    LOG_INFO("Window focus gained.");
}

void Engine::EventGamepadConnected(int id)
{
    LOG_INFO("Gamepad with ID | {} | connected", id);
}

void Engine::EventGamepadDisconnected(int id)
{
    LOG_INFO("Gamepad with ID | {} | disconnected", id);
}