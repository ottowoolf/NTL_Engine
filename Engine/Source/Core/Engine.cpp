
#include "Core/Engine.h"
#include "Core/EngineConfig.h"

Engine::Engine()
    : window_(sf::VideoMode(sf::Vector2u(gConfig.windowSize)), gConfig.windowTitle)
{
    window_.setIcon(sf::Image("Content/Textures/Logos/EnginIcon.png"));
    window_.setMinimumSize(window_.getSize() / 2u);
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
    // Update game logic here
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
}