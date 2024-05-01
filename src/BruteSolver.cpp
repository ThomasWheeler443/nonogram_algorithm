#include "BruteSolver.h"
#include "NonogramGrid.h"


/**
 * @brief Construct a new Brute Solver:: Brute Solver object
 * 
 * @param grid 
 */
BruteSolver::BruteSolver(NonogramGrid *grid) {
    count = 0;
    this->grid = grid;
}

/**
 * @brief Destroy the Brute Solver:: Brute Solver object
 * 
 */
BruteSolver::~BruteSolver() {
    delete grid;
}

/**
 * @brief Solve the nonogram using brute force
 * 
 */
void BruteSolver::solve() {

    count = 0;

    int width = grid->getWidth();
    int height = grid->getHeight();

    bool solved = false;
    while (!solved ) {
        
        incTile(0);

        // Verification done in O((m*n)^2) time
        solved = grid->verifyAll();

        count++;
    }

}

/**
 * @brief Get a 2d position from a 1d position
 * 
 * @param i 
 * @param x 
 * @param y 
 */
void BruteSolver::getPos(int i, int *x, int *y) {
    *x = i % grid->getWidth();
    *y = i / grid->getWidth();
    if (*y >= grid->getHeight()) {
        *y = *y % grid->getHeight();
    }
}

/**
 * @brief Binary increment on the nonogram grid
 * 
 * @param i 
 */
void BruteSolver::incTile(int i) {
    int x;
    int y;
    getPos(i, &x, &y);
    Tile tile = grid->getTile(x, y);
    if(tile == blank || tile == marked) {
        // Insert fill
        grid->changeTile(filled, x, y);
    }
    else {
        // Carry fill to next tile
        grid->changeTile(blank, x, y);
        incTile(i+1);
    }

}

/**
 * @brief Return the number of grids checked
 * 
 * @return unsigned long long int 
 */
unsigned long long int BruteSolver::getCount() {
    return count;
}