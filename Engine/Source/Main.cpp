#include <SFML/GpuPreference.hpp>

#include "Core/Engine.h"

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main()
{
    Engine engine;

    while (engine.IsRunning())
    {
        engine.processEvents();
        engine.update();
        engine.render();
    }
}