#include "Graphics/FX/FXRipple.h"
#include "Utils/Verify.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Time.hpp>

FXRipple::FXRipple()
{
    VERIFY(shader_.loadFromFile("Content/Shaders/Ripple.frag", sf::Shader::Type::Fragment));
}

void FXRipple::TriggerRipple(sf::Vector2f screenPos, sf::Vector2f resolution, sf::Color color)
{
    hitColor_ = color;

    // Convert screen position to UV coordinates (0.0 to 1.0)
    hitUvPosition_.x = screenPos.x / resolution.x;
    hitUvPosition_.y = 1.0f - (screenPos.y / resolution.y); // Invert Y-axis for UV coordinates
    startTime_ = clock_.getElapsedTime().asSeconds();
    isActive_ = true;
}

void FXRipple::Apply(const sf::Texture &input, sf::RenderTarget &output)
{

    if (!isActive_)
    {
        sf::Sprite sprite(input);
        output.draw(sprite);
        return;
    }

    float timePassed = clock_.getElapsedTime().asSeconds() - startTime_;

    float duration = 0.5f; // Duration of the ripple effect in seconds
    float progress = timePassed / duration;

    if (progress > 1.0f)
        isActive_ = false;

    shader_.setUniform("sourceTexture", sf::Shader::CurrentTexture);
    shader_.setUniform("progress", progress);
    shader_.setUniform("hitCenter", hitUvPosition_);

    // Set the hit color uniform
    shader_.setUniform("hitColor", sf::Glsl::Vec4(hitColor_));

    output.draw(sf::Sprite(input), &shader_);
}