#include <iostream>
#include <cstdlib>

#include "RMM.h"
using namespace std;

void work(int size, int* pIntArray);

int main() {
    RMM rmm;
    RMM rmm1;
    cout << "Region based Memory pool initialised" << endl;
    rmm.print_status();
    rmm1.print_status();

    for (int j = 0; j <= 2; j++) {
	int *pIntArray;
        cout << "Random integer arrays of size 1 thru 5 constructed in the RMM pool: "<< endl;
        // create 5 integer arrays of size 1 thru 5 in the pool and do some work on them
        for (int i = 0; i <= 4; i++) {
            pIntArray = (int*)rmm.allocate((i + 1) * sizeof(int));
            work(i + 1, pIntArray);
	    int* pIntArray1 = (int*)rmm1.allocate((i + 1) * sizeof(int));
            work(i + 1, pIntArray1);
        }

        rmm.print_status();
	rmm1.print_status();

	//Purposefully dont free rmm1 to be sure it stays persistant despire rmm
	cout << "Adding new memory into pIntArray and check status again" << endl;

	pIntArray[0] = 123;

	rmm.print_status();
	rmm1.print_status();
        
        // Free the region.
        cout << "Reset the region so as to reclaim the memory allocated for all the objects so far: " << endl;
        rmm.reset();
        rmm.print_status();
    }

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
