#include <iostream>
#include <cstdlib>
#include <list>

#include "RMM.h"
using namespace std;

int main() {
    RMM rmm(sizeof(list<int>));
    RMM rmm1(sizeof(list<int>));
    cout << "Region based Memory pool initialised" << endl;
    rmm.print_status();
    rmm1.print_status();
    
    for (int i = 0; i <= 3; i++) {
    // create an instance of list<int> in the same pool and do some work
        cout << "An instance of list<int> constructed in the pool" << endl;
        void* raw = rmm.allocate(sizeof(list<int>));
        list<int>* pFoo = new (raw) list<int>;
        pFoo->push_back(rand());
        pFoo->push_back(rand());


	void* raw1 = rmm1.allocate(sizeof(list<int>));
	if (raw1 == nullptr){
		cout << "nullptr" << endl;
		break;
	}
        list<int>* pFoo1 = new (raw1) list<int>;
        pFoo1->push_back(rand());
        pFoo1->push_back(rand());
	pFoo1->push_back(rand());
	pFoo1->push_back(rand());
	pFoo1->push_back(rand());
        cout << "Items in the integer list: " << endl;

        for (int item: *pFoo) {
            cout << item << ", ";
        }

        cout << endl;
        pFoo->~list<int>();
        rmm.print_status();

	cout << "rmm1 list: " << endl << endl;

	for (int item: *pFoo1) {
            cout << item << ", ";
        }

        cout << endl;
        pFoo1->~list<int>();
        rmm1.print_status();


        // Free the region.
        cout << "Reset the region so as to reclaim the memory allocated for all the objects so far: " << endl;
        rmm.reset();
        rmm.print_status();
	cout << "Reset the region so as to reclaim the memory allocated for all the objects so far: " << endl;
        rmm1.reset();
        rmm1.print_status();
    }

    return 0;
}

