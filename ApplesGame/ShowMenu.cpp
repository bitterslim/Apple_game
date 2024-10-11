#include "ShowMenu.h"
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int EnterAppleCount(sf::RenderWindow& window, ApplesGame::Game& game)
{
    std::string appleCountStr = "";
    sf::Text inputText;
    inputText.setFont(game.font);
    inputText.setCharacterSize(30);
    inputText.setPosition(100, 200);
    inputText.setFillColor(sf::Color::White);

    window.setKeyRepeatEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode >= '0' && event.text.unicode <= '9')
                {
                    appleCountStr += static_cast<char>(event.text.unicode);
                }
                else if (event.text.unicode == 8 && !appleCountStr.empty())
                {
                    appleCountStr.pop_back();
                }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Enter && !appleCountStr.empty())
                {
                    int appleCount = std::stoi(appleCountStr);
                    return appleCount;
                }

            }
        }

        window.clear();
        window.draw(game.backgroundSprite);

        game.gameText.setString("Enter the number of apples:");
        game.gameText.setCharacterSize(40);
        game.gameText.setPosition(100, 100);
        game.gameText.setFillColor(sf::Color::White);
        window.draw(game.gameText);

        inputText.setString("Apple Count: " + appleCountStr);
        window.draw(inputText);

        window.display();
    }

    window.setKeyRepeatEnabled(false);

    return -1;
}

int ShowMenu(sf::RenderWindow& window, ApplesGame::Game& game)
{
    game.font.loadFromFile("Resources/Fonts/Roboto-Black.ttf");
    game.gameText.setFont(game.font);

    int mode = 0;
    int appleCount = 0;

    bool finiteApplesSelected = false;
    bool infiniteApplesSelected = false;
    bool speedBoostSelected = false;
    bool noSpeedBoostSelected = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Num1:
                    finiteApplesSelected = !finiteApplesSelected;
                    if (finiteApplesSelected)
                    {
                        mode |= ApplesGame::GameMode::FiniteApples;
                        infiniteApplesSelected = false;
                        mode &= ~ApplesGame::GameMode::InfiniteApples;

                        int enteredAppleCount = EnterAppleCount(window, game);
                        if (enteredAppleCount == -1)
                        {
                            finiteApplesSelected = false;
                            mode &= ~ApplesGame::GameMode::FiniteApples;
                        }
                        else
                        {
                            appleCount = enteredAppleCount;
                            std::cout << "Player defined apple count: " << appleCount << std::endl;
                        }
                    }
                    else
                    {
                        mode &= ~ApplesGame::GameMode::FiniteApples;
                    }
                    break;
                case sf::Keyboard::Num2:
                    infiniteApplesSelected = !infiniteApplesSelected;
                    if (infiniteApplesSelected)
                    {
                        mode |= ApplesGame::GameMode::InfiniteApples;
                        finiteApplesSelected = false;
                        mode &= ~ApplesGame::GameMode::FiniteApples;
                    }
                    else
                    {
                        mode &= ~ApplesGame::GameMode::InfiniteApples;
                    }
                    break;
                case sf::Keyboard::Num3:
                    speedBoostSelected = !speedBoostSelected;
                    if (speedBoostSelected)
                    {
                        mode |= ApplesGame::GameMode::SpeedBoost;
                        noSpeedBoostSelected = false;
                        mode &= ~ApplesGame::GameMode::NoSpeedBoost;
                    }
                    else
                    {
                        mode &= ~ApplesGame::GameMode::SpeedBoost;
                    }
                    break;
                case sf::Keyboard::Num4:
                    noSpeedBoostSelected = !noSpeedBoostSelected;
                    if (noSpeedBoostSelected)
                    {
                        mode |= ApplesGame::GameMode::NoSpeedBoost;
                        speedBoostSelected = false;
                        mode &= ~ApplesGame::GameMode::SpeedBoost;
                    }
                    else
                    {
                        mode &= ~ApplesGame::GameMode::NoSpeedBoost;
                    }
                    break;
                case sf::Keyboard::Enter:
                    if ((mode & (ApplesGame::GameMode::FiniteApples | ApplesGame::GameMode::InfiniteApples)) &&
                        (mode & (ApplesGame::GameMode::SpeedBoost | ApplesGame::GameMode::NoSpeedBoost)))
                    {
                        ApplesGame::SetGameMode(game, mode, appleCount);
                        std::cout << "Game mode set with apple count: " << appleCount << std::endl;
                        return mode;
                    }
                    else
                    {
                        std::cout << "Please select both an apple mode and a speed mode before starting!" << std::endl;
                    }
                    break;
                default:
                    break;
                }
            }
        }

        window.clear();
        window.draw(game.backgroundSprite);

        game.gameText.setString("Select Game Mode");
        game.gameText.setCharacterSize(50);
        game.gameText.setPosition(100, 50);
        game.gameText.setFillColor(sf::Color::White);
        window.draw(game.gameText);

        game.gameText.setString("1: Finite Apples");
        game.gameText.setCharacterSize(30);
        game.gameText.setPosition(100, 150);
        game.gameText.setFillColor(finiteApplesSelected ? sf::Color::Green : sf::Color::White);
        window.draw(game.gameText);

        game.gameText.setString("2: Infinite Apples");
        game.gameText.setCharacterSize(30);
        game.gameText.setPosition(100, 200);
        game.gameText.setFillColor(infiniteApplesSelected ? sf::Color::Green : sf::Color::White);
        window.draw(game.gameText);

        game.gameText.setString("3: Speed Boost");
        game.gameText.setCharacterSize(30);
        game.gameText.setPosition(100, 250);
        game.gameText.setFillColor(speedBoostSelected ? sf::Color::Green : sf::Color::White);
        window.draw(game.gameText);

        game.gameText.setString("4: No Speed Boost");
        game.gameText.setCharacterSize(30);
        game.gameText.setPosition(100, 300);
        game.gameText.setFillColor(noSpeedBoostSelected ? sf::Color::Green : sf::Color::White);
        window.draw(game.gameText);

        game.gameText.setString("Press number keys to select options, Enter to start");
        game.gameText.setCharacterSize(20);
        game.gameText.setPosition(100, 400);
        game.gameText.setFillColor(sf::Color::White);
        window.draw(game.gameText);

        window.display();
    }

    return mode;
}
