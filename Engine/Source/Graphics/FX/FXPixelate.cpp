#include "Graphics/FX/FXPixelate.h"
#include "Utils/Verify.h"

#include <SFML/Graphics/Sprite.hpp>

FXPixelate::FXPixelate()
{
    VERIFY(shader_.loadFromFile("Content/Shaders/Pixelate.frag", sf::Shader::Type::Fragment));
}

void FXPixelate::Apply(const sf::Texture &input, sf::RenderTarget &output)
{
    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);
    shader_.setUniform("resolution", sf::Vector2f(output.getSize()));
    output.draw(sf::Sprite(input), &shader_);
}