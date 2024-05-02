#ifndef DFS_SOLVE_H
#define DFS_SOLVE_H

#include "NonogramGrid.h"

class DFSSolver {

    private:
        NonogramGrid *nono;
        Tile ***rowBuffer;
        int *numRowPos;
        int width;
        int height;
        int count;
        

    public:
        DFSSolver(NonogramGrid* nono);
        ~DFSSolver();

        void solve();

        void genAndTestGrids(Tile **currGrid, int level, bool *done);

        void genPosRows(int row);

        void genFromBBList(int row, bool *currList, int pos, int numSlots, int balls, int *rowCount);

        void createRowFromBBList(int row, bool *list, int numSlots, int *rowCount);

        void calcPosib();

        int nCr(int n, int r);

        int fact(int n);

        Tile **copyGrid(Tile **orig);

        void addRowToGrid(Tile **grid, int row, int genRowIndex);

        void freeGrid(Tile **grid);

        int getCount();
};

#endif