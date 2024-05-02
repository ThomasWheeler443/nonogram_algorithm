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

    // Get tomography
    this->tomo = tomo;

    // get width and height
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
TomographySet *NonogramGrid::getTomography() { return tomo; }

/**
 * @brief Return grid pointer
 *
 * @return Tile**
 */
Tile **NonogramGrid::getGrid() { return grid; }

/**
 * @brief Return tile in grid at pos (x,y)
 * 
 * @param x 
 * @param y 
 * @return Tile
 */
Tile NonogramGrid::getTile(int x, int y) {
    return grid[x][y];
}

/**
 * @brief Change a single tile of Monogram grid
 *
 * @param tile
 * @param x
 * @param y
 */
void NonogramGrid::changeTile(Tile tile, int x, int y) { grid[x][y] = tile; }

/**
 * @brief Change a part of a row in the Monogram grid
 *
 * @param tile
 * @param row
 * @param x1
 * @param x2
 */
void NonogramGrid::changeRow(Tile tile, int row, int x1, int x2) {
    for (int i = x1; i <= x2; i++) {
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
    for (int i = y1; i <= y2; i++) {
        grid[col][i] = tile;
    }
}

/**
 * @brief Verify that a row is filled in to tomography specifications. Does not
 * mean the row is correct
 *
 * @param row
 * @return true
 * @return false
 */
bool NonogramGrid::verifyRow(int row) {
    bool isStreak = false;
    int streakNum = 0;
    int streak = 0;
    int tomoIndex = 0;
    Tomography rowTomo = tomo->getRowTomography(row);
    for (int i = 0; i < width; i++) {
        if (!isStreak && grid[i][row] == filled) {
            if (tomoIndex >= rowTomo.size) {
                return false;
            }
            isStreak = true;
            streakNum++;
            streak++;
        } else if (grid[i][row] == filled) {
            streak++;
        } else if (isStreak) {
            isStreak = false;
            if (streak != rowTomo.tuple[tomoIndex]) {
                return false;
            }
            tomoIndex++;
            streak = 0;
        }
    }
    return streakNum == rowTomo.size;
}

/**
 * @brief Verify that a column is filled in to tomography specifications. Does
 * not mean the column is correct
 *
 * @param col
 * @return true
 * @return false
 */
bool NonogramGrid::verifyCol(int col) {
    bool isStreak = false;
    int streakNum = 0;
    int streak = 0;
    int tomoIndex = 0;
    Tomography colTomo = tomo->getColTomography(col);
    for (int i = 0; i < width; i++) {
        if (!isStreak && grid[col][i] == filled) {
            if (tomoIndex >= colTomo.size) {
                // Too many sections
                return false;
            }
            isStreak = true;
            streakNum++;
            streak++;
        } else if (grid[col][i] == filled) {
            streak++;
        } else if (isStreak) {
            isStreak = false;
            if (streak != colTomo.tuple[tomoIndex]) {
                // Section has incorrect size
                return false;
            }
            tomoIndex++;
            streak = 0;
        }
    }
    return streakNum == colTomo.size;
}

/**
 * @brief Verify that a board is filled in correctly
 * 
 * @return true 
 * @return false 
 */
bool NonogramGrid::verifyAll() {
    for(int i = 0; i < width; i++) {
        if(!verifyCol(i)) {
            return false;
        }
    }
    for(int i = 0; i < height; i++) {
        if(!verifyRow(i)) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Replace blank spaces in row with marked spaces
 * 
 * @param row 
 */
void NonogramGrid::markRow(int row) {
    for(int i = 0; i < width; i++) {
        if(grid[i][row] == blank) {
            grid[i][row] = marked;
        }
    }
}

/**
 * @brief Replace blank spaces in row with marked spaces 
 * @param col 
 */
void NonogramGrid::markCol(int col) {
    for(int i = 0; i < height; i++) {
        if(grid[col][i] == blank) {
            grid[col][i] = marked;
        }
    }
}

/**
 * @brief Return the width of the grid
 * 
 * @return int 
 */
int NonogramGrid::getWidth() {
    return width;
}

/**
 * @brief Return the height of the grid
 * 
 * @return int 
 */
int NonogramGrid::getHeight() {
    return height;
}


void NonogramGrid::setGrid(Tile **grid) {
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            this->grid[i][j] = grid[i][j];
        }
    }
}