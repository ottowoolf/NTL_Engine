#pragma once
#include <SFML/Graphics.hpp>

#include "Core/EngineVisitor.h"

class Engine
{
private:
    sf::RenderWindow window_;

public:
    Engine();

    bool IsRunning() const;

    void processEvents();
    void update();
    void render();

private:
    friend EngineVisitor;

    void EventWindowClosed();
};