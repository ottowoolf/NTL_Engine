#include "Core/Overlay.h"

#include <magic_enum/magic_enum.hpp>
#include <utility>

Overlay::Overlay(GuiManager &gui)
{
    overlayGroup_ = tgui::Group::create();
    overlayGroup_->setVisible(false); // Initially hide the overlay group

    InitBackground();
    InitButtons();
    gui.Add(overlayGroup_);
}

std::optional<OverlaySelection> Overlay::FetchSelection()
{
    return std::exchange(selectedOption_, std::nullopt);
}

void Overlay::ShowMenu(bool show)
{
    overlayGroup_->setVisible(show);
}

bool Overlay::IsMenuVisible() const
{
    return overlayGroup_->isVisible();
}

void Overlay::InitBackground()
{
    auto background = tgui::Panel::create();
    background->setSize("100%", "100%");
    background->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 150)); // Semi-transparent black
    overlayGroup_->add(background);
}

void Overlay::InitButtons()
{
    auto layout = tgui::VerticalLayout::create();
    layout->setSize("35%", "65%");
    layout->setPosition("33%", "20%");
    layout->setOrigin(0.5f, 0.5f); // Center the layout

    for (const auto &[selection, name] : magic_enum::enum_entries<OverlaySelection>())
    {
        auto button = tgui::Button::create(name.data());
        button->setTextSize(24);
        button->setSize("100%", "20%");
        button->onPress([this, selection]
                        { selectedOption_ = selection; });
        layout->add(button);
    }
    overlayGroup_->add(layout);
}