#pragma once
#include <SFML/Graphics.hpp>

#include "Core/EngineVisitor.h"
#include "Core/EngineContext.h"
#include "Scene/SceneFactory.h"
#include "Core/Overlay.h"

class Engine
{
private:
    sf::RenderWindow window_;
    EngineContext context_;
    SceneFactory::Scenes scenes_;
    Scene *currentScene_;
    Overlay overlay_;
    bool cursorWasVisible_;

public:
    Engine();

    bool IsRunning() const;
    bool HasFocus() const;

    void ProcessEvents();
    void Update();
    void Render();

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
    void EventOverlayPauseToggled();
    void EventOverlaySelect(const OverlaySelection &selection);
};