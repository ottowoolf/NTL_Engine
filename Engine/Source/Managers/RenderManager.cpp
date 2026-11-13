#include "Managers/RenderManager.h"
#include "Core/EngineConfig.h"
#include "Utils/Verify.h"
#include "Graphics/FX/FXInverted.h"
#include "Graphics/FX/FXWaves.h"
#include "Graphics/FX/FXBloom.h"
#include "Graphics/FX/FXMonitor.h"
#include "Graphics/FX/FXChromaticAbbr.h"
#include "Graphics/FX/FXPixelate.h"
#include "Graphics/FX/FXShockwave.h"
#include "Graphics/FX/FXRipple.h"
#include "Graphics/FX/FXPosterize.h"

#include <utility>

RenderManager::RenderManager() : target_(sf::Vector2u(gConfig.windowSize)), backgroundTexture_("Content/Textures/background.jpg"), background_(gConfig.windowSize)
{
    target_.setSmooth(true);
    background_.setTexture(&backgroundTexture_);
    background_.setFillColor(gConfig.backgroundColor);

    if (sf::Shader::isAvailable())
    {
        VERIFY(effectsTarget_.resize(sf::Vector2u(gConfig.windowSize)));

        // Create the ripple effect and store its pointer
        auto rippleEffect = std::make_unique<FXRipple>();
        rippleEffect_ = rippleEffect.get();

        effects_.emplace_back(std::move(rippleEffect));

        effects_.emplace_back(std::make_unique<FXBloom>());
        // effects_.emplace_back(std::make_unique<FXInverted>());
        // effects_.emplace_back(std::make_unique<FXPosterize>());
        effects_.emplace_back(std::make_unique<FXWaves>());
        effects_.emplace_back(std::make_unique<FXMonitor>());
        effects_.emplace_back(std::make_unique<FXChromaticAbbr>());
        // effects_.emplace_back(std::make_unique<FXPixelate>());
        // effects_.emplace_back(std::make_unique<FXShockwave>());
    }
}

void RenderManager::Draw(const sf::Drawable &drawable)
{
    target_.draw(drawable);
}

void RenderManager::SetView(const sf::View &view)
{
    target_.setView(view);
}

void RenderManager::ResetView()
{
    SetView(target_.getDefaultView());
}

void RenderManager::BeginDrawing()
{
    target_.clear();
    target_.draw(background_);
}

const sf::Texture &RenderManager::FinishDrawing()
{
    target_.display();

    sf::RenderTexture *input = &target_;
    sf::RenderTexture *output = &effectsTarget_;
    for (const auto &effect : effects_)
    {
        output->clear();
        effect->Apply(input->getTexture(), *output);
        output->display();
        std::swap(input, output);
    }

    return input->getTexture();
}