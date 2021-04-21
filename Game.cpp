//
// Created by A. Harrison Owen on 4/18/2021.
//

#include "Game.h"
#include <cmath>
int spritePosition = 1;

Game::Game(){
    this->initVariables();
    this->initWindow();
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
    
    this->kills = 0;
    this->maxEnemies = 5;
    this -> enemyAmount = 0;

}

const bool Game::running() const {
    return this -> _window -> isOpen();
}

void Game::pollEvents() {
    //std::cout << "sprite: " << this->_enemy.getPosition().x << std::endl;
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
                    std::cout << "X-space diff: " << abs(px-ex) << " Y-space diff: " << abs(py - ey) << "player health: " << pHealth << std::endl;
                    if(ex - px < 40 && abs(py-ey) < 80)
                    {
                        // if players interact, combat
                        this->pHealth -= 5;
                        this->eHealth -= 3;
                        this->ey += 50;
                        this->_enemy.move(0, 50);
                    }
                    else if(px < 20){
                        //write "*bonk*" to the screen
                        this->pHealth -= 2;
                    }
                    else{
                        // otherwise move. There should be an enemy move thing and a limiter to the screen;
                        if(spritePosition == 1){
                            this->_player.scale(-spritePosition, 1);
                            spritePosition=-1;

                            this->_player.move(23,0);
                        }
                        else {
                            this->px -= this->tile_size;
                            this->_player.setPosition(px, py);
                        }
                    }
                }
                else if(this->_ev.key.code == sf::Keyboard::Right)
                {
                    std::cout << "X-space diffX: " << abs(px-ex) << " Y-space diff: " << abs(py - ey) << "player health: " << pHealth << std::endl;

                    if(ex - px < 40 && abs(py-ey) < 50)
                    {
                        this->pHealth -= 5;
                        this->eHealth -= 3;
                        ey -= 50;
                        this->_enemy.move(0, -50);
                    }
                    else if(px > 750){
                        //write "*bonk*" to the screen
                        this->pHealth -= 2;
                    }
                    else{
                        //flips player sprite left or right when they move
                        if(spritePosition == -1){
                            this->_player.scale(-1, 1);
                            this->_player.move(-23,0);

                            spritePosition = 1;
                        }
                        //else just move
                        else {
                            this->px += this->tile_size;
                            this->_player.setPosition(px, py);
                        }
                    }

                }
                else if(this->_ev.key.code == sf::Keyboard::Down)
                {
                    std::cout << "X-space diffX: " << abs(px-ex) << " Y-space diff: " << abs(py - ey) << "player health: " << pHealth << std::endl;
                    //std::cout << py << "  " << ey << std::endl;
                    //with current setup, can't attack enemy by moving down
                    if(ey - py < 50 && abs(px-ex)<40)
                    {
                        this->pHealth -= 5;
                        this->eHealth -= 3;
                        this->ex += 10;
                        this->_enemy.move(10,0);
                    }
                    else if(py > 500){
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
                    std::cout << "X-space diffX: " << abs(px-ex) << " Y-space diff: " << abs(py - ey) << 
                        "player health: "<< pHealth << std::endl;

                    if(py - ey < 50 && abs(px-ex) < 40)
                    {
                        this->pHealth -= 5;
                        this->eHealth -= 3;
                        this->ex -= 10;
                        this->_enemy.move(-10,0);
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

    this->enemiesLogic();

}


// visualizes all positions and items in game
// clear old frame
// render objects
// disp. frame in window
void Game::render() {
    this->_window->clear();
    //draw objects here
    this->_window->draw(this->_background);
    this->renderEnemies();
   // this->_window->draw(this->_enemy);
    this->_window->draw(this->_player);
    this->_window->display();
}

void Game::initEnemies() {
    this->ex = 300.f;
    this->ey = 300.f;
    static sf::Texture enemy1Texture = loadTextures("../enemy1.png");
    _enemy.setTexture(enemy1Texture);
    this->_enemy.setPosition(ex,ey);
    this->_enemy.setScale(sf::Vector2f(4.0f,4.0f));

}

void Game::spawnEnemies()
{
    this->_enemy.setPosition(
       static_cast<float>( rand() % static_cast<int>(this->_window->getSize().x - this->_enemy.getScale().x)),
       static_cast<float>( rand() % static_cast<int>(this->_window->getSize().y + this->_enemy.getScale().y))
    );

    static sf::Texture enemy1Texture = loadTextures("../enemy1.png");
    this->_enemy.setTexture(enemy1Texture);

    this->enemies.push_back(this->_enemy);
}

void Game::enemiesLogic()
{
    if (this->enemyAmount < this->maxEnemies)
    {
        this->spawnEnemies();
        enemyAmount++;//might want to spawn batches of enemys
    }

    //this is the logic for enemy movemenet
    for (auto &e : this-> enemies) 
    {
        e.move(1.f, 1.f);
    }
}

void Game::renderEnemies()
{
    for (auto& e : this-> enemies)
    {
        this->_window->draw(e);
    }
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
    this->px = 200.f;
    this->py = 300.f;
    this->_player.setPosition(px,py);
    this->_player.setScale(sf::Vector2f(2.0f,2.0f));

}
