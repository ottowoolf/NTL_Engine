#pragma once
#include <SFML/Graphics.hpp>

#include "Core/EngineVisitor.h"
#include "Core/EngineContext.h"

class Engine
{
private:
    sf::RenderWindow window_;
    EngineContext context_;

public:
    Engine();

    bool IsRunning() const;

    void processEvents();
    void update();
    void render();

private:
    friend EngineVisitor;

    void EventWindowClosed();
    void EventWindowResized(sf::Vector2u size);
    void EventFocusLost();
    void EventFocusGained();
    void EventGamepadConnected(int id);
    void EventGamepadDisconnected(int id);
    void EventWindowScreenshot();
    void EventSceneChange(const std::string &sceneName);
    void EventSceneRestart();
    void EventSceneMenuReturn();
};