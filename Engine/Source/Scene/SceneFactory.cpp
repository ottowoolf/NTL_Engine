#include "Scene/SceneFactory.h"
#include "Bounce.h"
#include "Clicker.h"

namespace SceneFactory
{
    Scenes CreateScenes(EngineContext &context)
    {
        Scenes scenes;
        scenes.emplace("Clicker", std::make_unique<Clicker::Game>(context));

        scenes.emplace("Bounce", std::make_unique<Bounce::Game>(context));

        return scenes;
    }
}