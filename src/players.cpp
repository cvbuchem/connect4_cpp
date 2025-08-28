#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <random>

#include "players.hpp"
#include "board.hpp"

Player::Player(int playerNumber) : playerNumber(playerNumber) {

    int playerScore = 0;

}

Player::~Player() {} // Destructor implementation

HumanPlayer::HumanPlayer(int playerNumber) : Player(playerNumber) {}

int HumanPlayer::selectColumn(C4Board& c4board) {

    int col = -1;

    std::vector<int> availableColumns = c4board.getAvailableColumns();
    
    // for (int i = 0; i < c4board.N_COL; i++) {
    //     std::cout << availableColumns[i] << std::endl;
    // }

    // Ask for input until correct input is given
    bool correctInput = false;
    while (!correctInput) {

        // Ask for a read input
        std::cout << "Please enter the number of the column (1-" << c4board.N_COL << ")" << std::endl;
        std::cout << "where you wish to place your token: ";

        std::string input; 
        std::getline(std::cin, input);

        std::cout << std::endl;

        try {

            int inputCol = std::stoi(input); // throws if not a number
            
            if (inputCol < 1 || inputCol > c4board.N_COL) {

                std::cout << "Selected column number does not exist, please try another.\n" << std::endl;
            }

            else if (availableColumns[inputCol-1] == 1) {

                col = inputCol;
                correctInput = true;
            }

            else if (availableColumns[inputCol-1] == 0) {

                std::cout << "Selected column is already full, please try another.\n" << std::endl;

            }

        } 
        
        catch (const std::exception& e) {

            std::cout << "Invalid input. Please enter a valid input (a single integer).\n" << std::endl;

        }

    }

    return col;

}

VirtualPlayer::VirtualPlayer(int playerNumber) : Player(playerNumber) {}

int VirtualPlayer::selectColumn(C4Board& c4board) {

    // Random device and generator
    std::random_device rd;            // seed source
    std::mt19937 gen(rd());           // mersenne twister RNG
    std::uniform_int_distribution<> dist(1, c4board.N_COL);

    std::vector<int> availableColumns = c4board.getAvailableColumns();
    bool correctInput = false;

    int col;

    while (!correctInput) {

        // Generate random number
        int inputCol = dist(gen);

        if (availableColumns[inputCol-1] == 1) {

            col = inputCol;
            correctInput = true;
        }

    }

    return col;

}