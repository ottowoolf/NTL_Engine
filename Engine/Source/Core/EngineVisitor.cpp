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