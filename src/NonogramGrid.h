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

    TomographySet *getTomography();
    Tile **getGrid();

    Tile getTile(int x, int y);

    void changeTile(Tile tile, int x, int y);
    void changeRow(Tile tile, int row, int x1, int x2);
    void changeCol(Tile tile, int col, int y1, int y2);

    bool verifyRow(int row);
    bool verifyCol(int col);
    bool verifyAll();

    void markRow(int row);
    void markCol(int col);

    int getWidth();
    int getHeight();

    void setGrid(Tile **grid);
};

#endif
