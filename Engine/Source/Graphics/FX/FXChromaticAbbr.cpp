#include "Graphics/FX/FXChromaticAbbr.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

#include "Utils/Verify.h"

FXChromaticAbbr::FXChromaticAbbr()
{
    const std::string shaderPath = "Content/Shaders/ChromaticAbbr.frag";
    VERIFY(shader_.loadFromFile(shaderPath, sf::Shader::Type::Fragment));
}

void FXChromaticAbbr::Apply(const sf::Texture &input, sf::RenderTarget &output)
{
    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);
    shader_.setUniform("time", clock_.getElapsedTime().asSeconds());

    output.draw(sf::Sprite(input), &shader_);
}