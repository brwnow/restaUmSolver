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

    inline bool stateAlreadyVisited(uint64_t stateHash) {
        return stateHash & exploredSetBitmask ?
                                    hibitExploredSet->test( (size_t)((stateHash & bitmask32bits) - 0x1ULL) ) :
                                    lowbitExploredSet->test( (size_t)((stateHash & bitmask32bits) - 0x1ULL) );
    }

    inline void markStateAsVisited(uint64_t stateHash) {
        if(stateHash & exploredSetBitmask)
            hibitExploredSet->set( (size_t)((stateHash & bitmask32bits) - 0x1ULL) );
        else
            lowbitExploredSet->set( (size_t)((stateHash & bitmask32bits) - 0x1ULL) );
    }

    bool recursiveSolve(GameState currentState);

};

#endif // _SOLVER_HPP_