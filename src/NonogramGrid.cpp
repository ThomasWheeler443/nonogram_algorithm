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

/**
 * @brief Return tomography pointer
 * 
 * @return TomographySet* 
 */
TomographySet *NonogramGrid::getTomography() {
    return tomo;
}

/**
 * @brief Return grid pointer
 * 
 * @return Tile** 
 */
Tile **NonogramGrid::getGrid() {
    return grid;
}

/**
 * @brief Change a single tile of Monogram grid
 * 
 * @param tile 
 * @param x 
 * @param y 
 */
void NonogramGrid::changeTile(Tile tile, int x, int y) {
    grid[x][y] = tile;
}

/**
 * @brief Change a part of a row in the Monogram grid
 * 
 * @param tile 
 * @param row 
 * @param x1 
 * @param x2 
 */
void NonogramGrid::changeRow(Tile tile, int row, int x1, int x2) {
    for(int i = x1; i <= x2; i++) {
        grid[i][row] = tile;
    }
}

/**
 * @brief Change a part of a column in the Monogram grid
 * 
 * @param tile 
 * @param col 
 * @param y1 
 * @param y2 
 */
void NonogramGrid::changeCol(Tile tile, int col, int y1, int y2) {
    for(int i = y1; i <= y2; i++) {
        grid[col][i] = tile;
    }
}