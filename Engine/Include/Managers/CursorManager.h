#pragma once

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

class CursorManager
{

private:
    sf::RenderWindow &window_;
    sf::CircleShape cursorShape_;
    float cursorSpeed_;
    bool showCursor_;

public:
    CursorManager(sf::RenderWindow &window);

    void SetCursorSpeed(float speed);
    float GetCursorSpeed() const;

    void SetShowCursor(bool show);
    bool IsCursorVisible() const;

    void SetCursorPosition(const sf::Vector2f &position);
    sf::Vector2f GetCursorPosition() const;
    sf::Vector2f GetRelativeCursorPosition(const sf::View &view) const;

private:
    friend class Engine;
    void UpdateCursorPosition(float deltaTime);
    void RenderCursor() const;
};