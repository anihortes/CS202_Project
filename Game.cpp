//
// Created by A. Harrison Owen on 4/18/2021.
//

#include "Game.h"
#include <cmath>
int spritePosition = 1;

/*
 * We really need to start getting combat and enemy collisions working.
void combat(int playerHealth,int enemyHealth){
    playerHealth -= 3;
    enemyHealth -= 5;
}

bool enemyCollision(int playerX,int playerY,int enemyX, int enemyY){
    for(auto &e : enemies){
        combat(pHealth,e.health);
    }
};
*/

bool Game::checkBorder(int x, int y, int dx, int dy) {
    x+=dx;
    y+=dy;
    // left right and bottom values aren't perfect, but pretty good.
    if(x > 760 or x < 40 or y > 520 or y < 00){return false;}
    else{return true;}
}

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
    this->maxEnemies = 6;
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
                    // since collision detection wasn't working with the enemy, I got rid of it entirely
                    if(this->checkBorder(_player.getPosition().x,_player.getPosition().y,-move_dist,0)){
                        if(spritePosition == 1){
                            this->_player.scale(-spritePosition, 1);
                            //this->_player.move(46,0); this breaks checking the border.
                            spritePosition=-1;
                        }
                        this->_player.move(-move_dist, 0.f);
                    }
                    else{
                        pHealth -=2;
                        std::cout << " player health: " << pHealth << std::endl;
                    }
                }
                else if(this->_ev.key.code == sf::Keyboard::Right)
                {
                    if(this->checkBorder(_player.getPosition().x,_player.getPosition().y,move_dist,0)){
                        if(spritePosition == -1){
                            this->_player.scale(-1, 1);
                            //this->_player.move(-46,0);
                            spritePosition=1;
                        }
                        this->_player.move(move_dist, 0.f);
                    }
                    else{
                        pHealth -=2;
                        std::cout << " player health: " << pHealth << std::endl;
                    }

                }
                else if(this->_ev.key.code == sf::Keyboard::Down)
                {
                    if(this->checkBorder(_player.getPosition().x,_player.getPosition().y,0,move_dist)){
                        this->_player.move(0.f, move_dist);
                    }
                    else{
                        pHealth -=2;
                        std::cout << " player health: " << pHealth << std::endl;
                    }
                }
                else if(this->_ev.key.code == sf::Keyboard::Up)
                {
                    if(this->checkBorder(_player.getPosition().x,_player.getPosition().y,0,-move_dist)){
                        this->_player.move(0.f, -move_dist);
                    }
                    else{
                        pHealth -=2;
                        std::cout << " player health: " << pHealth << std::endl;
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
    //this->ex = 300.f;
    //this->ey = 300.f;
    static sf::Texture enemy1Texture = loadTextures("../enemy1.png");
    _enemy.setTexture(enemy1Texture);
    //this->_enemy.setPosition(ex,ey);
    this->_enemy.setScale(sf::Vector2f(4.0f,4.0f));

}

void Game::spawnEnemies()
{
    this->_enemy.setPosition(
       static_cast<float>( rand() % static_cast<int>(this->_window->getSize().x + this->_enemy.getScale().x)),
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

    int enemyDist = 10;
    //this is the logic for enemy movemenet
    for (auto &e : this-> enemies)
    {
        //for the x positions
        if (e.getPosition().x < 0 + 10*this->_enemy.getScale().x)
        {
            e.move(rand() % enemyDist, 0);
            //std::cout << "worked[1]" << std::endl;
        }

        else if (e.getPosition().x > this->_window->getSize().x - 10*this->_enemy.getScale().x)
        {
            e.move(-(rand() % enemyDist), 0);
            ///std::cout << "worked[2]" << std::endl;
        }

        //for the y positions
        else if (e.getPosition().y < 0 + 10*this->_enemy.getScale().y)
        {
            e.move(0 , rand() % enemyDist);
            //std::cout << "worked[3]" << std::endl;
        }

        else if (e.getPosition().y > this->_window->getSize().y - 10*this->_enemy.getScale().y)
        {
            e.move(0 , -(rand() % enemyDist));
            //std::cout << "worked[4]" << std::endl;
        }
        //for x and y positions
        else
        {
            e.move(rand() % 19 + (-9), rand() % 19 + (-9));
        }

        // kills enemies on contact with player. not sure how to do that though
        //if (abs(e.getPosition().y - this->py) < 40 && abs(e.getPosition().x - this->px) < 20){
        //    e.move(-1000,-1000);
        //}

        //std::cout << e.getPosition().x << " , " << e.getPosition().y << std::endl;
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
    this->px = 400.f;
    this->py = 300.f;
    this->_player.setPosition(px,py);
    this->_player.setScale(sf::Vector2f(2.0f,2.0f));

    std::cout << " player health: " << pHealth << std::endl;
}
