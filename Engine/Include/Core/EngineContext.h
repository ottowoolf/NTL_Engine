#pragma once

#include <SFML/Graphics/RenderWindow.hpp>

#include "Managers/RandomManager.h"
#include "Managers/TimeManager.h"
#include "Managers/SaveManager.h"
#include "Managers/ClipboardManager.h"
#include "Managers/ResourceManager.h"
#include "Managers/AudioManager.h"
#include "Managers/InputManager.h"
#include "Managers/RenderManager.h"
#include "Managers/ScreenshotManager.h"
#include "Managers/CursorManager.h"

struct EngineContext
{
    RandomManager random;
    TimeManager time;
    SaveManager save;
    ClipboardManager clipboard;
    ResourceManager resource;
    AudioManager audio;
    InputManager input;
    RenderManager renderer;
    ScreenshotManager screenshot;
    CursorManager cursor;

    EngineContext(sf::RenderWindow &window) : screenshot(window), cursor(window) {}
};