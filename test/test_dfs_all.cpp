#include "../src/DFSSolver.h"
#include "../src/CharBuffer.h"
#include "../src/NonogramGrid.h"
#include "../src/TomographySet.h"
#include <chrono>
#include <iostream>
#include <vector>


using namespace std;

int main() {

    const int numSizes = 7;
    vector<vector<const char*>> files;
    files.resize(numSizes);
    
    // 3x3
    files[0].resize(2);
    files[0][0] = "../nonograms/3x3/1.txt";
    files[0][1] = "../nonograms/3x3/2.txt";

    // 4x4
    files[1].resize(3);
    files[1][0] = "../nonograms/4x4/1.txt";
    files[1][1] = "../nonograms/4x4/2.txt";
    files[1][2] = "../nonograms/4x4/3.txt";

    // 5x5
    files[2].resize(5);
    files[2][0] = "../nonograms/5x5/1.txt";
    files[2][1] = "../nonograms/5x5/2.txt";
    files[2][2] = "../nonograms/5x5/3.txt";
    files[2][3] = "../nonograms/5x5/4.txt";
    files[2][4] = "../nonograms/5x5/5.txt";
    
    // 6x6
    files[3].resize(3);
    files[3][0] = "../nonograms/6x6/1.txt";
    files[3][1] = "../nonograms/6x6/2.txt";
    files[3][2] = "../nonograms/6x6/3.txt";

    // 7x7
    files[4].resize(5);
    files[4][0] = "../nonograms/7x7/1.txt";
    files[4][1] = "../nonograms/7x7/2.txt";
    files[4][2] = "../nonograms/7x7/3.txt";
    files[4][3] = "../nonograms/7x7/4.txt";
    files[4][4] = "../nonograms/7x7/5.txt";

    // 8x8
    files[5].resize(3);
    files[5][0] = "../nonograms/8x8/1.txt";
    files[5][1] = "../nonograms/8x8/2.txt";
    files[5][2] = "../nonograms/8x8/3.txt";

    // 10x10
    files[6].resize(2);
    files[6][0] = "../nonograms/10x10/1.txt";
    files[6][1] = "../nonograms/10x10/2.txt";


    TomographySet *set;
    NonogramGrid *nono;
    DFSSolver *dfs;
    CharBuffer *buffer;

    long long int dfsAvg[numSizes];


    for(int i = 0; i < numSizes; i++) {
        for(int j = 0; j < files[i].size(); j++) {
            cout << "File: \"" << files[i][j] << "\":\n";


            set = new TomographySet(files[i][j]);
            nono = new  NonogramGrid(set);
            dfs = new DFSSolver(nono);
            buffer = new CharBuffer(nono);

            // Time and solve nonogram
            auto start = chrono::system_clock::now();

            dfs->solve();

            auto time = chrono::system_clock::now() - start;
            auto time_ms = chrono::duration_cast<chrono::nanoseconds>(time);

            // Print Results

            buffer->update();
            buffer->print();

            cout << "\tNonogram checked " << dfs->getCount() << " grids\n";
            cout << "\tNonogram solved in " << time_ms.count() << " ns\n";

            // get new average
            if(j == 0) {
                dfsAvg[i] = time_ms.count();
            }
            else {
                dfsAvg[i] += (time_ms.count() - dfsAvg[i]) / (j+2);
            }

            delete set;
            delete nono;
            delete dfs;
            delete buffer;
        }
    }

    for(int i = 0; i < numSizes; i++) {
        cout << "Folder of: " << files[i][0] << "\n";
        cout << "\tDFS Avg: " << dfsAvg[i] << " ns\n";
    }

    return 0;
}