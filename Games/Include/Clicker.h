#pragma once

#include "Types/ClickerTypes.h"

namespace Clicker
{
    class Game : public Scene
    {
    private:
        Target target;
        Stats stats;
        sf::RectangleShape background;

    public:
        Game(EngineContext &);

        void Start();
        void Update();
        void Render() const;
        void OnPause(bool);

    private:
        void InitBackground();
        void InitTarget();
        void InitStats();

        void BindInputs();

        void StartTarget();
        void StartStats();

        void UpdateStats();
        void UpdateTarget();
        void UpdateTargetColor();

        void EventTargetClicked();
        void EventTargetTeleport();
        void EventStatsScoreIncrease();

        bool IsTargetHovered() const;
    };
}