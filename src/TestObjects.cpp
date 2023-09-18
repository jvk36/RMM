#include <iostream>
#include <cstdlib>
#include <list>

#include "RMM.h"
using namespace std;

int main() {
    RMM rmm(sizeof(list<int>));
    cout << "Region based Memory pool initialised" << endl;
    rmm.print_status();
    
    for (int i = 0; i <= 3; i++) {
    // create an instance of list<int> in the same pool and do some work
        cout << "An instance of list<int> constructed in the pool" << endl;
        void* raw = rmm.allocate(sizeof(list<int>));
        list<int>* pFoo = new (raw) list<int>;
        pFoo->push_back(rand());
        pFoo->push_back(rand());

        cout << "Items in the integer list: " << endl;

        for (int item: *pFoo) {
            cout << item << ", ";
        }

        cout << endl;
        pFoo->~list<int>();
        rmm.print_status();

        // Free the region.
        cout << "Reset the region so as to reclaim the memory allocated for all the objects so far: " << endl;
        rmm.reset();
        rmm.print_status();
    }
    cout << "Nested region count = " << rmm.get_nested_count() << endl;
    return 0;
}

