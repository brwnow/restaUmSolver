#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include "gamestate.hpp"

class Solver {
public:
    Solver(GameState initialState);

private:
    GameState initialState;
};

#endif // _SOLVER_HPP_