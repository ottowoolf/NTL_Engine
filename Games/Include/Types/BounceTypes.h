#pragma once

#include "Config/BounceConfig.h"

namespace Bounce
{
    enum Action
    {
        MoveLeft,
        MoveRight
    };

    struct Paddle
    {
        sf::RectangleShape paddleShape;
        float speed;
    };

    struct Ball
    {
        sf::CircleShape ballShape;
        sf::Vector2f direction;
        float speed;
    };

    struct Stats
    {
        int score;
        int highScore;
        int lives;

        sf::Text scoreText{GetDefaultFont()};
        sf::Text highScoreText{GetDefaultFont()};
        sf::Text livesText{GetDefaultFont()};
    };
}