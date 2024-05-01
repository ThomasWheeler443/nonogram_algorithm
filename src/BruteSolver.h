#ifndef BRUTE_SOLVE_H
#define BRUTE_SOLVE_H

#include "NonogramGrid.h"

class BruteSolver {

    private:
        NonogramGrid *grid;
        unsigned long long int count;

    public:
        BruteSolver(NonogramGrid *grid);
        ~BruteSolver();

        void solve();

        void getPos(int i, int *x, int *y);

        void incTile(int i);

        unsigned long long int getCount();
        
};

#endif