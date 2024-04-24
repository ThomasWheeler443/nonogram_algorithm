#include "../src/TomographySet.h"
#include <iostream>

using namespace std;

/**
 * @brief Test creation and saving of Tomography sets
 *
 * @return int
 */
int main() {
    // Make tomography set
    TomographySet *test = new TomographySet("../test/tomo_test_in.txt");
    cout << "Created Tomography from file\n";

    // Save tomography set
    test->save("../test/tomo_test_out.txt");
    cout << "Created file from Tomography\n";

    //Print tomography row set

    cout << "Printing formatted row string:\n";   

    int width;
    int height;
    int numChar;

    char ***formArr1 = test->rowFormatArray(&width, &height, &numChar);

    cout << "W: " << width << " H: " << height << " n: " << numChar << "\n";

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            cout << formArr1[j][i];
        }
        cout << "\n";
    }

    cout << "Printing formatted col string:\n";   

    char ***formArr2 = test->colFormatArray(&width, &height, &numChar);

    cout << "W: " << width << " H: " << height << " n: " << numChar << "\n";

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            cout << formArr2[j][i];
        }
        cout << "\n";
    }

    return 0;
}