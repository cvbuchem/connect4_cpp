#include <iostream>
#include <string>
#include <sstream>

#include "game.hpp"
#include "players.hpp"
#include "board.hpp"

void Game::gameSetup() {

    std::cout << "Setting up game" << std::endl;

    round = 0;

    player1 = playerSelection(1);
    player2 = playerSelection(2);

}

std::shared_ptr<Player> Game::playerSelection(int playerNumber) {

    // Display player selection menu
    std::cout << "\n### Player " << playerNumber << " selection ###\n" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "1: Human player" << std::endl;
    std::cout << "2: Virtual player - Random placement" << std::endl;
    std::cout << "3: Virtual player - Smart placement (NOT AVAILABLE)" << std::endl;

    int playerType = -1; 

    while (playerType != 1 && playerType != 2) {

        std::cout << "\nPlease select player type for player one using the corresponding number: ";

        std::string input; 
        std::getline(std::cin, input); 

        try {
         
            playerType = std::stoi(input);  // throws if not a number

            if (playerType == 3) {
                std::cout << "This option is not yet available. Please select another.\n";
            } 
            
            else if (playerType != 1 && playerType != 2) {
                std::cout << "Invalid input. Please enter the number of an existing player type.\n";
            }

        } catch (const std::exception& e) {
            std::cout << "Invalid input. Please enter a valid input (a single digit)\n";
        }

    }

    if (playerType == 1) {
        return std::make_unique<HumanPlayer>(playerNumber);
    } 
    
    else {
        return std::make_unique<VirtualPlayer>(playerNumber);
    }

}

void Game::playGame(){

    while (player1->playerScore < 3 && player2->playerScore < 3 && round <=5){
        playRound();
    }

    if (player1->playerScore > player2->playerScore){
        std::cout << "\n################################" << std::endl;
        std::cout << "#### Player 1 wins the game! ###" << std::endl;
        std::cout << "################################\n" << std::endl;
    }

    else if (player2->playerScore > player1->playerScore){
        std::cout << "\n################################" << std::endl;
        std::cout << "### Player 2 wins the game!  ###" << std::endl;
        std::cout << "################################\n" << std::endl;
    }

    else if (player2->playerScore > player1->playerScore){
        std::cout << "\n################################" << std::endl;
        std::cout << "########## It's a tie! #########" << std::endl;
        std::cout << "################################\n" << std::endl;
    }

}

void Game::playRound(){

    round += 1;
    std::cout << "\n### Round " << round << " ###" << std::endl;
    
    C4Board c4board;
    c4board.showBoard();

    int maxMoves = c4board.N_COL*c4board.N_ROW;
    int moveCounter = 0;

    // game loop will start here 
    while (moveCounter < maxMoves){

        moveCounter += 1;
        std::shared_ptr<Player> player;

        // Determine which player's turn it is
        if (moveCounter % 2 == 1){

            player = player1;
        }
        else {

            player = player2;
        }

        playerTurn(player, c4board); 
        c4board.showBoard();

        // Check for victory
        if (c4board.checkConnect4(player->playerNumber)){
            std::cout << "Player " << player->playerNumber << " wins this round!" << std::endl;
            player->playerScore++;
            break;
        };

    }

    if (moveCounter == maxMoves){

        std::cout << "It's a tie! Both players get a point." << std::endl;
        player1->playerScore++;
        player2->playerScore++;

    }

    std::cout << "\n    - Score -" << std::endl;
    std::cout << "   Player 1: " << player1->playerScore << std::endl;
    std::cout << "   Player 2: " << player2->playerScore << "\n" << std::endl;

}

void Game::playerTurn(std::shared_ptr<Player> player, C4Board& c4board){
    
    std::cout << "- It is player " << player->playerNumber << "'s turn -" << std::endl;

    int selectedColumn = player->selectColumn(c4board);
    
    c4board.placeToken(selectedColumn, player->playerNumber);

}