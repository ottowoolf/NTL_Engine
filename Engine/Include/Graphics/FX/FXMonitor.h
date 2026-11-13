#pragma once

#include "Graphics/Effect.h"

#include <SFML/Graphics/Shader.hpp>
#include <SFML/System/Clock.hpp>

class FXMonitor : public Effect
{
private:
    sf::Shader shader_;
    sf::Clock clock_;

public:
    FXMonitor();

    void Apply(const sf::Texture &input, sf::RenderTarget &output) override;
};