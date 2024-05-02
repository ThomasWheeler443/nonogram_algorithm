#include "../src/DFSSolver.h"
#include "../src/CharBuffer.h"
#include "../src/NonogramGrid.h"
#include "../src/TomographySet.h"
#include <chrono>
#include <iostream>


using namespace std;

int main() {
    //TomographySet set = TomographySet("../nonograms/5x5/single_example.txt");
    TomographySet set = TomographySet("../nonograms/tomo_test_in.txt");
    NonogramGrid nono = NonogramGrid(&set);
    DFSSolver dfs = DFSSolver(&nono);

    CharBuffer buffer = CharBuffer(&nono);

    cout << "Initial Nonogram:\n";

    buffer.print();

    cout << "Solving the Nonogram...\n";

    // Time and solve nonogram
    auto start = chrono::system_clock::now();

    dfs.solve();

    auto time = chrono::system_clock::now() - start;
    auto time_ms = chrono::duration_cast<chrono::nanoseconds>(time);

    // Print Results

    buffer.update();
    buffer.print();

    cout << "Nonogram checked " << dfs.getCount() << " grids\n";
    cout << "Nonogram solved in " << time_ms.count() << " ms\n";

    return 0;
}