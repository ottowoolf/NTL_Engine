#pragma once

#include "Graphics/Effect.h"

#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>

class FXRipple : public Effect
{

private:
    sf::Shader shader_;
    sf::Clock clock_;

    sf::Vector2f hitUvPosition_;
    bool isActive_ = false;
    float startTime_ = 0.0f;

    sf::Color hitColor_ = sf::Color::White; // Default color of the ripple effect

public:
    FXRipple();

    void Apply(const sf::Texture &input, sf::RenderTarget &output) override;

    void TriggerRipple(sf::Vector2f screenPos, sf::Vector2f resolution, sf::Color color = sf::Color::White);
};