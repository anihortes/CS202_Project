//
// Created by A. Harrison Owen on 4/18/2021.
//
#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#ifndef CS202_PROJECT_GAME_H
#define CS202_PROJECT_GAME_H

// This class is the game engine
class Game {
public:
    Game(); //constructor and destructor
    virtual ~Game();

    const bool running() const;

    void pollEvents();
    void update();
    void render();



private:
    sf::RenderWindow *_window;
    sf::Event _ev;

    //game objects
    //sf::RectangleShape _enemy;
    sf::Sprite _enemy;

    //private functions
    void initVariables();
    void initWindow();
    void initEnemies();
    sf::Texture loadTextures(std::string name);
};


#endif //CS202_PROJECT_GAME_H
