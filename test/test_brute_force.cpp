#include "../src/CharBuffer.h"
#include "../src/NonogramGrid.h"
#include "../src/TomographySet.h"
#include "../src/BruteSolver.h"
#include <chrono>
#include <iostream>

using namespace std;

int main() {
    TomographySet set = TomographySet("../nonograms/5x5_single_example.txt");
    NonogramGrid nono = NonogramGrid(&set);
    BruteSolver brute = BruteSolver(&nono);

    CharBuffer buffer = CharBuffer(&nono);

    cout << "Initial Nonogram:\n";

    buffer.print();

    cout << "Solving the Nonogram...\n";

    // Time and solve nonogram
    auto start = chrono::system_clock::now();

    brute.solve();

    auto time = chrono::system_clock::now() - start;
    auto time_ms = chrono::duration_cast<chrono::milliseconds>(time);

    // Print Results

    buffer.update();
    buffer.print();

    cout << "Nonogram constructed " << brute.getCount() << " grids\n";
    cout << "Nonogram solved in " << time_ms.count() << " ms\n";
    

    return 0;
}