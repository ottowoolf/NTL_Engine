#pragma once

#include "Graphics/Effect.h"

#include <SFML/Graphics/Shader.hpp>

class FXPosterize : public Effect
{
private:
    sf::Shader shader_;

public:
    FXPosterize();

    void Apply(const sf::Texture &input, sf::RenderTarget &output) override;
};