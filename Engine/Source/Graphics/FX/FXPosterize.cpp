#include "Graphics/FX/FXPosterize.h"

#include <SFML/Graphics/Sprite.hpp>

#include "Utils/Verify.h"

FXPosterize::FXPosterize()
{
    VERIFY(shader_.loadFromFile("Content/Shaders/Posterize.frag", sf::Shader::Type::Fragment));
}

void FXPosterize::Apply(const sf::Texture &input, sf::RenderTarget &output)
{
    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);

    output.draw(sf::Sprite(input), &shader_);
}