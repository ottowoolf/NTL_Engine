#include "Graphics/FX/FXInverted.h"

#include <SFML/Graphics/Sprite.hpp>

#include "Utils/Verify.h"

FXInverted::FXInverted()
{
    VERIFY(shader_.loadFromFile("Content/Shaders/Invert.frag", sf::Shader::Type::Fragment));
}

void FXInverted::Apply(const sf::Texture &input, sf::RenderTarget &output)
{
    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);

    output.draw(sf::Sprite(input), &shader_);
}