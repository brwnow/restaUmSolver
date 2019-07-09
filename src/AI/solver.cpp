#include "solver.hpp"

Solver::Solver(GameState initialState) :
    initialState(initialState),
    lowbitExploredSet(new bitset<0xFFFFFFFF>()),
    hibitExploredSet(new bitset<0xFFFFFFFF>()),
    solution(nullptr)
{

}

Solver::~Solver() {
    delete lowbitExploredSet;
    delete hibitExploredSet;
}

weak_ptr<const list<GameState>> Solver::getSolution() const {
    return weak_ptr<const list<GameState>>(solution);
}

bool Solver::solve() {
    solution = shared_ptr<list<GameState>>(new list<GameState>());

    lowbitExploredSet->reset();
    hibitExploredSet->reset();

    return recursiveSolve(initialState);
}

bool Solver::recursiveSolve(GameState currentState) {
    if(stateAlreadyVisited(currentState.hash())) {
        return false;
    } else if(currentState.getPiecesCount() == 1) {
        solution->push_front(currentState);

        return true;
    } else {
        list<GameState> *childStates = currentState.getChildStatesList();
        bool success = false;

        markStateAsVisited(currentState.hash());

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