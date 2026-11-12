#include <SFML/GpuPreference.hpp>

#include "Core/Engine.h"

SFML_DEFINE_DISCRETE_GPU_PREFERENCE

int main()
{
    try
    {
        Engine engine;

        while (engine.IsRunning())
        {
            engine.ProcessEvents();
            engine.Update();
            engine.Render();
        }
    }
    catch (const tgui::Exception &e)
    {
        LOG_ERROR("FATAL TGUI EXCEPTION: {}", e.what());
    }
    catch (const std::exception &e)
    {
        LOG_ERROR("FATAL STANDARD EXCEPTION: {}", e.what());
    }
}