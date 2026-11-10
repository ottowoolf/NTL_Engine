#pragma once

#include "Managers/RandomManager.h"
#include "Managers/TimeManager.h"
#include "Managers/SaveManager.h"
#include "Managers/ClipboardManager.h"

struct EngineContext
{
    RandomManager random;
    TimeManager time;
    SaveManager save;
    ClipboardManager clipboard;
};