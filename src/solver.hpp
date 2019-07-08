#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include <cstdint>
#include <memory>
#include <list>
#include <bitset>

#include "gamestate.hpp"

using std::shared_ptr;
using std::weak_ptr;
using std::list;
using std::bitset;

class Solver {
public:
    Solver(GameState initialState);

    weak_ptr<const list<GameState>> getSolution() const;

    bool solve();

private:
    static const uint64_t   exploredSetBitmask = 0x100000000ULL,
                            bitmask32bits = 0xFFFFFFFFULL;

    GameState                   initialState;
    bitset<0xFFFFFFFF>          *lowbitExploredSet,
                                *hibitExploredSet;
    shared_ptr<list<GameState>> solution;

    bool recursiveSolve(GameState currentState);

};

#endif // _SOLVER_HPP_