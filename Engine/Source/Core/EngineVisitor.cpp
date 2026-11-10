#include "Core/EngineVisitor.h"
#include "Core/Engine.h"

void EngineVisitor::operator()(const sf::Event::Closed &)
{
    engine.EventWindowClosed();
}

void EngineVisitor::operator()(const sf::Event::Resized &resized)
{
    engine.EventWindowResized(resized.size);
}

void EngineVisitor::operator()(const sf::Event::FocusLost &)
{
    engine.EventFocusLost();
}

void EngineVisitor::operator()(const sf::Event::FocusGained &)
{
    engine.EventFocusGained();
}

void EngineVisitor::operator()(const sf::Event::JoystickConnected &joystick)
{
    engine.EventGamepadConnected(joystick.joystickId);
}

void EngineVisitor::operator()(const sf::Event::JoystickDisconnected &joystick)
{
    engine.EventGamepadDisconnected(joystick.joystickId);
}