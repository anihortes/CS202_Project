// alden commit test
#include "Game.h"
#include <iostream>
#include <vector>
using std::vector;

sf::Event ev;
int tileSize = 50;

class Character{
public:
    Character() {
        x = 0;
        y = 0;
        movespeed = 100.0/tileSize;

        for(auto i = 0; i < 4; ++i){
            move[i] = false;
            walking = false;
            myRect.setSize(sf::Vector2f(50,50));
        }
    }
    float x,y,movespeed;
    void keyMove();
    void moving();

    enum MOVE{UP,DOWN,RIGHT};
    bool move[4];
    bool walking;
    int nextSpot;

    sf::RectangleShape myRect;
};

int main() {
    Game game;

    while (game.running()) {
        game.update();
        game.render();
    }

    return EXIT_SUCCESS;
}
