#ifndef NONO_GRID_H
#define NONO_GRID_H

#include "TomographySet.h"

/**
 * @brief Tiles can either be blank, marked as blank, or filled
 *
 */
enum Tile { blank, marked, filled };

class NonogramGrid {
  private:
    int width;
    int height;
    TomographySet *tomo;
    Tile **grid;


  public:
    NonogramGrid(int width, int height);
    NonogramGrid(TomographySet *tomo);

    ~NonogramGrid();
    
    void print();
};

#endif
