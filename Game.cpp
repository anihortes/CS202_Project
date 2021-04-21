//
// Created by A. Harrison Owen on 4/18/2021.
//

#include "Game.h"
Game::Game(){
    this -> initVariables();
    this -> initWindow();
    this->initBackground();
    this->initEnemies();
    this->initPlayer();
}

Game::~Game(){
    delete this -> _window;
}



//Private function
void Game::initWindow() {
    this -> _window = new sf::RenderWindow
            (sf::VideoMode(800, 600), "Dungeon Fight!");// need game name
    this->_window->setFramerateLimit(60);

}

void Game::initBackground()
{
    static sf::Texture backgroundTexture = loadTextures("../dungeon_floor.png");
    _background.setTexture(backgroundTexture);
    this->_background.setScale(sf::Vector2f(2.0f, 1.5f));

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
        if(eHealth<1)
        {
            // instead of closing should give a player wins screen
            this->_window->close();
            break;
        }
        else if(pHealth < 1)
        {
            // instead of closing, should give a game over screen
            this->_window->close();
            break;
        }
        switch(this->_ev.type){
            case sf::Event::Closed:
                this->_window->close();
                break;
            case sf::Event::KeyPressed:
                if(this->_ev.key.code == sf::Keyboard::Escape)
                {
                    this->_window->close();
                    break;
                }
                else if(this->_ev.key.code == sf::Keyboard::Left)
                {
                    if(px - ex < 50 and py - ey < 70)
                    {
                        // if players interact, combat
                        this->pHealth -= 5;
                        this->eHealth -= 3;
                    }
                    else if(px < 20){
                        //write "*bonk*" to the screen
                        this->pHealth -= 2;
                    }
                    else{
                        // otherwise move. There should be an enemy move thing and a limiter to the screen;
                        this->px-=this->tile_size;
                        this->_player.setPosition(px,py);
                    }
                }
                else if(this->_ev.key.code == sf::Keyboard::Right)
                {
                    /* With current setup, can't attack enemy by moving right
                    if(px - ex > -50 and py - ey < 70)
                    {
                        this->pHealth -= 5;
                        this->eHealth -= 3;
                    }
                    else */if(px > 750){
                        //write "*bonk*" to the screen
                        this->pHealth -= 2;
                    }
                    else{
                        this->px+=this->tile_size;
                        this->_player.setPosition(px,py);
                    }

                }
                else if(this->_ev.key.code == sf::Keyboard::Down)
                {
                    /* with current setup, can't attack enemy by moving down
                    if(abs(px - ex) < 50 and abs(py - ey) < 50)
                    {
                        this->pHealth -= 5;
                        this->eHealth -= 3;
                    }
                    else */if(py > 500){
                        //write "*bonk*" to the screen
                        this->pHealth -= 2;
                    }
                    else{
                        this->py+=this->tile_size;
                        this->_player.setPosition(px,py);
                    }

                }
                else if(this->_ev.key.code == sf::Keyboard::Up)
                {
                    if(px - ex < 50 and py - ey < 70)
                    {
                        this->pHealth -= 5;
                        this->eHealth -= 3;
                    }
                    else if(py < 20){
                        //write "*bonk*" to the screen
                        this->pHealth -= 2;
                    }
                    else{
                        this->py-=this->tile_size;
                        this->_player.setPosition(px,py);
                    }

                }
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
    this->_window->draw(this->_background);
    this->_window->draw(this->_enemy);
    this->_window->draw(this->_player);
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
    this->ex = 1.f;
    this->ey = 20.f;
    static sf::Texture enemy1Texture = loadTextures("../enemy1.png");
    _enemy.setTexture(enemy1Texture);
    this->_enemy.setPosition(ex,ey);
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

void Game::initPlayer(){
    static sf::Texture playerTexture = loadTextures("../man.png");
    _player.setTexture(playerTexture);
    this->px = 100.f;
    this->py = 200.f;
    this->_player.setPosition(px,py);
    this->_player.setScale(sf::Vector2f(2.0f,2.0f));

}
