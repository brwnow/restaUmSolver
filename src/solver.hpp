#ifndef _SOLVER_HPP_
#define _SOLVER_HPP_

#include <memory>
#include <list>

#include "gamestate.hpp"

using std::shared_ptr;
using std::weak_ptr;
using std::list;

class Solver {
public:
    Solver(GameState initialState);

    weak_ptr<const list<GameState>> getSolution() const;

    bool solve();

private:
    GameState initialState;
    shared_ptr<list<GameState>> solution;

    bool recursiveSolve(GameState currentState);

};

#endif // _SOLVER_HPP_