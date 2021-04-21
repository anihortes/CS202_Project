//
// Created by A. Harrison Owen on 4/18/2021.
//
#pragma once
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <ctime>
#include <vector>

#ifndef CS202_PROJECT_GAME_H
#define CS202_PROJECT_GAME_H

// This class is the game engine
class Game {
public:
    Game(); //constructor and destructor
    virtual ~Game();

    const bool running() const;

    bool checkBorder(int x,int y, int dx, int dy);

    void pollEvents();
    void update();
    void render();

    struct Enemy{
        Enemy(int x0,int y0,int ehealth);
        int x;
        int y;
        int health;
        sf::Sprite appearance;
    };

    int move_dist = 10.f;

private:
    sf::RenderWindow *_window;
    sf::Event _ev;

    //game objects
    sf::Sprite _background;

    sf::Sprite _player;
    void initPlayer();
    int px;
    int py;
    int pHealth = 100;
    int eHealth = 50;



    //enemies
    std::vector<Enemy> _enemies;
    //std::vector<sf::Sprite> enemies;
    sf::Sprite _enemy;
    int enemyAmount;
    int maxEnemies;
    int kills;

    //private functions
    void initVariables();
    void initWindow();
    void initBackground();


    void initEnemies();
    void spawnEnemies();
    void enemiesLogic();
    void renderEnemies();



    sf::Texture loadTextures(std::string name);
};


#endif //CS202_PROJECT_GAME_H
