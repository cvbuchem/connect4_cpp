#pragma once

#include <memory>

#include "players.hpp"
#include "board.hpp"

class Player; 

class Game {
    
    public:
        
        Game() = default; 
        void gameSetup();
        void playGame();
        void playRound();
        void playerTurn(std::shared_ptr<Player> player, C4Board& c4board);

        std::shared_ptr<Player> playerSelection(int playerNumber);

    private:

        int round;
        std::shared_ptr<Player> player1;
        std::shared_ptr<Player> player2;

};