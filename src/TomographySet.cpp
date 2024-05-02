#include "TomographySet.h"
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Construct a new Tomography Set:: Tomography Set object
 *
 */
TomographySet::TomographySet(int width, int height) {
    // Allocate rows and columns
    this->width = width;
    this->height = height;
    row = (Tomography *)calloc(height, sizeof(Tomography));
    col = (Tomography *)calloc(width, sizeof(Tomography));
}

/**
 * @brief Construct a new Tomography Set:: Tomography Set object
 *
 * @param file file to read
 */
TomographySet::TomographySet(const char *file) {

    // get file
    ifstream fin;
    fin.open(file);

    string line;

    // Get width and height
    getline(fin, line, ' ');
    width = stoi(line, 0, 10);

    getline(fin, line, '\n');
    height = stoi(line, 0, 10);

    // create row and col sets
    row = (Tomography *)calloc(height, sizeof(Tomography));
    col = (Tomography *)calloc(width, sizeof(Tomography));

    // Get row tomography
    int tempNum;
    for (int i = 0; i < height; i++) {
        getline(fin, line);
        if (line.compare("NONE") == 0) {
            row[i].size = 0;
            row[i].sum = 0;
            continue;
        }

        row[i].size = count(line.begin(), line.end(), ' ') + 1;
        row[i].tuple = (int *)calloc(row[i].size, sizeof(int));

        // Insert line elements
        int end = line.find(' ');
        int j = 0;
        while (j < row[i].size &&
               end != -1) { // Loop until no delimiter is left in the string.
            row[i].tuple[j] = stoi(line.substr(0, end), 0, 10);
            line.erase(line.begin(), line.begin() + end + 1);
            end = line.find(' ');
            j++;
        }
        row[i].tuple[j] = stoi(line.substr(0, end), 0, 10);

        row[i].sum = 0;
        for(int k = 0; k < row[i].size; k++) {
            row[i].sum += row[i].tuple[k];
        }
    }

    // Get col tomography
    for (int i = 0; i < width; i++) {
        getline(fin, line);
        if (line.compare("NONE") == 0) {
            continue;
        }

        col[i].size = count(line.begin(), line.end(), ' ') + 1;
        col[i].tuple = (int *)calloc(col[i].size, sizeof(int));

        // Insert line elements
        int end = line.find(' ');
        int j = 0;
        while (j < col[i].size &&
               end != -1) { // Loop until no delimiter is left in the string.
            col[i].tuple[j] = stoi(line.substr(0, end), 0, 10);
            line.erase(line.begin(), line.begin() + end + 1);
            end = line.find(' ');
            j++;
        }
        col[i].tuple[j] = stoi(line.substr(0, end), 0, 10);

        col[i].sum = 0;
        for(int k = 0; k < col[i].size; k++) {
            col[i].sum += col[i].tuple[k];
        }
    }

    fin.close();
}

/**
 * @brief Destroy the Tomography Set:: Tomography Set object
 *
 */
TomographySet::~TomographySet() {
    // Free rows
    for (int i = 0; i < height; i++) {
        free(row[i].tuple);
    }
    free(row);

    // Free columns
    for (int i = 0; i < width; i++) {
        free(col[i].tuple);
    }
    free(col);
}

/**
 * @brief Get the width of the tomography set
 *
 * @return int
 */
int TomographySet::getWidth() { return width; }

/**
 * @brief Get the height of the tomography set
 *
 * @return int
 */
int TomographySet::getHeight() { return height; }

/**
 * @brief Save tomography set as a file
 *
 * @param file
 */
void TomographySet::save(const char *file) {
    // create and clear file
    ofstream fout;
    fout.open(file);
    fout.clear();

    // Write width and height
    fout << width << ' ' << height << "\n";

    // Write row tomography
    for (int i = 0; i < height; i++) {
        if (row[i].size == 0) {
            fout << "NONE\n";
        } else {
            // Loop through tomography
            fout << row[i].tuple[0];
            for (int j = 1; j < row[i].size; j++) {
                fout << ' ' << row[i].tuple[j];
            }
            fout << "\n";
        }
    }

    // Write col tomography
    for (int i = 0; i < width; i++) {
        if (col[i].size == 0) {
            fout << "NONE\n";
        } else {
            // Loop through tomography
            fout << col[i].tuple[0];
            for (int j = 1; j < col[i].size; j++) {
                fout << ' ' << col[i].tuple[j];
            }
            fout << "\n";
        }
    }

    fout.close();
}

/**
 * @brief Get tomography for a specific row
 *
 * @param row
 * @return Tomography
 */
Tomography TomographySet::getRowTomography(int row) { return this->row[row]; }

/**
 * @brief Get tomography for a specific column
 *
 * @param col
 * @return Tomography
 */
Tomography TomographySet::getColTomography(int col) { return this->col[col]; }

/**
 * @brief Maximum size of the col tomography
 *
 * @return int
 */
int TomographySet::maxColSize() {
    int maxSize = 0;
    for (int i = 0; i < width; i++) {
        if (col[i].size > maxSize) {
            maxSize = col[i].size;
        }
    }

    return maxSize;
}

/**
 * @brief Maximum size of the row tomography
 *
 * @return int
 */
int TomographySet::maxRowSize() {
    int maxSize = 0;
    for (int i = 0; i < height; i++) {
        if (row[i].size > maxSize) {
            maxSize = row[i].size;
        }
    }

    return maxSize;
}

/**
 * @brief Get number of character spaces per number to print out the row
 * tomography
 *
 * @return int
 */
int TomographySet::charRowWidth() {
    // get largest number in row tomography
    int largest = 0;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < row[i].size; i++) {
            if (row[i].tuple[j] > largest) {
                largest = row[i].tuple[j];
            }
        }
    }

    return to_string(largest).length() + 1;
}

/**
 * @brief Get the number of character spaces per number to print out the col
 * tomography
 *
 * @return int
 */
int TomographySet::charColWidth() {
    // get largest number in col tomography
    int largest = 0;
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < col[i].size; i++) {
            if (col[i].tuple[j] > largest) {
                largest = col[i].tuple[j];
            }
        }
    }

    return to_string(largest).length() + 1;
}

/**
 * @brief Create a 2D array pf c strings representing the row tomography
 *
 * @param arrW
 * @param arrH
 * @param numChar
 * @return char***
 */
char ***TomographySet::rowFormatArray(int *arrW, int *arrH, int *numChar) {
    // Calculate width, height, and number of characters per string
    *arrW = this->maxRowSize();
    *arrH = height;
    *numChar = this->charRowWidth();

    int a;

    string tempString;

    // Create columns
    char ***outArr = (char ***)calloc(*arrW, sizeof(char **));
    for (int i = *arrW - 1; i >= 0; i--) {
        // Allocate rows
        outArr[i] = (char **)calloc(*arrH, sizeof(char *));
        for (int j = 0; j < *arrH; j++) {

            // Allocate c string and fill with spaces
            outArr[i][j] = (char *)calloc(*numChar, sizeof(char));
            memset(outArr[i][j], ' ', *numChar);

            // Start with last element of first array
            a = i - (*arrW - row[j].size);

            if (a >= 0) {
                tempString = to_string(row[j].tuple[a]);

                while (tempString.size() < *numChar) {
                    tempString = ' ' + tempString;
                }

                memcpy(outArr[i][j], tempString.c_str(), *numChar);
            }
        }
    }

    return outArr;
}

/**
 * @brief Create a 2d array of c strings representing the col tomography
 *
 * @param arrW
 * @param arrH
 * @param numChar
 * @return char***
 */
char ***TomographySet::colFormatArray(int *arrW, int *arrH, int *numChar) {

    // Calculate width, height, and number of characters per string
    *arrW = width;
    *arrH = this->maxColSize();
    *numChar = this->charColWidth();

    int a;

    string tempString;

    // Create columns
    char ***outArr = (char ***)calloc(*arrW, sizeof(char **));
    for (int i = 0; i < *arrW; i++) {
        // Allocate rows
        outArr[i] = (char **)calloc(*arrH, sizeof(char *));
        for (int j = *arrH - 1; j >= 0; j--) {

            // Allocate c string and fill with spaces
            outArr[i][j] = (char *)calloc(*numChar, sizeof(char));
            memset(outArr[i][j], ' ', *numChar);

            // Start with last element of first array
            a = j - (*arrH - col[i].size);

            if (a >= 0) {
                tempString = to_string(col[i].tuple[a]);
                while (tempString.size() < *numChar) {
                    tempString = ' ' + tempString;
                }

                memcpy(outArr[i][j], tempString.c_str(), *numChar);
            }
        }
    }

    return outArr;
}
