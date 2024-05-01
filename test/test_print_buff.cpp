#include "../src/CharBuffer.h"
#include "../src/NonogramGrid.h"
#include "../src/TomographySet.h"
#include <iostream>


int main() {
    TomographySet set = TomographySet("../nonograms/tomo_test_in.txt");
    NonogramGrid nono = NonogramGrid(&set);
    CharBuffer buffer = CharBuffer(&nono);

    buffer.print();

    nono.changeRow(filled, 2, 4, 5);
    nono.changeRow(filled, 3, 2, 7);
    nono.changeRow(filled, 4, 0, 9);
    nono.changeRow(filled, 8, 0, 9);
    nono.changeRow(filled, 9, 0, 9);

    nono.changeCol(filled, 2, 2, 9);
    nono.changeCol(filled, 3, 1, 9);
    nono.changeCol(filled, 4, 0, 9);
    nono.changeCol(filled, 7, 2, 9);
    

    nono.changeTile(filled, 1, 3);
    nono.changeTile(filled, 8, 3);

    nono.changeTile(filled, 6, 2);
    nono.changeTile(filled, 5, 0);

    nono.changeRow(filled, 1, 5, 6);

    std::cout << "\nIs Complete: " << nono.verifyAll() << "\n";

    buffer.update();
    buffer.print();

    return 0;
}