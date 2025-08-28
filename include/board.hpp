#pragma once

#include <map>
#include <string>
#include <vector>

#include "players.hpp"

class C4Board {

    public:

        C4Board() = default;
        void showBoard();   
        std::vector<int> getAvailableColumns();
        void placeToken(int selectedColumn, int playerNumber);
        bool checkConnect4(int playerNumber);

        static constexpr int N_COL = 7;
        static constexpr int N_ROW = 6;
        int maxMoves = N_ROW*N_COL;

        
    private:
        
        int board[N_ROW][N_COL] = {};
        std::map<int, std::string> symbolMap;
    

};