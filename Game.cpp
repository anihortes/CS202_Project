//
// Created by A. Harrison Owen on 4/18/2021.
//

#include "Game.h"
Game::Game(){
    this -> initVariables();
    this -> initWindow();
}

Game::~Game(){
    delete this -> _window;
}



//Private function
void Game::initWindow() {
    this -> _window = new sf::RenderWindow(sf::VideoMode(400, 400), "SFML window");
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
    this -> pollEvents();
}


// visualizes all positions and items in game
// clear old frame
// render objects
// disp. frame in window
void Game::render() {
    this->_window->clear();
    //draw objects here

    this->_window->display();
}