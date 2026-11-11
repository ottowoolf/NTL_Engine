#include "Managers/GuiManager.h"

#include "Utils/InputBindings.h"

GuiManager::GuiManager(sf::RenderWindow &window)
    : window_(window), gui_(window_)
{
    tgui::Theme::setDefault("Content/Themes/Black.txt");
    gui_.setTabKeyUsageEnabled(true);
    gui_.setFont("Content/Fonts/Audiowide.ttf");
}

void GuiManager::ProcessEvent(const sf::Event &event)
{
    event.visit([this](const auto &type)
                { this->HandleEvent(type); this->gui_.handleEvent(type); });
}

void GuiManager::Render()
{
    gui_.draw();
}

void GuiManager::AddWidget(tgui::Widget::Ptr &widget)
{
    gui_.add(widget);
}

void GuiManager::RemoveWidget(tgui::Widget::Ptr &widget)
{
    gui_.remove(widget);
}

void GuiManager::HandleEvent(const sf::Event::Resized &resized)
{
    const sf::Vector2f defaultSize = window_.getDefaultView().getSize();
    const sf::Vector2f scale = sf::Vector2f(resized.size).componentWiseDiv(defaultSize);
    gui_.setRelativeView({0.f, 0.f, 1 / scale.x, 1 / scale.y});
}

void GuiManager::HandleEvent(const sf::Event::JoystickButtonPressed &joystick)
{
    if (Input::HardwareToLogical(joystick.button, joystick.joystickId) == GamepadButton::South)
    {
        gui_.handleEvent(sf::Event::MouseButtonPressed{{}, sf::Mouse::getPosition(window_)});
    };
}

void GuiManager::HandleEvent(const sf::Event::JoystickButtonReleased &joystick)
{
    if (Input::HardwareToLogical(joystick.button, joystick.joystickId) == GamepadButton::South)
    {
        gui_.handleEvent(sf::Event::MouseButtonReleased{{}, sf::Mouse::getPosition(window_)});
    };
}
