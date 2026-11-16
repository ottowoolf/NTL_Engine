#include "Clicker.h"

#include <algorithm>

using namespace Clicker;

Game::Game(EngineContext &context) : Scene(context)
{
    InitBackground();
    InitTarget();
    InitStats();
}

void Game::InitBackground()
{
    background.setTexture(ctx.resource.FetchTexture(BG_TEXTURE_FILENAME));
    background.setSize(gConfig.windowSize);
}

void Game::InitTarget()
{
    target.shape.setRadius(TARGET_RADIUS);
    target.shape.setTexture(ctx.resource.FetchTexture(TARGET_TEXTURE_FILENAME));
    target.shape.setOrigin(target.shape.getGeometricCenter());

    target.teleportCooldown.SetDuration(TARGET_TELEPORT_COOLDOWN);
};

void Game::InitStats()
{
    stats.scoreText.setCharacterSize(STATS_TEXT_SIZE);
    stats.scoreText.setFillColor(STATS_SCORE_TEXT_COLOR);
    stats.scoreText.setPosition({5, 5});

    stats.finalCooldown.SetDuration(STATS_FINAL_COOLDOWN_DURATION);

    stats.finalCooldownText.setCharacterSize(STATS_TEXT_SIZE);
    stats.finalCooldownText.setFillColor(STATS_FINAL_COOLDOWN_TEXT_COLOR);
    stats.finalCooldownText.setPosition({5, 50});

    stats.bestTimeText.setCharacterSize(STATS_TEXT_SIZE);
    stats.bestTimeText.setFillColor(STATS_BEST_TIME_TEXT_COLOR);
    stats.bestTimeText.setPosition({5, 95});
};

void Game::Start()
{
    ctx.cursor.SetCursorSpeed(CURSOR_SPEED);

    BindInputs();

    StartTarget();
    StartStats();
}

void Game::BindInputs()
{
    ctx.input.Bind(Click, Input::Mouse{sf::Mouse::Button::Left});
    ctx.input.Bind(Click, Input::Gamepad{
                              GamepadButton::South});
}

void Game::StartTarget()
{
    target.shape.setFillColor(TARGET_COLOR);
    target.shape.setPosition(gConfig.windowSize / 2.0f);
}

void Game::StartStats()
{
    stats.score = 0;
    stats.scoreText.setString("Score: 0");

    stats.finalCooldown.Reset();

    float totalTime = stats.finalCooldown.GetDuration();
    stats.finalCooldownText.setString(std::format("Time left: {:.2f}s", totalTime));

    stats.bestTime = ctx.save.Get<float>(STATS_BEST_TIME_KEY, totalTime);
    stats.bestTimeText.setString(std::format("Best Time: {:.2f}", stats.bestTime));
}

void Game::Update()
{
    if (ctx.input.Pressed(Click) && IsTargetHovered())
    {
        EventTargetClicked();
    }
    if (stats.finalCooldown.IsRunning())
    {
        UpdateTarget();
        UpdateStats();
    }
}

void Game::UpdateTarget()
{
    if (target.teleportCooldown.IsOver())
    {
        EventTargetTeleport();
        target.teleportCooldown.Restart();
    }

    UpdateTargetColor();
}

void Game::UpdateTargetColor()
{
    float progress = target.teleportCooldown.GetElapsedTime() / target.teleportCooldown.GetDuration();

    sf::Color color = target.shape.getFillColor();

    color.a = std::uint8_t(255 * (1.0f - std::min(progress, 1.0f)));
    target.shape.setFillColor(color);
}

void Game::UpdateStats()
{
    float timeLeft = stats.finalCooldown.GetDuration() - stats.finalCooldown.GetElapsedTime();
    stats.finalCooldownText.setString(std::format("Time left: {:.2f}s", std::max(timeLeft, 0.0f)));

    if (stats.finalCooldown.IsOver())
    {
        LOG_INFO("You lost! Score: {}", stats.score);
        ctx.scenes.RestartCurrentScene();
    }
}

void Game::EventTargetClicked()
{
    EventTargetTeleport();
    target.teleportCooldown.Restart();

    if (stats.score == 0)
    {
        stats.finalCooldown.Start();
    }

    EventStatsScoreIncrease();
}

void Game::EventTargetTeleport()
{
    sf::Vector2f halfSize = target.shape.getGlobalBounds().size / 2.0f;
    target.shape.setPosition(ctx.random.Position(halfSize, gConfig.windowSize - halfSize));
}

void Game::EventStatsScoreIncrease()
{
    stats.score++;
    stats.scoreText.setString(std::format("Score: {}/{}", stats.score, STATS_SCORE_GOAL));

    if (stats.score == STATS_SCORE_GOAL)
    {
        float elapsedTime = stats.finalCooldown.GetElapsedTime();
        ctx.save.Set(STATS_BEST_TIME_KEY, std::min(elapsedTime, stats.bestTime));

        LOG_INFO("You won! Time: {:.2f}s", elapsedTime);
        ctx.scenes.RestartCurrentScene();
    }
}

bool Game::IsTargetHovered() const
{
    return Contains(target.shape, ctx.cursor.GetCursorPosition());
}

void Game::Render() const
{

    ctx.renderer.Draw(background);
    ctx.renderer.Draw(target.shape);

    ctx.renderer.Draw(stats.scoreText);
    ctx.renderer.Draw(stats.finalCooldownText);
    ctx.renderer.Draw(stats.bestTimeText);
}

void Game::OnPause(bool paused)
{
    if (paused)
    {
        stats.finalCooldown.Stop();
        target.teleportCooldown.Stop();
    }
    else
    {
        target.teleportCooldown.Start();
        stats.finalCooldown.Start();
    }
}