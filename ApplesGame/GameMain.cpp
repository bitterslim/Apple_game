#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Constants.h"
#include "Game.h"
#include "ShowMenu.h"
#include <iostream>



int main()
{
    using namespace ApplesGame;
    int seed = (int)time(nullptr);
    srand(seed);

    ApplesGame::Game game;
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Apples Game!");

    // Вызов функции ShowMenu
    int mode = ShowMenu(window, game);

    if (mode == -1)
    {
        std::cout << "Failed to load resources!" << std::endl;
        return 1;
    }

    // Game initialization
    SetGameMode(game, mode, game.appleCount);
    InitGame(game);

    // Init game clocks
    sf::Clock gameClock;
    float lastTime = gameClock.getElapsedTime().asSeconds();

    // Main loop
    while (window.isOpen())
    {
        // Reduce framerate to not spam CPU and GPU
        sf::sleep(sf::milliseconds(16));

        // Calculate time delta
        float currentTime = gameClock.getElapsedTime().asSeconds();
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        // Read events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                break;
            }
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                window.close();
                break;
            }
        }

        UpdateGame(game, deltaTime);

        // Draw game
        window.clear();
        DrawGame(game, window);

        window.display();
    }

    // Deinitialization
    DeinializeGame(game);

    return 0;
}
