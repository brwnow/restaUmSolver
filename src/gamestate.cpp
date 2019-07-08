#include "gamestate.hpp"

#include <windows.h>

const int8_t GameState::cellsVicinityTable[33][4] =
                                {
                                    {NO_NEIGHBOR, 3, NO_NEIGHBOR, 1},   // cell 0
                                    {NO_NEIGHBOR, 4, 0, 2},             // cell 1
                                    {NO_NEIGHBOR, 5, 1, NO_NEIGHBOR},   // cell 2
                                    {0, 8, NO_NEIGHBOR, 4},             // cell 3
                                    {1, 9, 3, 5},                       // cell 4
                                    {2, 10, 4, NO_NEIGHBOR},            // cell 5
                                    {NO_NEIGHBOR, 13, NO_NEIGHBOR, 7},  // cell 6
                                    {NO_NEIGHBOR, 14, 6, 8},            // cell 7
                                    {3, 15, 7, 9},                      // cell 8
                                    {4, 16, 8, 10},                     // cell 9
                                    {5, 17, 9, 11},                     // cell 10
                                    {NO_NEIGHBOR, 18, 10, 12},          // cell 11
                                    {NO_NEIGHBOR, 19, 11, NO_NEIGHBOR}, // cell 12
                                    {6, 20, NO_NEIGHBOR, 14},           // cell 13
                                    {7, 21, 13, 15},                    // cell 14
                                    {8, 22, 14, 16},                    // cell 15
                                    {9, 23, 15, 17},                    // cell 16
                                    {10, 24, 16, 18},                   // cell 17
                                    {11, 25, 17, 19},                   // cell 18
                                    {12, 26, 18, NO_NEIGHBOR},          // cell 19
                                    {13, NO_NEIGHBOR, NO_NEIGHBOR, 21}, // cell 20
                                    {14, NO_NEIGHBOR, 20, 22},          // cell 21
                                    {15, 27, 21, 23},                   // cell 22
                                    {16, 28, 22, 24},                   // cell 23
                                    {17, 29, 23, 25},                   // cell 24
                                    {18, NO_NEIGHBOR, 24, 26},          // cell 25
                                    {19, NO_NEIGHBOR, 25, NO_NEIGHBOR}, // cell 26
                                    {22, 30, NO_NEIGHBOR, 28},          // cell 27
                                    {23, 31, 27, 29},                   // cell 28
                                    {24, 32, 28, NO_NEIGHBOR},          // cell 29
                                    {27, NO_NEIGHBOR, NO_NEIGHBOR, 31}, // cell 30
                                    {28, NO_NEIGHBOR, 30, 32},          // cell 31
                                    {29, NO_NEIGHBOR, 31, NO_NEIGHBOR}  // cell 32
                                };

GameState::GameState() :
    boardState(defaultInitialState),
    piecesCount(defaultPiecesCount)
{

}

list<GameState>* GameState::getChildStatesList() const {
    list<GameState> *childStatesList = new list<GameState>();

    for(uint8_t cell = 0; cell < 33; ++cell) {
        if(getBoardCell(cell)) {
            for(uint8_t direction = up; direction <= right; ++direction) {
                int8_t neighbor = cellsVicinityTable[cell][direction];

                if(neighbor != NO_NEIGHBOR && getBoardCell((uint8_t)neighbor)) {
                    int8_t neighborOfNeighbor = cellsVicinityTable[neighbor][direction];

                    if(neighborOfNeighbor != NO_NEIGHBOR && !getBoardCell((uint8_t)neighborOfNeighbor)) {
                        GameState childState = *this;

                        childState.move(cell, direction);

                        childStatesList->push_front(childState);
                    }
                }
            }
        }
    }

    return childStatesList;
}

uint8_t GameState::getPiecesCount() const {
    return piecesCount;
}

uint64_t GameState::hash() const {
    return boardState;
}

void GameState::print() const {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {0, 0};

    SetConsoleCursorPosition(hConsole, pos);
    WriteConsole(hConsole, " ", 1, NULL, NULL);

    for(int k = 0; k < 35; ++k) {
        pos.Y = k;
        SetConsoleCursorPosition(hConsole, pos);
        WriteConsole(hConsole, "                                                                                                                             ", 125, NULL, NULL);
    }

    for(int i = 0; i < 33; ++i) {
        if(i < 6) {
            pos.X = (i % 3) * 3 + 8;
            pos.Y = (i / 3) * 2 + 1;

            SetConsoleCursorPosition(hConsole, pos);
            
            if(getBoardCell(i))
                WriteConsole(hConsole, "\262", 1, NULL, NULL);
            else
                WriteConsole(hConsole, "\372", 1, NULL, NULL);
        } else if(i > 26) {
            pos.X = ((i - 27) % 3) * 3 + 8;
            pos.Y = ((i - 27) / 3) * 2 + 11;

            SetConsoleCursorPosition(hConsole, pos);
            
            if(getBoardCell(i))
                WriteConsole(hConsole, "\262", 1, NULL, NULL);
            else
                WriteConsole(hConsole, "\372", 1, NULL, NULL);
        } else {
            pos.X = ((i - 6) % 7) * 3 + 2;
            pos.Y = ((i - 6) / 7) * 2 + 5;

            SetConsoleCursorPosition(hConsole, pos);
            
            if(getBoardCell(i))
                WriteConsole(hConsole, "\262", 1, NULL, NULL);
            else
                WriteConsole(hConsole, "\372", 1, NULL, NULL);
        }
    }
}