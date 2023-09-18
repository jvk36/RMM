#include <iostream>
#include <cstdlib>

#include "RMM.h"
using namespace std;

void populate(int size, int* pIntArray);
void copy_computation(int size, int* pIntArray, RMM *rmm);


int main() {
    RMM rmm; // default size of region is 10MB
    cout << "Top Level Region based Memory object initialised" << endl;
    rmm.print_status();

    RMM* rmm_child = rmm.create_nested_region(1024 * 1024); // nested region size = 1MB
    cout << "Nested region sized 1 MB initialized" << endl;
    cout << "Top Level Region Status: " << endl;
    rmm.print_status();
    cout << "Nested Region Status: " << endl;
    rmm_child->print_status();

    // create 5 integer arrays of size 1 thru 5 in the RMM object, do computations, and copy to nested region
    for (int i = 0; i <= 4; i++) {
        int* pIntArray = (int*)rmm.allocate((i + 1) * sizeof(int));
        cout << "Random integer array of size " << i+1 << " constructed in the Top Level RMM object: "<< endl;
        populate(i + 1, pIntArray);
        cout << "Copied a computation on the integers to the Nested RMM object: "<< endl;
        // do some computation and copy the results to the nested region.
        copy_computation(i + 1, pIntArray, rmm_child);

        // Reset the nested region.
        cout << "Reset the nested region so as to reclaim the memory allocated for the computation: " << endl;
        rmm_child->reset();
        rmm_child->print_status();
    }


    cout << "Top Level Region Status: " << endl;
    rmm.print_status();
    cout << "Nested region count = " << rmm.get_nested_count() << endl;
    delete rmm_child;

    // Reset the top-level region.
    cout << "Reset the top-level region: " << endl;
    rmm.reset();
    rmm.print_status();


    return 0;
}

void copy_computation(int size, int* pIntArray, RMM *rmm) {
    int* pNested;
    pNested = (int*)rmm->allocate(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        *(pNested + i) = *(pIntArray + i) / 2;
    }

    for (int i = 0; i < size; i++) {
        cout << *(pNested + i) << ", ";
    }
    cout << endl;
}

void populate(int size, int* pIntArray) {
    for (int i = 0; i < size; i++) {
        *(pIntArray + i) = rand();
    }

    for (int i = 0; i < size; i++) {
        cout << *(pIntArray + i) << ", ";
    }
    cout << endl;
}
