#include "../src/CharBuffer.h"
#include "../src/NonogramGrid.h"
#include "../src/TomographySet.h"
#include <iostream>


int main() {
    TomographySet set = TomographySet("../test/tomo_test_in.txt");
    NonogramGrid nono = NonogramGrid(&set);
    CharBuffer buffer = CharBuffer(&nono);

    buffer.print();

    std::cout << "\nEdit:\n";

    nono.changeRow(filled, 2, 4, 5);
    nono.changeRow(filled, 3, 2, 7);
    nono.changeRow(filled, 4, 0, 9);
    nono.changeRow(filled, 8, 0, 9);
    nono.changeRow(filled, 9, 0, 9);

    buffer.update();
    buffer.print();

    return 1;
}