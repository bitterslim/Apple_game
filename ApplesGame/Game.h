#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Math.h"
#include "Player.h"
#include "Apple.h"
#include "Obstacle.h"

namespace ApplesGame
{
    struct Game
    {
        Player player;
        Apple apples[NUM_APPLES];
        Obstacle obstacle[NUM_OBSTACLES];

        // Global game data
        int mode;
        int appleCount;
        int limitApple;
        bool speedBoostEnabled;
        int numEatenApples = 0;
        bool isGameFinished = false;
        bool isVictory = false;
        float timeSinceGameFinish = 0.f;
        sf::Texture backgroundTexture;
        sf::Texture gameOverTexture;
        sf::Sprite backgroundSprite;
        sf::Font font;
        sf::Text gameText;

        // Resources
        sf::Texture playerTexture;
        sf::Texture appleTexture;
        sf::Texture obstacleTexture;
        sf::SoundBuffer eatSoundBuffer;
        sf::Sound eatSound;
        sf::SoundBuffer hitSoundBuffer;
        sf::Sound hitSound;
    };

    void RestartGame(Game& game);
    void InitGame(Game& game);
    void UpdateGame(Game& game, float deltaTime);
    void DrawGame(Game& game, sf::RenderWindow& window);
    void DeinializeGame(Game& game);
}


namespace ApplesGame
{
    enum GameMode
    {
        FiniteApples = 1 << 0,
        InfiniteApples = 1 << 1,
        SpeedBoost = 1 << 2,
        NoSpeedBoost = 1 << 3
    };

    void SetGameMode(Game& game, int mode, int playerDefinedAppleCount = -1);
}

