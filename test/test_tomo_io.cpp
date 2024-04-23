#include "../src/TomographySet.h"
#include <iostream>

/**
 * @brief Test creation and saving of Tomography sets
 *
 * @return int
 */
int main() {
    // Make tomography set
    TomographySet *test = new TomographySet("../test/tomo_test_in.txt");
    std::cout << "Created Tomography from file\n";

    // Save tomography set
    test->save("../test/tomo_test_out.txt");
    std::cout << "Created file from Tomography\n";

    return 0;
}