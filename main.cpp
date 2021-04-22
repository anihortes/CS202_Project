// alden commit test
#include "Game.h"
#include <iostream>
#include <vector>
using std::vector;

sf::Event ev;
int tileSize = 50;

int main() {
    //makes rand number
    std::srand(static_cast<unsigned>(time(NULL)));

    sf::SoundBuffer deathBuf;
    deathBuf.loadFromFile("../DEAD.ogg");
    sf::Sound death;
    death.setBuffer(deathBuf);
    death.setVolume(10);

    sf::SoundBuffer buf;
    if(!buf.loadFromFile("../Dry_Guys.ogg"))
        return -1;
    sf::Sound music;
    music.setBuffer(buf);
    music.setLoop(true);

    //make game initializer
    Game game;

    //loop game
    music.play();
    while (game.running()) {
        //update game
        game.update();
        if(game.enemiesLogic() == true){
            death.play();
        }

        //render game
        game.render();
    }

    return EXIT_SUCCESS;
}
