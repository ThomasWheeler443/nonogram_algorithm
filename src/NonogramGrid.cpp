#include "NonogramGrid.h"
#include "TomographySet.h"
#include <cstdlib>

/**
 * @brief Construct a new Nonogram Grid:: Nonogram Grid object
 *
 */
NonogramGrid::NonogramGrid(int width, int height) {

    // Get width and height
    this->width = width;
    this->height = height;

    // Create blank tomography set
    tomo = (TomographySet *)calloc(1, sizeof(TomographySet));
    tomo = new TomographySet(width, height);

    // Create tile grid
    // Allocate columns
    grid = (Tile **)calloc(width, sizeof(Tile *));
    for (int i = 0; i < width; i++) {
        // Allocate rows
        grid[i] = (Tile *)calloc(height, sizeof(Tile));
    }
}

NonogramGrid::NonogramGrid(TomographySet *tomo) {
    
    //Get tomography
    this->tomo = tomo;

    //get width and height
    width = tomo->getWidth();
    height = tomo->getHeight();

    // Create tile grid
    // Allocate columns
    grid = (Tile **)calloc(width, sizeof(Tile *));
    for (int i = 0; i < width; i++) {
        // Allocate rows
        grid[i] = (Tile *)calloc(height, sizeof(Tile));
    }
}

/**
 * @brief Destroy the Nonogram Grid:: Nonogram Grid object
 *
 */
NonogramGrid::~NonogramGrid() {
    
    // Free grid
    for (int i = 0; i < width; i++) {
        free(grid[i]);
    }
    free(grid);

    // Free tomography
    delete tomo;
}

void NonogramGrid::print() {
    //
}