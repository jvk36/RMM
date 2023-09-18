#include <iostream>
#include <cstdlib>

#include "RMM.h"
using namespace std;

void work(int size, int* pIntArray);

int main() {
    RMM rmm;
    cout << "Region based Memory pool initialised" << endl;
    rmm.print_status();

    for (int j = 0; j <= 2; j++) {
        cout << "Random integer arrays of size 1 thru 5 constructed in the RMM pool: "<< endl;
        // create 5 integer arrays of size 1 thru 5 in the pool and do some work on them
        for (int i = 0; i <= 4; i++) {
            int* pIntArray = (int*)rmm.allocate((i + 1) * sizeof(int));
            work(i + 1, pIntArray);
        }

        rmm.print_status();
        
        // Free the region.
        cout << "Reset the region so as to reclaim the memory allocated for all the objects so far: " << endl;
        rmm.reset();
        rmm.print_status();
    }
    cout << "Nested region count = " << rmm.get_nested_count() << endl;
    return 0;
}

void work(int size, int* pIntArray) {
    for (int i = 0; i < size; i++) {
        *(pIntArray + i) = rand();
    }
    for (int i = 0; i < size; i++) {
        cout << *(pIntArray + i) << ", ";
    }
    cout << endl;
}
