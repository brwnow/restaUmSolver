#include "solver.hpp"

Solver::Solver(GameState initialState) :
    initialState(initialState),
    solution(nullptr)
{

}

weak_ptr<const list<GameState>> Solver::getSolution() const {
    return weak_ptr<const list<GameState>>(solution);
}

bool Solver::solve() {
    solution = shared_ptr<list<GameState>>(new list<GameState>());

    return recursiveSolve(initialState);
}

bool Solver::recursiveSolve(GameState currentState) {
    if(currentState.getPiecesCount() == 1) {
        solution->push_front(currentState);

        return true;
    } else {
        list<GameState> *childStates = currentState.getChildStatesList();
        bool success = false;

        for(list<GameState>::iterator it = childStates->begin(); it != childStates->end(); ++it) {
            success = recursiveSolve(*it);

            if(success)
                break;
        }

        if(success)
            solution->push_front(currentState);

        delete childStates;

        return success;
    }
}