#include "Managers/CursorManager.h"
#include "Core/EngineConfig.h"

#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/Mouse.hpp>
#include <algorithm>

CursorManager::CursorManager(sf::RenderWindow &window)
    : window_(window), cursorShape_(gConfig.cursorRadius), cursorSpeed_(gConfig.cursorSpeed), showCursor_(gConfig.showCursor)
{
    cursorShape_.setFillColor(gConfig.cursorColor);
    cursorShape_.setOrigin(cursorShape_.getGeometricCenter());
    cursorShape_.setPosition(gConfig.windowSize / 2.f);
}

void CursorManager::UpdateCursorPosition(float deltaTime)
{

    const sf::Vector2f joystickDirection(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::X) / 100.f, sf::Joystick::getAxisPosition(0, sf::Joystick::Axis::Y) / 100.f);

    if (joystickDirection.length() > gConfig.joyStickDeadZone)
    {
        cursorShape_.move(joystickDirection * cursorSpeed_ * deltaTime);
        cursorShape_.setPosition({std::clamp(cursorShape_.getPosition().x, 0.f, gConfig.windowSize.x - 1),
                                  std::clamp(cursorShape_.getPosition().y, 0.f, gConfig.windowSize.y - 1)});

        SetCursorPosition(cursorShape_.getPosition());
    }
    else
    {
        cursorShape_.setPosition(GetCursorPosition());
    }
}

void CursorManager::RenderCursor() const
{
    if (showCursor_)
    {
        window_.draw(cursorShape_);
    }
}

void CursorManager::SetCursorSpeed(float speed)
{
    cursorSpeed_ = speed;
}

float CursorManager::GetCursorSpeed() const
{
    return cursorSpeed_;
}

void CursorManager::SetShowCursor(bool show)
{
    showCursor_ = show;
}

bool CursorManager::IsCursorVisible() const
{
    return showCursor_;
}

void CursorManager::SetCursorPosition(const sf::Vector2f &position)
{
    sf::Mouse::setPosition(window_.mapCoordsToPixel(position, window_.getDefaultView()), window_);
}

sf::Vector2f CursorManager::GetCursorPosition() const
{
    return GetRelativeCursorPosition(window_.getDefaultView());
}

sf::Vector2f CursorManager::GetRelativeCursorPosition(const sf::View &view) const
{
    return window_.mapPixelToCoords(sf::Mouse::getPosition(window_), view);
}