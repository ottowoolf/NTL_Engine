#pragma once

#include "Graphics/Effect.h"

#include <SFML/Graphics/Shader.hpp>

class FXInverted : public Effect
{
private:
    sf::Shader shader_;

public:
    FXInverted();

    void Apply(const sf::Texture &input, sf::RenderTarget &output) override;
};