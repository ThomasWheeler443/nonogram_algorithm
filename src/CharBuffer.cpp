#include "CharBuffer.h"
#include "NonogramGrid.h"
#include "TomographySet.h"
#include <cstdlib>
#include <cstring>
#include <iostream>


using namespace std;

/**
 * @brief Construct a new Char Buffer:: Char Buffer object
 *
 * @param nonogram
 */
CharBuffer::CharBuffer(NonogramGrid *nonogram) {

    this->nonogram = nonogram;

    TomographySet *set = nonogram->getTomography();
    Tile **grid = nonogram->getGrid();

    int rowH;

    // Get formatted row tomography string array
    char ***rowTomoBuff = set->rowFormatArray(&rowW, &rowH, &lCharLength);

    // Get formatted row tomography string array
    int colW;

    char ***colTomoBuff = set->colFormatArray(&colW, &colH, &rCharLength);

    // Get width
    width = rowW + colW;
    height = rowH + colH;

    // Create buffer
    // Create columns
    buffer = (char ***)calloc(width, sizeof(char **));
    for (int i = 0; i < width; i++) {
        // Create rows
        buffer[i] = (char **)calloc(height, sizeof(char *));
        for (int j = 0; j < height; j++) {

            // Divide into quadrants
            // Quadrant 2: (Empty)
            if (i < rowW && j < colH) {
                buffer[i][j] = (char *)calloc(lCharLength, sizeof(char));
                memset(buffer[i][j], ' ', lCharLength);
            }

            // Quadrant 1: (colFormatArray)
            else if (j < colH) {
                buffer[i][j] = colTomoBuff[i - rowW][j];
            }

            // Quadrant 3: (rowFormatArray)
            else if (i < rowW) {
                buffer[i][j] = rowTomoBuff[i][j - colH];
            }

            // Quadrant 4: (grid)
            else {
                buffer[i][j] = (char *)calloc(rCharLength, sizeof(char));
                memset(buffer[i][j], ' ', rCharLength);

                switch (grid[i - rowW][j - colH]) {
                case blank:
                    buffer[i][j][rCharLength - 1] = '-';
                    break;
                case marked:
                    buffer[i][j][rCharLength - 1] = 'X';
                    break;
                case filled:
                    buffer[i][j][rCharLength - 1] = '#';
                    break;
                }
            }
        }
    }
}

void CharBuffer::update() {

    Tile **grid = nonogram->getGrid();

    for (int i = rowW; i < width; i++) {
        for (int j = colH; j < height; j++) {
            switch (grid[i - rowW][j - colH]) {
            case blank:
                buffer[i][j][rCharLength - 1] = '-';
                break;
            case marked:
                buffer[i][j][rCharLength - 1] = 'X';
                break;
            case filled:
                buffer[i][j][rCharLength - 1] = '#';
                break;
            }
        }
    }
}

void CharBuffer::print() {

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << buffer[j][i];
        }
        cout << "\n";
    }
}

void CharBuffer::resetPos() {
    for(int i = 0; i < height; i++) {
        cout << "\r";
    }
}