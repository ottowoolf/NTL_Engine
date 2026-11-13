#include "Graphics/FX/FXShockwave.h"
#include "Utils/Verify.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

FXShockwave::FXShockwave()
{
    VERIFY(shader_.loadFromFile("Content/Shaders/Shockwave.frag", sf::Shader::Type::Fragment));
}

void FXShockwave::Apply(const sf::Texture &input, sf::RenderTarget &output)
{
    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);

    shader_.setUniform("resolution", sf::Vector2f(output.getSize()));
    shader_.setUniform("time", clock_.getElapsedTime().asSeconds());

    output.draw(sf::Sprite(input), &shader_);
}