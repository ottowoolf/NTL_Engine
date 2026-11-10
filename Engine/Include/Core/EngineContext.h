#pragma once

#include "Managers/RandomManager.h"
#include "Managers/TimeManager.h"
#include "Managers/SaveManager.h"

struct EngineContext
{
    RandomManager random;
    TimeManager time;
    SaveManager save;
};