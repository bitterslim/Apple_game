#include "Game.h"
#include <cassert>
#include <iostream>
#include <algorithm>

namespace ApplesGame
{

    //player control and direction
    void HandlePlayerInput(Game& game)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            game.player.direction = PlayerDirection::Right;
            game.player.sprite.setRotation(0.f);
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            game.player.direction = PlayerDirection::Up;
            game.player.sprite.setRotation(270.f);
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            game.player.direction = PlayerDirection::Left;
            game.player.sprite.setRotation(0.f);
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            game.player.direction = PlayerDirection::Down;
            game.player.sprite.setRotation(90.f);
        }

    }




    //player postion
    void UpdatePlayer(Game& game, float deltaTime)
    {
        switch (game.player.direction)
        {

        case PlayerDirection::Right:
            game.player.position.x += game.player.speed * deltaTime;
            break;

        case PlayerDirection::Up:
            game.player.position.y -= game.player.speed * deltaTime;
            break;

        case PlayerDirection::Left:
            game.player.position.x -= game.player.speed * deltaTime;
            break;

        case PlayerDirection::Down:
            game.player.position.y += game.player.speed * deltaTime;
            break;
        }
    }

    void SetGameMode(Game& game, int mode, int playerDefinedAppleCount)
    {
        game.mode = mode;

        // Logic for setting apples based on mode
        if (mode & ApplesGame::GameMode::FiniteApples)
        {
            game.limitApple = playerDefinedAppleCount;
            game.appleCount = game.limitApple;
            std::cout << "Finite Apples mode: " << game.limitApple << " apples set." << std::endl;
        }
        else if (mode & ApplesGame::GameMode::InfiniteApples)
        {
            //           game.appleCount = -1; // Ѕесконечное количество €блок
            std::cout << "Infinite Apples mode: infinite apples set." << std::endl;
        }

        // Logic for speed boost based on mode
        if (mode & ApplesGame::GameMode::SpeedBoost)
        {
            game.speedBoostEnabled = true;
            std::cout << "Speed Boost enabled." << std::endl;
        }
        else if (mode & ApplesGame::GameMode::NoSpeedBoost)
        {
            game.speedBoostEnabled = false;
            std::cout << "No Speed Boost enabled." << std::endl;
        }
    }
    //collision with apple
    void CheckAppleCollision(Game& game)
    {
        int appleCountToCheck = (game.mode & GameMode::FiniteApples) ? game.limitApple : NUM_APPLES;

        for (int i = 0; i < appleCountToCheck; ++i)
        {
            if (IsCirclesCollide(game.player.position, PLAYER_SIZE, game.apples[i].position, OBSTACLE_SIZE))
            {
                game.numEatenApples++;

                if (game.mode & GameMode::FiniteApples)
                {
                    game.apples[i].position = { -100, -100 }; 
                }
                else
                {
                    // ¬ режиме бесконечных €блок обновл€ем позицию €блока
                    game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);                }

                game.gameText.setString("Apples eaten: " + std::to_string(game.numEatenApples));

                if (game.mode & GameMode::SpeedBoost)
                {
                    game.player.speed += ACCELERATION;
                }

                game.eatSound.play();
            }
        }
    }





    //collision with obstacle
    void CheckObstacleCollision(Game& game)
    {
        for (int i = 0; i < NUM_OBSTACLES; ++i)
        {
            if (IsCirclesCollide(game.player.position, PLAYER_SIZE, game.obstacle[i].position, OBSTACLE_SIZE))
            {
                game.isGameFinished = true;
                game.timeSinceGameFinish = 0.f;
                game.hitSound.play();
            }
        }
    }

    //collision with borders
    void CheckBorderCollision(Game& game)
    {
        if (game.player.position.x - PLAYER_SIZE / 2.f < 0.f ||
            game.player.position.x + PLAYER_SIZE / 2.f > SCREEN_WIDTH ||
            game.player.position.y - PLAYER_SIZE / 2.f < 0.f ||
            game.player.position.y + PLAYER_SIZE / 2.f > SCREEN_HEIGHT)
        {

            game.isGameFinished = true;
            game.timeSinceGameFinish = 0.f;
            game.hitSound.play();

        }
    }

    //Get textures
    void LoadTextures(Game& game)
    {
        assert(game.playerTexture.loadFromFile(RESOURCES_PATH + "\\littl-fly-guy.png"));
        assert(game.appleTexture.loadFromFile(RESOURCES_PATH + "\\junk.png"));
        assert(game.obstacleTexture.loadFromFile(RESOURCES_PATH + "\\obstacle.png"));
        assert(game.backgroundTexture.loadFromFile(RESOURCES_PATH + "\\grass.png"));
        assert(game.gameOverTexture.loadFromFile(RESOURCES_PATH + "\\gameover.png"));
    }

    //get sounds
    void LoadSounds(Game& game)
    {
        assert(game.eatSoundBuffer.loadFromFile(RESOURCES_PATH + "\\AppleEat.wav"));
        assert(game.hitSoundBuffer.loadFromFile(RESOURCES_PATH + "\\Death.wav"));
        game.hitSound.setBuffer(game.hitSoundBuffer);
        game.eatSound.setBuffer(game.eatSoundBuffer);
    }

    //get fonts
    void LoadFont(Game& game)
    {
        assert(game.font.loadFromFile("Resources/Fonts/Roboto-Black.ttf"));
        game.gameText.setFont(game.font);
        game.gameText.setCharacterSize(24);
        game.gameText.setFillColor(sf::Color::White);
        game.gameText.setPosition(10.f, 10.f);
    }

    //restart game
    void RestartGame(Game& game)
    {
        InitPlayer(game.player, game);

        // init player
        for (int i = 0; i < NUM_APPLES; ++i)
        {
            InitApple(game.apples[i], game.appleTexture);
        }

        // init obstacle
        for (int i = 0; i < NUM_OBSTACLES; ++i)
        {
            InitObstacle(game.obstacle[i], game.obstacleTexture);
        }

        game.numEatenApples = 0;
        game.isGameFinished = false;
        game.timeSinceGameFinish = 0;
        game.gameText.setString("Garbage eaten: " );

    }


    //init game
    void InitGame(Game& game)
    {
        LoadTextures(game);
        LoadSounds(game);
        LoadFont(game);

        game.backgroundSprite.setTexture(game.backgroundTexture);

        if (game.mode & ApplesGame::GameMode::FiniteApples)
        {
            game.appleCount = game.limitApple; 
            for (int i = 0; i < game.limitApple; ++i)
            {
                game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
        }
        else if (game.mode & ApplesGame::GameMode::InfiniteApples)
        {
            for (int i = 0; i < NUM_APPLES; ++i)
            {
                game.apples[i].position = GetRandomPositionInScreen(SCREEN_WIDTH, SCREEN_HEIGHT);
            }
        }

        RestartGame(game);
    }

    //update game
    void UpdateGame(Game& game, float deltaTime)
    {
        if (!game.isGameFinished)
        {
            HandlePlayerInput(game);
            UpdatePlayer(game, deltaTime);
            CheckAppleCollision(game);
            CheckObstacleCollision(game);
            CheckBorderCollision(game);

            if ((game.mode & GameMode::FiniteApples) && game.appleCount == game.numEatenApples)
            {
                game.isGameFinished = true;
            }
        }
        else
        {
            if (game.timeSinceGameFinish <= PAUSE_LENGTH)
            {
                game.timeSinceGameFinish += deltaTime;
                game.backgroundSprite.setTexture(game.gameOverTexture);
            }
            else
            {
                game.backgroundSprite.setTexture(game.backgroundTexture);
                RestartGame(game);
            }
        }
    }



    void DrawGame(Game& game, sf::RenderWindow& window)
    {
        window.draw(game.backgroundSprite);

        DrawPlayer(game.player, window);

        int appleCountToDraw = (game.mode & ApplesGame::GameMode::FiniteApples) ? game.limitApple : NUM_APPLES;

        for (int i = 0; i < appleCountToDraw; ++i)
        {
            game.apples[i].sprite.setPosition(game.apples[i].position.x, game.apples[i].position.y);
            window.draw(game.apples[i].sprite);
        }

        for (int i = 0; i < NUM_OBSTACLES; ++i)
        {
            game.obstacle[i].sprite.setPosition(game.obstacle[i].position.x, game.obstacle[i].position.y);
            window.draw(game.obstacle[i].sprite);
        }

        window.draw(game.gameText);
    }




    void DeinializeGame(Game& game)
    {
    }
}
