#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <cstdint>
#include <list>

using std::list;

class GameState {
public:
    GameState();

    list<GameState>* getChildStatesList() const;
    uint8_t getPiecesCount() const;
    uint64_t hash() const;

    void print() const;
private:
    static const uint8_t    up      = 0,
                            down    = 1,
                            left    = 2,
                            right   = 3;
    static const int8_t     NO_NEIGHBOR = -1;
    static const uint64_t   defaultInitialState = 0x1FFFEFFFF;
    static const uint8_t    defaultPiecesCount = 32;
    static const int8_t     cellsVicinityTable[33][4];

    uint64_t    boardState;
    uint8_t     piecesCount;

    inline bool getBoardCell(uint8_t index) const {
        return (0x1ULL << index) & boardState;
    }

    inline void setBoardCell(uint8_t index, bool value) {
        if(value)
            boardState |= 0x1ULL << index;
        else
            boardState &= ~(0x1ULL << index);
    }

    inline void move(uint8_t index, uint8_t direction) {
        const uint8_t   neighbor =              (uint8_t)cellsVicinityTable[index][direction],
                        neighborOfNeighbor =    (uint8_t)cellsVicinityTable[neighbor][direction];

        boardState &= ~(0x1ULL << index);
        boardState &= ~(0x1ULL << neighbor);
        boardState |= 0x1ULL << neighborOfNeighbor;

        --piecesCount;
    }
};

#endif // _GAME_STATE_HPP_