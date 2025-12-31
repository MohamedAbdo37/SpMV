#include <iostream>
#include <vector>
#include "utils.h"
// #include "SpMV.h"

using namespace std;

int main() {
    cout << "Hello World!" << endl;

    testUtils();

    cout << "test generate a dense vector:" << endl;
    srand(time(0)); 
    vector<double> vec = generateDoubleVector(10);
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i] << " ";
    }
    cout << endl;

    
    return 0;
}
