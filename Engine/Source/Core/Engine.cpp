
#include "Core/Engine.h"
#include "Core/EngineConfig.h"
#include "Utils/Log.h"
#include "Core/EngineContext.h"

Engine::Engine()
    : window_(sf::VideoMode(sf::Vector2u(gConfig.windowSize)), gConfig.windowTitle), context_(window_), scenes_(SceneFactory::CreateScenes(context_)), currentScene_(nullptr), overlay_(context_.gui), cursorWasVisible_(true)
{

    window_.setIcon(sf::Image("Content/Textures/Logos/NTL_Icon.png"));
    window_.setMinimumSize(window_.getSize() / 2u);
    window_.setKeyRepeatEnabled(false);
    window_.setMouseCursorVisible(false); // Hide the default mouse cursor

    if (gConfig.disableSfmlLogs)
    {
        sf::err().rdbuf(nullptr); // Disable SFML logs if the configuration flag is set
    }

    context_.audio.SetGlobalVolume(gConfig.globalVolume);
    context_.scenes.ChangeScene("Bounce");
    LOG_INFO("Engine initialized and Window created!");
}

bool Engine::IsRunning() const
{
    return window_.isOpen();
}

void Engine::ProcessEvents()
{
    if (const auto nextScene = context_.scenes.FetchNextScene())
    {
        LOG_INFO("Scene change detected. Next scene: {}", *nextScene);
        EventSceneChange(*nextScene);
    }

    while (const auto event = window_.pollEvent())
    {
        event->visit(EngineVisitor{*this});
        context_.gui.ProcessEvent(*event);

        if (!overlay_.IsMenuVisible())
        {
            currentScene_->OnEvent(*event);
        }
    }

    if (const auto selection = overlay_.FetchSelection())
    {
        EventOverlaySelect(*selection);
    }
}

void Engine::Update()
{
    context_.time.Update();
    context_.cursor.UpdateCursorPosition(context_.time.GetDeltaTime());

    if (!overlay_.IsMenuVisible())
    {
        currentScene_->Update();
    }
}

void Engine::Render()
{
    window_.clear(sf::Color(243, 240, 255)); // Clear the window with a light purple color

    context_.renderer.BeginDrawing();

    currentScene_->Render();

    window_.draw(sf::Sprite(context_.renderer.FinishDrawing()));

    context_.gui.Render();
    context_.cursor.RenderCursor();

    window_.display();
}

void Engine::EventWindowClosed()
{
    window_.close();
    LOG_INFO("Window closed. Engine shutting down.");
    LOG_INFO("Window closed after {:.2f} seconds of runtime.", context_.time.GetElapsedTime());
}

void Engine::EventWindowResized(sf::Vector2u size)
{
    LOG_INFO("Window resized to: {}x{}", size.x, size.y);
}

void Engine::EventFocusLost()
{
    currentScene_->OnPause(true);
    LOG_INFO("Window focus lost.");
}

void Engine::EventFocusGained()
{
    currentScene_->OnPause(overlay_.IsMenuVisible());

    LOG_INFO("Window focus gained.");
}

void Engine::EventGamepadConnected(int id)
{
    LOG_INFO("Gamepad with ID | {} | connected", id);
}

void Engine::EventGamepadDisconnected(int id)
{
    LOG_INFO("Gamepad with ID | {} | disconnected", id);
}

void Engine::EventWindowScreenshot()
{
    context_.screenshot.TakeScreenshot();
}

void Engine::EventSceneChange(const std::string &sceneName)
{
    assert(scenes_.contains(sceneName));
    Scene *newScene = scenes_.at(sceneName).get();

    if (currentScene_)
    {
        currentScene_->OnCleanup();
    }

    context_.input.ClearBindings();

    currentScene_ = newScene;

    currentScene_->Start();

    LOG_INFO("Changing scene to: {}", sceneName);
}

void Engine::EventSceneRestart()
{
    overlay_.ShowMenu(false);
    context_.scenes.RestartCurrentScene();
    LOG_INFO("Restarting current scene:!");
}

void Engine::EventSceneMenuReturn()
{
    overlay_.ShowMenu(false);
    context_.scenes.ChangeScene("Menu");

    context_.cursor.SetShowCursor(true);
    context_.cursor.SetCursorSpeed(gConfig.cursorSpeed);

    LOG_INFO("Returning to the menu.");
}

void Engine::EventOverlayPauseToggled()
{
    const bool isOverlayVisible = !overlay_.IsMenuVisible();
    overlay_.ShowMenu(isOverlayVisible);

    const bool cursorVisible = context_.cursor.IsCursorVisible();
    context_.cursor.SetShowCursor(isOverlayVisible || cursorVisible);
    cursorWasVisible_ = cursorVisible;

    currentScene_->OnPause(isOverlayVisible);
    LOG_INFO(isOverlayVisible ? "Game paused" : "Game resumed");
}

void Engine::EventOverlaySelect(const OverlaySelection &selection)
{
    switch (selection)
    {
    case OverlaySelection::Resume:
        EventOverlayPauseToggled();
        break;
    case OverlaySelection::Restart:
        EventSceneRestart();
        break;
    case OverlaySelection::Menu:
        EventSceneMenuReturn();
        break;
    case OverlaySelection::Quit:
        EventWindowClosed();
        break;
    default:
        break;
    }
}