//
// Created by A. Harrison Owen on 4/18/2021.
//

#include "Game.h"
Game::Game(){
    this -> initVariables();
    this -> initWindow();
    this->initEnemies();
}

Game::~Game(){
    delete this -> _window;
}



//Private function
void Game::initWindow() {
    this -> _window = new sf::RenderWindow
            (sf::VideoMode(400, 400), "Basic SFML Dungeon Game");// need game name
    this->_window->setFramerateLimit(60);
}

//Private function
void Game::initVariables() {
    this -> _window = nullptr;

}

const bool Game::running() const {
    return this -> _window -> isOpen();
}

void Game::pollEvents() {
    while(this -> _window -> pollEvent(this->_ev)){
        switch(this->_ev.type){
            case sf::Event::Closed:
                this->_window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->_ev.key.code == sf::Keyboard::Escape)
                    this->_window->close();
                break;
        }
    }
}

//under the hood logic and where things are
void Game::update() {
    //players turn
    this -> pollEvents();
    //enemy turn


}


// visualizes all positions and items in game
// clear old frame
// render objects
// disp. frame in window
void Game::render() {
    this->_window->clear();
    //draw objects here
    this->_window->draw(this->_enemy);
    this->_window->display();
}

void Game::initEnemies() {
    //this->_enemy.setPosition(1.f,20.f);
    //this->_enemy.setSize(sf::Vector2f(100.f,100.f));
    //this->_enemy.setScale(sf::Vector2f(0.5f,0.5f));
    //this->_enemy.setFillColor(sf::Color::Cyan);
    //this->_enemy.setOutlineColor(sf::Color::Blue);
    //this->_enemy.setOutlineThickness(2.f);

    //load texture/sprite
    static sf::Texture enemy1Texture = loadTextures("../enemy1.png");
    _enemy.setTexture(enemy1Texture);
    this->_enemy.setPosition(1.f,20.f);
    this->_enemy.setScale(sf::Vector2f(4.0f,4.0f));

}

sf::Texture Game::loadTextures(std::string name){

    sf::Texture texture;
    if (!texture.loadFromFile(name))
    {
        std::cout << "Texture load Failed!" << std::endl;
    }
    return texture;
}