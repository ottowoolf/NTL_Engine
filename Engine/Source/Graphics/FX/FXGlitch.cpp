#include "Graphics/FX/FXGlitch.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "Utils/Verify.h"

FXGlitch::FXGlitch()
{
    VERIFY(shader_.loadFromFile("Content/Shaders/Glitch.frag", sf::Shader::Type::Fragment));
}

void FXGlitch::Apply(const sf::Texture &input, sf::RenderTarget &output)
{
    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);
    shader_.setUniform("time", clock_.getElapsedTime().asSeconds());

    output.draw(sf::Sprite(input), &shader_);
}