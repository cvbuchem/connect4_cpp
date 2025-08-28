#include <iostream>
#include <vector>
#include <memory>

#include "board.hpp"
#include "players.hpp"

void C4Board::showBoard(){

    // Define symbols
    symbolMap[0] = '.'; // empty space
    symbolMap[1] = '1'; // player 1 token
    symbolMap[2] = '2'; // player 2 token

    // Print the board in the terminal
    std::string horizontalBorder(2*N_COL, '-');
    std::cout << "|" << horizontalBorder << "-|" << std::endl;
    for (int i = 0; i < N_ROW; ++i) {
        std::cout << "| ";
        for (int j = 0; j < N_COL; ++j) {
            std::cout << symbolMap[board[i][j]] << " ";
        }
        std::cout << "|" << std::endl;
    }
    std::cout << "|" << horizontalBorder << "-|" << std::endl;
    std::cout << "  ";
    for (int i = 0; i < N_COL; ++i) {
        std::cout << i+1 << " ";
    }
    std::cout << '\n' << std::endl;    
}

// Returns vector with 0s for full columns and 1s for columns with one or more spots left
std::vector<int> C4Board::getAvailableColumns(){

    std::vector<int> availableColumns(N_COL);

    for (int j = 0; j < N_COL; j++) {

        // std::cout << "Col " << j << std::endl;
        for (int i = 0; i < N_ROW; i++) {

            // Break out of loop when available space encountered
            if (board[i][j] == 0) {

                availableColumns[j] = 1;
                // std::cout << "Found spot!" << std::endl;
                break;
            }
        }
    }

    return availableColumns;

}

void C4Board::placeToken(int selectedColumn, int playerNumber){
 
    for (int i = N_ROW-1; i >= 0; i--) {

        if (board[i][selectedColumn-1] == 0){

            board[i][selectedColumn-1] = playerNumber;
            break;

        }

    }

}

bool C4Board::checkConnect4(int playerNumber){

    int counter;

    // Check all collumns
    for (int j = 0; j < N_COL; j++){
        counter = 0;
        for (int i = 0; i < N_ROW; i++){
            if (board[i][j] == playerNumber){
                counter++;
                if (counter == 4){
                    return true;
                }
            }
            else{
                counter = 0;
            }
        }
    }

    // Check all rows
    for (int i = 0; i < N_ROW; i++){
        counter = 0;
        for (int j = 0; j < N_COL; j++){
            if (board[i][j] == playerNumber){
                counter++;
                if (counter == 4){
                    return true;
                }
            }
            else{
                counter = 0;
            }
        }
    }
    
    // bottom-left → top-right (/)
    for (int row = N_ROW - 1; row >= 3; --row) {
        for (int col = 0; col <= N_COL - 4; ++col) {
            int count = 0;
            for (int k = 0; k < 4; ++k) {
                if (board[row - k][col + k] == playerNumber) {
                    count++;
                    if (count == 4) return true;
                } else {
                    break;  // no need to continue this diagonal
                }
            }
        }
    }

    // top-left → bottom-right (\)
    for (int row = 0; row <= N_ROW - 4; ++row) {
        for (int col = 0; col <= N_COL - 4; ++col) {
            int count = 0;
            for (int k = 0; k < 4; ++k) {
                if (board[row + k][col + k] == playerNumber) {
                    count++;
                    if (count == 4) return true;
                } else {
                    break;  // no need to continue this diagonal
                }
            }
        }
    }

    return false;

    // 

}
