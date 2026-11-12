#pragma once

#include "Managers/GuiManager.h"

#include <optional>

enum class OverlaySelection
{
    Resume,
    Restart,
    Menu,
    Quit
};

class Overlay
{
private:
    std::optional<OverlaySelection> selectedOption_;
    tgui::Group::Ptr overlayGroup_;

public:
    Overlay(GuiManager &gui);

    std::optional<OverlaySelection> FetchSelection();

    void ShowMenu(bool show);
    bool IsMenuVisible() const;

private:
    void InitBackground();
    void InitButtons();
};