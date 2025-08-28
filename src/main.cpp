#include <iostream>

#include "game.hpp"

int main() {

    std::cout << "\n################################" << std::endl;
    std::cout << "## Let\'s play some Connect 4! ##" << std::endl;
    std::cout << "################################\n" << std::endl;

    Game game;
    game.gameSetup();   
    game.playGame(); 

}