#include "Bounce.h"
#include "Managers/RandomManager.h"

using namespace Bounce;

Game::Game(EngineContext &context)
    : Scene(context), ballSpawnCooldown(BALL_SPAWN_COOLDOWN_DURATION), bounceSound(*ctx.resource.FetchSound(BOUNCE_SOUND_FILENAME)), backgroundMusic(*ctx.resource.FetchMusic(MUSIC_FILENAME))
{
    InitPaddle();
    InitStats();
    InitBackground();
    InitBounceSound();
    InitBackgroundMusic();
}

void Game::InitPaddle()
{
    paddle.paddleShape.setFillColor(PADDLE_COLOR);
    paddle.paddleShape.setSize(PADDLE_SIZE);
    paddle.paddleShape.setOrigin(paddle.paddleShape.getGeometricCenter());
    paddle.speed = PADDLE_SPEED;
}

void Game::InitStats()
{
    stats.scoreText.setFillColor(STATS_SCORE_TEXT_COLOR);
    stats.scoreText.setPosition({10, 10});

    stats.highScoreText.setFillColor(STATS_HIGH_SCORE_TEXT_COLOR);
    stats.highScoreText.setPosition({10, 40});

    stats.livesText.setFillColor(STATS_LIVES_TEXT_COLOR);
    stats.livesText.setPosition({10, 70});
}

void Game::InitBackground()
{
    background.setTexture(ctx.resource.FetchTexture(BACKGROUND_TEXTURE_FILENAME));
    background.setSize(gConfig.windowSize);
}

void Game::InitBounceSound()
{
    bounceSound.setVolume(BOUNCE_SOUND_VOLUME);
}

void Game::InitBackgroundMusic()
{
    backgroundMusic.setVolume(MUSIC_VOLUME);
    backgroundMusic.setPitch(MUSIC_PITCH);
    backgroundMusic.setLooping(true);
}

void Game::Start()
{

    ctx.cursor.SetShowCursor(false);

    BindInputs();

    balls.clear();

    StartPaddle();
    StartStats();
    StartMusic();

    ballSpawnCooldown.Restart();
}

void Game::BindInputs()
{
    ctx.input.Bind(Action::MoveLeft, Input::Keyboard(sf::Keyboard::Scan::Left));
    ctx.input.Bind(Action::MoveLeft, Input::Axis(sf::Joystick::Axis::X, -0.25f));

    ctx.input.Bind(Action::MoveRight, Input::Keyboard(sf::Keyboard::Scan::Right));
    ctx.input.Bind(Action::MoveRight, Input::Axis(sf::Joystick::Axis::X, 0.25f));
}

void Game::StartPaddle()
{
    paddle.paddleShape.setPosition(gConfig.windowSize.componentWiseMul({0.5f, 0.9f}));
}

void Game::StartStats()
{
    stats.score = 0;
    stats.scoreText.setString("Score: 0");

    stats.highScore = ctx.save.Get<int>(STATS_HIGH_SCORE_KEY);
    stats.highScoreText.setString("High Score: " + std::to_string(stats.highScore));

    stats.lives = PADDLE_LIVES;
    stats.livesText.setString("Lives: " + std::to_string(stats.lives));
}

void Game::StartMusic()
{
    backgroundMusic.play();
}

void Game::Update()
{

    if (ballSpawnCooldown.IsOver())
    {
        EventBallSpawn();
        ballSpawnCooldown.Restart();
    }

    UpdatePaddle();
    UpdateBalls();

    HandleCollisions();
}

void Game::UpdatePaddle()
{
    // Clamp paddle position to window bounds
    sf::Vector2f lastPos = paddle.paddleShape.getPosition();

    if (ctx.input.Pressed(MoveLeft))
    {
        paddle.paddleShape.move({-paddle.speed * ctx.time.GetDeltaTime(), 0});
    }
    if (ctx.input.Pressed(Action::MoveRight))
    {
        paddle.paddleShape.move({paddle.speed * ctx.time.GetDeltaTime(), 0});
    }
    if (IsOutsideWindowLeft(paddle.paddleShape) || IsOutsideWindowRight(paddle.paddleShape))
    {

        paddle.paddleShape.setPosition(lastPos);
    }
}

void Game::UpdateBalls()
{
    for (auto &ball : balls)
    {
        UpdateBall(ball);
    }
}

void Game::UpdateBall(Ball &ball)
{
    sf::Vector2f lastPos = ball.ballShape.getPosition();

    ball.ballShape.move(ball.direction * ball.speed * ctx.time.GetDeltaTime());
    if (IsOutsideWindowLeft(ball.ballShape) || IsOutsideWindowRight(ball.ballShape))
    {
        ball.direction.x *= -1;
        ball.ballShape.setPosition(lastPos);
    }
    if (IsOutsideWindowTop(ball.ballShape))
    {
        ball.direction.y *= -1;
        ball.ballShape.setPosition(lastPos);
    }
}

void Game::EventBallSpawn()
{
    auto &ball = balls.emplace_back();

    ball.ballShape.setRadius(BALL_RADIUS);
    ball.ballShape.setFillColor(randomManager.Color(sf::Color::White, sf::Color::Red));
    ball.ballShape.setOrigin(ball.ballShape.getGeometricCenter());
    ball.ballShape.setPosition(gConfig.windowSize.componentWiseMul({0.5f, 0.15f}));

    ball.direction = {1, ctx.random.Angle(sf::Angle::Zero, sf::degrees(360))};
    ball.speed = BALL_SPEED;
}

void Game::EventBallsMissed(int ballsMissed)
{
    stats.lives -= ballsMissed;
    stats.livesText.setString("Lives: " + std::to_string(stats.lives));

    if (stats.lives <= 0)
    {
        ctx.save.Set<int>(STATS_HIGH_SCORE_KEY, std::max(stats.score, stats.highScore));
        LOG_INFO("Game Over! Your score: {}", stats.score);
        LOG_INFO("Restarting scene...");
        ctx.scenes.RestartCurrentScene();
    }
}

void Game::HandleCollisions()
{
    HandleCollisionsPaddleBalls();
    HandleCollisionsBallsMap();
}

void Game::HandleCollisionsPaddleBalls()
{
    for (auto &ball : balls)
    {
        if (ball.direction.y > 0 && Intersects(paddle.paddleShape, ball.ballShape))
        {
            ResolveCollisionPaddleBall(ball);
        }
    }
}

void Game::ResolveCollisionPaddleBall(Ball &ball)
{
    ball.direction.y *= -1;
    bounceSound.play();

    if (ctx.renderer.GetRipple())
    {
        ctx.renderer.GetRipple()->TriggerRipple(ball.ballShape.getPosition(), gConfig.windowSize, randomManager.Color(sf::Color::White, sf::Color::Red));
    }
    stats.score++;
    stats.scoreText.setString("Score: " + std::to_string(stats.score));
}

void Game::HandleCollisionsBallsMap()
{
    int ballsMissed = (int)std::erase_if(balls, [](const Ball &ball)
                                         { return IsOutsideWindowBottom(ball.ballShape); });

    if (ballsMissed > 0)
    {
        EventBallsMissed(ballsMissed);
    }
}

void Game::Render() const
{
    ctx.renderer.Draw(background);

    ctx.renderer.Draw(paddle.paddleShape);

    for (const auto &ball : balls)
    {
        ctx.renderer.Draw(ball.ballShape);
    }

    ctx.renderer.Draw(stats.scoreText);
    ctx.renderer.Draw(stats.highScoreText);
    ctx.renderer.Draw(stats.livesText);
}

void Game::OnPause(bool paused)
{
    if (paused)
    {
        ballSpawnCooldown.Stop();
        backgroundMusic.pause();
        bounceSound.stop();
    }
    else
    {
        ballSpawnCooldown.Start();
        backgroundMusic.play();
    }
}

void Game::OnCleanup()
{
    backgroundMusic.stop();
    bounceSound.stop();
}