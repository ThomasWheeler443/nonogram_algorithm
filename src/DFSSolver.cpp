#include "DFSSolver.h"
#include "NonogramGrid.h"
#include "TomographySet.h"
#include <cstddef>
#include <cstdlib>
#include <cstring>
//#include <iostream>

/**
 * @brief Construct a new DFSSolver::DFSSolver object
 *
 * @param nono
 */
DFSSolver::DFSSolver(NonogramGrid *nono) {
    this->nono = nono;

    width = nono->getWidth();
    height = nono->getHeight();

    // Allocate row buffers based off height
    rowBuffer = (Tile ***)calloc(height, sizeof(Tile **));
    numRowPos = (int *)calloc(height, sizeof(int));

    // Calculate number of row pos per row
    calcPosib();

    int count = 0;
}

/**
 * @brief Destroy the DFSSolver::DFSSolver object
 *
 */
DFSSolver::~DFSSolver() {

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < numRowPos[i]; i++) {
            free(rowBuffer[i][j]);
        }
        free(rowBuffer[i]);
    }

    free(rowBuffer);
    free(numRowPos);

    delete nono;
}

/**
 * @brief Solve for best
 *
 */
void DFSSolver::solve() {

    count = 0;

    // Create initial grid
    Tile **initGrid = copyGrid(NULL);

    // Find and set nonogram to correct grid
    bool done = false;
    genAndTestGrids(initGrid, 0, &done);
}

/**
 * @brief Solve for the correct grid using initial grid
 *
 * @param currGrid
 * @param level
 */
void DFSSolver::genAndTestGrids(Tile **currGrid, int level, bool *done) {

    if (*done) {
        return;
    }
    // Test current nono
    nono->setGrid(currGrid);
    bool valid = nono->verifyAll();
    count++;
    if (valid) {
        *done = true;
        return;
    } else if (level < height) {
        // Generate necessary rows
        int numChild = numRowPos[level];
        if (rowBuffer[level] == nullptr) {
            genPosRows(level);
        }

        // Loop through children
        for (int i = 0; i < numChild; i++) {
            Tile **newGrid = copyGrid(currGrid);
            addRowToGrid(newGrid, level, i);
            genAndTestGrids(newGrid, level + 1, done);
            freeGrid(newGrid);
        }
    }
}

void DFSSolver::genPosRows(int row) {
    // Allocate row buffer fully for row
    rowBuffer[row] = (Tile **)calloc(numRowPos[row], sizeof(Tile *));
    for (int i = 0; i < numRowPos[row]; i++) {
        rowBuffer[row][i] = (Tile *)calloc(width, sizeof(Tile));
    }

    // Generate all row possibilities from the BB List
    Tomography tomo = nono->getTomography()->getRowTomography(row);
    int numSlots = width - tomo.sum + 1;
    int rowCount = 0;
    bool *initList = (bool *)calloc(numSlots, sizeof(bool));
    genFromBBList(row, initList, 0, numSlots, tomo.size, &rowCount);
}

/**
 * @brief
 *
 * @param row
 * @param currList
 * @param pos
 * @param numSlots
 * @param balls
 * @param rowCount
 */
void DFSSolver::genFromBBList(int row, bool *currList, int pos, int numSlots,
                              int balls, int *rowCount) {

    // Test if current list is viable
    if (pos + balls == numSlots) {
        // Fill remaining slots with balls
        for (int i = pos; i < numSlots; i++) {
            currList[i] = true;
        }
        createRowFromBBList(row, currList, numSlots, rowCount);
        *rowCount += 1;
    } else if (balls == 0) {
        createRowFromBBList(row, currList, numSlots, rowCount);
        *rowCount += 1;
    } else {
        // Allocate arrays
        bool *currList1 = (bool *)calloc(numSlots, sizeof(bool));
        bool *currList2 = (bool *)calloc(numSlots, sizeof(bool));
        memcpy(currList1, currList, numSlots);
        memcpy(currList2, currList, numSlots);

        // Split list based off if included or not
        // Put ball in pos
        currList1[pos] = true;
        genFromBBList(row, currList1, pos + 1, numSlots, balls - 1, rowCount);

        // Do not put ball is pos
        genFromBBList(row, currList2, pos + 1, numSlots, balls, rowCount);

        // Destroy arrays when finished
        free(currList1);
        free(currList2);
    }
}

/**
 * @brief Convert and Balls and Bins list into a nonogram row
 *
 * @param row
 * @param list
 * @param numSlots
 * @param rowCount
 */
void DFSSolver::createRowFromBBList(int row, bool *list, int numSlots,
                                    int *rowCount) {
    /*
    std::cout << "Row: " << row << " | Gen index: " << *rowCount << "\n\t[";
    for (int i = 0; i < numSlots; i++) {
        std::cout << list[i] << " ";
    }
    std::cout << "]\n";
    */

    Tomography tomo = nono->getTomography()->getRowTomography(row);
    int tilePos = 0;
    int tomoIndex = 0;
    for (int i = 0; i < numSlots; i++) {
        if (list[i]) {
            for (int j = tilePos; j < tomo.tuple[tomoIndex] + tilePos; j++) {
                rowBuffer[row][*rowCount][j] = filled;
            }
            tilePos += tomo.tuple[tomoIndex];
            tomoIndex++;
        }
        tilePos++;
    }

    // Print list
    /*
    std::cout << "\t";
    for (int i = 0; i < width; i++) {
        Tile tile = rowBuffer[row][*rowCount][i];
        if (tile == blank) {
            std::cout << "- ";
        } else if (tile == filled) {
            std::cout << "# ";
        }
    }
    std::cout << "\n";
    */
}

/**
 * @brief Calculate the number of possibilites for each row
 *
 */
void DFSSolver::calcPosib() {

    for (int i = 0; i < height; i++) {
        Tomography tempTomo = nono->getTomography()->getRowTomography(i);

        // See paper for derivation of equation
        numRowPos[i] = nCr(width - tempTomo.sum + 1, tempTomo.size);
    }
}

/**
 * @brief Calculate n Choose r possibilities
 *
 * @param n
 * @param r
 * @return int
 */
int DFSSolver::nCr(int n, int r) { return fact(n) / (fact(r) * fact(n - r)); }

/**
 * @brief Calculate n!
 *
 * @param n
 * @return int
 */
int DFSSolver::fact(int n) { return (n == 1 || n == 0) ? 1 : fact(n - 1) * n; }

/**
 * @brief Copy a grid to make a new grid
 *
 * @param orig
 * @return Tile**
 */
Tile **DFSSolver::copyGrid(Tile **orig) {

    Tile **newGrid = (Tile **)calloc(width, sizeof(Tile *));
    for (int i = 0; i < width; i++) {
        // Allocate rows
        newGrid[i] = (Tile *)calloc(height, sizeof(Tile));
    }

    if (orig != NULL) {
        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                newGrid[i][j] = orig[i][j];
            }
        }
    }

    return newGrid;
}

/**
 * @brief Add a row from the generated rows to the grid
 *
 * @param grid
 * @param row
 * @param genRowIndex
 */
void DFSSolver::addRowToGrid(Tile **grid, int row, int genRowIndex) {
    for (int i = 0; i < width; i++) {
        grid[i][row] = rowBuffer[row][genRowIndex][i];
    }
}

/**
 * @brief Destroy a grid
 *
 * @param grid
 */
void DFSSolver::freeGrid(Tile **grid) {
    for (int i = 0; i < width; i++) {
        free(grid[i]);
    }
    free(grid);
}

int DFSSolver::getCount() { return count; }
