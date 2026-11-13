#pragma once

#include "Graphics/Effect.h"

#include <SFML/Graphics/Shader.hpp>

class FXPixelate : public Effect
{
private:
    sf::Shader shader_;

public:
    FXPixelate();

    void Apply(const sf::Texture &input, sf::RenderTarget &output) override;
};