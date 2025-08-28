#pragma once

#include "board.hpp"

class C4Board;

class Player {

    public:

        Player(int playerNumber); // Constructor
        virtual ~Player(); // Destructor
        virtual int selectColumn(C4Board& c4board) = 0; // pure virtual

        int playerNumber;
        int playerScore;
};

class HumanPlayer : public Player {
    
    public:
        
        HumanPlayer(int playerNumber); 

        int selectColumn(C4Board& c4board);

};

class VirtualPlayer : public Player {

    public:

        VirtualPlayer(int playerNumber);

        int selectColumn(C4Board& c4board);

};