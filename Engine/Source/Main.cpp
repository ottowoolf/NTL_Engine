#include <SFML/GpuPreference.hpp>
#include <SFML/System/Sleep.hpp>

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

            if (!engine.HasFocus())
            {
                sf::sleep(sf::milliseconds(10));
                continue;
            }

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