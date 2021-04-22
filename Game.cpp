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
    this->maxEnemies = 6;
    this -> enemyAmount = 0;
}

const bool Game::running() const {
    return this -> _window -> isOpen();
}

//sprite flip on move left causes hitbox to not match sprite.
//but moving to adjust causes error with border check
void flipSprite(sf::Sprite &player, int &spritePosition,int move){
    // if sprite not facing same direction as moving, flip sprite.
    if(spritePosition != move){
        spritePosition = move;
        player.scale(-1, 1);
    }
};
void Game::pollEvents() {
    while(this -> _window -> pollEvent(this->_ev)){
        // specify win condition, i.e. 10 kills
        if(this->kills>9)
        {
            // tells the player they won, then ends game.
            std::cout << "YOU WIN!" << std::endl;
            // instead of closing should give a player wins screen
            this->_window->close();
            break;
        }
        // specify lose condition.
        else if(pHealth < 1)
        {
            // prints Game Over and ends game.
            std::cout << "How did you run into that many walls?!" << std::endl;
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
                //on left or right click, player will flip to look and move in that direction
                else if(this->_ev.key.code == sf::Keyboard::Left)
                {
                    flipSprite(this->_player,spritePosition,-1);
                    this->playerMove(-1,0);
                }
                else if(this->_ev.key.code == sf::Keyboard::Right)
                {
                    flipSprite(this->_player,spritePosition,1);
                    this->playerMove(1,0);
                }
                // on up or down click, player will move in that direction.
                else if(this->_ev.key.code == sf::Keyboard::Down){this->playerMove(0,1);}
                else if(this->_ev.key.code == sf::Keyboard::Up){this->playerMove(0,-1);}
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

Game::Enemy::Enemy(int x0, int y0, int ehealth):x(x0),y(y0),health(ehealth){}

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
    //this->_enemy.setTexture(enemy1Texture);
    //this->enemies.push_back(this->_enemy);

    Enemy _e(_enemy.getPosition().x,_enemy.getPosition().y,this->eHealth);
    _e.appearance.setScale(sf::Vector2f(4.0f,4.0f));
    _e.appearance.setPosition(_e.x,_e.y);
    _e.appearance.setTexture(enemy1Texture);
    this->_enemies.push_back(_e);
}

void deathSound(sf::Sound death){
    sf::SoundBuffer buf;
    buf.loadFromFile("../DEAD.ogg");
    death.setBuffer(buf);
    death.play();
    while(death.getStatus() != sf::Sound::Status::Stopped){

    }
}

bool Game::enemiesLogic()
{
    bool death = false;
    if (this->enemyAmount < this->maxEnemies)
    {
        this->spawnEnemies();
        enemyAmount++;//might want to spawn batches of enemys
    }

    int enemyDist = 10;
    //this is the logic f|| enemy movemenet
    int enemynum = 0;
    for (auto &e : this-> _enemies)
    {
        ++enemynum;

        //f|| the x positions
        if (e.appearance.getPosition().x < 0 + 10*this->_enemy.getScale().x)
        {
            e.appearance.move(rand() % enemyDist, 0);
            e.x = e.appearance.getPosition().x;
        }

        else if (e.appearance.getPosition().x > this->_window->getSize().x - 10*this->_enemy.getScale().x)
        {
            e.appearance.move(-(rand() % enemyDist), 0);
            e.x = e.appearance.getPosition().x;
        }

        //f|| the y positions
        else if (e.appearance.getPosition().y < 0 + 10*this->_enemy.getScale().y)
        {
            e.appearance.move(0 , rand() % enemyDist);
            e.y = e.appearance.getPosition().y;
        }

        else if (e.appearance.getPosition().y > this->_window->getSize().y - 10*this->_enemy.getScale().y)
        {
            e.appearance.move(0 , -(rand() % enemyDist));
            e.y = e.appearance.getPosition().y;
        }
        //f|| x and y positions
        else
        {
            e.appearance.move(rand() % 19 + (-9), rand() % 19 + (-9));
            e.x = e.appearance.getPosition().x;
            e.y = e.appearance.getPosition().y;
        }

        // damages enemies on contact with player.
        if (abs(e.y - _player.getPosition().y) < 60 && abs(e.x - _player.getPosition().x) < 40){
            if (e.health > 0)
            {
                e.health -=1;
                std::cout << "enemy " << enemynum << " health " << e.health << std::endl;
            }
            else if(e.health == 0){
                death = true;
                this->kills += 1;
                std::cout << this->kills << " kills" << std::endl;
                _enemies.erase(begin(_enemies)+(enemynum-1));
                this->enemyAmount--;
            }
        }

    }
    return death;
}

void Game::renderEnemies()
{
    for (auto& e : this-> _enemies)
    {
        this->_window->draw(e.appearance);
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
// checks if the movement will put you past screen boundaries.
bool Game::checkBorder(int x, int y, int dx, int dy) {
    x+=dx;
    y+=dy;
    // if you can make the move returns true, if you hit a wall it returns false.
    if(x > 760 || x < 40 || y > 520 || y < 00){return false;}
    else{return true;}
}
// give it unit directions of movement
void Game::playerMove(int hori,int vert) {
    //checks if it'll hit a wall if it moves in direction specified
    if(this->checkBorder(_player.getPosition().x,_player.getPosition().y,move_dist*hori,move_dist*vert)){
        this->_player.move(move_dist*hori, move_dist*vert);
    }
    else{
        // if it hits wall, you take damage for running into a wall and it lets you know.
        pHealth -=2;
        std::cout << " player health: " << pHealth << std::endl;
    }
}