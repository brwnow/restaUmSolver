#include <iostream>
#include <list>
#include <memory>

#include "gamestate.hpp"
#include "solver.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::list;
using std::shared_ptr;

int main(int argc, char *argv[]) {
    GameState gameState;
    Solver solver(gameState);

    if(solver.solve()) {
        shared_ptr<const list<GameState>> solutionList = solver.getSolution().lock();

        if(solutionList) {
            int counter = 1;

            for(list<GameState>::const_iterator it = solutionList->begin(); it != solutionList->end(); ++it) {
                (*it).print();

                cout << "Step " << counter++ << " of " << solutionList->size();

                cin.ignore();
            }
        } else {
            cout << "Error while trying to print the final solution.\n\n";
        }
    } else {
        cout << "FAIL!!! :(\n\n";
    }

    return 0;
}