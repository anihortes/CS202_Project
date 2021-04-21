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

    void pollEvents();
    void update();
    void render();



private:
    sf::RenderWindow *_window;
    sf::Event _ev;

    //game objects
    //sf::RectangleShape _enemy;
    sf::Sprite _background;
    /*
    class Player_Character(){
        public:
        Player_Character():x_location(0),y_location(0){};

        //move_player(sf::Event ev){}
        sf::Sprite _player = loadTextures("../enemy1.png");


        int x_location;
        int y_location;
        private:
    }
*/
    sf::Sprite _player;
    void initPlayer();
    int px;
    int py;
    int ex;
    int ey;
    int tile_size = 10;
    int pHealth = 100;
    int eHealth = 50;


    //enemies
    std::vector<sf::Sprite> enemies;
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
