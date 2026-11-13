#include "Graphics/FX/FXMonitor.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "Utils/Verify.h"

FXMonitor::FXMonitor()
{
    const std::string shaderPath = "Content/Shaders/Monitor.frag";
    VERIFY(shader_.loadFromFile(shaderPath, sf::Shader::Type::Fragment));
}

void FXMonitor::Apply(const sf::Texture &input, sf::RenderTarget &output)
{
    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);
    shader_.setUniform("resolution", sf::Vector2f(output.getSize()));
    shader_.setUniform("time", clock_.getElapsedTime().asSeconds());

    output.draw(sf::Sprite(input), &shader_);
}